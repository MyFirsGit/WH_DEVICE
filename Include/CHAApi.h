#ifndef _CHA_API_H_
#define _CHA_API_H_

#include "Apidef.h"

//#ifdef __cplusplus
//extern "C" {
//#endif


#pragma pack(push,1)

typedef enum _ch_err_detail {
	CH_RES_OK				= 0,	// 操作成功
	CH_SET_PARAM_ERR            = 1,	// 设定值：参数异常
	CH_FUNC_PARAM_ERR           = 2,	// 函数参数异常
	CH_SEQUENCE_ERR	            = 3,	// 函数调用顺序异常
	CH_FUNC_ERR_RETURN	        = 4,	// 函数返回异常
	CH_LOGIC_ERR	            = 5,	// 逻辑异常
	CH_OTHER_ERR                = 6,    // 其它错误   
	CH_OPEN_FAILED				= 11,	// 打开时	串口打开失败
	CH_ALREADY_OPENED			= 12,	// 打开时	串口重复打开
	CH_CLOSE_FAILED				= 13,	// 关闭时	串口关闭失败
	CH_ALREADY_CLOSED			= 14,	// 关闭时	串口重复关闭
	CH_NOT_OPEN					= 15,	// 通信时	串口未打开
	CH_CMD_EXCEPTION			= 16,	// 通信时	命令异常
	CH_SEND_EXCEPTION			= 17,	// 通信时	送信异常
	CH_RECEIVE_EXCEPTION		= 18,	// 通信时	接收异常
	CH_DESERIALIZE_EXCEPTION	= 19,	// 通信时	解析回复信息异常
	CH_RECEIVE_TIMEOUT			= 20,	// 通信时	接收超时


	CHTRS_RES_WINERR           = 1001, // 系统错误

	CHTRS_ERR_HANDLE           = 1003, // The handle is invalid.
	CHTRS_RES_ERR_CHREAD       = 1100, // Could not create thread. Window error.
	CHTRS_RES_ERR_TIMEOUT      = 1101, // Timeout. Could not finished task in time.
	CHTRS_RES_RESET            = 1102, // Operation was terminate because of reseting.
	CHTRS_RES_STRANGE          = 1103, // Unrecognizable response.
	CHTRS_RECV_EMPTY           = 1104, // There is no data to receive.

	CHTRS_HTDL_ERR_FULL        = 1201, // Could not open connection because the conneciton pool is full
	CHTRS_HTDL_ERR_OPNTO       = 1202, // The operation could not finish in time.
	CHTRS_HTDL_ERR_WORKNG      = 1203, // Could not allocate workspace, out of memory.
	CHTRS_HTDL_ERR_SQUENG      = 1204, // Could not allocate the queue, out of memory.
	CHTRS_HTDL_ERR_RBUFNG      = 1206, // Could not allocate buffer for receiving data, out of memory.
	CHTRS_HTDL_ERR_SENDFAIL    = 1207, // Sending error. Unknow reason.
	CHTRS_HTDL_ERR_PORT        = 1208, // Could not open the specified serial port.
	CHTRS_HTDL_ERR_CTSOFF      = 1209, // Serial port does not support CTS (clear-to-send) event
	CHTRS_HTDL_ERR_SQUE        = 1210, // 发送队列满
	CHTRS_HTDL_ERR_RQUE        = 1211, // Too many items are queueing to be received

	CHTRS_MTX_ERR_ENQUIRE      = 1300, // ENQ发送失败，不能发送报文
	CHTRS_MTX_ERR_SEND         = 1301, // 三次重试仍然发送失败

	CHTRS_RFID_A_SUM_ERR       = 1500, // 票箱A的RFID数据SUM值异常
	CHTRS_RFID_B_SUM_ERR       = 1501, // 票箱B的RFID数据SUM值异常
	CHTRS_RFID_A_B_SUM_ERR     = 1502, // 票箱A和B的RFID数据SUM值异常

	CHTRS_MSG_EMPTY				= 1350, // The message is empty now.
	CHTRS_MSG_OVRFLW	        = 1351, // The buffer is too small to store message.
	CHTRS_CMD_INVALID	        = 1352, // Unsupported command.
	CHTRS_CMD_PARAM				= 1400, // Invalid parameter.
	CHTRS_CMD_REJECT	        = 1401  // Too many commands are queuing, could not send command.
}CH_ERR_DETAIL;
// 返回状态结构体
/*
结构体中变量说明
	uiProviderId	模块厂家标识：亿雅捷0x01、三星0x02、怡力 0x03、广电0x04、中软0x06、欧姆龙0x05；普天0x07。
	uiModuleType	模块类型标识：0x04硬币处理模块。
	uiType	状态类型：0-正常；1-警告；2-故障；3-只接收模式；4-只找零模式。
	uiErrorType	标准状态代码－注1 
	uiErrorCode	原始状态代码－注2
	cReverse	预留信息
注1：详见标准状态代码定义;模块有可能返回多个状态代码。
注2：为不同模块厂家提供的原始状态代码，同时每个原始状态代码都能够对应到唯一的标准状态代码中；原始代码对应标准状态代码可以为多对一。上位机通过该值，可以显示出详细的错误原因及故障点定位。
*/
typedef struct
{
	UINT uiProviderId;
	UINT uiModuleType;
	UINT uiType;
	UINT uiErrorType[16];
	UINT uiErrorCode[16];
	char cReverse[8];
} tCHADevReturn;

// 清币结构 
typedef struct _tClearCoin
{
	BOOL bClearMHopper1; // 主找零器2清币标志
	BOOL bClearMHopper2; // 主找零器1清币标志
	BOOL bClearChange1;  // 补充、找零箱1清币标志
	BOOL bClearChange2;  // 补充、找零箱2清币标志

}tCHAClearCoin;

// 模块容器配置信息结构体 有两类，当前版本使用第二种结构
/*
模块容器配置信息结构体中变量说明
	uiCoinBoxNum	硬币容器数量
	uiBoxType	容器类型：1：加币箱；2：循环箱；3：暂存器；4：缓存找零器；5：回收箱。
	uiBoxNo	容器序号：初始值为0；同一类型容器序号单独排号，例如加币箱配置4个，序号分别为1－4。
	uiCoinValue	单位分；容器中所能存放硬币的面额，该字段值只能为100、50、0； 其中0表示不能确定该容器的面额。
	uiCoinNum	容器中硬币的数量 
	uiCoinMaxNum	容器中能存入硬币最大的数量 
	uiBoxStatus	容器状态： 0-正常；1-未安装；2-已满；3-将满；4-已空；5-将空。该状态为模块硬件检测的状态，通过计数判断的状态由上位机进行判断
*/
typedef struct
{
	UINT uiBoxType;
	UINT uiBoxNo;
	UINT uiCoinValue;
	UINT uiCoinNum;
	UINT uiCoinMaxNum;
	UINT uiBoxStatus;
} tCoinBoxValueInfo;
typedef struct
{
	UINT uiCoinBoxNum;
	tCoinBoxValueInfo* pCoinBoxValueInfo;
} tCHACoinBoxInfo;
//////////////////////////////////////////////////////////////////////////
// 结构二硬币箱库存数据
typedef struct _struct_box_info  
{
	WORD OneY_inHopper;							   //1元Hopper箱中的硬币数量 
	WORD HalfY_inHopper;                           //5角Hopper箱中的硬币数量 
	WORD OneY_preparation;                         //1元备用箱中的硬币数量
	WORD HalfY_preparation;                        //5角备用箱中的硬币数量
	WORD OneY_inRecover;						   //1元回收箱中的硬币数量
	WORD OneY_maxthreshold_inRecover;				//回收箱1元满载阈值

	_struct_box_info()
	{
		OneY_inHopper=0;
		HalfY_inHopper=0;
		OneY_preparation=0;
		HalfY_preparation=0;
		OneY_inRecover=0;
		OneY_maxthreshold_inRecover=200;
	}
}tCoinBoxInfo;
// 接受硬币信息结构体
typedef struct
{
	tCoinBoxValueInfo stCoinBoxValueInfo[3];
	UINT uiEjectCoinNum;
} tCHACoinValueInfo;

// 传感器状态结构体（某些厂家会使用该类型结构）
/*
	传感器状态结构体中变量说明
	uiSensorNum	传感器数量
	uiSensorID	传感器ID
	uiStatus	0：未遮挡；1：遮挡。
*/
typedef struct
{
	UINT uiSensorID;
	UINT uiStatus;
} tSensorStatusEx;
typedef struct
{
	UINT uiSensorNum;
	tSensorStatusEx* pSensorStatus;
} tCHASensorStatus;

// 解析各位数据代表意义
typedef enum CH_SENSOR_POS{
	BYTE_IN_CH_POS_00	= 0x01,
	BYTE_IN_CH_POS_01	= 0x02,
	BYTE_IN_CH_POS_02	= 0x04,
	BYTE_IN_CH_POS_03	= 0x08,
	BYTE_IN_CH_POS_04	= 0x10,
	BYTE_IN_CH_POS_05	= 0x20,
	BYTE_IN_CH_POS_06	= 0x40,
	BYTE_IN_CH_POS_07	= 0x80,
};

// 模块状态，厂家不同，获取方式不同，该结构由lib层赋值，上位机应用
typedef struct _struct_dev_status
{
	// 机械状态详细信息
	WORD wHopperACnt;			//A循环找零箱中硬币数量
	WORD wHopperBCnt;			//B循环找零箱中硬币数量
	WORD wPreparationACnt;		//A备用箱中硬币数量
	WORD wPreparationBCnt;		//B备用箱中硬币数量
	WORD wRecoverCnt;			//回收箱中硬币数量(由于现实中5角硬币基本不使用，所以此处不做区分处理，当做只有1元硬币使用)
	
	// 整机
	bool bIsCoinModuleStandby;	// 硬币模块是否到位？true:到位；false：未到位
	bool bIsMoneyBoxExist;		// 回收箱是否到位
	// Hopper A
	bool bIsHopperAFull;		// Hopper 是否满
	bool bIsHopperAEmpty;		// Hopper 是否空
	// Hopper B
	bool bIsHopperBFull;		// Hopper 是否满
	bool bIsHopperBEmpty;		// Hopper 是否空
	// 备用钱箱A
	bool bIsChangeBoxAInstall;	// Change BoxA是否安装
	bool bIsChangeBoxAFull;		// Change BoxA是否满
	bool bIsChangeBoxAEmpty;	// Change BoxA是否空
	// 备用钱箱B
	bool bIsChangeBoxBInstall;	// Change BoxB是否安装
	bool bIsChangeBoxBFull;		// Change BoxB是否满
	bool bIsChangeBoxBEmpty;	// Change BoxB是否空
	_struct_dev_status()
	{
		wHopperACnt = 0;
		wHopperBCnt = 0;
		wPreparationACnt = 0;
		wPreparationBCnt = 0;
		wRecoverCnt = 0;
		bIsCoinModuleStandby = false;
		bIsMoneyBoxExist = true;
		bIsHopperAFull = false;
		bIsHopperAEmpty = false;
		bIsHopperBFull = false;
		bIsHopperBEmpty = false;
		bIsChangeBoxAInstall = false;
		bIsChangeBoxAFull = false;
		bIsChangeBoxAEmpty = false;
		bIsChangeBoxBInstall = false;
		bIsChangeBoxBFull = false;
		bIsChangeBoxBEmpty = false;
	}
	inline void Deserialize(const BYTE* data)
	{
		BYTE MechanismStatus[10] = {0};
		memcpy(MechanismStatus,data + 10,10);

		bIsCoinModuleStandby = !(MechanismStatus[0] & BYTE_IN_CH_POS_03);
		bIsHopperAFull		 = (MechanismStatus[2] & BYTE_IN_CH_POS_04);
		bIsHopperAEmpty		 = (MechanismStatus[2] & BYTE_IN_CH_POS_00);

		bIsHopperBFull		 = (MechanismStatus[3] & BYTE_IN_CH_POS_04);
		bIsHopperBEmpty		 = (MechanismStatus[3] & BYTE_IN_CH_POS_00);

		bIsChangeBoxAInstall = !(MechanismStatus[4] & BYTE_IN_CH_POS_05);
		bIsChangeBoxAFull	 = (MechanismStatus[4] & BYTE_IN_CH_POS_04);
		bIsChangeBoxAEmpty	 = (MechanismStatus[4] & BYTE_IN_CH_POS_00);

		bIsChangeBoxBInstall = !(MechanismStatus[5] & BYTE_IN_CH_POS_05);
		bIsChangeBoxBFull	 = (MechanismStatus[5] & BYTE_IN_CH_POS_04);
		bIsChangeBoxBEmpty	 = (MechanismStatus[5] & BYTE_IN_CH_POS_00);
	}
} tCHADevStatus;

/*
// 找零硬币信息结构体
	找零硬币信息结构体中变量说明
	uiCoinValue	单位分；找零硬币的面额，该字段值只能为100、50。
	uiCoinNum	对应面额找零硬币的数量 
	uiCoinTypeNum	需找零硬币种类数量（按面额区分）

*/
typedef struct
{
	UINT uiCoinValue;
	UINT uiCoinNum;
} tCoinChangeInfo;

// 设置金额结构
typedef struct _tSetCoinNum
{
	int uiMHopper1Num; // 主找零器2硬币个数，小于1100。	//武汉11号线专用
	int uiMHopper2Num; // 主找零器1硬币个数，小于1100。	//武汉11号线专用

	UINT uiCoinBoxCoinANum; // 硬币钱箱硬币A个数，加上硬币B小于3000。
	UINT uiCoinBoxCoinBNum; // 硬币钱箱硬币B个数，加上硬币A小于3000。

	BYTE byEscrow1Num; // 暂存器1硬币数，小于70。
	BYTE byEscrow2Num; // 暂存器2硬币数，小于70。

	BYTE byMHopper1Type; // 主找零器2硬币类型，1 = 1元硬币，2 = 5角硬币。	//武汉11号线专用
	BYTE byMHopper2Type; // 主找零器1硬币类型，1 = 1元硬币，2 = 5角硬币。	//武汉11号线专用
		
	BYTE byEjectCoinNum; // 退币个数

}tCHASetCoinNum;

// 钞票结构
typedef struct _tCoinInfo
{ 
	char acCurrency[4]; // 币种
	int iCount;			// 张数
	long lDenomination; // 面额
	char cSerial;		// 钞票套数(第四或第五套'4','5')
}tCHACoinInfo;

/*
typedef struct
{
	UINT uiCoinTypeNum;
	tCoinChangeInfo* pCoinChangeInfo;
} tCHAChangeNum;
*/
typedef struct 
{
	WORD wMHopper1Num; // 循环找零器1找零数	
	WORD wMHopper2Num; // 循环零器2找零数	
	WORD wChange1Num;//	找零器1
	WORD wChange2Num;// 找零器2
}tCHAChangeNum;

typedef struct COIN_ACCEPTABLE_{
	bool CH_COIN_ALLOW_1 ;
	bool CH_COIN_ALLOW_05;
	COIN_ACCEPTABLE_()
	{
		CH_COIN_ALLOW_1 = true;
		CH_COIN_ALLOW_05= true;
	}

}COIN_ACCEPTABLE;

//
typedef struct _ch_operator_coin_num_info
{
	unsigned short escrow1;		// 暂存1硬币数变化
	unsigned short escrow2_05;	// 暂存2硬币数变化
	unsigned short hopper1;		// hopper1硬币数变化
	unsigned short hopper2;		// hopper2硬币数变化
	unsigned short reject;		// 本次交易退币

	_ch_operator_coin_num_info(){
		escrow1   =0;    
		escrow2_05=0;   
		hopper1    =0;  
		hopper2    =0;    
	}

} CH_OPERATOR_COIN_NUM_INFO;

#pragma pack(pop)


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
AFC_API_DLL_IMP int CHA_CommOpen(UINT uiCommPort, UINT uiBaudRate,CString logPath,CString logName, tCHADevReturn * pDevStatus);
// 初始化
/*
btXinCtl:
	0x00 暂存部硬币送到出币口
	0x10 暂存部硬币送到Hopper或回收箱
	0x20 暂存部硬币保持原样
*/
AFC_API_DLL_IMP int CHA_Init(BYTE btXinCtl,tCHADevReturn * pDevStatus);
// 获取设备状态
AFC_API_DLL_IMP int CHA_GetDevStatus(tCHADevReturn * pDevStatus);
// 获取传感器状态
AFC_API_DLL_IMP int CHA_GetSensorStatus(tCHASensorStatus* pSensorStatus, tCHADevReturn * pDevStatus);
// 获取容器配置信息
AFC_API_DLL_IMP int CHA_GetCoinBoxInfo(tCHADevStatus *pCoinBoxInfo,tCHADevReturn * pDevStatus);
// 设置硬币数量
AFC_API_DLL_IMP int CHA_SetCoinBoxInfo(tCoinBoxInfo *pCoinBoxInfo,tCHADevReturn * pDevStatus);
// 开始接收硬币
AFC_API_DLL_IMP int CHA_StartReceiveCoin(tCHADevReturn * pDevStatus);
// 结束接收硬币
AFC_API_DLL_IMP int CHA_StopReceiveCoin(tCHADevReturn * pDevStatus);
// 获取接收硬币信息
AFC_API_DLL_IMP int CHA_GetReceiveNumber(tCHACoinValueInfo *pCoinValueInfo, tCHADevReturn * pDevStatus);
// 存入硬币
AFC_API_DLL_IMP int CHA_AcceptCoin(tCHACoinValueInfo *pCoinValueInfo, tCHADevReturn * pDevStatus);
// 退出硬币
AFC_API_DLL_IMP int CHA_EjectCoin(UINT * uiReturnCoinNum ,tCHADevReturn * pDevStatus);
// 找零
AFC_API_DLL_IMP int CHA_ChangeCoin(tCHAChangeNum * pChangeNum,tCHADevReturn * pDevStatus);
// 更换容器
AFC_API_DLL_IMP int CHA_StartReplaceBOX(UINT uiBoxType, UINT uiBoxNo,UINT uiOpType,tCHADevReturn * pDevStatus);
// 停止更换容器
AFC_API_DLL_IMP int CHA_StopReplaceBOX(UINT uiBoxType, UINT uiBoxNo, UINT uiOpType,tCHADevReturn * pDevStatus);
// 清空硬币
AFC_API_DLL_IMP int CHA_ClearCoin(UINT uiBoxTypeOutput, UINT uiBoxNoOutput, UINT uiBoxTypeInput, UINT uiBoxNoInput, tCoinBoxInfo *pCoinBoxInfo,UINT uiCoinNum,tCHADevReturn * pDevStatus);
// 读容器RFID信息
AFC_API_DLL_IMP int CHA_ReadRFIDInfo(UINT uiBoxType, UINT uiBoxNo,unsigned char RFIDInfo[36],tCHADevReturn * pDevStatus);
// 写容器RFID信息
AFC_API_DLL_IMP int CHA_WriteRFIDInfo(UINT uiBoxType, UINT uiBoxNo,unsigned char RFIDInfo[36],tCHADevReturn * pDevStatus);
// 获取模块介质版本
AFC_API_DLL_IMP int CHA_GetVersion(char cVersion[32],tCHADevReturn * pDevStatus);
// 获取模块序号
AFC_API_DLL_IMP int CHA_GetSerialNumber(char cVersion[32],tCHADevReturn * pDevStatus);
// 获取审计数据
AFC_API_DLL_IMP int CHA_GetAuditData(tCHACoinBoxInfo *pCoinBoxInfo,tCHADevReturn * pDevStatus);
// 关闭通讯
AFC_API_DLL_IMP int CHA_CloseComm(tCHADevReturn * pDevStatus);

//#if defined (__cplusplus)
//} // end of extern "C"
//#endif

#endif