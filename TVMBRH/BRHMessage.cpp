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
@brief      ���캯��

@param      (i)LPBRH_RSP_OPEN     RSPOpenReader

@retval     ��     

@exception  ��
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
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHOpen::~CBRHOpen(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHOpen::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHClose::CBRHClose():CBRHCommands()
{						   
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHClose::~CBRHClose(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHClose::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
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
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHReset::~CBRHReset(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHReset::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHReboot::CBRHReboot():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHReboot::~CBRHReboot(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHReboot::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHGetStatus::CBRHGetStatus():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHGetStatus::~CBRHGetStatus(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHGetStatus::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHGetStatus::ExecuteCommand()
{
	tBncDevReturn  p_psStatus;
	long lCompleteCode = BNC_GetStatus(&p_psStatus);
	// T_XfsCdrStatus�ṹ��BRH_RSP_GET_STATUS�ṹʵ�ʶ�������ͬ�ġ�
	memcpy(&m_status, &p_psStatus, sizeof(tBncDevReturn));
	OnComplete(lCompleteCode);
	return lCompleteCode;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �õ�BRH������Ϣ

@param      (o)BRH_RSP_GET_STATUS* status    BRH״̬     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHGetSystemStatus::CBRHGetSystemStatus():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHGetSystemStatus::~CBRHGetSystemStatus(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHGetSystemStatus::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      �õ�BRH������Ϣ

@param      (o)BRH_RSP_GET_SYSTEM_STATUS* status    BRH״̬     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCancel::CBRHCancel():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCancel::~CBRHCancel(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCancel::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
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
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHEmpty::~CBRHEmpty(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHEmpty::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ȡ�÷������

@param      ��

@retval     ��

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
void CBRHEmpty::GetResponse(tBncChangeNum* result){
	if(NULL != result){
		*result = m_result;
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHReject::CBRHReject():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHReject::~CBRHReject(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHReject::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      �õ�BRH������Ϣ

@param      (o)long* amount    BRH���ܳ�Ʊ���     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHSelfTest::CBRHSelfTest():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHSelfTest::~CBRHSelfTest(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHSelfTest::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHPark::CBRHPark():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHPark::~CBRHPark(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHPark::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCancelWaitingCashTaken::CBRHCancelWaitingCashTaken():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCancelWaitingCashTaken::~CBRHCancelWaitingCashTaken(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCancelWaitingCashTaken::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInStart::CBRHCashInStart():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInStart::~CBRHCashInStart(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashInStart::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashIn::CBRHCashIn():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashIn::~CBRHCashIn(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashIn::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      �õ�BRH������Ϣ

@param      (o)long* amount    BRH���ܳ�Ʊ���     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInRollback::CBRHCashInRollback():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInRollback::~CBRHCashInRollback(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashInRollback::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      �õ�BRH������Ϣ

@param      (o)long* amount    BRH�˳����ν��ܵ����г�Ʊ     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInEnd::CBRHCashInEnd():CBRHCommands()
{
	memset(&m_cashIntoInfo,0x00,sizeof(m_cashIntoInfo));
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHCashInEnd::~CBRHCashInEnd(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHCashInEnd::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      �õ�BRH������Ϣ

@param      (o)long* amount    BRH�˳����ν��ܵ����г�Ʊ     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHEject::CBRHEject():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHEject::~CBRHEject(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHEject::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      �õ�BRH������Ϣ

@param      (o)long* amount    BRH�˳����ν��ܵ����г�Ʊ     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHDispenseRequest::CBRHDispenseRequest(tBncChangeNum *pChangeNum, tBncDevReturn *pDevStatus):CBRHCommands()
{
	memcpy(&m_pChangeNum, pChangeNum, sizeof(tBncChangeNum));
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHDispenseRequest::~CBRHDispenseRequest(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHDispenseRequest::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ��ȡ������ϸ��Ϣ

@param      ��

@retval     ��

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHRetract::CBRHRetract():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHRetract::~CBRHRetract(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHRetract::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      �õ�BRH������Ϣ

@param      (o)long* amount    BRH���ܳ�Ʊ���     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHQueryCashUnit::CBRHQueryCashUnit():CBRHCommands()
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHQueryCashUnit::~CBRHQueryCashUnit(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHQueryCashUnit::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      �õ�BRH������Ϣ

@param      (o)long* amount    BRH���ܳ�Ʊ���     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
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
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHUpdateCashUnit::~CBRHUpdateCashUnit(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHUpdateCashUnit::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
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
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHQueryDenominations::~CBRHQueryDenominations(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHQueryDenominations::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
@brief      �õ�BRH������Ϣ

@param      (o)long* amount    BRH���ܳ�Ʊ���     

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
		//throw CRWException(m_RWID.rwtype,CRWException::OTHER_ERR,_T(__FILE__),__LINE__,_T("�ڴ�ռ丳ֵ����"));
	}
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��  

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHUpdateDenominations::CBRHUpdateDenominations(tBncSetInhibitList *p_psBuyTicketSetInhibitList, tBncSetInhibitList *p_psRechargeSetInhibitList):CBRHCommands()
{
	memcpy(&m_psBuyTicketSetInhibitList, p_psBuyTicketSetInhibitList, sizeof(tBncSetInhibitList));
	memcpy(&m_psRechargeSetInhibitList, p_psRechargeSetInhibitList, sizeof(tBncSetInhibitList));

}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHUpdateDenominations::~CBRHUpdateDenominations(void)
{
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      �ж������Ƿ���Ч

@param      ��         

@retval     ��     

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHUpdateDenominations::IsValidCommand()
{
	return SP_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��         

@retval     ��     

@exception  ��
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
// @brief		���캯��
//
// @param		BH_FACEVALUE_TABLE& bhTable
//
// @retval	��  
//
// @exception	��
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
 @brief		���캯��

 @param		��

 @retval	��  

 @exception	��
*/
//////////////////////////////////////////////////////////////////////////
CBRHOpenAndValidate::CBRHOpenAndValidate():CBRHCommands()
{
	//done_phase CBRHCommandsHASE_READY;
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief		��������

 @param		��

 @retval	��  

 @exception	��
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
 @brief		ִ������

 @param		��

 @retval	long  0 : �ɹ�	��0 : ʧ��

 @exception	��
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
 @brief		ȡ��ִ�н��

 @param		(o)BH_STATUS *res	ֽ�ҽ���ģ��״̬�����ṹ

 @retval	long  0 : �ɹ�	��0 : ʧ��

 @exception	��
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
 @brief		MEI ȡ��ִ�н��

 @param		(o)BH_STATUS *res	ֽ�ҽ���ģ��״̬�����ṹ

 @retval	long  0 : �ɹ�	��0 : ʧ��

 @exception	��
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
 @brief		��ֽ�ҽ���ģ������״̬

 @param		��

 @retval	long  0 : �ɹ�	��0 : ʧ��

 @exception	��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHOpenAndValidate::OpenAndValidateFunction()
{
	long errCode = 0;


	// ���¿ɽ��������Ϣ
	CBRHUpdateDenominations setDenominations(&m_BuyTicketSetInhibitList, &m_RechargeSetInhibitList);
	errCode = setDenominations.ExecuteCommand();
	if(errCode != BNC_NO_ERROR){
		return errCode;
	}

	// 20180120,lichao:���ڶ��̣߳���ֹֹͣ���������ٿ�ʼ��������֮ǰ������
	if(isStopAccept){
		return CBRHHardwareException::ERR_CANCELLED;
	}

	if (!isAccepting){
		BRH_SetAcceptFlag(true);
		// ��ʼ����ֽ��

		CBRHCashInStart startCmd;
		errCode = startCmd.ExecuteCommand();
		if (errCode != BNC_NO_ERROR){
			BRH_SetAcceptFlag(false);
			return errCode;
		}
	}

	// ����ֽ��
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
		if(TRUE/*IsAcceptFaceValue(tmpType)*/){	// �����������յ����
			m_bhStatus.bh_faceValue = tmpType;
			m_feedback.psBncCashInfo[m_feedback.iNumOfItems-1].iValue = tmpType;
			m_feedback.psBncCashInfo[m_feedback.iNumOfItems-1].iCount = 1;
			//return errCode;
		}
		else{
			CBRHCashInRollback refCmd;
			errCode = refCmd.ExecuteCommand();					// �˳���ǰ���յ�����
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
@brief      �������������Ϣ���캯��

@param      BNR_MODULE_ID boxId,UINT faceValue

@retval     ��

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHSetCashType::CBRHSetCashType(BNR_MODULE_ID boxId,UINT faceValue){
}

//////////////////////////////////////////////////////////////////////////
/*
@brief      ��������

@param      ��

@retval     ��

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHSetCashType::~CBRHSetCashType(){

}

//////////////////////////////////////////////////////////////////////////
/*
@brief      ����ģ�������Ϣ

@param      ��

@retval     ��

@exception  ��
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

@retval     ��

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHEncash::CBRHEncash(){

}

//////////////////////////////////////////////////////////////////////////
/*
@brief      ��������

@param      ��

@retval     ��

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
CBRHEncash::~CBRHEncash(){

}

//////////////////////////////////////////////////////////////////////////
/*
@brief      

@param      ��

@retval     ��

@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
long CBRHEncash::ExecuteCommand(){
	return SP_SUCCESS;
}