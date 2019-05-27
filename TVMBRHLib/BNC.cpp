// BNC.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "BNC.h"

//----------------------------------------------CBNCCommands相关---------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
/************************ Defines and typedefs *******************************/
#define BNC_CASHTAKEN_TIME_OUT_IN_MS (30000)
#define BNC_DEFAULT_OPERATION_TIME_OUT_IN_MS (5000)
#define BNC_OPEN_OPERATION_TIME_OUT_IN_MS    (1000)
#define BNC_RESET_OPERATION_TIME_OUT_IN_MS   (60000)
#define BNC_CASHIN_OPERATION_TIME_OUT_IN_MS  (300000)
#define LPSZ_NULL_TO_EMPTY(lpsz) { if(!lpsz) { lpsz = _T(""); } }

static HANDLE listenerEvent = NULL;			// 操作完成事件

HSERVICE CBNCCommands::gCDMService = NULL;
HSERVICE CBNCCommands::gCIMService = NULL;

CBNCCommands::CBNCCommands()
{
	m_bOpenAgain = true;
	m_bXfsStartup = false;
	m_bXfsCleanUp = false;

	m_lpCUInfoWFSResult = NULL;
	m_lpCount = NULL;
	m_BrhVersion = 0;
	m_IsOpen = false;

	m_IsAccepting = false;
	m_psCashInfo = tBncCashInfo();
}

CBNCCommands::~CBNCCommands()
{
	if (m_lpCUInfoWFSResult)
	{
		WFSFreeResult(m_lpCUInfoWFSResult);
	}
	//if (m_lpCashInNoteList)
	//{
	//	WFSFreeResult(m_lpCashInNoteList);
	//}
	if (m_lpCount)
	{
		WFSFreeResult(m_lpCount);
	}
}

long CBNCCommands::Open(long lBrhVersion)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Open: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	long lRet = 0;
	if (!m_bXfsStartup) {
		lRet = xfs_startup();
		if (lRet != 0)
		{
			sLogString.Format(_T("Open: xfs_startup fail!"));
			LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

			return WFS_ERR_NOT_STARTED;
		}
	}

	lRet = xfs_Open(LOGICALNAME_CDM, CBNCCommands::gCDMService, _T(WFS_SERVICE_CLASS_NAME_CDM), 0, lBrhVersion);
	if (WFS_SUCCESS != lRet) {
		if (lRet == WFS_ERR_INTERNAL_ERROR && m_bOpenAgain)
		{
			CBNCCommands::gCDMService = NULL;
			sLogString.Format(_T("xfs_Open CDM ReturnCode = 0x%02x"), lRet);
			LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
			//CString strExeFileName = _T("F_G60DP2.exe");//程序意外退出或崩溃，纸币模块该进程无法断掉
			//ComKillAppEx(strExeFileName);
			m_bOpenAgain = false;
			return Open(lBrhVersion);
		}
		sLogString.Format(_T("xfs_Open CDM ReturnCode = 0x%02x"), lRet);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return WFS_ERR_NOT_STARTED;

	}
	xfs_Rigister(gCDMService);
	lRet = xfs_Open(LOGICALNAME_CIM, CBNCCommands::gCIMService, _T(WFS_SERVICE_CLASS_NAME_CIM), 0, lBrhVersion);
	if (WFS_SUCCESS != lRet) {
		sLogString.Format(_T("xfs_Open CIM ReturnCode = 0x%02x"), lRet);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return WFS_ERR_NOT_STARTED;

	}
	xfs_Rigister(gCIMService);
	sLogString.Format(_T("Open: ReturnCode = 0x%02x"), lRet);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return lRet;
}

long CBNCCommands::Close()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Close: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	long result = WFS_SUCCESS;
	if (CBNCCommands::gCDMService != NULL)
	{
		result = xfs_Close(CBNCCommands::gCDMService);
		CBNCCommands::gCDMService = NULL;
	}
	if (CBNCCommands::gCIMService != NULL)
	{
		result = xfs_Close(CBNCCommands::gCIMService);
		CBNCCommands::gCIMService = NULL;
	}
	sLogString = _T("");
	sLogString.Format(_T("Close: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	if (m_bXfsStartup)
	{
		result = xfs_cleanup();
		sLogString = _T("");
		sLogString.Format(_T("xfs_cleanup: ReturnCode = 0x%02x"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		m_bXfsStartup = false;
	}
	return result;
}

long CBNCCommands::Reset()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Reset: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	if (!CBNCCommands::gCDMService || !CBNCCommands::gCIMService) {
		sLogString = _T("设备未打开。");
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return BNC_ERR_EVENT_FAILURE;// 事件创建错误
	}
	HRESULT		hr;
	LPWFSRESULT lpWFSResult = NULL;
	// CIM
	WFSCIMITEMPOSITION stResetIn;
	stResetIn.usNumber = 7;
	stResetIn.fwOutputPosition = WFS_CIM_POSNULL;
	WFSCIMRETRACT stRetract;
	stRetract.fwOutputPosition = WFS_CIM_POSNULL;
	stRetract.usIndex = 0;
	stRetract.usRetractArea = WFS_CIM_RA_RETRACT;
	stResetIn.lpRetractArea = new WFSCIMRETRACT;
	memcpy(stResetIn.lpRetractArea, &stRetract, sizeof(WFSCIMRETRACT));
	hr = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_RESET, (LPVOID)& stResetIn, BNC_RESET_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
		lpWFSResult = NULL;

	}
	sLogString.Format(_T("CIM Reset: ReturnCode = %d"), hr);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return hr;
}

long CBNCCommands::GetStatus(WFSCIMSTATUS& status)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("GetStatus()"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	LPVOID		lpQueryDetails = NULL;
	LPWFSRESULT lpWFSResult = NULL;
	LPWFSCIMCASHINFO lpCashInfo = NULL;
	//CDM
	HRESULT result = xfs_GetInfo(CBNCCommands::gCIMService, WFS_INF_CIM_STATUS, lpQueryDetails, BNC_RESET_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (WFS_SUCCESS == result) {
		if (WFS_SUCCESS == lpWFSResult->hResult && lpWFSResult->lpBuffer)
		{
			if (true)
			{
				memcpy(&status, (LPWFSCIMSTATUS)lpWFSResult->lpBuffer, sizeof(WFSCIMSTATUS));
			}
		}
	}

	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}
	sLogString.Format(_T("GetStatus: ReturnCode = %d"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::Cancel()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Cancel: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	HRESULT result = xfs_Cancel(CBNCCommands::gCIMService);
	sLogString = _T("");
	sLogString.Format(_T("Cancel: ReturnCode = %d"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	if (result == WFS_ERR_INVALID_REQ_ID)
	{
		result = WFS_SUCCESS;
	}
	return result;
}

long CBNCCommands::Empty()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Empty: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	HRESULT result = NULL;

	LPWFSCIMSTARTEX	lpStartEx = NULL;
	WFMAllocateBuffer(sizeof(WFSCIMSTARTEX),
		WFS_MEM_ZEROINIT, (LPVOID*)& lpStartEx);

	lpStartEx->fwExchangeType = WFS_CIM_CLEARRECYCLER;
	lpStartEx->usTellerID = 0;
	lpStartEx->usCount = 0;
	lpStartEx->lpusCUNumList = NULL;
	lpStartEx->lpOutput = NULL;
	LPWFSRESULT lpWFSResult = NULL;
	// 1.start exchange
	result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_START_EXCHANGE, (LPVOID)lpStartEx, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	LPWFSCIMCASHINFO lpCUInfo;

	//WFSCIMCASHINFO lpCUInfo;
	//QueryCimCashUnit(&lpCUInfo);
	if (result == WFS_SUCCESS) {
		m_lpCUInfoWFSResult = lpWFSResult;
		lpWFSResult = NULL;
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE :%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		if (m_lpCUInfoWFSResult)
		{
			lpCUInfo = (LPWFSCIMCASHINFO)m_lpCUInfoWFSResult->lpBuffer;
			for (int i = 0; i < lpCUInfo->usCount; i++)
			{
				sLogString.Format(_T("::StartExchange:CU_COUNT[%d] = (%d)"), i, lpCUInfo->lppCashIn[i]->ulCount);
				LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
			}
		}

	}
	else {
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE success:%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return result;
	}

	if (lpStartEx != NULL)
	{
		WFMFreeBuffer(lpStartEx);
	}
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}
	for (int n = 0; n < lpCUInfo->usCount; n++)
	{
		LPWFSCIMCASHIN pCashUnit = lpCUInfo->lppCashIn[n];
		if ((strcmp((*pCashUnit->lppPhysical)->lpPhysicalPositionName, "Stacker1") == 0)
			|| (strcmp((*pCashUnit->lppPhysical)->lpPhysicalPositionName, "Stacker2") == 0)
			|| (strcmp((*pCashUnit->lppPhysical)->lpPhysicalPositionName, "Stacker3") == 0)
			|| (strcmp((*pCashUnit->lppPhysical)->lpPhysicalPositionName, "Stacker4") == 0))
		{
			lpCUInfo->lppCashIn[n]->ulCount = 0;
			//lpCUInfo->lppCashIn[n]->ulCashInCount = 0;
			lpCUInfo->lppCashIn[n]->lppPhysical[0]->ulCount = 0;
			//lpCUInfo->lppCashIn[n]->ulCashInCount = 0;
			//(*pCashUnit->lppPhysical)->ulCount = 0;
			//(*pCashUnit->lppPhysical)->ulCashInCount = 0;
		}
	}
	result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_END_EXCHANGE, (LPVOID)lpCUInfo, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);

	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}
	sLogString.Format(_T("Empty: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::QueryCimCashUnit(LPWFSCIMCASHINFO lpcashUnit)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("QueryCimCashUnit: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	LPWFSRESULT lpWFSResult = NULL;
	LPVOID lpCmdData = NULL;
	HRESULT result = xfs_GetInfo(CBNCCommands::gCIMService, WFS_INF_CIM_CASH_UNIT_INFO, lpCmdData, BNC_DEFAULT_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (WFS_SUCCESS == result) {
		memcpy(lpcashUnit, (LPWFSCIMCASHINFO)lpWFSResult->lpBuffer, sizeof(WFSCIMCASHINFO));
	}
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}
	sLogString = _T("");
	sLogString.Format(_T("QueryCimCashUnit: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return result;
}

long CBNCCommands::QueryCdmCashUnit(LPWFSCDMCUINFO lpcashUnit)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("QueryCdmCashUnit: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	LPWFSRESULT lpWFSResult = NULL;
	LPVOID lpCmdData = NULL;
	HRESULT result = xfs_GetInfo(CBNCCommands::gCDMService, WFS_INF_CDM_CASH_UNIT_INFO, lpCmdData, BNC_DEFAULT_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (WFS_SUCCESS == result) {
		memcpy(lpcashUnit, (LPWFSCDMCUINFO)lpWFSResult->lpBuffer, sizeof(WFSCDMCUINFO));
	}
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}
	sLogString = _T("");
	sLogString.Format(_T("QueryCdmCashUnit: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return result;
}

long CBNCCommands::CancelWaitingCashTaken()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("CancelWaitingCashTaken: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	LPWFSRESULT lpWFSResult = NULL;
	LPVOID lpCmdData = NULL;
	WFSCIMRETRACT stRetract;
	stRetract.fwOutputPosition = (WORD)WFS_CIM_POSNULL;
	stRetract.usRetractArea = (WORD)WFS_CIM_RA_RETRACT;//回收物件到回收现金单元
	stRetract.usIndex = (WORD)1;
	lpCmdData = &stRetract;
	HRESULT result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_RETRACT, lpCmdData, BNC_RESET_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (WFS_SUCCESS == result) {
		//还不知道具体返回值，等测试完再决定怎么处理。
	}

	sLogString = _T("");
	sLogString.Format(_T("CancelWaitingCashTaken: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return result;
}

long CBNCCommands::CashInStart()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("CashInStart: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	WFSCIMCASHINSTART stCashInStart;
	stCashInStart.bUseRecycleUnits = TRUE;
	stCashInStart.fwOutputPosition = (WORD)WFS_CIM_POSNULL;
	stCashInStart.fwInputPosition = (WORD)WFS_CIM_POSNULL;
	stCashInStart.usTellerID = 0;
	LPWFSRESULT lpWFSResult = NULL;
	LPVOID lpCmdData = NULL;
	lpCmdData = &stCashInStart;
	HRESULT result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_CASH_IN_START, lpCmdData, BNC_RESET_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (result == WFS_SUCCESS) {
	}
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}

	sLogString = _T("");
	sLogString.Format(_T("CashInStart: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::CashIn(WFSCIMNOTENUMBERLIST& CashInNoteList, int nTimeOut)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("CashIn: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	LPWFSRESULT lpWFSResult = NULL;
	LPVOID lpCmdData = NULL;

	HRESULT result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_CASH_IN, lpCmdData, nTimeOut, &lpWFSResult);
	if (result == WFS_SUCCESS || result == 0xfffffae5) {
		LPWFSCIMNOTENUMBERLIST lpNoteNumberList = NULL;
		if (lpWFSResult)
		{
			lpNoteNumberList = (LPWFSCIMNOTENUMBERLIST)lpWFSResult->lpBuffer;
		}
		if (!lpNoteNumberList)
		{
			return WFS_SUCCESS;
		}
		sLogString.Format(_T("CashIn: usNumOfNoteNumbers = %d"), lpNoteNumberList->usNumOfNoteNumbers);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

		SaveCashInNoteList(CashInNoteList, lpNoteNumberList);
	}
	else {
		if (result == WFS_ERR_CANCELED) {
			sLogString.Format(_T("CashIn:Canceled\n "));
			return result;
		}
	}
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}
	if (result == 0xfffffae5)
	{
		result = WFS_SUCCESS;
		sLogString.Format(_T("CashIn: 到达物理最大张数"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	}

	sLogString.Format(_T("CashIn: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}
long CBNCCommands::CashInRollback()									// 退出本次接受的所有钞票
{
	CString sLogString(_T(""));
	//RetractPart();
	sLogString.Format(_T("CashInRollback: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	LPWFSRESULT lpWFSResult = NULL;
	LPVOID lpCmdData = NULL;

	HRESULT result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_CASH_IN_ROLLBACK, lpCmdData, BNC_RESET_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}

	sLogString = _T("");
	sLogString.Format(_T("CashInRollback: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}
long CBNCCommands::CashInEnd(WFSCIMCASHINFO& lpCashInfo)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("CashInEnd: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	LPWFSRESULT lpWFSResult = NULL;
	LPVOID lpCmdData = NULL;

	HRESULT result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_CASH_IN_END, lpCmdData, BNC_RESET_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (result == WFS_SUCCESS) {
		memcpy(&lpCashInfo, (LPWFSCIMCASHINFO)lpWFSResult->lpBuffer, sizeof(WFSCIMCASHINFO));
	}
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}

	sLogString = _T("");
	sLogString.Format(_T("CashInEnd: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::Eject()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Eject: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	LPWFSRESULT lpWFSResult = NULL;
	LPVOID lpCmdData = NULL;

	LPWORD lpfwPosition = WFS_CDM_POSNULL;
	HRESULT result = xfs_Execute(CBNCCommands::gCDMService, WFS_CMD_CDM_PRESENT, lpCmdData, BNC_RESET_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}


	sLogString = _T("");
	sLogString.Format(_T("Eject: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::Refill(long lCount)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Refill: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	LPWFSCDMSTARTEX	lpCdmStartEx = NULL;
	WFMAllocateBuffer(sizeof(WFSCDMSTARTEX),
		WFS_MEM_ZEROINIT, (LPVOID*)& lpCdmStartEx);
	lpCdmStartEx->fwExchangeType = WFS_CDM_EXTOCASSETTES;
	lpCdmStartEx->usTellerID = 0;
	lpCdmStartEx->usCount = 0;
	lpCdmStartEx->lpusCUNumList = NULL;
	LPWFSRESULT lpCDMWFSResult = NULL;
	LPWFSRESULT lpCDMWFSStartResult = NULL;
	HRESULT result = xfs_Execute(CBNCCommands::gCDMService, WFS_CMD_CDM_START_EXCHANGE, (LPVOID)lpCdmStartEx, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpCDMWFSResult);
	LPWFSCDMCUINFO lpCDMCUInfo = NULL;
	if (result == WFS_SUCCESS)
	{
		lpCDMWFSStartResult = lpCDMWFSResult;
		sLogString.Format(_T("WFS_CMD_CDM_START_EXCHANGE SUCCESS:%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		if (lpCDMWFSResult)
		{
			lpCDMCUInfo = (LPWFSCDMCUINFO)lpCDMWFSStartResult->lpBuffer;
			lpCDMWFSResult = NULL;
		}
	}
	else {
		sLogString.Format(_T("WFS_CMD_CDM_START_EXCHANGE FAIL:%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		if (lpCdmStartEx != NULL)
		{
			WFMFreeBuffer(lpCdmStartEx);
		}
		if (lpCDMWFSResult)
		{
			WFSFreeResult(lpCDMWFSResult);
		}

		return result;
	}
	if (lpCdmStartEx != NULL)
	{
		WFMFreeBuffer(lpCdmStartEx);
	}
	for (int n = 0; n < lpCDMCUInfo->usCount; n++)
	{
		WFSCDMCASHUNIT& stCdmCashUnit = *lpCDMCUInfo->lppList[n];
		if (strcmp((*stCdmCashUnit.lppPhysical)->lpPhysicalPositionName, "Cassette1") == 0)
		{
			lpCDMCUInfo->lppList[n]->ulCount = lCount;
			//(*stCdmCashUnit.lppPhysical)->ulCount = lCount;
		}
	}
	result = xfs_Execute(CBNCCommands::gCDMService, WFS_CMD_CDM_END_EXCHANGE, (LPVOID)lpCDMCUInfo, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpCDMWFSResult);
	if (lpCDMWFSStartResult)
	{
		WFMFreeBuffer(lpCDMWFSStartResult);
		lpCDMWFSStartResult = NULL;
	}
	if (lpCDMWFSResult)
	{
		WFSFreeResult(lpCDMWFSResult);
	}
	sLogString.Format(_T("WFS_CMD_CDM_END_EXCHANGE:%d"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	sLogString.Format(_T("Refill: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::Dispense(long cycBox1, long cycBox2, long cycBox3, long cycBox4, WFSCDMDENOMINATION& lpDenomination)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Dispense: 循环箱一[%d]循环箱二[%d]循环箱三[%d]循环箱四[%d]"), cycBox1, cycBox2, cycBox3, cycBox4);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	WFSCDMCUINFO stCashUnit;
	QueryCdmCashUnit(&stCashUnit);

	WFSCDMDENOMINATE stDenominate;
	WFSCDMDISPENSE stInp = { 0 };
	WFSCDMDENOMINATION stDenomination = { 0 };
	stInp.lpDenomination = &stDenomination;

	stInp.usMixNumber = 0;
	stDenominate.usMixNumber = 0;

	stInp.fwPosition = WFS_CDM_POSNULL;
	stDenomination.ulAmount = 0;//(1*lOneYCount+5*lFiveYCount);
	stDenomination.usCount = stCashUnit.usCount;
	stDenomination.lpulValues = new ULONG[stDenomination.usCount];
	memset(stDenomination.lpulValues, 0, stDenomination.usCount * sizeof(ULONG));
	stDenomination.lpulValues[1] = cycBox1;
	stDenomination.lpulValues[2] = cycBox2;
	stDenomination.lpulValues[3] = cycBox3;
	stDenomination.lpulValues[4] = cycBox4;

	FillMemory(stDenomination.cCurrencyID, sizeof(stDenomination.cCurrencyID), 0x20);
	CString szCryID = _T("CNY");
	for (int i = 0; i < sizeof(stDenomination.cCurrencyID) && i < szCryID.GetLength(); i++)
	{
		stDenomination.cCurrencyID[i] = szCryID[i];
	}
	sLogString.Format(_T("cdm_denominate( lAmount[%d], pPos[%d], strCurrencyID[%s], lMixNumber[%d], usCount[%d])"),
		stDenomination.ulAmount, stInp.fwPosition, stDenomination.cCurrencyID, stInp.usMixNumber, stDenomination.usCount);
	LPWFSRESULT lpWfsResult = NULL;
	stDenominate.lpDenomination = &stDenomination;
	stInp.lpDenomination = &stDenomination;
	//HRESULT result = xfs_Execute(CBRHCommands::gCDMService,WFS_CMD_CDM_DENOMINATE, &stDenominate, BNR_CASHTAKEN_TIME_OUT_IN_MS,&lpWfsResult);
	//sLogString = _T("");
	//sLogString.Format(_T("Denominate: ReturnCode = 0x%02x"),result);
	//theBRH_TRACE->WriteData( _T("<") + sLogString,NULL,0);

	HRESULT result = xfs_Execute(CBNCCommands::gCDMService, WFS_CMD_CDM_DISPENSE, &stInp, BNC_CASHTAKEN_TIME_OUT_IN_MS, &lpWfsResult);
	if (result == WFS_SUCCESS) {
		memcpy(&lpDenomination, (LPWFSCDMDENOMINATION)lpWfsResult->lpBuffer, sizeof(WFSCDMDENOMINATION));
	}
	else
	{
		if (lpWfsResult)
		{
			WFSFreeResult(lpWfsResult);
		}
		return result;
	}
	if (lpWfsResult)
	{
		WFSFreeResult(lpWfsResult);
	}
	result = Present();
	sLogString = _T("");
	sLogString.Format(_T("Dispense: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::Present()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Present: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	LPWFSRESULT lpWfsResult = NULL;

	WORD lpfwPosition = WFS_CDM_POSNULL;
	HRESULT result = xfs_Execute(CBNCCommands::gCDMService, WFS_CMD_CDM_PRESENT, &lpfwPosition, BNC_CASHTAKEN_TIME_OUT_IN_MS, &lpWfsResult);
	if (lpWfsResult)
	{
		WFSFreeResult(lpWfsResult);
	}

	sLogString = _T("");
	sLogString.Format(_T("Present: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::Retract()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("Retract: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	HRESULT result = CancelWaitingCashTaken();
	sLogString = _T("");
	sLogString.Format(_T("Retract: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}
// 配置现金单元信息
long CBNCCommands::ConfigureCashUnit()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("ConfigureCashUnit: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	LPWFSCIMSTARTEX	lpStartEx = NULL;
	WFMAllocateBuffer(sizeof(WFSCIMSTARTEX),
		WFS_MEM_ZEROINIT, (LPVOID*)& lpStartEx);

	lpStartEx->fwExchangeType = WFS_CIM_CLEARRECYCLER;
	lpStartEx->usTellerID = 0;
	LPWFSRESULT lpWFSResult = NULL;
	// 1.start exchange
	HRESULT result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_START_EXCHANGE, (LPVOID)lpStartEx, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (result == WFS_SUCCESS) {
		m_lpCUInfoWFSResult = lpWFSResult;
		lpWFSResult = NULL;
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE fail:%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		if (m_lpCUInfoWFSResult)
		{
			LPWFSCIMCASHINFO lpCUInfo = (LPWFSCIMCASHINFO)m_lpCUInfoWFSResult->lpBuffer;
			for (int i = 0; i < lpCUInfo->usCount; i++)
			{
				sLogString.Format(_T("::EndExchange:CU_COUNT[%d] = (%d)"), i, lpCUInfo->lppCashIn[i]->ulCount);
				LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
			}
		}

	}
	else {
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE success:%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return result;
	}

	if (lpStartEx != NULL)
	{
		WFMFreeBuffer(lpStartEx);
	}
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}
	sLogString.Format(_T("ConfigureCashUnit: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}
// 更新现金单元信息		
long CBNCCommands::UpdateCashUnit()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("UpdateCashUnit: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	LPWFSRESULT lpWFSResult = NULL;
	LPWFSCIMCASHINFO lpCUInfo = NULL;
	if (m_lpCUInfoWFSResult)
	{
		lpCUInfo = (LPWFSCIMCASHINFO)m_lpCUInfoWFSResult->lpBuffer;
		for (int i = 0; i < lpCUInfo->usCount; i++)
		{
			sLogString.Format(_T("::EndExchange:CU_COUNT[%d] = (%d)"), i, lpCUInfo->lppCashIn[i]->ulCount);
			LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		}
	}
	HRESULT result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_END_EXCHANGE, (LPVOID)lpCUInfo, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}
	sLogString.Format(_T("WFS_CMD_CIM_END_EXCHANGE: %d"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	sLogString = _T("");
	sLogString.Format(_T("UpdateCashUnit: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::ReplaceCashUnit()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("ReplaceCashUnit: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	HRESULT result;

	
	LPWFSCIMSTARTEX	lpStartEx = NULL;
	WFMAllocateBuffer(sizeof(WFSCIMSTARTEX),
		WFS_MEM_ZEROINIT, (LPVOID*)& lpStartEx);

	lpStartEx->fwExchangeType = WFS_CIM_EXBYHAND;
	lpStartEx->usTellerID = 0;
	lpStartEx->usCount = 0;
	lpStartEx->lpusCUNumList = NULL;
	lpStartEx->lpOutput = NULL;
	LPWFSRESULT lpWFSResult = NULL;
	// 1.start exchange
	result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_START_EXCHANGE, (LPVOID)lpStartEx, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	LPWFSCIMCASHINFO lpCUInfo;

	//WFSCIMCASHINFO lpCUInfo;
	//QueryCimCashUnit((&lpCUInfo));
	if (result == WFS_SUCCESS) {
		//m_lpCUInfoWFSResult = lpWFSResult;
		//lpWFSResult = NULL;
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE :%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		if (lpWFSResult->lpBuffer)
		{
			lpCUInfo = (LPWFSCIMCASHINFO)lpWFSResult->lpBuffer;
			for (int i = 0; i < lpCUInfo->usCount; i++)
			{
				sLogString.Format(_T("::StartExchange:CU_COUNT[%d] = (%d)name[%s]"), i, lpCUInfo->lppCashIn[i]->ulCount, (char*)lpCUInfo->lppCashIn[i]->lppPhysical[0]->lpPhysicalPositionName);
				LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
			}
		}

	}
	else {
		if (lpWFSResult)
		{
			WFSFreeResult(lpWFSResult);
			lpWFSResult = NULL;
		}

		if (result == WFS_ERR_CIM_EXCHANGEACTIVE)
		{
			WFSCIMCASHINFO lpCUInfo;
			QueryCimCashUnit((&lpCUInfo));

			result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_END_EXCHANGE, (LPVOID)& lpCUInfo, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
		}
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE fail:%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return result;
	}

	if (lpStartEx != NULL)
	{
		WFMFreeBuffer(lpStartEx);
	}

	LPVOID lpCdmCmd = NULL;
	LPWFSRESULT lpWFSEndResult = NULL;

	result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_END_EXCHANGE, (LPVOID)lpCUInfo, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSEndResult);
	sLogString.Format(_T("WFS_CMD_CIM_end_EXCHANGE :%d"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
		lpWFSResult = NULL;

	}

	if (lpCUInfo)
	{
		WFMFreeBuffer(lpCUInfo);
	}
	if (lpWFSEndResult)
	{
		WFSFreeResult(lpWFSEndResult);
	}
	sLogString.Format(_T("WFS_CMD_CDM_end_EXCHANGE:%d"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	USHORT usNoteId[] = { 0x0301,0x0303,0x0304,0x0306,0x0307,
		0x2301,0x2303,0x2304,0x2305,0x2306,0x2307,
		0x4303,0x4304,0x4305,0x4306,0x4307,
		0x6307,0
	};

	if (result == WFS_SUCCESS)
	{
		UpdateDenominations(usNoteId);
	}
	sLogString.Format(_T("ReplaceCashUnit: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::CheckCashUnit(LPWFSCIMCASHINFO lpcashUnit)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("CheckCashUnit: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	HRESULT result;


	LPWFSCIMSTARTEX	lpStartEx = NULL;
	WFMAllocateBuffer(sizeof(WFSCIMSTARTEX),
		WFS_MEM_ZEROINIT, (LPVOID*)& lpStartEx);

	lpStartEx->fwExchangeType = WFS_CIM_EXBYHAND;
	lpStartEx->usTellerID = 0;
	lpStartEx->usCount = 0;
	lpStartEx->lpusCUNumList = NULL;
	lpStartEx->lpOutput = NULL;
	LPWFSRESULT lpWFSResult = NULL;
	// 1.start exchange
	result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_START_EXCHANGE, (LPVOID)lpStartEx, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	LPWFSCIMCASHINFO lpCUInfo;

	//WFSCIMCASHINFO lpCUInfo;
	//QueryCimCashUnit((&lpCUInfo));
	if (result == WFS_SUCCESS) {
		//m_lpCUInfoWFSResult = lpWFSResult;
		//lpWFSResult = NULL;
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE :%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		if (lpWFSResult->lpBuffer)
		{
			memcpy(lpcashUnit, (LPWFSCIMCASHINFO)lpWFSResult->lpBuffer, sizeof(WFSCIMCASHINFO));

			//lpcashUnit = (LPWFSCIMCASHINFO)lpWFSResult->lpBuffer;
			lpCUInfo = (LPWFSCIMCASHINFO)lpWFSResult->lpBuffer;
			for (int i = 0; i < lpCUInfo->usCount; i++)
			{
				sLogString.Format(_T("::StartExchange:CU_COUNT[%d] = (%d)name[%s]"), i, lpCUInfo->lppCashIn[i]->ulCount, (char*)lpCUInfo->lppCashIn[i]->lppPhysical[0]->lpPhysicalPositionName);
				LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
			}
		}

	}
	else {
		if (lpWFSResult)
		{
			WFSFreeResult(lpWFSResult);
			lpWFSResult = NULL;
		}

		if (result == WFS_ERR_CIM_EXCHANGEACTIVE)
		{
			WFSCIMCASHINFO lpCUInfo;
			QueryCimCashUnit((&lpCUInfo));

			result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_END_EXCHANGE, (LPVOID)& lpCUInfo, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
		}
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE fail:%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return result;
	}

	if (lpStartEx != NULL)
	{
		WFMFreeBuffer(lpStartEx);
	}

	LPVOID lpCdmCmd = NULL;
	LPWFSRESULT lpWFSEndResult = NULL;

	result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_END_EXCHANGE, (LPVOID)lpCUInfo, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSEndResult);
	sLogString.Format(_T("WFS_CMD_CIM_end_EXCHANGE :%d"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
		lpWFSResult = NULL;

	}

	if (lpCUInfo)
	{
		WFMFreeBuffer(lpCUInfo);
	}
	if (lpWFSEndResult)
	{
		WFSFreeResult(lpWFSEndResult);
	}
	sLogString.Format(_T("ReplaceCashUnit: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}
// 更新面值	
long CBNCCommands::UpdateDenominations(USHORT* usNotesId)
{
	CString sLogString(_T(""));
	sLogString.Format(_T("UpdateDenominations: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	//USHORT usNoteId[] = {0x0301,0x0303,0x0304,0x0306,0x0307,
	//	0x2301,0x2303,0x2304,0x2305,0x2306,0x2307,
	//	0x4303,0x4304,0x4305,0x4306,0x4307,
	//	0x6307,0
	//};
	USHORT usNoteI[18] = { 0 };
	for (int i = 0; i < 18; i++)
	{
		if (usNotesId[i] != 0x0000) {
			usNoteI[i] = usNotesId[i];
		}
		else {
			usNoteI[i] = 0;
			break;
		}
	}
	LPWFSRESULT lpWFSResult = NULL;

	HRESULT result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_CONFIGURE_NOTETYPES, (LPUSHORT)& usNoteI, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}

	sLogString = _T("");
	sLogString.Format(_T("UpdateDenominations: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

long CBNCCommands::ClearCollectionUnitCount()
{
	CString sLogString(_T(""));
	sLogString.Format(_T("ClearCollectionUnitCount: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	HRESULT result = NULL;

	LPWFSCIMSTARTEX	lpStartEx = NULL;
	WFMAllocateBuffer(sizeof(WFSCIMSTARTEX),
		WFS_MEM_ZEROINIT, (LPVOID*)& lpStartEx);

	lpStartEx->fwExchangeType = WFS_CIM_EXBYHAND;
	lpStartEx->usTellerID = 0;
	lpStartEx->usCount = 0;
	lpStartEx->lpusCUNumList = NULL;
	lpStartEx->lpOutput = NULL;
	LPWFSRESULT lpWFSResult = NULL;
	// 1.start exchange
	result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_START_EXCHANGE, (LPVOID)lpStartEx, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSResult);
	LPWFSCIMCASHINFO lpCUInfo;

	//WFSCIMCASHINFO lpCUInfo;
	//QueryCimCashUnit(&lpCUInfo);
	if (result == WFS_SUCCESS) {
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE :%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		if (lpWFSResult->lpBuffer)
		{
			lpCUInfo = (LPWFSCIMCASHINFO)lpWFSResult->lpBuffer;
			for (int i = 0; i < lpCUInfo->usCount; i++)
			{
				sLogString.Format(_T("::StartExchange:CU_COUNT[%d] = (%d)"), i, lpCUInfo->lppCashIn[i]->ulCount);
				LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
			}
		}

	}
	else {
		sLogString.Format(_T("WFS_CMD_CIM_START_EXCHANGE FAIL:%d"), result);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return result;
	}

	if (lpStartEx != NULL)
	{
		WFMFreeBuffer(lpStartEx);
	}
	for (int n = 0; n < lpCUInfo->usCount; n++)
	{
		LPWFSCIMCASHIN pCashUnit = lpCUInfo->lppCashIn[n];
		if ((strcmp((*pCashUnit->lppPhysical)->lpPhysicalPositionName, "CashBox") == 0))
		{
			lpCUInfo->lppCashIn[n]->ulCount = 0;
			lpCUInfo->lppCashIn[n]->lppPhysical[0]->ulCount = 0;
		}
	}
	LPWFSRESULT lpWFSEndResult = NULL;

	result = xfs_Execute(CBNCCommands::gCIMService, WFS_CMD_CIM_END_EXCHANGE, (LPVOID)lpCUInfo, BNC_CASHIN_OPERATION_TIME_OUT_IN_MS, &lpWFSEndResult);
	if (lpWFSResult)
	{
		WFSFreeResult(lpWFSResult);
	}
	if (lpWFSEndResult)
	{
		WFSFreeResult(lpWFSEndResult);
	}
	sLogString.Format(_T("Empty: ReturnCode = 0x%02x"), result);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	return result;
}

void CBNCCommands::GetEmptyExcResult(WFSRESULT& stWfsResult)
{
	memcpy(&stWfsResult, m_lpCUInfoWFSResult, sizeof(WFSRESULT));
}

long CBNCCommands::xfs_cleanup()
{
	CString szLogString = _T("");
	szLogString.Format(_T("xfs_cleanup"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	long lRet = 0;
	if (m_bXfsCleanUp)
	{
		HRESULT hr = WFSCleanUp();
		lRet = hr;
		if (hr == WFS_SUCCESS)
		{
			m_bXfsCleanUp = false;
			szLogString.Format(_T("[%d] WFSCleanUp"), (hr));
			LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);

		}
		else
		{
			szLogString.Format(_T("[%d] WFSCleanUp() fail!"), hr);
			LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
		}
	}
	szLogString.Format(_T("xfs_cleanup"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);

	return lRet;
}

long CBNCCommands::xfs_startup()
{
	CString szLogString = _T("");
	szLogString.Format(_T("xfs_startup"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	long lRet = 0;
	if (!m_bXfsStartup)
	{
		// call XFS command
		WORD wVerMin = MAKEWORD(2, 0);
		WORD wVerMax = MAKEWORD(3, 10);
		DWORD dwVersionsRequired = MAKELONG(wVerMax, wVerMin);

		WFSVERSION wfsVersion = { 0 };
		HRESULT hr = WFSStartUp(dwVersionsRequired, &wfsVersion);

		USES_CONVERSION;
		szLogString.Format(_T("[%d] WFSStartUp. \nXFS Version %d.%02d (min %d.%02d, max %d.%02d) -- %s (Status: %s)"),
			hr,
			LOBYTE(wfsVersion.wVersion), HIBYTE(wfsVersion.wVersion),
			LOBYTE(wfsVersion.wLowVersion), HIBYTE(wfsVersion.wLowVersion),
			LOBYTE(wfsVersion.wHighVersion), HIBYTE(wfsVersion.wHighVersion),
			A2T(wfsVersion.szDescription), A2T(wfsVersion.szSystemStatus));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
		lRet = hr;
		if (hr == WFS_SUCCESS || hr == WFS_ERR_ALREADY_STARTED)
		{
			m_bXfsStartup = true;
			m_bXfsCleanUp = (hr == WFS_SUCCESS);
			hr = WFS_SUCCESS;
		}
		else
		{
		}
		szLogString.Format(_T("xfs_startup return = %d"), hr);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
		lRet = hr;
		m_bOpenAgain = true;
	}
	szLogString.Format(_T("xfs_startup"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	return lRet;
}

HRESULT CBNCCommands::xfs_Open(LPCTSTR lpszLogicalName, HSERVICE & hService, LPCTSTR lpszServiceClass, DWORD dwTimeOut, long lBrhVer)
{
	CString szLogString = _T("");
	szLogString.Format(_T("xfs_Open"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);

	if (hService)
	{
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
		return 0;
	}
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);

	HAPP hApp = WFS_DEFAULT_HAPP;

	CString szAppID = lpszServiceClass;
	CString szLogicalName;

	szLogicalName = lpszLogicalName;

	USES_CONVERSION;

	DWORD dwTraceLevel = 0; // WFS_TRACE_ALL_API;

	WORD wMinor = MAKEWORD(2, 0);
	WORD wMajor = MAKEWORD(3, 10);
	DWORD dwSrvcVersionsRequired = MAKELONG(wMajor, wMinor);

	WFSVERSION stSrvcVersion = { 0 };
	WFSVERSION stSPIVersion = { 0 };

	HRESULT hr = WFSOpen(
		T2A(szLogicalName.GetBuffer(0)),
		hApp,
		T2A(szAppID.GetBuffer(0)),
		dwTraceLevel,
		dwTimeOut,
		dwSrvcVersionsRequired,
		&stSrvcVersion,
		&stSPIVersion,
		&hService);

	CString szInfo, szInfo1;

	szInfo.Format(_T("[%d] WFSOpen(%s) { hService[0x%08X] }."), (hr), szLogicalName, hService);
	szInfo1.Format(_T("SRV Version %d.%02d (min %d.%02d, max %d.%02d) -- %s (Status: %s)"),
		LOBYTE(stSrvcVersion.wVersion), HIBYTE(stSrvcVersion.wVersion),
		LOBYTE(stSrvcVersion.wLowVersion), HIBYTE(stSrvcVersion.wLowVersion),
		LOBYTE(stSrvcVersion.wHighVersion), HIBYTE(stSrvcVersion.wHighVersion),
		A2T(stSrvcVersion.szDescription), A2T(stSrvcVersion.szSystemStatus));
	szInfo += szInfo1;

	szInfo1.Format(_T("SPI Version %d.%02d (min %d.%02d, max %d.%02d) -- %s (Status: %s)"),
		LOBYTE(stSPIVersion.wVersion), HIBYTE(stSPIVersion.wVersion),
		LOBYTE(stSPIVersion.wLowVersion), HIBYTE(stSPIVersion.wLowVersion),
		LOBYTE(stSPIVersion.wHighVersion), HIBYTE(stSPIVersion.wHighVersion),
		A2T(stSPIVersion.szDescription), A2T(stSPIVersion.szSystemStatus));

	szInfo += szInfo1;
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	CString sVerSion;
	sVerSion.Format(_T("%d%02d)"), LOBYTE(stSPIVersion.wVersion), HIBYTE(stSPIVersion.wVersion));
	//lBrhVer = _ttol(sVerSion);
	m_BrhVersion = _ttol(sVerSion);
	if (hr != WFS_SUCCESS)
	{
		szLogString.Format(_T("[%d] WFSOpen(%s) fail!!"), hr, szLogicalName);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
		return hr;
	}
	szLogString.Format(_T("WFSOpen"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	return hr;
}

HRESULT CBNCCommands::xfs_Close(HSERVICE & hService)
{
	CString szLogString = _T("");
	szLogString.Format(_T("WFSClose()"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);

	if (!hService)
	{
		szLogString.Format(_T("WFSClose()"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
		return 0;
	}
	HRESULT hr = WFSClose(hService);
	if (hr == WFS_SUCCESS)
	{
		hService = NULL;
	}
	szLogString.Format(_T("WFSClose() return = [%d]"), hr);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	return hr;
}

HRESULT CBNCCommands::xfs_Rigister(HSERVICE hService)
{
	DWORD dwEventClass = SYSTEM_EVENTS | SERVICE_EVENTS | USER_EVENTS | EXECUTE_EVENTS;
	CString szLogString = _T("");
	szLogString.Format(_T("xfs_Rigister()"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);

	HRESULT hr = WFSRegister(hService, dwEventClass, GetDesktopWindow());
	if (hr != WFS_SUCCESS)
	{
		szLogString.Format(_T("xfs_Rigister() fail!!"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	}
	else
	{
		szLogString.Format(_T("xfs_Rigister() success!!"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	}
	return NULL;
}

HRESULT CBNCCommands::xfs_Execute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
	CString szLogString = _T("");
	szLogString.Format(_T("xfs_Execute()"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);

	HRESULT hr = WFSExecute(hService, dwCommand, lpCmdData, dwTimeOut, lppResult);
	if (hr != WFS_SUCCESS)
	{
		szLogString.Format(_T("[%d] WFSExecute(%d) fail!"), hr, (dwCommand));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	}
	else
	{
		szLogString.Format(_T("[%d] WFSExecute(%d) success!"), hr, (dwCommand));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	}
	return hr;

}

HRESULT CBNCCommands::xfs_GetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
	CString szLogString = _T("");
	szLogString.Format(_T("xfs_GetInfo()"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);

	HRESULT hr = WFSGetInfo(hService, dwCategory, lpQueryDetails, dwTimeOut, lppResult);
	if (hr != WFS_SUCCESS)
	{
		szLogString.Format(_T("[%d] WFSGetInfo(%d) fail!"), hr, (dwCategory));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	}
	else
	{
		szLogString.Format(_T("[%d] WFSGetInfo(%d) success!"), hr, (dwCategory));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	}
	return hr;

}

HRESULT CBNCCommands::xfs_Cancel(HSERVICE hService)
{
	CString szLogString = _T("");
	szLogString.Format(_T("xfs_Cancel ()"));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);

	if (!hService) return 0;

	HRESULT hr = WFSCancelAsyncRequest(hService, NULL);
	if (hr != WFS_SUCCESS)
	{
		szLogString.Format(_T("[%d] WFSCancelAsyncRequest() fail!"), hr);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	}
	else {
		szLogString.Format(_T("[%d] WFSCancelAsyncRequest() success!"), hr);
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, szLogString);
	}
	return hr;
}

void CBNCCommands::SaveCashInNoteList(WFSCIMNOTENUMBERLIST & CashInNoteList, LPWFSCIMNOTENUMBERLIST lpNoteList)
{
	if (!lpNoteList)
	{
		return;
	}
	memcpy(&CashInNoteList, lpNoteList, sizeof(WFSCIMNOTENUMBERLIST));
}

void CBNCCommands::BNC_SetAcceptFlag(bool flag)
{
	m_IsAccepting = flag;
}

bool CBNCCommands::BNC_GetAcceptFlag()
{
	return m_IsAccepting;
}

int CBNCCommands::GetCashInfoResponse(tBncCashInfo * p_psCashInfo)
{
	if (p_psCashInfo == NULL || p_psCashInfo->psBncCashInfo == NULL)
		return BNC_RETURN_FAULT;

	p_psCashInfo->iNumOfItems = m_lpCashInNoteList.usNumOfNoteNumbers;

	for (int n = 0; n < m_lpCashInNoteList.usNumOfNoteNumbers; n++)
	{
		long lAmount = NoteID2Amount(m_lpCashInNoteList.lppNoteNumber[n]->usNoteID);
		switch (lAmount)
		{
		case BNC_FACE_CNY1:
			p_psCashInfo->psBncCashInfo[0].iCount += m_lpCashInNoteList.lppNoteNumber[n]->ulCount;
			p_psCashInfo->psBncCashInfo[0].iValue += m_lpCashInNoteList.lppNoteNumber[n]->ulCount * BNC_FACE_CNY1;
			break;
		case BNC_FACE_CNY5:
			p_psCashInfo->psBncCashInfo[1].iCount += m_lpCashInNoteList.lppNoteNumber[n]->ulCount;
			p_psCashInfo->psBncCashInfo[1].iValue += m_lpCashInNoteList.lppNoteNumber[n]->ulCount * BNC_FACE_CNY5;
			break;
		case BNC_FACE_CNY10:
			p_psCashInfo->psBncCashInfo[2].iCount += m_lpCashInNoteList.lppNoteNumber[n]->ulCount;
			p_psCashInfo->psBncCashInfo[2].iValue += m_lpCashInNoteList.lppNoteNumber[n]->ulCount * BNC_FACE_CNY10;
			break;
		case BNC_FACE_CNY20:
			p_psCashInfo->psBncCashInfo[3].iCount += m_lpCashInNoteList.lppNoteNumber[n]->ulCount;
			p_psCashInfo->psBncCashInfo[3].iValue += m_lpCashInNoteList.lppNoteNumber[n]->ulCount * BNC_FACE_CNY20;
			break;
		case BNC_FACE_CNY50:
			p_psCashInfo->psBncCashInfo[4].iCount += m_lpCashInNoteList.lppNoteNumber[n]->ulCount;
			p_psCashInfo->psBncCashInfo[4].iValue += m_lpCashInNoteList.lppNoteNumber[n]->ulCount * BNC_FACE_CNY50;
			break;
		case BNC_FACE_CNY100:
			p_psCashInfo->psBncCashInfo[5].iCount += m_lpCashInNoteList.lppNoteNumber[n]->ulCount;
			p_psCashInfo->psBncCashInfo[5].iValue += m_lpCashInNoteList.lppNoteNumber[n]->ulCount * BNC_FACE_CNY100;
			break;
		default:
			break;
		}
	}
	return BNC_RETURN_NO_ERROR;
}

int CBNCCommands::GetEnCashInfoResponse(tBncEnCashInfo * cashInfo)
{
	if (cashInfo == NULL) {
	}
	else {
		*cashInfo = m_cashIntoInfo;
	}
	return BNC_RETURN_NO_ERROR;
}
bool CBNCCommands::GetIsExecute(){
	WFSCIMSTATUS status;
	GetStatus(status);
	WFSCIMINPOS  apos;  
	WFSCIMINPOS  bpos;
	memcpy(&apos,*(status.lppPositions), sizeof(WFSCIMINPOS));
	memcpy(&bpos,*(++status.lppPositions), sizeof(WFSCIMINPOS));
	return apos.fwPositionStatus||bpos.fwPositionStatus||apos.fwTransportStatus||bpos.fwTransportStatus;  //0为关闭，1为开启
}


long NoteID2Amount(USHORT usNoteID)
{
	long lAmount = 0;
	switch (usNoteID)
	{
	case 0x0301:
	case 0x2301:
		lAmount = 100;
		break;
	case 0x0303:
	case 0x2303:
	case 0x4303:
		lAmount = 500;
		break;
	case 0x0304:
	case 0x2304:
	case 0x4304:
		lAmount = 1000;
		break;
	case 0x2305:
	case 0x4305:
		lAmount = 2000;
		break;
	case 0x0306:
	case 0x2306:
	case 0x4306:
		lAmount = 5000;
		break;
	case 0x0307:
	case 0x2307:
	case 0x4307:
	case 0x6307:
		lAmount = 10000;
		break;
	}
	return lAmount;
}

//创建CBNCCommands类对象
CBNCCommands bncCommands;
//---------------------------------------------------以下是标准化接口-------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
/*****************************************************************************/
/*                                                                           */
// 以下接口在LIB实现，在DLL层使用，如果厂家提供dll则可仿造TIM模块实现，如果厂家
// 提供串口协议，则需封装完协议后再实现以下接口
/* # wang feng                                                               */
/*****************************************************************************/
//　通信串口打开
// 功能说明：调用此接口可打开低层串口通信。
// 参数说明见表23。
// 1	unsigned int	uiCommPort	In	串口通信号
// 2	unsigned int	uiBaudRate	In	波特率
// 返回值说明
// 1	Int	0	成功
// 2	Int	1	串口打开出错
int  BNC_open(unsigned int uiCommPort, unsigned int uiBaudRate,CString path, CString fileName)
{
	//如果传入的值为空值
	if (path == _T("") || fileName == _T(""))
		return BNC_RETURN_NO_ERROR;
	//初始化日志
	LogApi.Initialize(path, fileName);

	if (!bncCommands.m_IsOpen)
	{
		long errCode = 0;
		long lBrhVersion = 0;
		errCode = bncCommands.Open(lBrhVersion);
		if (errCode != WFS_SUCCESS)
			return BNC_RETURN_FAULT;
		bncCommands.m_IsOpen = TRUE;
	}
	return BNC_RETURN_NO_ERROR;
}

//　初始化
// 功能说明： 初始化模块，检测模块各硬件、将模块恢复到初始状态等。
// 参数说明见下表。
// 1	tBncInitNumInfo *	pNumInfo	Out	退出和回收钱币信息
// 2	tBNDDevReturn	pDevStatus	Out	            设备返回状态
// 返回值说明见下表。
// 1	Int	0	成功
// 2	Int	1	传入参数为空
int BNC_Init(tBncInitNumInfo *pNumInfo, tBncDevReturn * pDevStatus)
{
	if (pNumInfo == NULL || pDevStatus == NULL)
		return BNC_RETURN_FAULT;

	pDevStatus->iType = BNC_ITYPE_FAULT;
	pDevStatus->iErrorCode = BNC_ITYPE_FAULT;

	return BNC_RETURN_FAULT;
}

//　通信串口关闭
//  功能说明：调用此接口可关闭低层串口通信。
// 	返回值说明
// 	1	Int	0	成功
// 	2	Int	1	关闭错误
int BNC_close()
{
	long errCode = 0;
	errCode = bncCommands.Close();
	if (errCode != WFS_SUCCESS)
		return BNC_RETURN_FAULT;
	bncCommands.m_IsOpen = FALSE;
	LogApi.CloseLog();
	return BNC_RETURN_NO_ERROR;
}

//　获取模块固件版本
int BNC_GetVersion(char* pVersion, tBncDevReturn * p_psStatus)
{
	if (pVersion == NULL || p_psStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = 0;
	ltoa(bncCommands.m_BrhVersion, pVersion, 10);
	errCode = BNC_GetStatus(p_psStatus);
	return errCode;
}
// 功能说明：用于获取控制模块内的firmware版本号（如果模块有），目前只针对GRG的纸币模块有效。
// 参数说明
// 1	char*	pVersion	Out	固件版本（如果有）
// 2	tBncDevReturn &	p_psStatus	Out	返回状态信息
// 返回值说明见表27。
// 1	Int	0	成功
// 2	Int	1	关闭错误


//　设置识别可用钞票
//  功能说明：此命令用于设置可接收的钞票，对于禁止接收的真钞会退出。
// 	参数说明见表3。
// 	1	tBncSetInhibitList *	p_psBuyTicketSetInhibitList	In	设置售票时钞票可用信息结构体数组
// 	2	tBncSetInhibitList *	p_psRechargeSetInhibitList	In	设置充值时钞票可用信息结构体数组
// 	3	tBncDevReturn *	p_psStatus	Out	保存BNA返回的逻辑错误码
// 	返回值说明
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
int  BNC_SetPrevalue(tBncSetInhibitList *p_psBuyTicketSetInhibitList, tBncSetInhibitList *p_psRechargeSetInhibitList, tBncDevReturn * p_psStatus)
{
	if ((p_psBuyTicketSetInhibitList == NULL && p_psRechargeSetInhibitList == NULL) || p_psStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = 0;
	tBncSetInhibitList* m_InhibitList;
	if (p_psBuyTicketSetInhibitList->iNumOfItems > 0 && p_psBuyTicketSetInhibitList->psBncCashInfo != NULL)
		m_InhibitList = p_psBuyTicketSetInhibitList;
	else if (p_psRechargeSetInhibitList->iNumOfItems > 0 && p_psRechargeSetInhibitList->psBncCashInfo != NULL)
		m_InhibitList = p_psRechargeSetInhibitList;
	USHORT usNotesId[18] = { 0 };
	int index = 0;
	if (m_InhibitList->psBncCashInfo != NULL)
	{
		for (int i = 0; i < m_InhibitList->iNumOfItems; i++)
		{
			if (m_InhibitList->psBncCashInfo[i].bAccepted)
			{
				if (m_InhibitList->psBncCashInfo[i].iValue == BNC_FACE_CNY1)
				{
					usNotesId[i] = 0x0301;
					index++;
					usNotesId[i] = 0x2301;
					index++;
				}
				else if (m_InhibitList->psBncCashInfo[i].iValue == BNC_FACE_CNY5)
				{
					usNotesId[i] = 0x0303;
					index++;
					usNotesId[i] = 0x2303;
					index++;
					usNotesId[i] = 0x4303;
					index++;
				}
				else if (m_InhibitList->psBncCashInfo[i].iValue == BNC_FACE_CNY10)
				{
					usNotesId[i] = 0x0304;
					index++;
					usNotesId[i] = 0x2304;
					index++;
					usNotesId[i] = 0x4304;
					index++;
				}
				else if (m_InhibitList->psBncCashInfo[i].iValue == BNC_FACE_CNY20)
				{
					usNotesId[i] = 0x2305;
					index++;
					usNotesId[i] = 0x4305;
					index++;
				}
				else if (m_InhibitList->psBncCashInfo[i].iValue == BNC_FACE_CNY50)
				{
					usNotesId[i] = 0x0306;
					index++;
					usNotesId[i] = 0x2306;
					index++;
					usNotesId[i] = 0x4306;
					index++;
				}
				else if (m_InhibitList->psBncCashInfo[i].iValue == BNC_FACE_CNY100)
				{
					usNotesId[i] = 0x0307;
					index++;
					usNotesId[i] = 0x2307;
					index++;
					usNotesId[i] = 0x4307;
					index++;
					usNotesId[i] = 0x6307;
					index++;
				}
			}
		}
	}
	errCode = bncCommands.UpdateDenominations(usNotesId);
	if (errCode != WFS_SUCCESS)
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}

	p_psStatus->iType = BNC_ITYPE_NO_ERROR;
	p_psStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
}

//　复位
// 功能说明：此命令用于清理通道中的钞票，机芯恢复正常工作。
// 参数说明
// 1	Int	iMode	In	如果通道中有钞票，可以选择的操作由 p_iResetMode 设定可以设置为：
 //0：将传输系统和暂存区的钞票压入钱箱,如果失败则报暂停服务错误；
 //1：将传输系统和暂存区的钞票退出,如果失败则报暂停服务错误；
// 默认为 0 方式
// 2	Int	iRetryTimes	In	复位重试次数
// 3	tBncInitNumInfo *	pNumInfo	Out	退出和回收钱币信息
// 4	tBncDevReturn *	p_psStatus	Out	保存BNC返回的逻辑错误码
// 返回值说明
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
int BNC_Reset(int iMode, int iRetryTimes, tBncInitNumInfo *pNumInfo, tBncDevReturn * p_psStatus)
{
	if (pNumInfo == NULL || p_psStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = 0;
	errCode = bncCommands.ReplaceCashUnit();
	if (errCode != WFS_SUCCESS)
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
	//复位重试次数
	for (int i = 0; i < iRetryTimes; i++)
	{
		errCode = bncCommands.Reset();
		if (errCode == WFS_SUCCESS)
			break;
	}

	if (errCode != WFS_SUCCESS)
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}

	p_psStatus->iType = BNC_ITYPE_NO_ERROR;
	p_psStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
}


//　获取模块状态
//  功能说明：调用此接口可获取模块当前状态，详细信息查看返回结构体。
// 	参数说明
// 	tBncDevReturn *	p_psStatus	Out	保存BNC返回的逻辑错误码
// 	返回值说明
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
int BNC_GetStatus(tBncDevReturn * p_psStatus)
{
	if (p_psStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = 0;
	WFSCIMSTATUS sta;
	errCode = bncCommands.GetStatus(sta);
	if (errCode == WFS_SUCCESS)
	{
		//memcpy(p_psStatus->acDevReturn, &sta, sizeof(sta));
		//使用memcpy，如果要取出数据内容，有两种方法：1.再次使用memcpy进行解析 2.强制类型转换.
		//memcpy(&sta, p_psStatus->acDevReturn, sizeof(sta));
		p_psStatus->iType = BNC_ITYPE_NO_ERROR;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_NO_ERROR;
	}
	else
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
}

// 获取模块详细状态
int BNC_GetSysDevStatus(tBncSysDevStatus* p_psSysStatus)
{
	if (p_psSysStatus == NULL)
		return BNC_RETURN_FAULT;
	long errCode = 0;
	WFSCIMSTATUS sta;
	errCode = bncCommands.GetStatus(sta);
	if (errCode == WFS_SUCCESS)
	{
		if (sta.fwDevice == WFS_CIM_DEVONLINE && sta.fwAcceptor == WFS_CIM_ACCOK)
		{
			p_psSysStatus->bIsChangeBoxInstalled = TRUE;
			p_psSysStatus->bIsCollectBoxInstalled = TRUE;
		}
		else
		{
			p_psSysStatus->bIsChangeBoxInstalled = FALSE;
			p_psSysStatus->bIsCollectBoxInstalled = FALSE;
		}
		return BNC_RETURN_NO_ERROR;
	}
	return BNC_RETURN_FAULT;
}
// 结构体返回的状态信息;因此在硬件返回信息字符串中内容格式如下:
// [CurrentCode],[CurrentOCCode],[NrOfDocumentInintermediateStorage],[ResolutionMode],[SequenceNr] ,[ ValidationMode] ,[WorkMode] 

//　读取审计信息
// 	功能说明：读取设备的审计信息。
// 	参数说明见下表。
// 	1	tBncAuditCashNum *	pBncAuditCashNum	Out	容器审计信息
// 	2	tBncDevReturn *	pDevStatus	Out	返回状态信息
// 	返回值说明见下表。
// 	1	int	0：执行成功；1，执行失败。
int BNC_GetAuditData(tBncAuditCashNum *pBncAuditCashNum, tBncDevReturn *pDevStatus)
{
	//该函数不用
	if (pBncAuditCashNum == NULL || pDevStatus == NULL)
		return BNC_RETURN_FAULT;

	pDevStatus->iType = BNC_ITYPE_FAULT;
	pDevStatus->iErrorCode = BNC_ITYPE_FAULT;
	return BNC_RETURN_FAULT;
}

//　读取容器配置信息
// 	函数定义：
// 	功能说明：读取钱箱结构体信息。
// 	参数说明见下表。
// 	1	tBncBillBoxInfo *	pBillBoxInfo	Out	返回钱箱结构体信息
// 	2	tBncDevReturn *	pDevStatus	Out	返回状态信息
// 	返回值见表80。
// 	1	int	0：执行成功；1，执行失败。
int BNC_GetBillBoxInfo(tBncBillBoxInfo *pBillBoxInfo, tBncDevReturn *pDevStatus)
{
	//该函数不用
	if (pBillBoxInfo == NULL || pDevStatus == NULL)
		return BNC_RETURN_FAULT;

	pDevStatus->iType = BNC_ITYPE_FAULT;
	pDevStatus->iErrorCode = BNC_ITYPE_FAULT;
	return BNC_RETURN_FAULT;
}

//　设置容器配置信息
// 	函数定义：
// 	功能说明：设置容器配置信息（设置纸币数量）
// 	参数说明见下表。
// 	1	UNIT	uiSlotID	In	槽位ID
// 	2	tBncBillBoxInfo *	pBillBoxInfo	In	容器配置信息
// 	3	tBncDevReturn *	pDevStatus	Out	返回状态信息
// 	返回值见下表。
// 	1	int	0：执行成功；1，执行失败。
int BNC_SetBillBoxInfo(UINT uiSlotID, tBncBillBoxInfo *pBillBoxInfo, tBncDevReturn *pDevStatus)
{
	//该函数不用
	if (pBillBoxInfo == NULL || pDevStatus == NULL)
		return BNC_RETURN_FAULT;

	pDevStatus->iType = BNC_ITYPE_FAULT;
	pDevStatus->iErrorCode = BNC_ITYPE_FAULT;
	return BNC_RETURN_FAULT;
}


//　开始接收钞票
// 	功能说明：机芯进入预备存款状态，指示灯开始闪烁提示用户投入纸币。实现验钞，退钞，钞票压入暂存区等功能。
// 	参数说明见下表
// 	1	tBncDevReturn *	p_psStatus	Out	保存BNC返回的逻辑错误码
// 	返回值说明见下表
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
// 	备注：可在子线程或主线程中启动，使纸币模块进入等待接收纸币的工作状态，程序将进入阻塞，除非成功接收纸币或在另外线程中调用BNC_Stop可以使该函数退出运行。
int BNC_Start(tBncDevReturn * p_psStatus)
{
	if (p_psStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = 0;
	if(!bncCommands.GetIsExecute()){
		if (!bncCommands.BNC_GetAcceptFlag())
		{
			bncCommands.BNC_SetAcceptFlag(TRUE);
			//开始接收纸币
			errCode = bncCommands.CashInStart();
			if (errCode != WFS_SUCCESS)
			{
				bncCommands.BNC_SetAcceptFlag(FALSE);
				p_psStatus->iType = BNC_ITYPE_FAULT;
				p_psStatus->iErrorCode = errCode;
				return BNC_RETURN_FAULT;
			}
		}

	int dwTimeOut = 0;
	//接收纸币
	memset(&bncCommands.m_lpCashInNoteList, 0, sizeof(WFSCIMNOTENUMBERLIST));
	errCode = bncCommands.CashIn(bncCommands.m_lpCashInNoteList, dwTimeOut);
	if (errCode != WFS_SUCCESS)
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
	p_psStatus->iType = BNC_ITYPE_NO_ERROR;
	p_psStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
	}else{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
}
//　停止接收钞票
// 	功能说明：机芯停止接收钞票，指示灯熄灭。
// 	参数说明见下表
// 	1	tBncDevReturn *	p_psStatus	Out	保存BNA返回的逻辑错误码
//      tBncCashInfo *p_psCashInfo  Out 保存已接收钞票数据
// 	返回值说明见下表
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
int BNC_Stop(tBncEnCashInfo *p_psCashInfo, tBncDevReturn * p_psStatus)
{
	if (p_psCashInfo == NULL || p_psStatus == NULL)
		return BNC_RETURN_FAULT;
	long errCode = 0;
	WFSCIMCASHINFO lpCUInfo;
	if(!bncCommands.GetIsExecute()){
	errCode = bncCommands.CashInEnd(lpCUInfo);
	bncCommands.BNC_SetAcceptFlag(FALSE);
	if (errCode != WFS_SUCCESS)
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
	else
	{
		for (int i = 0; i < lpCUInfo.usCount; i++)
		{
			//钱箱物理名称
			CString szPhyName(lpCUInfo.lppCashIn[i]->lppPhysical[0]->lpPhysicalPositionName);
			if (lpCUInfo.lppCashIn[i]->ulCashInCount > 0)
			{
				if (szPhyName == _T("Stacker1"))
				{
					p_psCashInfo->wRecyclerAIntoCount = lpCUInfo.lppCashIn[i]->ulCashInCount;
				}
				if (szPhyName == _T("Stacker2"))
				{
					p_psCashInfo->wRecyclerBIntoCount = lpCUInfo.lppCashIn[i]->ulCashInCount;
				}
				if (szPhyName == _T("Stacker3"))
				{
					p_psCashInfo->wRecyclerCIntoCount = lpCUInfo.lppCashIn[i]->ulCashInCount;
				}
				if (szPhyName == _T("Stacker4"))
				{
					p_psCashInfo->wRecyclerDIntoCount = lpCUInfo.lppCashIn[i]->ulCashInCount;
				}
				if (szPhyName == _T("CashBox"))
				{
					LPWFSCIMNOTENUMBERLIST lpNoteNumberList = lpCUInfo.lppCashIn[i]->lpNoteNumberList;
					for (int j = 0; j < lpNoteNumberList->usNumOfNoteNumbers; j++)
					{
						long lAmount = NoteID2Amount(lpNoteNumberList->lppNoteNumber[j]->usNoteID);
						switch (lAmount)
						{
						case BNC_FACE_CNY1:
							p_psCashInfo->wCashBox_CNY1_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case BNC_FACE_CNY5:
							p_psCashInfo->wCashBox_CNY5_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case BNC_FACE_CNY10:
							p_psCashInfo->wCashBox_CNY10_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case BNC_FACE_CNY20:
							p_psCashInfo->wCashBox_CNY20_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case BNC_FACE_CNY50:
							p_psCashInfo->wCashBox_CNY50_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case BNC_FACE_CNY100:
							p_psCashInfo->wCashBox_CNY100_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						default:
							break;
						}
					}
				}
			}
		}
	}
	p_psStatus->iType = BNC_ITYPE_NO_ERROR;
	p_psStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
	}else{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
}

//　获取识别钞票信息
// 	功能说明：获取机芯接收的钞票信息。
// 	参数说明见下表
// 	1	tBncCashInfo *	p_psCashInfo	Out	返回钞票信息结构体，临时钱箱的信息
// 	2	BYTE&	p_byOperation	Out	最后一张处理纸币的状态 
// 		0:没有钞票插入; 
// 		1:无法识别的钞票退出到退钞口; 
// 		2:用户由退钞口把钞票（不能识别或者取消操作退出的）取走; 
// 		3:钞票放入又被强行拽出; 
// 		4:钞票被拉紧; 
// 		5:真钞处理完毕; 
// 		6:钞票拉紧并且超时被迫停止接收; 
// 		7:退钞口有钞票未取走超时; 
// 		8:入钞口至暂存区有钞票正在处理; 
// 		9:钱箱已经取走; 
// 		10:钱箱已满; 
// 		11:机芯进出口长时间阻塞(技术故障); 
// 		12:未知错误导致暂停服务。
// 	3	tBncDevReturn *	p_psStatus	Out	保存BNC返回的逻辑错误码
// 
// 	返回值说明见下表
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
// 
// 	备注：可在BNC_Start，执行成功后，调用该函数，获取临时钱箱与最后一张纸币的处理信息。
// 	e)	对于G&D的纸币模块，p_byOperation可以获取0，1，3，5；
// 	f)	对于MEI的纸币模块，p_byOperation可以获取0，1，3，5；
// 	g)	对于G&D的纸币模块，p_byOperation可以获取0，1，5，6，7，9，10；
// 	h)	对于钱箱已满，钱箱已取走，机芯故障，未知错误等其他错误，可以通过BNA_ GetStatu的硬件返回信息来判断获取。
int  BNC_GetCashInfo(tBncCashInfo *p_psCashInfo, BYTE& p_byOperation, tBncDevReturn *p_psStatus)
{
	if (p_psCashInfo == NULL || p_psStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = 0;
	errCode = bncCommands.GetCashInfoResponse(p_psCashInfo);
	if (p_psCashInfo->iNumOfItems == 0)
	{
		p_byOperation = 1;
	}
	else
	{
		p_byOperation = 0;
	}
	if (errCode != WFS_SUCCESS)
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
	p_psStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
}

//　压箱
// 	功能说明：将暂存器的纸币全部压入钱箱。
// 	参数说明见下表
// 	1	tBncDevReturn *	p_psStatus	Out	保存BNC返回的逻辑错误码
// 	返回值说明见下表
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
int  BNC_Encash(tBncDevReturn *p_psStatus)
{
	if (p_psStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = 0;
	WFSCIMCASHINFO lpCUInfo;
	memset(&bncCommands.m_cashIntoInfo, 0x00, sizeof(bncCommands.m_cashIntoInfo));
	
	errCode = bncCommands.CashInEnd(lpCUInfo);
	if (errCode == WFS_SUCCESS) {
		for (int i = 0; i < lpCUInfo.usCount; i++)
		{
			//钱箱物理名称
			CString szPhyName(lpCUInfo.lppCashIn[i]->lppPhysical[0]->lpPhysicalPositionName);
			if (lpCUInfo.lppCashIn[i]->ulCashInCount > 0)
			{
				if (szPhyName == _T("Stacker1"))
				{
					bncCommands.m_cashIntoInfo.wRecyclerAIntoCount = lpCUInfo.lppCashIn[i]->ulCashInCount;
				}
				if (szPhyName == _T("Stacker2"))
				{
					bncCommands.m_cashIntoInfo.wRecyclerBIntoCount = lpCUInfo.lppCashIn[i]->ulCashInCount;
				}
				if (szPhyName == _T("Stacker3"))
				{
					bncCommands.m_cashIntoInfo.wRecyclerCIntoCount = lpCUInfo.lppCashIn[i]->ulCashInCount;
				}
				if (szPhyName == _T("Stacker4"))
				{
					bncCommands.m_cashIntoInfo.wRecyclerDIntoCount = lpCUInfo.lppCashIn[i]->ulCashInCount;
				}
				if (szPhyName == _T("CashBox"))
				{
					LPWFSCIMNOTENUMBERLIST lpNoteNumberList = lpCUInfo.lppCashIn[i]->lpNoteNumberList;

					for (int j = 0; j < lpNoteNumberList->usNumOfNoteNumbers; j++)
					{
						switch (lpNoteNumberList->lppNoteNumber[j]->usNoteID)
						{
						case 0x0301:
						case 0x2301:
							bncCommands.m_cashIntoInfo.wCashBox_CNY1_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case 0x0303:
						case 0x2303:
						case 0x4303:
							bncCommands.m_cashIntoInfo.wCashBox_CNY5_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case 0x0304:
						case 0x2304:
						case 0x4304:
							bncCommands.m_cashIntoInfo.wCashBox_CNY10_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case 0x2305:
						case 0x4305:
							bncCommands.m_cashIntoInfo.wCashBox_CNY20_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case 0x0306:
						case 0x2306:
						case 0x4306:
							bncCommands.m_cashIntoInfo.wCashBox_CNY50_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						case 0x0307:
						case 0x2307:
						case 0x4307:
						case 0x6307:
							bncCommands.m_cashIntoInfo.wCashBox_CNY100_IntoCount += lpNoteNumberList->lppNoteNumber[j]->ulCount;
							break;
						}
					}
				}
			}
		}
	}
	if (errCode != WFS_SUCCESS)
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}

	p_psStatus->iType = BNC_ITYPE_NO_ERROR;
	p_psStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;

}

//　退钞
// 	功能说明：将暂存器的纸币全部退出。
// 	参数说明见下表
// 	1	tBncDevReturn *	p_psStatus	Out	保存BNA返回的逻辑错误码
// 	返回值说明见下表
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
int  BNC_Refund(tBncDevReturn *p_psStatus)
{
	if (p_psStatus == NULL)
		return BNC_RETURN_FAULT;
	long errCode = 0;
	if(!bncCommands.GetIsExecute()){
	errCode = bncCommands.CashInRollback();
	bncCommands.BNC_SetAcceptFlag(FALSE);
	if (errCode != WFS_SUCCESS)
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}

	p_psStatus->iType = BNC_ITYPE_NO_ERROR;
	p_psStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
	}else{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
}


//　获取钱箱ID
// 	功能说明：调用此接口可获取钱箱ID，详细信息查看返回结构体。
// 	参数说明见下表
// 	1	char*	p_BoxID	Out	获取钱箱ID
// 	2	tBncDevReturn *	p_psStatus	Out	保存BNC返回的逻辑错误码
// 
// 	返回值说明见下表
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
int BNC_GetBoxID(char * p_BoxID, tBncDevReturn * p_psStatus)
{
	if (p_BoxID == NULL || p_psStatus == NULL)
		return BNC_RETURN_FAULT;

	p_psStatus->iType = BNC_ITYPE_FAULT;
	p_psStatus->iErrorCode = BNC_ITYPE_FAULT;
	return BNC_RETURN_FAULT;
}

//　找零配钞
// 	功能说明：找零配钞
// 	参数说明见下表。
// 	1	tBncChangeNum *	pChangeNum	In/Out	找零的纸币面额及数量信息
// 	2	tBncDevReturn *	pDevStatus	Out	返回状态信息
// 	返回值说明见下表。
// 	1	int	0：执行成功；1，执行失败。
int BNC_ChangeBill(tBncChangeNum *pChangeNum, tBncDevReturn *pDevStatus)
{
	if (pChangeNum == NULL || pDevStatus == NULL)
		return BNC_RETURN_FAULT;
	long errCode = 0;
	//获取找零前钱箱信息
	WFSCDMCUINFO stCdmCuInfoBef;
	errCode = bncCommands.QueryCdmCashUnit(&stCdmCuInfoBef);
	if (errCode != WFS_SUCCESS)
	{
		pDevStatus->iType = BNC_ITYPE_FAULT;
		pDevStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
	//找零
	WFSCDMDENOMINATION denomination;
	errCode = bncCommands.Dispense(pChangeNum->uiDispenseNumber[0], pChangeNum->uiDispenseNumber[1], pChangeNum->uiDispenseNumber[2], pChangeNum->uiDispenseNumber[3], denomination);
	if (errCode != WFS_SUCCESS)
	{
		pDevStatus->iType = BNC_ITYPE_FAULT;
		pDevStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
	else
	{
		if (denomination.lpulValues[1])
		{
			pChangeNum->uiOutNumber[0] = denomination.lpulValues[1];
		}
		if (denomination.lpulValues[2])
		{
			pChangeNum->uiOutNumber[1] = denomination.lpulValues[2];
		}
		if (denomination.lpulValues[3])
		{
			pChangeNum->uiOutNumber[2] = denomination.lpulValues[3];
		}
		if (denomination.lpulValues[4])
		{
			pChangeNum->uiOutNumber[3] = denomination.lpulValues[4];
		}
	}

	pDevStatus->iType = BNC_ITYPE_NO_ERROR;
	pDevStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
}

//　取消找零
// 	功能说明：取消找零操作。
// 	参数说明见下表。
// 	1	tBncDevReturn *	p_psStatus	Out	保存BNC返回的逻辑错误码
// 	返回值说明见下表。
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
int  BNC_Cancel(tBncDevReturn *p_psStatus)
{
	if (p_psStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = bncCommands.Cancel();
	bncCommands.BNC_SetAcceptFlag(FALSE);
	if (errCode != WFS_SUCCESS || errCode != WFS_ERR_OP_IN_PROGRESS)
	{
		p_psStatus->iType = BNC_ITYPE_FAULT;
		p_psStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}

	p_psStatus->iType = BNC_ITYPE_NO_ERROR;
	p_psStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
}

//　开始更换纸币找零箱
// 	功能说明：此接口用于更换纸币找零箱。
// 	参数说明见下表。
// 	1	UNIT	uiBoxType	In	指定纸币容器的类型容器类型：0-废币箱 1-1元纸币箱, 2-5元纸币箱, 3-10
// 	元纸币箱, 4-20元纸币箱, 5-50元纸币箱, 6-100元纸币箱
// 	2	UINT	uiBoxNo	In	制定纸币容器的序号0 ~ 6 其中： 0号废币箱 1号为5元找零箱，2号为1元找零箱
// 	3	tBncDevReturn *	pDevStatus	Out	返回状态信息
// 	返回值见下表。
// 	1	int	0：执行成功；1：执行失败。
int BNC_StartReplaceBox(UINT uiBoxType, UINT uiBoxNo, tBncDevReturn *pDevStatus)
{
	if (pDevStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = bncCommands.ReplaceCashUnit();
	if (errCode != WFS_SUCCESS)
	{
		pDevStatus->iType = BNC_ITYPE_FAULT;
		pDevStatus->iErrorCode = errCode;
		return BNC_RETURN_FAULT;
	}
	pDevStatus->iType = BNC_ITYPE_NO_ERROR;
	pDevStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
}

//  停止更换纸币找零箱
// 	功能说明：停止更换纸币找零箱。
// 	参数说明见下表。
// 	1	UNIT	uiBoxType	In	指定纸币容器类型
// 	2	UNIT	uiBoxNo	In	指定纸币容器序号
// 	2	tBncDevReturn *	p_psStatus	Out	保存BNC返回的逻辑错误码
// 
// 	返回值说明见下表。
// 	1	Int	0	成功
// 	2	Int	1	传入参数为空
int BNC_StopReplaceBox(UINT uiBoxType, UINT uiBoxNo, tBncDevReturn *pDevStatus)
{
	if (pDevStatus == NULL)
		return BNC_RETURN_FAULT;

	long errCode = 0;
	pDevStatus->iType = BNC_ITYPE_NO_ERROR;
	pDevStatus->iErrorCode = errCode;
	return BNC_RETURN_NO_ERROR;
}

//　设置钱箱RFID信息
// 	功能说明：写入钱箱RFID信息。
// 	参数说明见下表。
// 	1	UNIT	uiSLotID	In	槽位ID
// 	2	tBncRfidInfo *	pRFIDInfo	In	设置RFID信息
// 	3	tBncDevReturn *	pDevStatus	Out	返回状态信息
// 	返回值见下表。
// 	1	int	0：执行成功；1，执行失败。
int BNC_WriteRFIDInfo(UINT uiSLotID, tBncRfidInfo * pRFIDInfo, tBncDevReturn * pDevStatus)
{
	//G60无RFID，直接返回错误
	if (pRFIDInfo == NULL || pDevStatus == NULL)
		return BNC_RETURN_FAULT;

	pDevStatus->iType = BNC_ITYPE_FAULT;
	pDevStatus->iErrorCode = BNC_ITYPE_FAULT;
	return BNC_RETURN_FAULT;
}

//　读取钱箱RFID信息
// 	功能说明：读取钱箱RFID信息。
// 	参数说明见下表。
// 	1	UNIT	uiSLotID	In	槽位ID
// 	2	tBncRfidInfo *	pRFIDInfo	Out	设置RFID信息
// 	3	tBncDevReturn *	pDevStatus	Out	返回状态信息
// 	返回值说明见下表。
// 	1	int	0：执行成功；1，执行失败。
int BNC_ReadRFIDInfo(UINT uiSLotID, tBncRfidInfo* pRFIDInfo, tBncDevReturn * pDevStatus)
{
	//G60无RFID，直接返回错误
	if (pRFIDInfo == NULL || pDevStatus == NULL)
		return BNC_RETURN_FAULT;

	pDevStatus->iType = BNC_ITYPE_FAULT;
	pDevStatus->iErrorCode = BNC_ITYPE_FAULT;
	return BNC_RETURN_FAULT;
}

//   清空钱箱
//	OUT tBncChangeNum* pBoxInfo
int BNC_Empty(tBncChangeNum* pBoxInfo)
{
	if (pBoxInfo == NULL)
		return BNC_RETURN_FAULT;

	// 特殊情况：纸币模块执行了cash_in 命令且未结束，那么无法执行清空命令
	// 使用rollback命令先回收一次用于结束
	long errCode = 0;
	errCode = bncCommands.CashInRollback();
	/*if (errCode != WFS_SUCCESS)
		return BNC_RETURN_FAULT;*/

		//清空
	errCode = bncCommands.Empty();
	if (errCode != WFS_SUCCESS)
	{
		return BNC_RETURN_FAULT;
	}
	else
	{
		WFSRESULT result;
		bncCommands.GetEmptyExcResult(result);
		{
			LPWFSCIMCASHINFO lpCUInfo = (LPWFSCIMCASHINFO)result.lpBuffer;
			for (int i = 0; i < lpCUInfo->usCount; i++)
			{
				CString szPhyName(lpCUInfo->lppCashIn[i]->lppPhysical[0]->lpPhysicalPositionName);//钱箱物理名称

				switch (lpCUInfo->lppCashIn[i]->ulValues)//面额
				{
				case 1:
				{
					if (szPhyName == _T("Stacker1"))
					{
						pBoxInfo->uiDispenseNumber[0] = lpCUInfo->lppCashIn[i]->ulCashInCount;
						pBoxInfo->uiOutNumber[0] = lpCUInfo->lppCashIn[i]->ulCount;
					}
					if (szPhyName == _T("Stacker2"))
					{
						pBoxInfo->uiDispenseNumber[1] = lpCUInfo->lppCashIn[i]->ulCashInCount;
						pBoxInfo->uiOutNumber[1] = lpCUInfo->lppCashIn[i]->ulCount;
					}
				}
				break;
				case 5:
				{
					if (szPhyName == _T("Stacker3"))
					{
						pBoxInfo->uiDispenseNumber[2] = lpCUInfo->lppCashIn[i]->ulCashInCount;
						pBoxInfo->uiOutNumber[2] = lpCUInfo->lppCashIn[i]->ulCount;

					}
					if (szPhyName == _T("Stacker4"))
					{
						pBoxInfo->uiDispenseNumber[3] = lpCUInfo->lppCashIn[i]->ulCashInCount;
						pBoxInfo->uiOutNumber[3] = lpCUInfo->lppCashIn[i]->ulCount;
					}
				}
				break;
				default:
					break;
				}
			}

		}

	}
	return BNC_RETURN_NO_ERROR;
}
