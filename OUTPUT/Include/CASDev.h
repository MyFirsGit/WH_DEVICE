// CASDev.h: interface for the OCASDev class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CASDEV_H__F07F2DC3_A28E_4199_9596_25F0F8C46765__INCLUDED_)
#define AFX_CASDEV_H__F07F2DC3_A28E_4199_9596_25F0F8C46765__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ODevBase.h"
#include "CASDevDef.h"
#include "CASDevStruct.h"

class AFX_EXT_CLASS OCASDev
{
public:
	OCASDev();
	virtual ~OCASDev();
	
public:	
	// 设置通信参数
	int iSetCommPara(tDevReturn* p_psrStatus);
	int	iSetCommParaEx(tDevReturn* p_psrStatus);
	
	// 交易命令
	// 初始化
	int iInit(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// 读模块状态
	int iGetDevStatus(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// 获取设备是否可用
	int iGetStatus(tDevReturn* p_psrStatus);

	// 获取设备能力
	int iGetDevCapability(UINT *p_puiCapability, UINT p_uiNumber);
	
	// 设置接收硬币类型
	int iSetReceiveType(BYTE p_byReceiveType, tDevReturn* p_psrStatus);
	// 开始接收硬币
	int iStartReceiveCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// 停止接收硬币
	int iStopReceiveCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// 读取接收金额
	int iGetReceiveNumber(tReceiveCoinNum* p_psReceiveCoinNum, tDevReturn* p_psrStatus);
	
	// 将暂存器中的硬币倒出到缓存找零器或钱箱
	int iAcceptCoin(BYTE p_byEscrow1Dir, BYTE p_byEscrow2Dir, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// 将暂存器中的硬币倒出到缓存找零器或钱箱，由动态库内部决定倒出方向
	int iAcceptCoinEx(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);

	// 退出硬币
	int iEjectCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	
	// 开始加币
	int iStartAddCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// 停止加币
	int iStopAddCoin(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);	
	
	// 逻辑配钞
	int iDenominate(UINT p_uiChange, tChange* p_psChange, tDevReturn* p_psrStatus);
	// 根据要求从Hopper中出硬币到出币口
	int iChange(tChange p_sChange, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// 根据要求从Hopper中出硬币到出币口，由动态库计算每个Hopper的找零数
	int iChangeEx(UINT p_uiChange, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);

	// 强制设置各Hopper及硬币钱箱中的硬币数
	int iSetCoinNumber(tSetCoinNum p_sCoinNum, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	// 保存记录
	int iSaveRecord(tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);

	// 清币
	int iClearCoin(tClearCoin p_sClearCoin, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);

	// 写iButton数据
	int iSetiButton(BYTE p_byiButtonNo, BYTE p_byAddress, BYTE p_byDataLen, LPBYTE p_pbyiButtonData, tDevReturn* p_psrStatus);
	// 读iButton数据
	int iGetiButton(BYTE p_byiButtonNo, BYTE p_byAddress, BYTE p_byDataLen, LPBYTE p_pbyiButtonData, tDevReturn* p_psrStatus);
	// 清除iButton数据
	int iCleariButton(BYTE p_byiButtonNo, tDevReturn* p_psrStatus);
	// 读iButton ID
	int iGetiButtonID(BYTE p_byiButtonNo, LPBYTE p_pbyiBtnID, tDevReturn* p_psrStatus);
	
	// 蜂鸣器发声
	int iBeep(BYTE p_byBeepCount, BYTE p_byBeepTime, BYTE p_byBeepInterval, tDevReturn *p_psrStatus);
	
	// 获取硬件介质程序版本号
	int iGetDevVersion(LPTSTR p_pcDevVersion, BYTE& p_byDataLen, tDevReturn* p_psrStatus);
	// 获取模块类型
	int iGetDevType(LPTSTR p_pcDevType, BYTE& p_byDataLen, tDevReturn* p_psrStatus);
	// 获取动态库版本号
	int iGetVersion(LPTSTR p_pcVersion);
	// 获取CPLD版本号
	int iGetCPLDVersion(LPTSTR p_pcCPLDVersion, BYTE& p_byDataLen, tDevReturn* p_psrStatus);
	
	// 写序列号
	int iSetSerialNumber(LPCTSTR p_pcSerialNo, const BYTE p_byDataLen, tDevReturn* p_psrStatus);
	// 读取序列号
	int iGetSerialNumber(LPTSTR p_pcSerialNo, BYTE& p_byDataLen, tDevReturn* p_psrStatus); 
	
	//added by hguang 2010-09-02
	// 下载文件
	int iDownloadFile(LPCTSTR p_pcFilePath, tDevReturn* p_psrStatus);
	//文件下载进度
	int iGetCurFileProgress(tCoinSystem_Pdl_Progress *p_psPdlProgress);
	//end added

	// ODevBase公有导出函数	
	// 获取错误状态结构体
	tDevReturn tGetErrorFlag();	
	// 读取硬件错误标志
	int iGetErrorFlag();
	
	// 获得驱动的逻辑设备名
	void vGetLogicalDevName(LPTSTR p_pcLogicalDevName);	
	// 设置驱动的逻辑设备名
	void vSetLogicalDevName(LPCTSTR p_pcLogicalDevName);
	
	// 清除接收缓冲区
	void vClearRecvBuf();	
	// 关闭通讯
	int iCloseComm();

	//	维护接口，只在测试时或检测时使用，应用中不使用
	// 查询凸轮转动的次数及退币数
	int iGetCamInfo(LPWORD p_pwLoopNum, LPWORD p_pwEjectNum, tDevReturn* p_psrStatus);
	
	// 暂存器控制
	int iEscrowControl(BYTE p_byDevNo, BYTE p_byAction, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// 换向器控制
	int iRouterControl(BYTE p_byDevNo, BYTE p_byAction, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// 主找零器控制
	int iMHopperControl(BYTE p_byDevNo,	BYTE p_byAction, WORD p_wDispNum, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// 缓存找零器控制
	int iSHopperControl(BYTE p_byDevNo,	BYTE p_byAction, WORD p_wDispNum, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// 凸轮控制
	int iCamControl(BYTE p_byLoopNum, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// 硬币接收器控制
	int iCoinReceiverControl(BYTE p_byAction, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	// 闸门控制
	int iShutterControl(BYTE p_byAction, tCASStatus* p_psCASStatus, tDevReturn* p_psrStatus);
	
	//added by hguang 2010-09-06
	int iReadLogDataEx(UINT p_uiStartAddress,	UINT p_uiLogLength,BYTE* p_pbyLogData,tDevReturn* p_psStatus);		
	int iReadLogInfoEx(tCoinLog p_tLogInfo[10],tDevReturn* p_psStatus);
    int iClearLog(tDevReturn* p_psStatus);

	//维护接口
	int iWriteLogDataEx(UINT p_uiStartAddress,	UINT p_uiLogLength,BYTE* p_pbyLogData,tDevReturn* p_psStatus);
	//end added
		
	//added by hguang 2013-08-26	
	//向RFID 写一个Block 数据
	int iRFWriteBlock(const tCAS006_IN_RWRFID* p_psWRFID, const tCAS006_DATA* p_psData, tDevReturn *p_psStatus);
	
	//从RFID 读一个Block 数据
	int iRFReadBlock(const tCAS006_IN_RWRFID* p_psRRFID, tCAS006_DATA* p_psData, tDevReturn *p_psStatus);
	
	//读取RFID 的物理编号
	int iGetRFIDCardInfo(const tCAS006_IN_CARD_INFO* p_psCardInfo, tCAS006_DATA* p_psData, tDevReturn *p_psStatus);
	
	//读取钱SN 号
	int iGetCoinBoxSerialNumber(const tCAS006_IN_CARD_INFO* p_psCardInfo, tCAS006_DATA* p_psData, tDevReturn* p_psStatus);

	//设置钱箱序列号
	int iSetCoinBoxSerialNumber(const tCAS006_IN_CARD_INFO* p_psCardInfo, const tCAS006_DATA* p_psData, tDevReturn* p_psStatus);
	ODevBase* GetDevBase();

	//added by hguang 2011-12-14
	//清币
	int iClearCoinEx(tClearCoin p_sClearCoin, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psrStatus);
	
	//清指定数量的硬币
	int iClearCoin(const tCAS006_ClearNum* p_psClearNum, tCASStatus* p_psCASStatus, tCoinInfo* p_psCoinInfo, tDevReturn* p_psStatus);
private:
	 //OCASBase m_pCASBase;
	class OCASBase* m_pCASBase;
};

#endif // !defined(AFX_CASDEV_H__F07F2DC3_A28E_4199_9596_25F0F8C46765__INCLUDED_)
