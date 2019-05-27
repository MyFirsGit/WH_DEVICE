
//　打印机连接port定义：
#define POS_PT_COM			1000L
#define POS_PT_LPT			1001L
#define POS_PT_USB			1002L
#define POS_PT_NET			1003L

// 打印机错误码定义：
#define POS_ES_PAPERENDING  6L //纸将尽
#define POS_ES_DRAWERHIGH   5L //钱箱高电平
#define POS_ES_CUT          4L //切刀未复位
#define POS_ES_DOOROPEN     3L //纸仓门开
#define	POS_ES_HEAT         2L //机头过热
#define POS_ES_PAPEROUT     1L //打印机缺纸
#define POS_ES_SUCCESS      0L //成功/发送成功/状态正常/打印完成
#define POS_ES_INVALIDPARA  -1L //参数错误
#define POS_ES_WRITEFAIL    -2L //写失败
#define POS_ES_READFAIL     -3L //读失败
#define POS_ES_NONMONOCHROMEBITMAP -4L //非单色位图
#define POS_ES_OVERTIME     -5L //超时/写超时/读超时/打印未完成
#define POS_ES_FILEOPENERROR -6L //文件/图片打开失败
#define POS_ES_OTHERERRORS   -100L //其他原因导致的错误

// barcode type
#define POS_BT_UPCA			4001L
#define POS_BT_UPCE			4002L
#define POS_BT_JAN13		4003L
#define POS_BT_JAN8			4004L
#define POS_BT_CODE39		4005L
#define POS_BT_ITF			4006L
#define POS_BT_CODABAR		4007L
#define POS_BT_CODE93		4073L
#define POS_BT_CODE128		4074L

//Dimensional barcode type
#define POS_BT_PDF417		4100L
#define POS_BT_DATAMATRIX	4101L
#define POS_BT_QRCODE		4102L

// HRI type
#define POS_HT_NONE			4011L
#define POS_HT_UP			4012L
#define POS_HT_DOWN			4013L
#define POS_HT_BOTH			4014L

//TSPL
#define TSPL_PRINTER_STATUS_OUTPAPER 1L	//打印机缺纸
#define TSPL_PRINTER_STATUS_WORK 2L	//打印中
#define TSPL_PRINTER_STATUS_ENCLOSURENOCLOSE 3L	//机壳未关
#define TSPL_PRINTER_STATUS_ERROR 4L	//打印机内部错误

#define TSPL_PARAM_LESS_EQUAL_ZERO		-2L		//参数小于等于0
#define TSPL_PARAM_GREAT_RANGE          -3L		//参数大于指定范围
#define TSPL_SUCCESS					0L
#define TSPL_IDERROR					-1L


//
//const int  PRINT_MOVEDOWN_ROWNUM = 0x08;   //打印机打印完毕走纸行数
//const int  Printer_WAIT_TIME = 30000;     //打印机等待时间
//const int  BOX_WAIT_TIME = 5000;     //打开钱箱等待时间
//
//
//static const unsigned long  COMMAND_Printer_CONNECT = 0x5101  ; //打开串口
//static const unsigned long  COMMAND_Printer_PRINT = 0x5102  ;   //打印命令
//static const unsigned long  COMMAND_Printer_CLOSE = 0x5103  ;   //关闭打印机
//static const unsigned long  COMMAND_Printer_OPENBOX = 0x5104  ;  //关闭钱箱
