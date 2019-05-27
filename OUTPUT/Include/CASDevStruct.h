#ifndef __CASDEVSTRUCT_H
#define __CASDEVSTRUCT_H

//////////////////////////////////////////////////////////////////////////
//
//	适用模块：
//	CAS006:	深圳地铁四号线硬币模块
//	CAS006A:土耳其ATM硬币找零模块
//	CAS006B:北京地铁八号线、西安地铁硬币模块
//
//////////////////////////////////////////////////////////////////////////

//========硬币类型定义================================
#define COIN_TYPEA				1
#define COIN_TYPEB				2

//========可用标志定义================================
#define HOPPER_ENABLE			0
#define HOPPER_DISABLE			0x80

//========倒硬币方向定义==============================
#define COIN_2_SHOPPER			1	// 倒入缓存找零器
#define COIN_2_COINCASE1		2	// 倒入钱箱1
#define COIN_2_OUTLET			3	// 倒入出币口
#define COIN_2_COINCASE2		4	// 倒入钱箱2


//========IBUTTON状态定义========================================
													// 传感器					未检测到或故障				检测到或正常
#define S_MHOPPER1_IBUTTON		0x01				// 大Hopper1加币箱			0: 未检测到加币箱1 或故障	1: 检测到加币箱1 且正常
#define S_MHOPPER2_IBUTTON		0x02				// 大Hopper2加币箱			0: 未检测到加币箱2 或故障	1: 检测到加币箱2 且正常
#define S_RETRACT_VALT1			0x04				// 硬币回收箱1				0: 未检测到回收箱1 或故障	1: 检测到回收箱1 且正常
#define S_RETRACT_VALT2			0x08				// 硬币回收箱2				0: 未检测到回收箱2 或故障	1: 检测到回收箱2 且正常
#define S_EEPROM				0x10				// EEPROM					0: 未检测到EEPROM 或故障	1: 检测到EEPROM 且正常
#define S_COIN_SHUTTER			0x20				// 硬币闸门状态				0: 硬币闸门关闭				1: 硬币闸门打开  
#define S_CHANNEL_STATUS		0x40				// 通道运动状态				0: 不运动					1: 运动
#define S_BUTTON_RESERVED		0x80

#define S_RECEIVER_STATUS		0x01				// 接收功能状态				0: 不可用					1: 可用
#define S_CHANGE_STATUS			0x02				// 找零功能状态				0: 不可用					1: 可用

//========传感器定义========================================
													// 传感器					未检测到或故障			检测到或正常
#define S_BUCKLE1_LOWER			0x0000000000000001	// 加币扣1位置下传感器		0: 传感器被挡			1: 传感器未挡
#define S_BUCKLE1_UPPER			0x0000000000000002	// 加币扣1位置上传感器		0: 传感器被挡			1: 传感器未挡
#define S_BUCKLE2_LOWER			0x0000000000000004	// 加币扣2位置下传感器		0: 传感器被挡			1: 传感器未挡
#define S_BUCKLE2_UPPER			0x0000000000000008	// 加币扣2位置上传感器		0: 传感器被挡			1: 传感器未挡
#define S_ROUTER_RIGHT			0x0000000000000010	// 换向器右边传感器			0: 传感器被挡			1: 传感器未挡
#define S_ROUTER_LEFT			0x0000000000000020	// 换向器左边传感器			0: 传感器被挡			1: 传感器未挡
#define S_ESCROW1_RIGHT			0x0000000000000040	// 暂存器1右传感器			0: 传感器被挡			1: 传感器未挡
#define S_ESCROW1_CENTER		0x0000000000000080	// 暂存器1中传感器			0: 传感器被挡			1: 传感器未挡

#define S_ESCROW1_LEFT			0x0000000000000100	// 暂存器1左传感器			0: 传感器被挡			1: 传感器未挡
#define S_ESCROW2_RIGHT			0x0000000000000200	// 暂存器2右传感器			0: 传感器被挡			1: 传感器未挡
#define S_ESCROW2_CENTER		0x0000000000000400	// 暂存器2中传感器			0: 传感器被挡			1: 传感器未挡
#define S_ESCROW2_LEFT			0x0000000000000800	// 暂存器2左传感器			0: 传感器被挡			1: 传感器未挡
#define S_MAGNET1_IN_POS		0x0000000000001000	// 电磁铁1到位检测			0: 传感器被挡			1: 传感器未挡
#define S_MAGNET2_IN_POS		0x0000000000002000	// 电磁铁2到位检测			0: 传感器被挡			1: 传感器未挡
#define S_MHOPPER1				0x0000000000004000	// 主找零器1出币传感器		0: 有币					1: 无币
#define S_MHOPPER2				0x0000000000008000	// 主找零器2出币传感器		0: 有币					1: 无币

#define S_THOPPER1				0x0000000000010000	// 高见泽小Hopper1			0: 有币					1: 无币
#define S_THOPPER2				0x0000000000020000	// 高见泽小Hopper2			0: 有币					1: 无币
#define S_EHOPPER1				0x0000000000040000	// 缓存找零器1出币传感器	0: 有币					1: 无币
#define S_EHOPPER2				0x0000000000080000	// 缓存找零器2出币传感器	0: 有币					1: 无币
#define S_EHOPPER3				0x0000000000100000	// 缓存找零器3出币传感器	0: 有币					1: 无币
#define S_EHOPPER4				0x0000000000200000	// 缓存找零器4出币传感器	0: 有币					1: 无币
#define S_PLATE1_OPEN			0x0000000000400000	// 加币箱1挡板打开			0: 传感器被挡			1: 传感器未挡
#define S_PLATE1_CLOSE			0x0000000000800000	// 加币箱1挡板关闭			0: 传感器被挡			1: 传感器未挡

#define S_PLATE2_OPEN			0x0000000001000000	// 加币箱2挡板打开			0: 传感器被挡			1: 传感器未挡
#define S_PLATE2_CLOSE			0x0000000002000000	// 加币箱2挡板关闭			0: 传感器被挡			1: 传感器未挡
#define S_COINCASE_IN_POS		0x0000000004000000	// 硬币钱箱到位传感器		0: 传感器被挡			1: 传感器未挡
#define S_CHANNEL_MOTOR			0x0000000008000000	// 通道马达转到传感器		0: 传感器被挡			1: 传感器未挡
#define S_COIN_IN				0x0000000010000000	// 投币入口传感器			0: 有币					1: 无币
#define S_COIN_OUT1				0x0000000020000000	// 投币出口传感器1			0: 有币					1: 无币
#define S_BRACKET_POS			0x0000000040000000	// 拖架位置传感器			0: 有币					1: 无币
#define S_CAM_SENSOR			0x0000000080000000	// 凸轮传感器				0: 传感器被挡			1: 传感器未挡

#define S_CHANNEL1				0x0000000100000000	// 通道传感器1				0: 传感器被挡			1: 传感器未挡
#define S_CHANNEL2				0x0000000200000000	// 通道传感器2				0: 传感器被挡			1: 传感器未挡
#define S_COIN_OUT2				0x0000000400000000	// 投币出口传感器2			0: 有币					1: 无币
#define S_SHUTTER_OPEN			0x0000000800000000	// 闸门开传感器				0: 传感器被挡			1: 传感器未挡（保留）
#define S_SHUTTER_CLOSE			0x0000001000000000	// 闸门关传感器				0: 传感器被挡			1: 传感器未挡（保留）
#define S_COINCASE_IN_POS2		0x0000002000000000	// 硬币钱箱2到位传感器		0: 传感器被挡			1: 传感器未挡（CAS006B）
#define S_SENSOR_RESERVED56		0x0000004000000000
#define S_SENSOR_RESERVED57		0x0000008000000000

#define S_SENSOR_RESERVED60		0x0000010000000000
#define S_SENSOR_RESERVED61		0x0000020000000000
#define S_SENSOR_RESERVED62		0x0000040000000000
#define S_SENSOR_RESERVED63		0x0000080000000000
#define S_SENSOR_RESERVED64		0x0000100000000000
#define S_SENSOR_RESERVED65		0x0000200000000000
#define S_SENSOR_RESERVED66		0x0000400000000000
#define S_SENSOR_RESERVED67		0x0000800000000000

// 部件状态
typedef struct 
{
	BYTE byMHopper1Button;	// 大Hopper1加币箱			0: 未检测到加币箱1 或故障	1: 检测到加币箱1 且正常
	BYTE byMHopper2Button;	// 大Hopper2加币箱			0: 未检测到加币箱2 或故障	1: 检测到加币箱2 且正常
	BYTE byRetractValt1;	// 硬币回收箱1				0: 未检测到回收箱1 或故障	1: 检测到回收箱1 且正常
	BYTE byRetractValt2;	// 硬币回收箱2				0: 未检测到回收箱2 或故障	1: 检测到回收箱2 且正常（CAS006B）
	BYTE byEEPROM;			// EEPROM					0: 未检测到EEPROM 或故障	1: 检测到EEPROM 且正常
	BYTE byCoinShutter;		// 硬币闸门状态				0: 硬币闸门关闭				1: 硬币闸门打开（保留）
	BYTE byChannelStatus;	// 通道运动状态				0: 不运动					1: 运动（CAS006）
	BYTE byReserved17;

	BYTE byReceiverStatus;	// 接收功能状态（此状态只在初始化模块时才会改变）	0: 不可用	1: 可用
	BYTE byChangeStatus;	// 找零功能状态（此状态只在初始化模块时才会改变）	0: 不可用	1: 可用
	BYTE byReserved22;
	BYTE byReserved23;
	BYTE byReserved24;
	BYTE byReserved25;
	BYTE byReserved26;
	BYTE byReserved27;
}tiButtonStatus;

// 传感器状态
typedef struct 
{
							// 传感器					未检测到或故障			检测到或正常
	BYTE byBuckle1Lower;	// 加币扣1位置下传感器		0: 传感器被挡			1: 传感器未挡
	BYTE byBuckle1Upper;	// 加币扣1位置上传感器		0: 传感器被挡			1: 传感器未挡
	BYTE byBuckle2Lower;	// 加币扣2位置下传感器		0: 传感器被挡			1: 传感器未挡
	BYTE byBuckle2Upper;	// 加币扣2位置上传感器		0: 传感器被挡			1: 传感器未挡
	BYTE byRouterRight;		// 换向器右边传感器			0: 传感器被挡			1: 传感器未挡
	BYTE byRouterLeft;		// 换向器左边传感器			0: 传感器被挡			1: 传感器未挡
	BYTE byEscrow1Right;	// 暂存器1右传感器			0: 传感器被挡			1: 传感器未挡
	BYTE byEscrow1Center;	// 暂存器1中传感器			0: 传感器被挡			1: 传感器未挡
	
	BYTE byEscrow1Left;		// 暂存器1左传感器			0: 传感器被挡			1: 传感器未挡
	BYTE byEscrow2Right;	// 暂存器2右传感器			0: 传感器被挡			1: 传感器未挡（CAS006）
	BYTE byEscrow2Center;	// 暂存器2中传感器			0: 传感器被挡			1: 传感器未挡（CAS006）
	BYTE byEscrow2Left;		// 暂存器2左传感器			0: 传感器被挡			1: 传感器未挡（CAS006）
	BYTE byMagnet1InPos;	// 电磁铁1到位检测			0: 传感器被挡			1: 传感器未挡
	BYTE byMagnet2InPos;	// 电磁铁2到位检测			0: 传感器被挡			1: 传感器未挡
	BYTE byMHopper1;		// 主找零器1出币传感器		0: 有币					1: 无币
	BYTE byMHopper2;		// 主找零器2出币传感器		0: 有币					1: 无币
	
	BYTE byTHopper1;		// 高见泽小Hopper1			0: 有币					1: 无币（CAS006B）
	BYTE byTHopper2;		// 高见泽小Hopper2			0: 有币					1: 无币（CAS006B）
	BYTE byEHopper1;		// 缓存找零器1出币传感器	0: 有币					1: 无币（CAS006）
	BYTE byEHopper2;		// 缓存找零器2出币传感器	0: 有币					1: 无币（CAS006）
	BYTE byEHopper3;		// 缓存找零器3出币传感器	0: 有币					1: 无币（CAS006）
	BYTE byEHopper4;		// 缓存找零器4出币传感器	0: 有币					1: 无币（CAS006）
	BYTE byPlate1Open;		// 加币箱1挡板打开			0: 传感器被挡			1: 传感器未挡
	BYTE byPlate1Close;		// 加币箱1挡板关闭			0: 传感器被挡			1: 传感器未挡
	
	BYTE byPlate2Open;		// 加币箱2挡板打开			0: 传感器被挡			1: 传感器未挡
	BYTE byPlate2Close;		// 加币箱2挡板关闭			0: 传感器被挡			1: 传感器未挡
	BYTE byCoincaseInPos;	// 硬币钱箱到位传感器		0: 传感器被挡			1: 传感器未挡
	BYTE byChannelMotor;	// 通道马达转到传感器		0: 传感器被挡			1: 传感器未挡
	BYTE byCoinIn;			// 投币入口传感器			0: 有币					1: 无币
	BYTE byCoinOut1;		// 投币出口传感器1			0: 有币					1: 无币
	BYTE byBracketPos;		// 拖架位置传感器			0: 有币					1: 无币
	BYTE byCamSensor;		// 凸轮传感器				0: 传感器被挡			1: 传感器未挡
	
	BYTE byChannel1;		// 通道传感器1				0: 传感器被挡			1: 传感器未挡（保留）
	BYTE byChannel2;		// 通道传感器2				0: 传感器被挡			1: 传感器未挡（保留）
	BYTE byCoinOut2;		// 投币出口传感器2			0: 有币					1: 无币		 （保留）
	BYTE byShutterOpen;		// 闸门开传感器				0: 传感器被挡			1: 传感器未挡（保留）
	BYTE byShutterClose;	// 闸门关传感器				0: 传感器被挡			1: 传感器未挡（保留）
	BYTE byCoincase2InPos;	// 硬币钱箱2到位传感器		0: 传感器被挡			1: 传感器未挡（CAS006B）
	BYTE byReserved56;
	BYTE byReserved57;

	BYTE byReserved60;
	BYTE byReserved61;
	BYTE byReserved62;
	BYTE byReserved63;
	BYTE byReserved64;
	BYTE byReserved65;
	BYTE byReserved66;
	BYTE byReserved67;
}tSensorStatus;

typedef struct 
{
	tiButtonStatus siButtonStatus;
	tSensorStatus  sSensorStatus;
}tCASStatus;

// 硬币信息
typedef struct 
{
	int  iMHopper1Num;			// 大Hopper1硬币个数，返回范围-32768~32767
	int  iMHopper2Num;			// 大Hopper2硬币个数，返回范围-32768~32767
	int  iSHopper1Num;			// 小Hopper1硬币个数，返回范围-32768~32767
	int  iSHopper2Num;			// 小Hopper2硬币个数，返回范围-32768~32767
	int  iSHopper3Num;			// 小Hopper3硬币个数，返回范围-32768~32767
	int  iSHopper4Num;			// 小Hopper4硬币个数，返回范围-32768~32767

	int  iCoincase1Coin1;		// 硬币钱箱1硬币1个数，返回范围-32768~32767
	int	 iCoincase1Coin2;		// 硬币钱箱1硬币2个数，返回范围-32768~32767
	int  iCoincase2Coin1;		// 硬币钱箱2硬币1个数，返回范围-32768~32767
	int	 iCoincase2Coin2;		// 硬币钱箱2硬币2个数，返回范围-32768~32767

	BYTE byEscrow1Num;			// 暂存器1硬币个数
	BYTE byEscrow2Num;			// 暂存器2硬币个数
	BYTE byEscrow3Num;			// 暂存器3硬币个数
	BYTE byEscrow4Num;			// 暂存器4硬币个数

	BYTE byMHopper1Type;		// 大Hopper1硬币类型。MSB为HOPDISABLE位，1表示禁止，0表示使能
	BYTE byMHopper2Type;		// 大Hopper1硬币类型。MSB为HOPDISABLE位，1表示禁止，0表示使能
	BYTE bySHopper1Type;		// 小Hopper1硬币类型。MSB为HOPDISABLE位，1表示禁止，0表示使能
	BYTE bySHopper2Type;		// 小Hopper2硬币类型。MSB为HOPDISABLE位，1表示禁止，0表示使能
	BYTE bySHopper3Type;		// 小Hopper3硬币类型。MSB为HOPDISABLE位，1表示禁止，0表示使能
	BYTE bySHopper4Type;		// 小Hopper4硬币类型。MSB为HOPDISABLE位，1表示禁止，0表示使能

	BYTE byEjectCoinNum;		// 本次交易退币数
								// 暂存器1的硬币类型和小Hopper1的硬币类型一样
								// 暂存器2的硬币类型和小Hopper2的硬币类型一样
								// 暂存器3的硬币类型和小Hopper3的硬币类型一样
								// 暂存器4的硬币类型和小Hopper4的硬币类型一样
	
}tCoinInfo;

// 找零结构 
typedef struct 
{
	BYTE byMHopper1Num;		// 大Hopper1找零数
	BYTE byMHopper2Num;		// 大Hopper2找零数
	
	BYTE bySHopper1Num;		// 小Hopper1找零数
	BYTE bySHopper2Num;		// 小Hopper2找零数
	BYTE bySHopper3Num;		// 小Hopper3找零数
	BYTE bySHopper4Num;		// 小Hopper4找零数
}tChange;

// 接收金额
typedef struct 
{
	BYTE byEscrow1Num;		// 暂存器1硬币个数
	BYTE byEscrow2Num;		// 暂存器2硬币个数
	BYTE byEscrow3Num;		// 暂存器3硬币个数
	BYTE byEscrow4Num;		// 暂存器4硬币个数
	BYTE byEjectCoinNum;	// 本次交易退币数
}tReceiveCoinNum;

// 设置金额
typedef struct 
{
	WORD wMHopper1Num;		// 大Hopper1硬币个数，设置范围0~32767
	WORD wMHopper2Num;		// 大Hopper2硬币个数，设置范围0~32767	
	WORD wSHopper1Num;		// 小Hopper1找零数，设置范围0~32767
	WORD wSHopper2Num;		// 小Hopper2找零数，设置范围0~32767
	WORD wSHopper3Num;		// 小Hopper3找零数，设置范围0~32767
	WORD wSHopper4Num;		// 小Hopper4找零数，设置范围0~32767

	WORD wCoincase1Coin1;	// 硬币钱箱1硬币1个数，设置范围0~32767
	WORD wCoincase1Coin2;	// 硬币钱箱1硬币2个数，设置范围0~32767
	WORD wCoincase2Coin1;	// 硬币钱箱2硬币1个数，设置范围0~32767	
	WORD wCoincase2Coin2;	// 硬币钱箱2硬币2个数，设置范围0~32767	

	BYTE byEscrow1Num;		// 暂存器1硬币个数
	BYTE byEscrow2Num;		// 暂存器2硬币个数
	BYTE byEscrow3Num;		// 暂存器3硬币个数
	BYTE byEscrow4Num;		// 暂存器4硬币个数

	BYTE byMHopper1Type;	// 大Hopper1硬币类型，硬币类型1~0x7F。主hopper1硬币类型（CAS-007）
	BYTE byMHopper2Type;	// 大Hopper1硬币类型，硬币类型1~0x7F。主hopper2硬币类型（CAS-007）
	BYTE bySHopper1Type;	// 小Hopper1硬币类型，硬币类型1~0x7F。主hopper3硬币类型（CAS-007）
	BYTE bySHopper2Type;	// 小Hopper2硬币类型，硬币类型1~0x7F。主hopper4硬币类型（CAS-007）
	BYTE bySHopper3Type;	// 小Hopper3硬币类型，硬币类型1~0x7F。安装Hopper配置（CAS-007）
	BYTE bySHopper4Type;	// 小Hopper4硬币类型，硬币类型1~0x7F。
	
}tSetCoinNum;

// 清币结构 
typedef struct 
{
	bool bMHopper1Flag;		// 大Hopper1清币标志，true=清币，false=不清币
	bool bMHopper2Flag;		// 大Hopper2清币标志，true=清币，false=不清币
	
	bool bSHopper1Flag;		// 小Hopper1清币标志，true=清币，false=不清币
	bool bSHopper2Flag;		// 小Hopper2清币标志，true=清币，false=不清币
	bool bSHopper3Flag;		// 小Hopper3清币标志，true=清币，false=不清币
	bool bSHopper4Flag;		// 小Hopper4清币标志，true=清币，false=不清币

	BYTE byCoincase;		// 清币方向，1=硬币钱箱1，2=硬币钱箱2
}tClearCoin;

// 日期
typedef struct 
{
	BYTE byYear;			// 年
	BYTE byMonth;			// 月
	BYTE byDay;				// 日
}tDate;

// 时间
typedef struct 
{
	BYTE byHour;			// 时
	BYTE byMinute;			// 分
	BYTE bySecond;			// 秒
}tTime;

// 日期时间
typedef struct 
{
	BYTE byYear;			// 年
	BYTE byMonth;			// 月
	BYTE byDay;				// 日
	BYTE byHour;			// 时
	BYTE byMinute;			// 分
	BYTE bySecond;			// 秒
}tDateTime;

//在线下载进度
typedef struct _tCoinSystem_Pdl_Progress
{
	char       acFileName[MAX_PATH];    //当前下载文件名
	
	int        iTotalSize;              //文件大小
	
	int        iCurPos;					//当前下载位置	
	
}tCoinSystem_Pdl_Progress;

//设备日志
typedef struct
{
	
	BYTE       abyLogDate[4];         //日志记录日期 年月日时

	UINT       uiLogStartAddress;     //记录DwLogDate当天的日志开始地址

	UINT       uiLogEndAddress;	      //记录DwLogDate当天的日志结束地址	
	
}tCoinLog;

//added by hguang 2013-08-26
//读写卡箱RFID数据
typedef struct 
{
	BYTE				byBoxId;						//卡箱号
	
	BYTE				byBlockIndex;					//RFID block号
	
	BYTE				byReserved[2];					//保留字段
	
}tCAS006_IN_RWRFID;

//卡箱信息
typedef struct 
{
	BYTE				byBoxId;						//卡箱号
	
	BYTE				byReserved[3];					//保留字段
	
}tCAS006_IN_CARD_INFO;

//读/写数据
typedef struct 
{		
	char				caData[64];						// 写入/读出的数据
}tCAS006_DATA;
//end added

// 指定数量清币
typedef struct
{
	unsigned short ushMHopper[4];					//主找零清币数	[0] MH1 [1] MH2 [3/4]保留
	unsigned short ushSHopper[4];						//缓存找零清币数[0] SH1 [1] SH2 [3/4]保留
	
	unsigned char byCoincase;						//清币方向
	unsigned char byRsv[7];							//保留字段
}tCAS006_ClearNum;
#endif // __CASDEVSTRUCT_H