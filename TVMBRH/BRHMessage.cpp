#include "StdAfx.h"
#include "BRHMessage.h"
//#include "SysInfo.h"
//#include "DCR4000Comm.h"
//#include "MaintenanceInfo.h"
#include "BRHException.h"
#include "BRHHardwareException.h"
bool isAccepting = false;
bool isStopAccept = false;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void  BRH_SetStopAcceptFlag(bool flag)
{
	isStopAccept = flag;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      (i)LPBRH_RSP_OPEN     RSPOpenReader

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHOpen::CBRHOpen(int port, int BaudRate, CString logPath, CString logName):CBRHCommands()
{
	m_port = port;
	m_BaudRate =BaudRate;
	m_logName = logName;
	m_logPath = logPath;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHOpen::~CBRHOpen(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHOpen::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHOpen::ExecuteCommand(void)
{
	m_logPath = m_logPath.TrimRight(_T("\\"))+ _T("\\");
	long lCompleteCode = BNC_open(m_port,m_BaudRate,m_logPath, m_logName);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHClose::CBRHClose():CBRHCommands()
{						   
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHClose::~CBRHClose(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHClose::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHClose::ExecuteCommand(void)
{
	long lCompleteCode = BNC_close();
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHReset::CBRHReset(int iMode, int iRetryTimes, tBncInitNumInfo* pNumInfo,tBncDevReturn* p_psStatus):CBRHCommands()
{
	m_iMode = iMode;
	m_iRetryTimes = iRetryTimes;
	//m_pNumInfo = pNumInfo;
	
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHReset::~CBRHReset(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHReset::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHReset::ExecuteCommand()
{
	long lCompleteCode = BNC_Reset(m_iMode,m_iRetryTimes,&m_pNumInfo,&m_psStatus);
	OnComplete(lCompleteCode);
	BRH_SetAcceptFlag(false);
	return lCompleteCode;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHReboot::CBRHReboot():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHReboot::~CBRHReboot(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHReboot::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHReboot::ExecuteCommand(void)
{
	return SP_SUCCESS;

	//long lCompleteCode = Reboot();
	//OnComplete(lCompleteCode);
	//return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHGetStatus::CBRHGetStatus():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHGetStatus::~CBRHGetStatus(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHGetStatus::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHGetStatus::ExecuteCommand()
{
	tBncDevReturn  p_psStatus;
	long lCompleteCode = BNC_GetStatus(&p_psStatus);
	// T_XfsCdrStatus结构与BRH_RSP_GET_STATUS结构实际定义是相同的。
	memcpy(&m_status, &p_psStatus, sizeof(tBncDevReturn));
	OnComplete(lCompleteCode);
	return lCompleteCode;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)BRH_RSP_GET_STATUS* status    BRH状态     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHGetStatus::GetBRHResponse(tBncDevReturn* status)
{
	try {
		if(status == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			memcpy(status, &m_status, sizeof(tBncDevReturn));
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHGetSystemStatus::CBRHGetSystemStatus():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHGetSystemStatus::~CBRHGetSystemStatus(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHGetSystemStatus::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHGetSystemStatus::ExecuteCommand()
{
	long lCompleteCode = BNC_GetSysDevStatus(&m_status);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)BRH_RSP_GET_SYSTEM_STATUS* status    BRH状态     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHGetSystemStatus::GetBRHResponse(tBncSysDevStatus* status)
{
	try {
		if(status == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			memcpy(status, &m_status, sizeof(tBncSysDevStatus));
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCancel::CBRHCancel():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCancel::~CBRHCancel(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCancel::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCancel::ExecuteCommand()
{
	tBncDevReturn p_psStatus;
	long lCompleteCode = BNC_Cancel(&p_psStatus);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHEmpty::CBRHEmpty(char* pcuName, BOOL toFloat):CBRHCommands()
{
	memset(m_pcuName,0, sizeof(m_pcuName));
	strcpy(m_pcuName, pcuName);
	m_toFloat = toFloat;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHEmpty::~CBRHEmpty(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHEmpty::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHEmpty::ExecuteCommand(void)
{
	long lCompleteCode = BNC_Empty(&m_result);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      取得反馈结果

@param      无

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
void CBRHEmpty::GetResponse(tBncChangeNum* result){
	if(NULL != result){
		*result = m_result;
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHReject::CBRHReject():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHReject::~CBRHReject(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHReject::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHReject::ExecuteCommand(void)
{
	return SP_SUCCESS;

	//long lCompleteCode = Reject(&m_amount);
	//OnComplete(lCompleteCode);
	//return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)long* amount    BRH接受钞票金额     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHReject::GetBRHResponse(UINT32* amount)
{
	try {
		if(amount == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			*amount = m_amount;
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHSelfTest::CBRHSelfTest():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHSelfTest::~CBRHSelfTest(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHSelfTest::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHSelfTest::ExecuteCommand(void)
{
	return SP_SUCCESS;

	//long lCompleteCode = SelfTest();
	//OnComplete(lCompleteCode);
	//return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHPark::CBRHPark():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHPark::~CBRHPark(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHPark::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHPark::ExecuteCommand(void)
{
	return SP_SUCCESS;

	//long lCompleteCode = Park();
	//OnComplete(lCompleteCode);
	//return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCancelWaitingCashTaken::CBRHCancelWaitingCashTaken():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCancelWaitingCashTaken::~CBRHCancelWaitingCashTaken(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCancelWaitingCashTaken::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCancelWaitingCashTaken::ExecuteCommand(void)
{
	return SP_SUCCESS;

	//long lCompleteCode = CancelWaitingCashTaken();
	//OnComplete(lCompleteCode);
	//return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInStart::CBRHCashInStart():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInStart::~CBRHCashInStart(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashInStart::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashInStart::ExecuteCommand()
{
	long lCompleteCode = BNC_Start(&m_psStatus);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashIn::CBRHCashIn():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashIn::~CBRHCashIn(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashIn::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashIn::ExecuteCommand()
{
	BYTE operate;
	long lCompleteCode = BNC_GetCashInfo(&m_CashInfo,operate,&m_Return);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)long* amount    BRH接受钞票金额     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHCashIn::GetBRHResponse(tBncCashInfo *p_psCashInfo,tBncDevReturn *p_psStatus)
{
	try {
		if(p_psCashInfo == NULL || p_psStatus == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			memcpy(p_psCashInfo,&m_CashInfo,sizeof(tBncCashInfo));
			memcpy(p_psStatus,&m_Return,sizeof(tBncDevReturn));
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInRollback::CBRHCashInRollback():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInRollback::~CBRHCashInRollback(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashInRollback::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashInRollback::ExecuteCommand()
{
	tBncDevReturn p_psStatus;
	long lCompleteCode = BNC_Refund(&p_psStatus);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)long* amount    BRH退出本次接受的所有钞票     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHCashInRollback::GetBRHResponse(UINT32* amount)
{
	try {
		if(amount == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			*amount = m_amount;
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInEnd::CBRHCashInEnd():CBRHCommands()
{
	memset(&m_cashIntoInfo,0x00,sizeof(m_cashIntoInfo));
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInEnd::~CBRHCashInEnd(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashInEnd::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashInEnd::ExecuteCommand()
{
	tBncDevReturn  p_psStatus;

	long lCompleteCode = BNC_Stop(&m_cashIntoInfo,&p_psStatus);

	OnComplete(lCompleteCode);
	BRH_SetAcceptFlag(false);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)long* amount    BRH退出本次接受的所有钞票     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHCashInEnd::GetBRHResponse(tBncEnCashInfo* intoInfo)
{
	try {
		if(intoInfo == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			*intoInfo = m_cashIntoInfo;
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHEject::CBRHEject():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHEject::~CBRHEject(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHEject::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHEject::ExecuteCommand()
{
	tBncDevReturn *p_psStatus;
	long lCompleteCode = BNC_Refund(p_psStatus);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)long* amount    BRH退出本次接受的所有钞票     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHEject::GetBRHResponse(UINT32* amount)
{
	try {
		if(amount == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			*amount = m_amount;
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHDispenseRequest::CBRHDispenseRequest(tBncChangeNum *pChangeNum, tBncDevReturn *pDevStatus):CBRHCommands()
{
	memcpy(&m_pChangeNum, pChangeNum, sizeof(tBncChangeNum));
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHDispenseRequest::~CBRHDispenseRequest(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHDispenseRequest::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHDispenseRequest::ExecuteCommand()
{
	tBncDevReturn *pDevStatus;
	long lCompleteCode = BNC_ChangeBill(&m_pChangeNum,pDevStatus);

	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      获取找零详细信息

@param      无

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
void CBRHDispenseRequest::GetResponse(CHANGE_RESULT* result){
	if(NULL != result){
		*result = m_changeResult;
	}
	else{
		//throw CInnerException(CInnerException::MODULE_ID,CInnerException::OTHER_ERR,_T(""));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHRetract::CBRHRetract():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHRetract::~CBRHRetract(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHRetract::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHRetract::ExecuteCommand()
{
	tBncDevReturn p_psStatus;
	long lCompleteCode = BNC_Cancel(&p_psStatus);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)long* amount    BRH接受钞票金额     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHRetract::GetBRHResponse(UINT32* amount)
{
	try {
		if(amount == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			*amount = m_amount;
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHQueryCashUnit::CBRHQueryCashUnit():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHQueryCashUnit::~CBRHQueryCashUnit(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHQueryCashUnit::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHQueryCashUnit::ExecuteCommand()
{
	tBncBillBoxInfo pBillBoxInfo;
	tBncDevReturn pDevStatus;
	//m_QueryCashUnit.logicalCashUnitList.maxSize = NBMAXLCU;
	//m_QueryCashUnit.physicalCashUnitList.maxSize =  NBMAXPCU;
	long lCompleteCode = BNC_GetBillBoxInfo(&pBillBoxInfo,&pDevStatus);
	//if(0 == lCompleteCode){
	//	for(int i = 0;i < m_QueryCashUnit.logicalCashUnitList.size;i++){
	//		T_XfsLogicalCashUnit LogicalCashUnit = m_QueryCashUnit.logicalCashUnitList.items[i];
	//		CASH_BOX_INFO boxInfo;

	//		boxInfo.cashType = LogicalCashUnit.cashType;
	//		boxInfo.logicalNumber = LogicalCashUnit.number;
	//		boxInfo.TotalCount    = LogicalCashUnit.count;
	//		memcpy(boxInfo.PhysicalName,LogicalCashUnit.physicalCashUnit->name,SIZE_OF_PHYSICAL_NAME);

	//		mapCashBoxInfo[boxInfo.logicalNumber] = boxInfo;
	//	}
	//}
	memcpy(&m_QueryCashUnit, &pBillBoxInfo, sizeof(tBncBillBoxInfo));
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)long* amount    BRH接受钞票金额     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHQueryCashUnit::GetBRHResponse(tBncBillBoxInfo* queryCashUnit)
{
	try {
		if(queryCashUnit == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			memcpy(queryCashUnit, &m_QueryCashUnit, sizeof(tBncBillBoxInfo));
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHUpdateCashUnit::CBRHUpdateCashUnit(UINT uiSlotID,tBncBillBoxInfo *pBillBoxInfo):CBRHCommands()
{
	m_uiSlotID = uiSlotID;
	m_pBillBoxInfo = pBillBoxInfo;
	//memcpy(&m_UpdateCashUnit, updateCashUnit, sizeof(BRH_CMD_UPDATE_CASHUNIT));
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHUpdateCashUnit::~CBRHUpdateCashUnit(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHUpdateCashUnit::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHUpdateCashUnit::ExecuteCommand()
{

	tBncDevReturn *pDevStatus;
	long lCompleteCode = BNC_SetBillBoxInfo(m_uiSlotID, m_pBillBoxInfo, pDevStatus);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHQueryDenominations::CBRHQueryDenominations(tBncSetInhibitList *p_psBuyTicketSetInhibitList, 
												tBncSetInhibitList *p_psRechargeSetInhibitList):CBRHCommands()
{
	m_psBuyTicketSetInhibitList = p_psBuyTicketSetInhibitList;
	m_psRechargeSetInhibitList = p_psRechargeSetInhibitList;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHQueryDenominations::~CBRHQueryDenominations(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHQueryDenominations::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHQueryDenominations::ExecuteCommand()
{
	//m_QueryDenominations.maxSize = MAX_NR_OF_DENOMINATION;
	long lCompleteCode = BNC_SetPrevalue(m_psBuyTicketSetInhibitList, m_psRechargeSetInhibitList, m_psStatus);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      得到BRH返回信息

@param      (o)long* amount    BRH接受钞票金额     

@retval     void     

@exception  CSysException
*/
//////////////////////////////////////////////////////////////////////////
void CBRHQueryDenominations::GetBRHResponse(tBncSetInhibitList *BuyTicketSetInhibitList, 
											tBncSetInhibitList *RechargeSetInhibitList,
											tBncDevReturn * Status)
{
	try {
		if(RechargeSetInhibitList == NULL){
			//throw CRWException(m_RWID.rwtype,CRWException::FUNC_PARAM_ERR,_T(__FILE__),__LINE__);
		}
		else{
			memcpy(BuyTicketSetInhibitList, &m_psBuyTicketSetInhibitList, sizeof(tBncSetInhibitList));
			memcpy(Status, &m_psStatus, sizeof(tBncDevReturn));
			memcpy(RechargeSetInhibitList, &m_psRechargeSetInhibitList, sizeof(tBncSetInhibitList));
		}
	}
	//catch(CSysException&) {
	//	throw;
	//}
	catch(...) {
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("内存空间赋值错误！"));
	}
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      构造函数

@param      无  

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHUpdateDenominations::CBRHUpdateDenominations(tBncSetInhibitList *p_psBuyTicketSetInhibitList, tBncSetInhibitList *p_psRechargeSetInhibitList):CBRHCommands()
{
	memcpy(&m_psBuyTicketSetInhibitList, p_psBuyTicketSetInhibitList, sizeof(tBncSetInhibitList));
	memcpy(&m_psRechargeSetInhibitList, p_psRechargeSetInhibitList, sizeof(tBncSetInhibitList));

}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHUpdateDenominations::~CBRHUpdateDenominations(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      判断命令是否有效

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHUpdateDenominations::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      执行命令

@param      无         

@retval     无     

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHUpdateDenominations::ExecuteCommand()
{
	tBncDevReturn  p_psStatus;
	long lCompleteCode = BNC_SetPrevalue(&m_psBuyTicketSetInhibitList, m_psRechargeSetInhibitList, &p_psStatus);
	OnComplete(lCompleteCode);
	return lCompleteCode;
}

void  BRH_SetAcceptFlag(bool flag)
{
	isAccepting = flag;
}
////////////////////////////////////////////////////////////////////////////
///**
// @brief		构造函数
//
// @param		BH_FACEVALUE_TABLE& bhTable
//
// @retval	无  
//
// @exception	无
//*/
//////////////////////////////////////////////////////////////////////////
CBRHOpenAndValidate::CBRHOpenAndValidate(tBncSetInhibitList& brhTable,long lTranType):CBRHCommands()
{
	//done_phase = DONE_P()SE_READY;
	//memcpy(&m_BuyTicketSetInhibitList,&brhTable,sizeof(tBncSetInhibitList));
	if (lTranType == 0)
	{
		m_BuyTicketSetInhibitList.iNumOfItems = brhTable.iNumOfItems;
		m_BuyTicketSetInhibitList.psBncCashInfo = new tBncSetInhibitItem[brhTable.iNumOfItems];
		memcpy(m_BuyTicketSetInhibitList.psBncCashInfo,brhTable.psBncCashInfo,m_BuyTicketSetInhibitList.iNumOfItems*sizeof(tBncSetInhibitItem));
	}
	else
	{
		m_RechargeSetInhibitList.iNumOfItems = brhTable.iNumOfItems;
		m_RechargeSetInhibitList.psBncCashInfo = new tBncSetInhibitItem[brhTable.iNumOfItems];
		memcpy(m_RechargeSetInhibitList.psBncCashInfo,brhTable.psBncCashInfo,m_RechargeSetInhibitList.iNumOfItems*sizeof(tBncSetInhibitItem));

	}
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief		构造函数

 @param		无

 @retval	无  

 @exception	无
*/
//////////////////////////////////////////////////////////////////////////
CBRHOpenAndValidate::CBRHOpenAndValidate():CBRHCommands()
{
	//done_phase CBRHCommandsHASE_READY;
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief		析构函数

 @param		无

 @retval	无  

 @exception	无
*/
//////////////////////////////////////////////////////////////////////////
CBRHOpenAndValidate::~CBRHOpenAndValidate()
{
	if (m_BuyTicketSetInhibitList.psBncCashInfo)
	{
		delete[] m_BuyTicketSetInhibitList.psBncCashInfo;
		m_BuyTicketSetInhibitList.psBncCashInfo = NULL;
	}
	if (m_RechargeSetInhibitList.psBncCashInfo)
	{
		delete[] m_BuyTicketSetInhibitList.psBncCashInfo;
		m_BuyTicketSetInhibitList.psBncCashInfo = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief		执行命令

 @param		无

 @retval	long  0 : 成功	非0 : 失败

 @exception	无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHOpenAndValidate::ExecuteCommand(void)
{
	long lRet = 1;
	lRet = OpenAndValidateFunction();
	this->OnComplete(lRet);
	return lRet;
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief		取得执行结果

 @param		(o)BH_STATUS *res	纸币接收模块状态解析结构

 @retval	long  0 : 成功	非0 : 失败

 @exception	无
*/
////////////////////////////////////////////////////////////////////////
long CBRHOpenAndValidate::GetResponse(BRH_STATUS* rsp)
{
	try {
		*rsp = m_bhStatus;
	}
	catch (...){
		return CBRHException::ERR_OTHERS;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief		MEI 取得执行结果

 @param		(o)BH_STATUS *res	纸币接收模块状态解析结构

 @retval	long  0 : 成功	非0 : 失败

 @exception	无
*/
////////////////////////////////////////////////////////////////////////
long CBRHOpenAndValidate::GetResponse(tBncCashInfo* rsp)
{
	try {
		*rsp = m_feedback;
	}
	catch (...){
		return CBRHException::ERR_OTHERS;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief		向纸币接收模块请求状态

 @param		无

 @retval	long  0 : 成功	非0 : 失败

 @exception	无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHOpenAndValidate::OpenAndValidateFunction()
{
	long errCode = 0;


	// 更新可接收面额信息
	CBRHUpdateDenominations setDenominations(&m_BuyTicketSetInhibitList, &m_RechargeSetInhibitList);
	errCode = setDenominations.ExecuteCommand();
	if(errCode != BNC_NO_ERROR){
		return errCode;
	}

	// 20180120,lichao:由于多线程，防止停止接收命令再开始接收命令之前被处理。
	if(isStopAccept){
		return CBRHHardwareException::ERR_CANCELLED;
	}

	if (!isAccepting){
		BRH_SetAcceptFlag(true);
		// 开始接收纸币

		CBRHCashInStart startCmd;
		errCode = startCmd.ExecuteCommand();
		if (errCode != BNC_NO_ERROR){
			BRH_SetAcceptFlag(false);
			return errCode;
		}
	}

	// 接收纸币
	CBRHCashIn cashInCmd;
	errCode = cashInCmd.ExecuteCommand();
	if (errCode == BNC_NO_ERROR){
		cashInCmd.GetBRHResponse(&m_feedback,&m_return);
		BankNoteAndCoinType_t tmpType;
		switch (m_feedback.psBncCashInfo[m_feedback.iNumOfItems-1].iValue) {
		case 100: 
			tmpType = Banknote1Yuan;
			break;
		case 500: 
			tmpType = Banknote5Yuan;
			break;
		case 1000:
			tmpType = Banknote10Yuan;
			break;
		case 2000: 
			tmpType = Banknote20Yuan;
			break;
		case 5000: 
			tmpType = Banknote50Yuan;
			break;
		case 10000: 
			tmpType = Banknote100Yuan;
			break;
		default: 
			tmpType = VALUE_UNKNOWN;
		}
		if(TRUE/*IsAcceptFaceValue(tmpType)*/){	// 如果是允许接收的面额
			m_bhStatus.bh_faceValue = tmpType;
			m_feedback.psBncCashInfo[m_feedback.iNumOfItems-1].iValue = tmpType;
			m_feedback.psBncCashInfo[m_feedback.iNumOfItems-1].iCount = 1;
			//return errCode;
		}
		else{
			CBRHCashInRollback refCmd;
			errCode = refCmd.ExecuteCommand();					// 退出当前接收的所有
			if (errCode==BNC_NO_ERROR){
				errCode = BNC_EJECT_SUCCESS;
			}
		}
	}
	if(isStopAccept){
		errCode = CBRHHardwareException::ERR_CANCELLED;
	}
	OnComplete(errCode);
	return errCode;
}

bool CBRHOpenAndValidate::IsAcceptFaceValue(BankNoteAndCoinType_t& thisFaceValue)
{
	return false;
}


//////////////////////////////////////////////////////////////////////////
/*
@brief      设置箱子面额信息构造函数

@param      BNR_MODULE_ID boxId,UINT faceValue

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHSetCashType::CBRHSetCashType(BNR_MODULE_ID boxId,UINT faceValue){
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      析构函数

@param      无

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHSetCashType::~CBRHSetCashType(){

}

//////////////////////////////////////////////////////////////////////////
/*
@brief      设置模块面额信息

@param      无

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHSetCashType::ExecuteCommand(){
	return SP_SUCCESS;

	//long lCompleteCode = SetCashType(m_boxId,&m_cashTypeInfo);
	//OnComplete(lCompleteCode);
	//return lCompleteCode;
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      

@param      BNR_MODULE_ID boxId,UINT faceValue

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHEncash::CBRHEncash(){

}

//////////////////////////////////////////////////////////////////////////
/*
@brief      析构函数

@param      无

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
CBRHEncash::~CBRHEncash(){

}

//////////////////////////////////////////////////////////////////////////
/*
@brief      

@param      无

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////
long CBRHEncash::ExecuteCommand(){
	return SP_SUCCESS;
}