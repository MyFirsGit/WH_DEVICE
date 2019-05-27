// CHA.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "CHA.h"

OCASDev m_OCASDev;

void CHA_SetCHADevReturn(const int errCode, const tDevReturn *l_s, tCHADevReturn * pDevStatus)
{
	pDevStatus->uiProviderId = 0x04;
	pDevStatus->uiModuleType = 0x04;
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
		pDevStatus->uiType = 0x02;
	else
		pDevStatus->uiType = CHTRS_RES_OK;
	pDevStatus->uiErrorType[0] = l_s[0].iType;
	pDevStatus->uiErrorCode[0] = l_s[0].iLogicCode;
}
/*****************************************************************************/
/*                                                                           */
/*  Function Declarations                                                    */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
// 以下接口在LIB实现，在DLL层使用，如果厂家提供dll则可仿造TIM模块实现，如果厂家
// 提供串口协议，则需封装完协议后再实现以下接口
/* # wang feng                                                               */
/*****************************************************************************/
// 通讯建立
int CHA_CommOpen(UINT uiCommPort, UINT uiBaudRate, CString path, CString fileName, tCHADevReturn * pDevStatus)
{
	//如果传入的值为空值
	if (path == _T("") || fileName == _T(""))
		return CHTRS_RES_FAILED;
	//初始化日志
	LogApi.Initialize(path, fileName);

	CString sLogString(_T(""));
	if (pDevStatus == NULL)
	{
		sLogString.Format(_T("pDevStatus is null "));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}

	sLogString.Format(_T("CHA_CommOpen: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	// 若打开，则需要关闭
	if (m_hCH != NULL)
	{
		errCode = m_OCASDev.iCloseComm();
		m_hCH = NULL;
		if (errCode != CHTRS_RES_OK) {
			CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
			sLogString.Format(_T("iCloseComm: 串口关闭失败。"));
			LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
			return CHTRS_RES_FAILED;
		}
	}

	//打开串口
	errCode = m_OCASDev.iSetCommPara(l_s);

	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	else
	{
		m_hCH = 1;;
	}
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	sLogString.Format(_T("iSetCommPara: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return errCode;

}
// 初始化
/*
btXinCtl:
	0x00 暂存部硬币送到出币口
	0x10 暂存部硬币送到Hopper或回收箱
	0x20 暂存部硬币保持原样
*/
int CHA_Init(BYTE btXinCtl, tCHADevReturn * pDevStatus)
{
	if (pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_Init: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_Init: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}

	//初始化
	errCode = m_OCASDev.iInit(&p_psCASStatus, &p_psCoinInfo, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	sLogString.Format(_T("iInit: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 获取设备状态
int CHA_GetDevStatus(tCHADevReturn * pDevStatus)
{
	if (pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_GetDevStatus: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_GetDevStatus: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}

	//获取设备状态
	errCode = m_OCASDev.iGetDevStatus(&p_psCASStatus, &p_psCoinInfo, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	sLogString.Format(_T("iGetDevStatus: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 获取传感器状态
int CHA_GetSensorStatus(tCHASensorStatus* pSensorStatus, tCHADevReturn * pDevStatus)
{
	if (pSensorStatus == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_GetDevStatus: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_GetSensorStatus: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}

	//获取设备状态
	errCode = m_OCASDev.iGetDevStatus(&p_psCASStatus, &p_psCoinInfo, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	else
	{
		int sensorID = 0;
		for (int i = 0; i < pSensorStatus->uiSensorNum; i++)
		{
			sensorID++;
			if (sensorID == 1)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byBuckle1Lower;
			}
			else if (sensorID == 2)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byBuckle1Upper;
			}
			else if (sensorID == 3)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byBuckle2Lower;
			}
			else if (sensorID == 4)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byBuckle2Upper;
			}
			else if (sensorID == 5)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byRouterRight;
			}
			else if (sensorID == 6)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byRouterLeft;
			}
			else if (sensorID == 7)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEscrow1Right;
			}
			else if (sensorID == 8)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEscrow1Center;
			}
			else if (sensorID == 9)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEscrow1Left;
			}
			else if (sensorID == 10)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEscrow2Right;
			}
			else if (sensorID == 11)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEscrow2Center;
			}
			else if (sensorID == 12)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEscrow2Left;
			}
			else if (sensorID == 13)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byMagnet1InPos;
			}
			else if (sensorID == 14)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byMagnet2InPos;
			}
			else if (sensorID == 15)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byMHopper1;
			}
			else if (sensorID == 16)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byMHopper2;
			}
			else if (sensorID == 17)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEHopper1;
			}
			else if (sensorID == 18)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEHopper2;
			}
			else if (sensorID == 19)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEHopper3;
			}
			else if (sensorID == 20)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byEHopper4;
			}
			else if (sensorID == 21)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byPlate1Open;
			}
			else if (sensorID == 22)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byPlate1Close;
			}
			else if (sensorID == 23)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byPlate2Open;
			}
			else if (sensorID == 24)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byPlate2Close;
			}
			else if (sensorID == 25)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byCoincaseInPos;
			}
			else if (sensorID == 26)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byChannelMotor;
			}
			else if (sensorID == 27)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byCoinIn;
			}
			else if (sensorID == 28)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byCoinOut1;
			}
			else if (sensorID == 29)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byBracketPos;
			}
			else if (sensorID == 30)
			{
				pSensorStatus->pSensorStatus[i].uiSensorID = sensorID;
				pSensorStatus->pSensorStatus[i].uiStatus = p_psCASStatus.sSensorStatus.byCamSensor;
			}
		}
	}
	sLogString.Format(_T("iGetDevStatus: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 获取容器配置信息
int CHA_GetCoinBoxInfo(tCHADevStatus *pCoinBoxInfo, tCHADevReturn * pDevStatus)
{
	if (pCoinBoxInfo == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_GetCoinBoxInfo: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_GetCoinBoxInfo: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	//获取设备状态
	errCode = m_OCASDev.iGetDevStatus(&p_psCASStatus, &p_psCoinInfo, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	else
	{
		//cas006有两个大Hopper，加币Hopper；两个虚拟Hopper，虚拟Hopper是循环Hopper。它们各自分开计数

		//循环Hopper
		pCoinBoxInfo->wHopperACnt = p_psCoinInfo.iSHopper1Num;
		pCoinBoxInfo->wHopperBCnt = p_psCoinInfo.iSHopper2Num;

		//备用箱中硬币数据量，大Hopper
		pCoinBoxInfo->wPreparationACnt = p_psCoinInfo.iMHopper1Num;
		pCoinBoxInfo->wPreparationBCnt = p_psCoinInfo.iMHopper2Num;

		//回收箱硬币数量
		pCoinBoxInfo->wRecoverCnt = p_psCoinInfo.iCoincase1Coin1 + p_psCoinInfo.iCoincase2Coin1;

		//两个大Hopper状态正常情况下，表示整机状态正常
		if (p_psCASStatus.siButtonStatus.byMHopper1Button == 1 && p_psCASStatus.siButtonStatus.byMHopper2Button == 1)
			pCoinBoxInfo->bIsCoinModuleStandby = TRUE;
		else
			pCoinBoxInfo->bIsCoinModuleStandby = FALSE;

		//回收箱状态
		if (p_psCASStatus.siButtonStatus.byRetractValt1 == 1 && p_psCASStatus.siButtonStatus.byRetractValt2 == 1)
			pCoinBoxInfo->bIsMoneyBoxExist = TRUE;
		else
			pCoinBoxInfo->bIsMoneyBoxExist = FALSE;

		//循环HopperA是否满
		if (p_psCoinInfo.iSHopper1Num >= CHA_SHOPPRT_A_MAX)
			pCoinBoxInfo->bIsHopperAFull = TRUE;
		else
			pCoinBoxInfo->bIsHopperAFull = FALSE;

		//循环HopperA是否空
		if (p_psCoinInfo.iSHopper1Num <= SHOPPER_EMPTY)
			pCoinBoxInfo->bIsHopperAEmpty = TRUE;
		else
			pCoinBoxInfo->bIsHopperAEmpty = FALSE;

		//循环HopperB是否满
		if (p_psCoinInfo.iSHopper2Num >= CHA_SHOPPRT_B_MAX)
			pCoinBoxInfo->bIsHopperBFull = TRUE;
		else
			pCoinBoxInfo->bIsHopperBFull = FALSE;

		//循环HopperB是否空
		if (p_psCoinInfo.iSHopper2Num <= SHOPPER_EMPTY)
			pCoinBoxInfo->bIsHopperBEmpty = TRUE;
		else
			pCoinBoxInfo->bIsHopperBEmpty = FALSE;

		// 备用钱箱A
		if (p_psCASStatus.siButtonStatus.byRetractValt1 == 1)
			pCoinBoxInfo->bIsChangeBoxAInstall = TRUE;
		else
			pCoinBoxInfo->bIsChangeBoxAInstall = FALSE;

		if (p_psCoinInfo.iCoincase1Coin1 >= CHA_HOPPRT_A_MAX)
			pCoinBoxInfo->bIsChangeBoxAFull = TRUE;
		else
			pCoinBoxInfo->bIsChangeBoxAFull = FALSE;

		if (p_psCoinInfo.iCoincase1Coin1 <= CHA_HOPPRT_A_MIN)
			pCoinBoxInfo->bIsChangeBoxAEmpty = TRUE;
		else
			pCoinBoxInfo->bIsChangeBoxAEmpty = FALSE;

		// 备用钱箱B
		if (p_psCASStatus.siButtonStatus.byRetractValt2 == 1)
			pCoinBoxInfo->bIsChangeBoxBInstall = TRUE;
		else
			pCoinBoxInfo->bIsChangeBoxBInstall = FALSE;

		if (p_psCoinInfo.iCoincase2Coin1 >= CHA_HOPPRT_B_MAX)
			pCoinBoxInfo->bIsChangeBoxBFull = TRUE;
		else
			pCoinBoxInfo->bIsChangeBoxBFull = FALSE;

		if (p_psCoinInfo.iCoincase2Coin1 <= CHA_HOPPRT_B_MIN)
			pCoinBoxInfo->bIsChangeBoxBEmpty = TRUE;
		else
			pCoinBoxInfo->bIsChangeBoxBEmpty = FALSE;
	}
	sLogString.Format(_T("iGetDevStatus: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 设置硬币数量
int CHA_SetCoinBoxInfo(tCoinBoxInfo *pCoinBoxInfo, tCHADevReturn * pDevStatus)
{
	if (pCoinBoxInfo == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_SetCoinBoxInfo: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tSetCoinNum p_sCoinNum;
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };

	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_SetCoinBoxInfo: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	p_sCoinNum.wMHopper1Num = pCoinBoxInfo->OneY_inHopper;
	p_sCoinNum.wMHopper2Num = pCoinBoxInfo->HalfY_inHopper;
	p_sCoinNum.wSHopper1Num = 0xffff;
	p_sCoinNum.wSHopper2Num = 0xffff;
	p_sCoinNum.wSHopper3Num = 0xffff;
	p_sCoinNum.wSHopper4Num = 0xffff;
	p_sCoinNum.wCoincase1Coin1 = 0/*0xffff*/;
	p_sCoinNum.wCoincase1Coin2 = 0/*0xffff*/;
	p_sCoinNum.wCoincase2Coin1 = 0xffff;
	p_sCoinNum.wCoincase2Coin2 = 0xffff;
	p_sCoinNum.byEscrow1Num = 0xff;
	p_sCoinNum.byEscrow2Num = 0xff;
	p_sCoinNum.byEscrow3Num = 0xff;
	p_sCoinNum.byEscrow4Num = 0xff;
	p_sCoinNum.byMHopper1Type = 0xff;
	p_sCoinNum.byMHopper2Type = 0xff;
	p_sCoinNum.bySHopper1Type = 0xff;
	p_sCoinNum.bySHopper2Type = 0xff;
	p_sCoinNum.bySHopper3Type = 0xff;
	p_sCoinNum.bySHopper4Type = 0xff;

	//设置硬币
	errCode = m_OCASDev.iSetCoinNumber(p_sCoinNum, &p_psCASStatus, &p_psCoinInfo, l_s);

	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	sLogString.Format(_T("iSetCoinNumber: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 开始接收硬币
int CHA_StartReceiveCoin(tCHADevReturn * pDevStatus)
{
	if (pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_StartReceiveCoin: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_StartReceiveCoin: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	//开始接收硬币
	errCode = m_OCASDev.iStartReceiveCoin(&p_psCASStatus, &p_psCoinInfo, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	sLogString.Format(_T("iStartReceiveCoin: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 结束接收硬币
int CHA_StopReceiveCoin(tCHADevReturn * pDevStatus)
{
	if (pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_StopReceiveCoin: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_StopReceiveCoin: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	//停止接收硬币
	errCode = m_OCASDev.iStopReceiveCoin(&p_psCASStatus, &p_psCoinInfo, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	sLogString.Format(_T("iStopReceiveCoin: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 获取接收硬币信息
int CHA_GetReceiveNumber(tCHACoinValueInfo *pCoinValueInfo, tCHADevReturn * pDevStatus)
{
	if (pCoinValueInfo == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_GetReceiveNumber: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tReceiveCoinNum p_psReceiveCoinNum = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_GetReceiveNumber: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	//获取接收金额
	errCode = m_OCASDev.iGetReceiveNumber(&p_psReceiveCoinNum, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	else
	{
		//Cas006一共两个暂存
		pCoinValueInfo->uiEjectCoinNum = p_psReceiveCoinNum.byEjectCoinNum;
		pCoinValueInfo->stCoinBoxValueInfo[0].uiBoxNo = 0x01;
		pCoinValueInfo->stCoinBoxValueInfo[0].uiBoxType = 0x03;
		pCoinValueInfo->stCoinBoxValueInfo[0].uiCoinMaxNum = 100;//暂存能存储多少，需要确认
		pCoinValueInfo->stCoinBoxValueInfo[0].uiCoinNum = p_psReceiveCoinNum.byEscrow1Num;
		pCoinValueInfo->stCoinBoxValueInfo[0].uiCoinValue = 100;
		pCoinValueInfo->stCoinBoxValueInfo[0].uiBoxStatus = 0x0;

		pCoinValueInfo->stCoinBoxValueInfo[1].uiBoxNo = 0x02;
		pCoinValueInfo->stCoinBoxValueInfo[1].uiBoxType = 0x03;
		pCoinValueInfo->stCoinBoxValueInfo[1].uiCoinMaxNum = 100;//暂存能存储多少，需要确认
		pCoinValueInfo->stCoinBoxValueInfo[1].uiCoinNum = p_psReceiveCoinNum.byEscrow2Num;
		pCoinValueInfo->stCoinBoxValueInfo[1].uiCoinValue = 100;
		pCoinValueInfo->stCoinBoxValueInfo[1].uiBoxStatus = 0x0;
	}
	sLogString.Format(_T("iGetReceiveNumber: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 存入硬币
int CHA_AcceptCoin(tCHACoinValueInfo *pCoinValueInfo, tCHADevReturn * pDevStatus)
{
	if (pCoinValueInfo == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_AcceptCoin: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	memset(pCoinValueInfo, 0, sizeof(pCoinValueInfo));
	memset(pDevStatus, 0, sizeof(pDevStatus));
	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_AcceptCoin: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	//读取暂存数据
	errCode = CHA_GetReceiveNumber(pCoinValueInfo, pDevStatus);
	if (errCode != CHTRS_RES_OK)
		return errCode;

	//自动存入硬币
	errCode = m_OCASDev.iAcceptCoinEx(&p_psCASStatus, &p_psCoinInfo, l_s);

	sLogString.Format(_T("iAcceptCoinEx: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return errCode;
}
// 退出硬币
int CHA_EjectCoin(UINT * uiReturnCoinNum, tCHADevReturn * pDevStatus)
{
	if (uiReturnCoinNum == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_EjectCoin: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };
	tReceiveCoinNum p_psReceiveCoinNum = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_EjectCoin: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	//获取接收金额
	errCode = m_OCASDev.iGetReceiveNumber(&p_psReceiveCoinNum, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		return errCode;
	}
	else
	{
		*uiReturnCoinNum = p_psReceiveCoinNum.byEscrow1Num + p_psReceiveCoinNum.byEscrow2Num;
	}
	//退币
	errCode = m_OCASDev.iEjectCoin(&p_psCASStatus, &p_psCoinInfo, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	sLogString.Format(_T("iEjectCoin: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 找零
int CHA_ChangeCoin(tCHAChangeNum * pChangeNum, tCHADevReturn * pDevStatus)
{
	if (pChangeNum == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_ChangeCoin: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	tChange p_sChange = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_ChangeCoin: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}

	//找零
	p_sChange.byMHopper1Num = pChangeNum->wMHopper1Num;
	p_sChange.byMHopper2Num = pChangeNum->wMHopper2Num;
	p_sChange.bySHopper1Num = pChangeNum->wChange1Num;
	p_sChange.bySHopper2Num = pChangeNum->wChange2Num;
	errCode = m_OCASDev.iChange(p_sChange, &p_psCASStatus, &p_psCoinInfo, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	sLogString.Format(_T("iChange: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);

	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	return errCode;
}
// 更换容器
int CHA_StartReplaceBOX(UINT uiBoxType, UINT uiBoxNo, UINT uiOpType, tCHADevReturn * pDevStatus)
{
	return CHTRS_RES_FAILED;
}
// 停止更换容器
int CHA_StopReplaceBOX(UINT uiBoxType, UINT uiBoxNo, UINT uiOpType, tCHADevReturn * pDevStatus)
{
	return CHTRS_RES_FAILED;
}
// 清空硬币
int CHA_ClearCoin(UINT uiBoxTypeOutput, UINT uiBoxNoOutput, UINT uiBoxTypeInput, UINT uiBoxNoInput, tCoinBoxInfo *pCoinBoxInfo, UINT uiCoinNum, tCHADevReturn * pDevStatus)
{
	if (pCoinBoxInfo == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;
	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_ClearCoin: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tClearCoin p_sClearCoin = { 0 };
	tDevReturn l_s[8] = { 0 };
	tCASStatus p_psCASStatus = { 0 };
	tCoinInfo  p_psCoinInfo = { 0 };

	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_ClearCoin: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}

	//清币有两种模式，一种是自动清币，另一种是清指定数量的币

	//清所有币
	if (uiBoxTypeOutput == 0)
	{
		p_sClearCoin.bMHopper1Flag = TRUE;
		p_sClearCoin.bMHopper2Flag = TRUE;
		p_sClearCoin.bSHopper1Flag = TRUE;
		p_sClearCoin.bSHopper2Flag = TRUE;
	}
	else
	{
		//虚拟Hopper，可循环，主Hopper
		//虚拟Hopper类型为2，主Hopper为4
		if (uiBoxTypeOutput == 2)
		{
			if (uiBoxNoOutput == 1)
				p_sClearCoin.bSHopper1Flag = TRUE;
			else if (uiBoxNoOutput == 2)
				p_sClearCoin.bSHopper2Flag = TRUE;
		}
		else if (uiBoxTypeOutput == 4)
		{
			if (uiBoxNoOutput == 1)
				p_sClearCoin.bMHopper1Flag = TRUE;
			else if (uiBoxNoOutput == 2)
				p_sClearCoin.bMHopper2Flag = TRUE;
		}
	}

	//清币
	//errCode = m_OCASDev.iClearCoinEx(p_sClearCoin, &p_psCASStatus, &p_psCoinInfo, l_s);
	errCode = m_OCASDev.iClearCoin(p_sClearCoin, &p_psCASStatus, &p_psCoinInfo, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	else
	{
		pCoinBoxInfo->HalfY_inHopper = p_psCoinInfo.iSHopper1Num;
		pCoinBoxInfo->OneY_inHopper = p_psCoinInfo.iSHopper2Num;
		pCoinBoxInfo->HalfY_preparation = p_psCoinInfo.iMHopper1Num;
		pCoinBoxInfo->OneY_preparation = p_psCoinInfo.iMHopper2Num;
		pCoinBoxInfo->OneY_inRecover = p_psCoinInfo.iCoincase1Coin1 + p_psCoinInfo.iCoincase2Coin1;
		pCoinBoxInfo->OneY_maxthreshold_inRecover = CHA_COINCASE_A_MAX;
	}

	sLogString.Format(_T("iClearCoinEx: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
}
// 读容器RFID信息
int CHA_ReadRFIDInfo(UINT uiBoxType, UINT uiBoxNo, unsigned char RFIDInfo[36], tCHADevReturn * pDevStatus)
{
	if ((uiBoxType != 1 && uiBoxType != 5) || uiBoxNo == 0 || RFIDInfo == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_ReadRFIDInfo: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tCAS006_IN_RWRFID p_psWRFID = { 0 };
	tCAS006_DATA p_psData = { 0 };
	tDevReturn l_s[8] = { 0 };

	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_ReadRFIDInfo: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}

	switch (uiBoxType)
	{
	case 1:
		if (uiBoxNo == 1)
		{
			p_psWRFID.byBoxId = 0x01;
			p_psWRFID.byBlockIndex = 8;
		}
		else if (uiBoxNo == 2)
		{
			p_psWRFID.byBoxId = 0x02;
			p_psWRFID.byBlockIndex = 9;
		}
		break;
	case 5:
		if (uiBoxNo == 1)
		{
			p_psWRFID.byBoxId = 0x03;
			p_psWRFID.byBlockIndex = 10;
		}
		else if (uiBoxNo == 2)
		{
			p_psWRFID.byBoxId = 0x04;
			p_psWRFID.byBlockIndex = 12;
		}
		break;
	default:
		break;
	}

	//读RFID数据
	errCode = m_OCASDev.iRFReadBlock(&p_psWRFID, &p_psData, l_s);

	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	else
	{
		memcpy(RFIDInfo, p_psData.caData, 36);
	}

	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	sLogString.Format(_T("iRFReadBlock: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return errCode;
}
// 写容器RFID信息
int CHA_WriteRFIDInfo(UINT uiBoxType, UINT uiBoxNo, unsigned char RFIDInfo[36], tCHADevReturn * pDevStatus)
{
	if ((uiBoxType != 1 && uiBoxType != 5) || uiBoxNo == 0 || RFIDInfo == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_WriteRFIDInfo: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tCAS006_IN_RWRFID p_psWRFID = { 0 };
	tCAS006_DATA p_psData = { 0 };
	tDevReturn l_s[8] = { 0 };
	int tt = sizeof(RFIDInfo);
	memcpy(p_psData.caData, RFIDInfo, 36);

	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_WriteRFIDInfo: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}

	switch (uiBoxType)
	{
	case 1:
		if (uiBoxNo == 1)
		{
			p_psWRFID.byBoxId = 0x01;
			p_psWRFID.byBlockIndex = 8;
		}
		else if (uiBoxNo == 2)
		{
			p_psWRFID.byBoxId = 0x02;
			p_psWRFID.byBlockIndex = 9;
		}
		break;
	case 5:
		if (uiBoxNo == 1)
		{
			p_psWRFID.byBoxId = 0x03;
			p_psWRFID.byBlockIndex = 10;
		}
		else if (uiBoxNo == 2)
		{
			p_psWRFID.byBoxId = 0x04;
			p_psWRFID.byBlockIndex = 12;
		}
		break;
	default:
		break;
	}

	//写入RFID数据
	errCode = m_OCASDev.iRFWriteBlock(&p_psWRFID, &p_psData, l_s);

	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}

	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	sLogString.Format(_T("iRFWriteBlock: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return errCode;
}
// 获取模块介质版本
int CHA_GetVersion(char cVersion[32], tCHADevReturn * pDevStatus)
{
	if (cVersion == NULL || pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_GetVersion: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_GetVersion: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	LPTSTR p_pcDevType;
	byte p_byDataLen;
	//errCode = m_OCASDev.iGetDevVersion(p_pcDevType, p_byDataLen, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	else
	{
		if (p_pcDevType != NULL)
		{
			USES_CONVERSION;
			const char* p_version = W2A(p_pcDevType);
			memcpy(cVersion, p_version, p_byDataLen);
		}
	}
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	sLogString.Format(_T("iGetDevVersion: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return errCode;
}
// 获取模块序号
int CHA_GetSerialNumber(char cVersion[32], tCHADevReturn * pDevStatus)
{
	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_GetSerialNumber: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	tDevReturn l_s[8] = { 0 };
	if (m_hCH == NULL)
	{
		CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_GetSerialNumber: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	LPTSTR p_pcDevType;
	byte p_byDataLen;
	//errCode = m_OCASDev.iGetDevType(p_pcDevType, p_byDataLen, l_s);
	if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	{
		errCode = CHTRS_RES_FAILED;
	}
	else
	{
		if (p_pcDevType != NULL)
		{
			USES_CONVERSION;
			const char* p_version = W2A(p_pcDevType);
			memcpy(cVersion, p_version, p_byDataLen);
		}
	}
	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	sLogString.Format(_T("iGetDevType: ReturnCode = 0x%02x,iLogicCode = 0x%02x"), errCode, l_s[0].iLogicCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	return errCode;
}
// 获取审计数据
int CHA_GetAuditData(tCHACoinBoxInfo *pCoinBoxInfo, tCHADevReturn * pDevStatus)
{
	//硬件不支持
	return CHTRS_RES_FAILED;

	//if (pCoinBoxInfo == NULL || pCoinBoxInfo->uiCoinBoxNum == 0 || pCoinBoxInfo->pCoinBoxValueInfo == NULL || pDevStatus == NULL)
	//	return CHTRS_RES_FAILED;

	//CString sLogString(_T(""));

	//sLogString.Format(_T("CHA_GetAuditData: "));
	//LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	//DWORD errCode = CHTRS_RES_OK;
	//tDevReturn l_s[8] = { 0 };
	//tCASStatus p_psCASStatus = { 0 };
	//tCoinInfo  p_psCoinInfo = { 0 };
	//if (m_hCH == NULL)
	//{
	//	CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	//	pDevStatus->uiType = 0x02;
	//	sLogString.Format(_T("CHA_GetAuditData: CH句柄无效，设备未正确连接。"));
	//	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	//	return CHTRS_RES_FAILED;
	//}
	////获取设备状态
	//errCode = m_OCASDev.iGetDevStatus(&p_psCASStatus, &p_psCoinInfo, l_s);
	//if (errCode != CHTRS_RES_OK || l_s[0].iLogicCode != CHTRS_RES_OK)
	//{
	//	errCode = CHTRS_RES_FAILED;
	//}
	//else
	//{
	//	//cas006有两个大Hopper，加币Hopper；两个虚拟Hopper，虚拟Hopper是循环Hopper。
	//	for (int i = 0; i < pCoinBoxInfo->uiCoinBoxNum; i++)
	//	{
	//		switch (i)
	//		{
	//		case 0:
	//			//加币HopperA
	//			pCoinBoxInfo->pCoinBoxValueInfo[0].uiBoxNo = 1;
	//			pCoinBoxInfo->pCoinBoxValueInfo[0].uiBoxType = 1;
	//			pCoinBoxInfo->pCoinBoxValueInfo[0].uiCoinValue = 100;
	//			pCoinBoxInfo->pCoinBoxValueInfo[0].uiCoinMaxNum = theCHA_INFO.GetCHAChangeBoxAFullCnt();
	//			pCoinBoxInfo->pCoinBoxValueInfo[0].uiCoinNum = p_psCoinInfo.iMHopper1Num;
	//			if (p_psCoinInfo.iMHopper1Num >= theCHA_INFO.GetCHAChangeBoxAFullCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[0].uiBoxStatus = 2;//已满
	//			else if (p_psCoinInfo.iMHopper1Num <= theCHA_INFO.GetCHAChangeBoxAEmptyCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[0].uiBoxStatus = 5;//将空
	//			else
	//				pCoinBoxInfo->pCoinBoxValueInfo[0].uiBoxStatus = 0;//正常
	//			break;
	//		case 1:
	//			//加币HopperB
	//			pCoinBoxInfo->pCoinBoxValueInfo[1].uiBoxNo = 2;
	//			pCoinBoxInfo->pCoinBoxValueInfo[1].uiBoxType = 1;
	//			pCoinBoxInfo->pCoinBoxValueInfo[1].uiCoinValue = 100;
	//			pCoinBoxInfo->pCoinBoxValueInfo[1].uiCoinMaxNum = theCHA_INFO.GetCHAChangeBoxBFullCnt();
	//			pCoinBoxInfo->pCoinBoxValueInfo[1].uiCoinNum = p_psCoinInfo.iMHopper2Num;
	//			if (p_psCoinInfo.iMHopper2Num >= theCHA_INFO.GetCHAChangeBoxBFullCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[1].uiBoxStatus = 2;//已满
	//			else if (p_psCoinInfo.iMHopper2Num <= theCHA_INFO.GetCHAChangeBoxBEmptyCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[1].uiBoxStatus = 5;//将空
	//			else
	//				pCoinBoxInfo->pCoinBoxValueInfo[1].uiBoxStatus = 0;//正常
	//			break;
	//		case 2:
	//			//暂存A
	//			pCoinBoxInfo->pCoinBoxValueInfo[2].uiBoxNo = 3;
	//			pCoinBoxInfo->pCoinBoxValueInfo[2].uiBoxType = 3;
	//			pCoinBoxInfo->pCoinBoxValueInfo[2].uiCoinValue = 100;
	//			pCoinBoxInfo->pCoinBoxValueInfo[2].uiCoinMaxNum = 255;
	//			pCoinBoxInfo->pCoinBoxValueInfo[2].uiCoinNum = p_psCoinInfo.byEscrow1Num;
	//			pCoinBoxInfo->pCoinBoxValueInfo[2].uiBoxStatus = 0;//正常
	//			break;
	//		case 3:
	//			//暂存B
	//			pCoinBoxInfo->pCoinBoxValueInfo[3].uiBoxNo = 4;
	//			pCoinBoxInfo->pCoinBoxValueInfo[3].uiBoxType = 3;
	//			pCoinBoxInfo->pCoinBoxValueInfo[3].uiCoinValue = 100;
	//			pCoinBoxInfo->pCoinBoxValueInfo[3].uiCoinMaxNum = 255;
	//			pCoinBoxInfo->pCoinBoxValueInfo[3].uiCoinNum = p_psCoinInfo.byEscrow2Num;
	//			pCoinBoxInfo->pCoinBoxValueInfo[3].uiBoxStatus = 0;//正常
	//			break;
	//		case 4:
	//			//循环HopperA
	//			pCoinBoxInfo->pCoinBoxValueInfo[4].uiBoxNo = 5;
	//			pCoinBoxInfo->pCoinBoxValueInfo[4].uiBoxType = 4;
	//			pCoinBoxInfo->pCoinBoxValueInfo[4].uiCoinValue = 100;
	//			pCoinBoxInfo->pCoinBoxValueInfo[4].uiCoinMaxNum = theCHA_INFO.GetCHAHopperAFullCnt();
	//			pCoinBoxInfo->pCoinBoxValueInfo[4].uiCoinNum = p_psCoinInfo.iSHopper1Num;
	//			if (p_psCoinInfo.iSHopper1Num >= theCHA_INFO.GetCHAHopperAFullCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[4].uiBoxStatus = 2;//已满
	//			else if (p_psCoinInfo.iSHopper1Num <= theCHA_INFO.GetCHAHopperAEmptyCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[4].uiBoxStatus = 5;//将空
	//			else
	//				pCoinBoxInfo->pCoinBoxValueInfo[4].uiBoxStatus = 0;//正常
	//			break;
	//		case 5:
	//			//循环HopperB
	//			pCoinBoxInfo->pCoinBoxValueInfo[5].uiBoxNo = 6;
	//			pCoinBoxInfo->pCoinBoxValueInfo[5].uiBoxType = 4;
	//			pCoinBoxInfo->pCoinBoxValueInfo[5].uiCoinValue = 100;
	//			pCoinBoxInfo->pCoinBoxValueInfo[5].uiCoinMaxNum = theCHA_INFO.GetCHAHopperBFullCnt();
	//			pCoinBoxInfo->pCoinBoxValueInfo[5].uiCoinNum = p_psCoinInfo.iSHopper2Num;
	//			if (p_psCoinInfo.iSHopper2Num >= theCHA_INFO.GetCHAHopperBFullCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[5].uiBoxStatus = 2;//已满
	//			else if (p_psCoinInfo.iSHopper2Num <= theCHA_INFO.GetCHAHopperBEmptyCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[5].uiBoxStatus = 5;//将空
	//			else
	//				pCoinBoxInfo->pCoinBoxValueInfo[5].uiBoxStatus = 0;//正常
	//			break;
	//		case 6:
	//			//回收箱A
	//			pCoinBoxInfo->pCoinBoxValueInfo[6].uiBoxNo = 7;
	//			pCoinBoxInfo->pCoinBoxValueInfo[6].uiBoxType = 5;
	//			pCoinBoxInfo->pCoinBoxValueInfo[6].uiCoinValue = 100;
	//			pCoinBoxInfo->pCoinBoxValueInfo[6].uiCoinMaxNum = theCHA_INFO.GetCHACoinCaseACoinFullCnt();
	//			pCoinBoxInfo->pCoinBoxValueInfo[6].uiCoinNum = p_psCoinInfo.iCoincase1Coin1;
	//			if (p_psCoinInfo.iCoincase1Coin1 >= theCHA_INFO.GetCHACoinCaseACoinFullCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[6].uiBoxStatus = 2;//已满
	//			else
	//				pCoinBoxInfo->pCoinBoxValueInfo[6].uiBoxStatus = 0;//正常
	//			break;
	//		case 7:
	//			//回收箱B
	//			pCoinBoxInfo->pCoinBoxValueInfo[7].uiBoxNo = 8;
	//			pCoinBoxInfo->pCoinBoxValueInfo[7].uiBoxType = 5;
	//			pCoinBoxInfo->pCoinBoxValueInfo[7].uiCoinValue = 100;
	//			pCoinBoxInfo->pCoinBoxValueInfo[7].uiCoinMaxNum = theCHA_INFO.GetCHACoinCaseBCoinFullCnt();
	//			pCoinBoxInfo->pCoinBoxValueInfo[7].uiCoinNum = p_psCoinInfo.iCoincase2Coin1;
	//			if (p_psCoinInfo.iCoincase2Coin1 >= theCHA_INFO.GetCHACoinCaseBCoinFullCnt())
	//				pCoinBoxInfo->pCoinBoxValueInfo[7].uiBoxStatus = 2;//已满
	//			else
	//				pCoinBoxInfo->pCoinBoxValueInfo[7].uiBoxStatus = 0;//正常
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	//CHA_SetCHADevReturn(errCode, l_s, pDevStatus);
	//sLogString.Format(_T("iGetDevStatus: ReturnCode = 0x%02x"), errCode);
	//LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
	//return errCode;
}
// 关闭通讯
int CHA_CloseComm(tCHADevReturn * pDevStatus)
{
	if (pDevStatus == NULL)
		return CHTRS_RES_FAILED;

	CString sLogString(_T(""));

	sLogString.Format(_T("CHA_CloseComm: "));
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	DWORD errCode = CHTRS_RES_OK;
	if (m_hCH == NULL)
	{
		pDevStatus->uiProviderId = 0x04;
		pDevStatus->uiModuleType = 0x04;
		pDevStatus->uiType = 0x02;
		sLogString.Format(_T("CHA_CloseComm: CH句柄无效，设备未正确连接。"));
		LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);
		return CHTRS_RES_FAILED;
	}
	//关闭通讯
	errCode = m_OCASDev.iCloseComm();

	pDevStatus->uiProviderId = 0x04;
	pDevStatus->uiModuleType = 0x04;
	if (errCode != CHTRS_RES_OK)
		pDevStatus->uiType = 0x02;
	else
		pDevStatus->uiType = CHTRS_RES_OK;
	pDevStatus->uiErrorType[0] = errCode;
	pDevStatus->uiErrorCode[0] = errCode;
	sLogString.Format(_T("iCloseComm: ReturnCode = 0x%02x"), errCode);
	LogApi.WriteLog(_T(""), CString(__FUNCTION__), __LINE__, sLogString);

	LogApi.CloseLog();
	return errCode;
}
