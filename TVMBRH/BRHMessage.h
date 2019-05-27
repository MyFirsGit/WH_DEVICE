#pragma once
#include "BRHExp.h"
#include "BRHDef.h"
#include "Command.h"
#include "BNCApi.h"

void  BRH_API BRH_SetStopAcceptFlag(bool flag);
void  BRH_API BRH_SetAcceptFlag(bool flag);


//////////////////////////ֽ��ѭ���豸����////////////////////////////////////////////////////////////
/** 
@brief   BRH������
*/
class BRH_API CBRHOpen :	public CCommand
{
public:
	CBRHOpen(int port, int BaudRate, CString logPath, CString logName);
	~CBRHOpen(void);
	long ExecuteCommand();
	long IsValidCommand();
private:
	int m_port;
	int m_BaudRate;
	CString m_logPath;
	CString m_logName;
};

/** 
@brief   BRH�ر�����
*/
class BRH_API CBRHClose :	public CCommand
{
public:
	CBRHClose();
	~CBRHClose(void);
	long IsValidCommand();
	long ExecuteCommand();
};

/** 
@brief   BRH��λ����
*/
class BRH_API CBRHReset :	public CCommand
{
public:
	CBRHReset(int iMode, int iRetryTimes, tBncInitNumInfo* pNumInfo,tBncDevReturn* p_psStatus);
	~CBRHReset(void);
	long ExecuteCommand();
	long IsValidCommand();
private:
	int m_iMode;
	int m_iRetryTimes;
	tBncInitNumInfo m_pNumInfo;
	tBncDevReturn m_psStatus;
};

/** 
@brief   BRH��������
*/
class BRH_API CBRHReboot :	public CCommand
{
public:
	CBRHReboot();
	~CBRHReboot(void);
	long ExecuteCommand();
	long IsValidCommand();
};

/** 
@brief   BRH��ȡ״̬����
*/
class BRH_API CBRHGetStatus :	public CCommand
{
public:
	CBRHGetStatus();
	~CBRHGetStatus(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(tBncDevReturn* status);
private:
	tBncDevReturn m_status;
};

/** 
@brief   BRH��ȡ��ϸ״̬����
*/
class BRH_API CBRHGetSystemStatus :	public CCommand
{
public:
	CBRHGetSystemStatus();
	~CBRHGetSystemStatus(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(tBncSysDevStatus* status);
private:
	tBncSysDevStatus m_status;
};

/** 
@brief   BRHȡ����������
*/
class BRH_API CBRHCancel :	public CCommand
{
public:
	CBRHCancel();
	~CBRHCancel(void);
	long ExecuteCommand();
	long IsValidCommand();
};

/** 
@brief   BRH���ѭ��������򲹱�������
*/
class BRH_API CBRHEmpty :	public CCommand
{
public:
	CBRHEmpty(char* pcuName, BOOL toFloat);
	~CBRHEmpty(void);
	long ExecuteCommand();
	long IsValidCommand();

	void GetResponse(tBncChangeNum* result);
private:
	char m_pcuName[256];
	BOOL m_toFloat;
	tBncChangeNum m_result;
};

/** 
@brief   BRH����ݴ��еĳ�Ʊ��ѭ���������Ǯ������
*/
class BRH_API CBRHReject :	public CCommand
{
public:
	CBRHReject();
	~CBRHReject(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(UINT32* amount);
private:
	UINT32 m_amount;
};

/** 
@brief   BRH�Լ�
*/
class BRH_API CBRHSelfTest :	public CCommand
{
public:
	CBRHSelfTest();
	~CBRHSelfTest(void);
	long ExecuteCommand();
	long IsValidCommand();
};

/** 
@brief   BRHԤ������ģ�飬ʹ��ж��
*/
class BRH_API CBRHPark :	public CCommand
{
public:
	CBRHPark();
	~CBRHPark(void);
	long ExecuteCommand();
	long IsValidCommand();
};

/** 
@brief   BRHȡ���ȴ��û�ȡ�߳�Ʊ
*/
class BRH_API CBRHCancelWaitingCashTaken :	public CCommand
{
public:
	CBRHCancelWaitingCashTaken();
	~CBRHCancelWaitingCashTaken(void);
	long ExecuteCommand();
	long IsValidCommand();
};

/** 
@brief   BRH��ʼ���ճ�Ʊ
*/
class BRH_API CBRHCashInStart :	public CCommand
{
public:
	CBRHCashInStart();
	~CBRHCashInStart(void);
	long ExecuteCommand();
	long IsValidCommand();
private:
	tBncDevReturn m_psStatus;
};

/** 
@brief   BRH���ܳ�Ʊ���ƶ����ݴ�
*/
class BRH_API CBRHCashIn :	public CCommand
{
public:
	CBRHCashIn();
	~CBRHCashIn(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(tBncCashInfo *p_psCashInfo,tBncDevReturn *p_psStatus);
private:
	tBncCashInfo m_CashInfo;
	tBncDevReturn m_Return;
};

/** 
@brief   BRH�˳����ν��ܵ����г�Ʊ
*/
class BRH_API CBRHCashInRollback :	public CCommand
{
public:
	CBRHCashInRollback();
	~CBRHCashInRollback(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(UINT32* amount);
private:
	UINT32 m_amount;
};

/** 
@brief   BRH�������ܳ�Ʊ
*/
class BRH_API CBRHCashInEnd :	public CCommand 
{
public:
	CBRHCashInEnd();
	~CBRHCashInEnd(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(tBncEnCashInfo* intoInfo);
private:
	UINT32 m_amount;
	tBncEnCashInfo m_cashIntoInfo;
};

/** 
@brief   BRH�˳������ڳ�Ʊδʶ��
*/
class BRH_API CBRHEject :	public CCommand
{
public:
	CBRHEject();
	~CBRHEject(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(UINT32* amount);
private:
	UINT32 m_amount;
};

/** 
@brief   BRH��������
*/
class BRH_API CBRHDispenseRequest :	public CCommand
{
public:
	CBRHDispenseRequest(tBncChangeNum *pChangeNum, tBncDevReturn *pDevStatus);
	~CBRHDispenseRequest(void);
	long ExecuteCommand();
	long IsValidCommand();

	void GetResponse(CHANGE_RESULT* result);
private:
	tBncChangeNum m_pChangeNum;
	tBncDevReturn m_pDevStatus;
	CHANGE_RESULT	m_changeResult;
};



/** 
@brief   BRH��������ĳ�Ʊ
*/
class BRH_API CBRHRetract :	public CCommand
{
public:
	CBRHRetract();
	~CBRHRetract(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(UINT32* amount);
private:
	UINT32 m_amount;
};

/** 
@brief   BRH��ȡ�ֽ�Ԫ��Ϣ
*/
class BRH_API CBRHQueryCashUnit :	public CCommand
{
public:
	CBRHQueryCashUnit();
	~CBRHQueryCashUnit(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(tBncBillBoxInfo* queryCashUnit);
private:
	tBncBillBoxInfo m_QueryCashUnit;
};

/** 
@brief   BRH�����ֽ�Ԫ
*/
class BRH_API CBRHUpdateCashUnit :	public CCommand
{
public:
	CBRHUpdateCashUnit(UINT uiSlotID,tBncBillBoxInfo *pBillBoxInfo);
	~CBRHUpdateCashUnit(void);
	long ExecuteCommand();
	long IsValidCommand();
private:
	UINT m_uiSlotID;
	tBncBillBoxInfo* m_pBillBoxInfo;
};


/** 
@brief   BRH��ȡ��ֵ
*/
class BRH_API CBRHQueryDenominations :	public CCommand
{
public:
	CBRHQueryDenominations(tBncSetInhibitList *p_psBuyTicketSetInhibitList, tBncSetInhibitList *p_psRechargeSetInhibitList);

	~CBRHQueryDenominations(void);
	long ExecuteCommand();
	long IsValidCommand();
	void GetBRHResponse(tBncSetInhibitList *BuyTicketSetInhibitList, 
		tBncSetInhibitList *RechargeSetInhibitList,
		tBncDevReturn * Status);
private:
	//BRH_RSP_QUERY_DENOMINATIONS m_QueryDenominations;
	tBncSetInhibitList *m_psBuyTicketSetInhibitList;
	tBncSetInhibitList *m_psRechargeSetInhibitList;
	tBncDevReturn * m_psStatus;

};

/** 
@brief   BRH������ֵ
*/
class BRH_API CBRHUpdateDenominations :	public CCommand
{
public:
	CBRHUpdateDenominations(tBncSetInhibitList *p_psBuyTicketSetInhibitList, tBncSetInhibitList *p_psRechargeSetInhibitList);
	~CBRHUpdateDenominations(void);
	long ExecuteCommand();
	long IsValidCommand();
private:
	tBncSetInhibitList m_psBuyTicketSetInhibitList;
	tBncSetInhibitList *m_psRechargeSetInhibitList;
};


/**
 @brief	���������ȴ�Ͷ��ʶ��V1+ST��
*/
class BRH_API CBRHOpenAndValidate : public CCommand
{
public:
	CBRHOpenAndValidate();
	CBRHOpenAndValidate(tBncSetInhibitList& brhTable,long lTranType = 0);//lTranType:0 ��Ʊ ��0����ֵ
	~CBRHOpenAndValidate();
public:
	long ExecuteCommand();	
	long GetResponse(BRH_STATUS*);
	long GetResponse(tBncCashInfo*);
public:
	DWORD done_phase;				// ִ�н��
private:
	long OpenAndValidateFunction();
	long GetFace();
	bool IsAcceptFaceValue(BankNoteAndCoinType_t& thisFaceValue);
	BRH_STATUS m_bhStatus;
	tBncCashInfo m_feedback;
	tBncSetInhibitList m_BuyTicketSetInhibitList;
	tBncSetInhibitList m_RechargeSetInhibitList;
	tBncDevReturn m_return;
};

/*
 @brief �����������������Ϣ
*/
class BRH_API CBRHSetCashType : public CCommand
{
public:
	CBRHSetCashType(BNR_MODULE_ID boxId,UINT faceValue);
	~CBRHSetCashType();
public:
	long ExecuteCommand();
private:
	BNR_MODULE_ID	  m_boxId;
	UINT m_cashTypeInfo;
};

class BRH_API CBRHEncash : public CCommand
{
public:
	CBRHEncash();
	~CBRHEncash();
public:
	long ExecuteCommand();
private:

};