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
	// 常规命令
	long Open(long lBrhVersion);								// 打开
	long Close();												// 关闭
	long Reset();												// 复位
	long GetStatus(WFSCIMSTATUS& status);						// 获取状态		
	long Cancel();												// 取消当前的异步操作（取消等待用户取走钞票不能使用此命令，需要使用CancelWaitingCashTaken）

	long Empty();												// 清空循环找零箱或纸币补充箱,压钞到钱箱
   // 获取现金单元信息，由于后面接口需要用用到钱箱信息，所以在初始化后需要调用一次该接口以获得钱箱信息
	long QueryCimCashUnit(LPWFSCIMCASHINFO lpcashUnit);
	long QueryCdmCashUnit(LPWFSCDMCUINFO lpcashUnit);

	// 纸币接收
	long CancelWaitingCashTaken();								// 取消等待用户取走钞票
	long CashInStart();											// 开始接收钞票
	long CashIn(WFSCIMNOTENUMBERLIST& CashInNoteList, int nTimeOut = 300000);						// 接受钞票，移动到暂存
	long CashInRollback();										// 退出本次接受的所有钞票	
	long CashInEnd(WFSCIMCASHINFO& lpCashInfo);					// 结束接受钞票			
	long Eject();												// 退钞（用于钞票未识别）
	long Refill(long lCount);
	// 纸币找零
	long Dispense(long cycBox1, long cycBox2, long cycBox3, long cycBox4, WFSCDMDENOMINATION& lpDenomination);		// 找零请求
	long Present();												// 开始现金找零
	long Retract();

	// 现金单元（包含数量）
	long ConfigureCashUnit();
	long UpdateCashUnit();										// 更新现金单元
	long ReplaceCashUnit();
	long CheckCashUnit(LPWFSCIMCASHINFO lpcashUnit);

	long UpdateDenominations(USHORT* usNotesId);									// 更新面值
	long ClearCollectionUnitCount();							// 清空回收箱计数
   //// 箱子面值信息
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
	bool GetIsExecute();  //获取是否可以执行其他命令，避免钱出来再回去
private:
	bool m_IsAccepting;   //此锁为防止两个cashinstart
};

// 根据人民币NoteID转换为金额，单位分
long NoteID2Amount(USHORT usNoteID);