#pragma once
#include "xfscim.h"
#include "XFSCDM.H"
#include "XFSADMIN.H"
#include "BNCApi.h"
#include "AFCLogApi.h"
#define LOGICALNAME_CDM			 _T("FJSERV_G60CDM")
#define LOGICALNAME_CIM			 _T("FJSERV_G60CIM")



typedef enum _enum_bnc_itype
{
	BNC_ITYPE_NO_ERROR = 0x00,
	BNC_ITYPE_ALARM = 0x01,
	BNC_ITYPE_FAULT = 0x02,

}ENUM_BNC_ITYPES;
typedef enum _enum_bnc_returncode
{
	BNC_RETURN_NO_ERROR = 0x00,
	BNC_RETURN_FAULT = 0x01,
}ENUM_BNC_RETURNCODE;
typedef enum _enum_bncblankface
{
	BNC_FACE_CNY1 = 100,
	BNC_FACE_CNY5 = 500,
	BNC_FACE_CNY10 = 1000,
	BNC_FACE_CNY20 = 2000,
	BNC_FACE_CNY50 = 5000,
	BNC_FACE_CNY100 = 10000,
}ENUM_BNC_BLANKFACE;
class CBNCCommands
{
public:
	CBNCCommands();
	~CBNCCommands();

public:
	long m_BrhVersion;
	bool m_IsOpen;
	WFSCIMNOTENUMBERLIST m_lpCashInNoteList;
	// ��������
	long Open(long lBrhVersion);								// ��
	long Close();												// �ر�
	long Reset();												// ��λ
	long GetStatus(WFSCIMSTATUS& status);						// ��ȡ״̬		
	long Cancel();												// ȡ����ǰ���첽������ȡ���ȴ��û�ȡ�߳�Ʊ����ʹ�ô������Ҫʹ��CancelWaitingCashTaken��

	long Empty();												// ���ѭ���������ֽ�Ҳ�����,ѹ����Ǯ��
   // ��ȡ�ֽ�Ԫ��Ϣ�����ں���ӿ���Ҫ���õ�Ǯ����Ϣ�������ڳ�ʼ������Ҫ����һ�θýӿ��Ի��Ǯ����Ϣ
	long QueryCimCashUnit(LPWFSCIMCASHINFO lpcashUnit);
	long QueryCdmCashUnit(LPWFSCDMCUINFO lpcashUnit);

	// ֽ�ҽ���
	long CancelWaitingCashTaken();								// ȡ���ȴ��û�ȡ�߳�Ʊ
	long CashInStart();											// ��ʼ���ճ�Ʊ
	long CashIn(WFSCIMNOTENUMBERLIST& CashInNoteList, int nTimeOut = 300000);						// ���ܳ�Ʊ���ƶ����ݴ�
	long CashInRollback();										// �˳����ν��ܵ����г�Ʊ	
	long CashInEnd(WFSCIMCASHINFO& lpCashInfo);					// �������ܳ�Ʊ			
	long Eject();												// �˳������ڳ�Ʊδʶ��
	long Refill(long lCount);
	// ֽ������
	long Dispense(long cycBox1, long cycBox2, long cycBox3, long cycBox4, WFSCDMDENOMINATION& lpDenomination);		// ��������
	long Present();												// ��ʼ�ֽ�����
	long Retract();

	// �ֽ�Ԫ������������
	long ConfigureCashUnit();
	long UpdateCashUnit();										// �����ֽ�Ԫ
	long ReplaceCashUnit();
	long CheckCashUnit(LPWFSCIMCASHINFO lpcashUnit);

	long UpdateDenominations(USHORT* usNotesId);									// ������ֵ
	long ClearCollectionUnitCount();							// ��ջ��������
   //// ������ֵ��Ϣ
	void GetEmptyExcResult(WFSRESULT& stWfsResult);
private:
	bool m_bXfsStartup;
	bool m_bXfsCleanUp;
	//CDM
	static HSERVICE gCDMService;
	//CIM
	static HSERVICE gCIMService;

	long xfs_cleanup();
	long xfs_startup();
	HRESULT xfs_Open(LPCTSTR lpszLogicalName, HSERVICE& hService, LPCTSTR lpszServiceClass, DWORD dwTimeOut = 0, long lBrhVer = 0);
	HRESULT xfs_Close(HSERVICE& hService);
	HRESULT xfs_Rigister(HSERVICE hService);
	HRESULT xfs_Execute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT* lppResult);
	HRESULT xfs_GetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT* lppResult);
	HRESULT xfs_Cancel(HSERVICE hService);
	void	SaveCashInNoteList(WFSCIMNOTENUMBERLIST& CashInNoteList, LPWFSCIMNOTENUMBERLIST lpNoteList);

private:
	LPWFSRESULT m_lpCUInfoWFSResult;
	LPWFSRESULT m_lpCount;
	bool m_bOpenAgain;

public:
	tBncCashInfo m_psCashInfo;
	tBncEnCashInfo m_cashIntoInfo;
	void BNC_SetAcceptFlag(bool flag);
	bool BNC_GetAcceptFlag();
	void BNC_SetCashInFlag(bool flag);
	bool BNC_GetCashInFlag();
	int GetCashInfoResponse(tBncCashInfo* p_psCashInfo);
	int GetEnCashInfoResponse(tBncEnCashInfo* cashInfo);
	bool GetIsExecute();  //��ȡ�Ƿ����ִ�������������Ǯ�����ٻ�ȥ
private:
	bool m_IsAccepting;   //����Ϊ��ֹ����cashinstart
};

// ���������NoteIDת��Ϊ����λ��
long NoteID2Amount(USHORT usNoteID);