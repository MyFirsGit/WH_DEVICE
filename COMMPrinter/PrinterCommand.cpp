#include "stdafx.h"
#include "PrinterCommand.h"
#include "PrinterException.h"
#include "LoadDll.h"


static const int PRINT_MAX_WIDTH = 40;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
/**
@brief    　构造函数

@param      (i)int nPort 串口的端口号
@param      (i)int nBaud 串口的波特率
@param      (i)int nSize 字长

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////

CPrinterCommand::CPrinterCommand(int nPort,int nBaud ,int nSize)
{
	this->m_nBaud = nBaud;
	this->m_nPort = nPort;
	this->m_nSize = nSize;
	//m_hPrinter = INVALID_HANDLE_VALUE;
	m_hPrinterID = 0;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      析构函数

@param      (i)无

@retval     无

@exception  无
*/
//////////////////////////////////////////////////////////////////////////

CPrinterCommand::~CPrinterCommand(void)
{
}


//////////////////////////////////////////////////////////////////////////
/**
@brief      连接打印机

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_Open()
{
	long iRet = 0;

	//　*** 协议开发
	//iRet = ConnectFunction();

	//  *** 封装库开发
	if (hInst==NULL){
		iRet = LoadSDKLibrary();
	}
	// 连接打印机
	if(!iRet){
		/* 
		 不同连接方式下的szName赋值格式：
			COM: COM1:9600,N,8,1
			LPT: LPT1:
			USB: SP-USB1
			ETH: 192.168.1.203:9100
		 不同连接方式下的strPort赋值格式：
			COM: POS_PT_COM
			LPT: POS_PT_LPT
			USB: POS_PT_USB
			ETH: POS_PT_NET		
		*/
		m_hPrinterID = POS_Port_OpenA((LPSTR)(LPCSTR)"SP-USB1", POS_PT_USB, FALSE, "");
		if(m_hPrinterID < 0){
			POS_Port_Close(m_hPrinterID);
			iRet = CPrinterException::ERROR_Printer_OPEN_COM;
		}
	}
	else{
		iRet = CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	return iRet;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief      断开连接

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_Close()
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return iRet;
	}

	// 已打开打印机
	if (m_hPrinterID>=0){
		iRet = POS_Port_Close(m_hPrinterID);
	}	

	return iRet;
}



//////////////////////////////////////////////////////////////////////////
/**
@brief      初始化打印机

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_Init()
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	// 未打开打印机
	if (m_hPrinterID<0){
		return CPrinterException::ERROR_Printer_NOTOPEN;
	}


	return iRet;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief      打印机复位

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_Reset()
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	PRT_Close();
	iRet = PRT_Open();
	if (!iRet){
		iRet = PRT_Init();
	}

	return iRet;
}



//////////////////////////////////////////////////////////////////////////
/**
@brief      获取打印机状态

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_GetStatus()
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	// 未打开打印机
	if (m_hPrinterID<0){
		return CPrinterException::ERROR_Printer_NOTOPEN;
	}

	iRet = POS_Status_RTQueryTypeStatus(m_hPrinterID, 3);
	switch (iRet)
	{
	case POS_ES_CUT:
		return CPrinterException::ERROR_Printer_KNIFE_ERROR;
		break;
	case POS_ES_INVALIDPARA:
		return CPrinterException::ERROR_Printer_PARAMTER_ERROR;
		break;
	case POS_ES_WRITEFAIL:
		return CPrinterException::ERROR_Printer_WRITEFILE;
		break;
	case POS_ES_READFAIL:
		return CPrinterException::ERROR_Printer_READFILE;
		break;
	case POS_ES_OVERTIME:
		return CPrinterException::ERROR_Printer_WAIT_TIMEOUT;
		break;
	case POS_ES_OTHERERRORS:
		return CPrinterException::ERROR_Printer_OTHER_ERROR;
		break;
	default:
		break;
	}


	iRet = POS_Status_RTQueryTypeStatus(m_hPrinterID, 4);
	switch (iRet)
	{
	case POS_ES_PAPEROUT:
		return CPrinterException::ERROR_Printer_NO_PAPER;
		break;
	case POS_ES_PAPERENDING:
		return CPrinterException::ERROR_Printer_LESS_PAPER;
		break;
	case POS_ES_INVALIDPARA:
		return CPrinterException::ERROR_Printer_PARAMTER_ERROR;
		break;
	case POS_ES_WRITEFAIL:
		return CPrinterException::ERROR_Printer_WRITEFILE;
		break;
	case POS_ES_READFAIL:
		return CPrinterException::ERROR_Printer_READFILE;
		break;
	case POS_ES_OVERTIME:
		return CPrinterException::ERROR_Printer_WAIT_TIMEOUT;
		break;
	case POS_ES_OTHERERRORS:
		return CPrinterException::ERROR_Printer_OTHER_ERROR;
		break;
	default:
		break;
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief      打印

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_Print(const WCHAR* strText)
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	// 未打开打印机
	if (m_hPrinterID<0){
		return CPrinterException::ERROR_Printer_NOTOPEN;
	}

	LONG ret = POS_Output_PrintStringW(m_hPrinterID, strText);
	switch (iRet)
	{
	case POS_ES_INVALIDPARA:
		return CPrinterException::ERROR_Printer_PARAMTER_ERROR;
		break;
	case POS_ES_WRITEFAIL:
		return CPrinterException::ERROR_Printer_WRITEFILE;
		break;
	case POS_ES_READFAIL:
		return CPrinterException::ERROR_Printer_READFILE;
		break;
	case POS_ES_OVERTIME:
		return CPrinterException::ERROR_Printer_WAIT_TIMEOUT;
		break;
	case POS_ES_OTHERERRORS:
		return CPrinterException::ERROR_Printer_OTHER_ERROR;
		break;
	default:
		break;
	}

	return iRet;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief      打印

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_PrintText(CStringArray* sArray, bool bOpenBox)
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	// 未打开打印机
	if (m_hPrinterID<0){
		return CPrinterException::ERROR_Printer_NOTOPEN;
	}

	//POS_Control_AlignType(m_hPrinterID,0);//左对齐
	//POS_Control_AlignType(m_hPrinterID,1);//居中对齐
	//POS_Control_AlignType(m_hPrinterID,2);//右对齐

	// 1. 处理打印内容
	CStringArray* sArrText = NULL;
	if ( sArray != NULL) {
		if ( sArray->GetSize() > 0 ) {
			sArrText = new CStringArray();
			for (int i= 0;i < sArray->GetSize();i++) {
				CString sOne = sArray->GetAt(i);
				sArrText->Add(sOne);
			}
		}
	}

	char* buff = NULL;
	if(sArrText != NULL){
		int cnt = (int)sArrText->GetCount();
		int iSize = cnt*100 + 20; 
		buff = new char[iSize];
		memset(buff,0,iSize);

		// 开钱箱指令
		if (bOpenBox == true) {
			iRet = PRT_OpenMoneyBox();
		}

		// 取得打印内容及打印指令
		for (int i=0;i<cnt;i++) {
			CString msg = sArrText->GetAt(i);	// 获取当前打印内容
			bool isPor = false;						// 是否葡萄牙文
			int codePage = 0;						// 编码页
			int fontType = 1;						// 字符字体标志

			// 繁体中文
			if((msg.Find(_T("[CN]")) >= 0)||(msg.Find(_T("CN]")) >= 0)){
				isPor = false;
				msg.Replace(_T("[CN]"),_T(""));
				msg.Replace(_T("CN]"),_T(""));
				codePage = 54936;
				fontType = 0;
			}
			// 葡萄牙文
			else if(msg.Find(_T("[PN]")) >= 0){
				isPor = true;
				msg.Replace(_T("[PN]"),_T(""));
				codePage = 860;
				fontType = 1;
			}
			// 英文
			else if(msg.Find(_T("[EN]")) >= 0){
				isPor = false;
				msg.Replace(_T("[EN]"),_T(""));
				codePage = 54936;
				fontType = 1;
			}

			// 设置字体大小
			if (fontType ==0 ){

			}
			else{

			}

			// 对字符串进行拆分与格式化
			CString tmpMsg = msg + _T("\n");
			//msg = SplitAndFormatPrintLine(tmpMsg);
			iRet = PRT_Print(tmpMsg.GetBuffer());	
		}

		if(cnt>0){
			iRet = PRT_FeedLine();
			iRet = PRT_CutPaper();
		}
	}
	else{
		// 开钱箱指令
		if (bOpenBox == true) {
			iRet = PRT_OpenMoneyBox();
		}
	}

	return iRet;
}



//////////////////////////////////////////////////////////////////////////
/**
@brief      打开钱箱

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_OpenMoneyBox()
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	// 未打开打印机
	if (m_hPrinterID<0){
		return CPrinterException::ERROR_Printer_NOTOPEN;
	}

	LONG ret = POS_Control_CashDraw(m_hPrinterID, 1, 100, 100);
	switch (iRet)
	{
	case POS_ES_INVALIDPARA:
		return CPrinterException::ERROR_Printer_PARAMTER_ERROR;
		break;
	case POS_ES_WRITEFAIL:
		return CPrinterException::ERROR_Printer_WRITEFILE;
		break;
	case POS_ES_READFAIL:
		return CPrinterException::ERROR_Printer_READFILE;
		break;
	case POS_ES_OVERTIME:
		return CPrinterException::ERROR_Printer_WAIT_TIMEOUT;
		break;
	case POS_ES_OTHERERRORS:
		return CPrinterException::ERROR_Printer_OTHER_ERROR;
		break;
	default:
		break;
	}

	return iRet;
}




//////////////////////////////////////////////////////////////////////////
/**
 @brief      拆分并格式化打印字符串
                                                                 
 @param      (i)无

 @retval      int   \n
                0 : 成功  非0 : 失败

 @exception   无
*/
//////////////////////////////////////////////////////////////////////////
CString CPrinterCommand::SplitAndFormatPrintLine(CString lineMsg)
{
	int iRet = 0;
	CString msg = lineMsg;
	//超过一行的，不做对齐处理
	if (GetAactualCharacterWidth(msg)>PRINT_MAX_WIDTH){
		return msg;
	}

	// 带#号的字符串为需要居中的字符串
	if (msg.Find(_T("#")) >= 0)
	{
		msg.Replace(_T("#"),_T(""));
		// 居中
		iRet = PRT_SetAlign(ALIGN_MID);
	}
	// 带@@号的字符串为需要右对齐的字符串（邮箱中有@，为区分使用@@）
	else if (msg.Find(_T("@@")) >= 0)
	{
		msg.Replace(_T("@@"),_T(""));
		// 右对齐
		iRet = PRT_SetAlign(ALIGN_RIGHT);
	}
	// 带:号的字符串为需要拆分成两列的字符串
	else if (msg.Find(_T(":")) >= 0)
	{
		CString strLeft(_T(""));
		CString strRight(_T(""));

		int iPos = msg.FindOneOf(_T(":"));
		// :号右边有内容
		if(msg.Mid(iPos+1) != _T("")){
			strLeft = msg.Left(iPos-1)/* + cCmdRowPrint*/;
			strRight = msg.Mid(iPos+1);
			/*
				左字符串 + 补齐的空格 + 右字符串
				暂时不实现
			*/
		}
		else{

		}

	}
	// 带$号的字符串为需要拆分成三列的字符串
	else if (msg.Find(_T("$")) >= 0)
	{
		CStringArray arryPrintLines;
		CString strLeft(_T(""));
		CString strMid(_T(""));
		CString strRight(_T(""));
		CString strLine = msg;
		int iPos = 0;
		// 拆分数据
		// 三列数据
		while((iPos=strLine.Find(_T("$")))!=-1){
			arryPrintLines.Add(strLine.Left(iPos));
			strLine.Delete(0,iPos+1);
		}
			arryPrintLines.Add(strLine);	
			strLeft = arryPrintLines.ElementAt(0) ;	
			strMid = arryPrintLines.ElementAt(1) ;
			// 防止出现缺少一个$，导致系统出问题
			if (arryPrintLines.GetCount() > 2)
			{
				strRight = arryPrintLines.ElementAt(2);
			}
			else
			{
				strRight = _T("");
			}			
			/*
				左字符串 + 补齐的空格 + 中间字符串 + 补齐的空格 + 右字符串
				暂时不实现
			*/	
	}
	// 无特殊符号标识左对齐
	else{

	}

	return msg;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief      打印

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_SetAlign(int alignType)
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	// 未打开打印机
	if (m_hPrinterID<0){
		return CPrinterException::ERROR_Printer_NOTOPEN;
	}

	if (alignType==ALIGN_LEFT){
		iRet = POS_Control_AlignType(m_hPrinterID,alignType);//左对齐
	}
	else if (alignType==ALIGN_LEFT){
		iRet = POS_Control_AlignType(m_hPrinterID,alignType);//居中对齐
	}
	else if (alignType==ALIGN_RIGHT){
		iRet = POS_Control_AlignType(m_hPrinterID,alignType);//右对齐
	}
	else{
		return CPrinterException::FUNC_PARAM_ERR;
	}

	switch (iRet)
	{
	case POS_ES_INVALIDPARA:
		return CPrinterException::ERROR_Printer_PARAMTER_ERROR;
		break;
	case POS_ES_WRITEFAIL:
		return CPrinterException::ERROR_Printer_WRITEFILE;
		break;
	case POS_ES_READFAIL:
		return CPrinterException::ERROR_Printer_READFILE;
		break;
	case POS_ES_OVERTIME:
		return CPrinterException::ERROR_Printer_WAIT_TIMEOUT;
		break;
	case POS_ES_OTHERERRORS:
		return CPrinterException::ERROR_Printer_OTHER_ERROR;
		break;
	default:
		break;
	}

	return iRet;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief      走纸

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_FeedLine()
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	// 未打开打印机
	if (m_hPrinterID<0){
		return CPrinterException::ERROR_Printer_NOTOPEN;
	}

	LONG ret = PRT_Print(_T("\n\n"));
	switch (iRet)
	{
	case POS_ES_INVALIDPARA:
		return CPrinterException::ERROR_Printer_PARAMTER_ERROR;
		break;
	case POS_ES_WRITEFAIL:
		return CPrinterException::ERROR_Printer_WRITEFILE;
		break;
	case POS_ES_READFAIL:
		return CPrinterException::ERROR_Printer_READFILE;
		break;
	case POS_ES_OVERTIME:
		return CPrinterException::ERROR_Printer_WAIT_TIMEOUT;
		break;
	case POS_ES_OTHERERRORS:
		return CPrinterException::ERROR_Printer_OTHER_ERROR;
		break;
	default:
		break;
	}

	return iRet;
}


//////////////////////////////////////////////////////////////////////////
/**
@brief      打开钱箱

@param      (i)void

@retval      long    0: 成功   非0 : 失败 

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
long  CPrinterCommand::PRT_CutPaper()
{
	long iRet = 0;

	// 未加载SDK
	if (hInst==NULL){
		return CPrinterException::ERROR_Printer_LOAD_SDK;
	}

	// 未打开打印机
	if (m_hPrinterID<0){
		return CPrinterException::ERROR_Printer_NOTOPEN;
	}
	/*
		功能：打印缓冲区内容，进纸由参数 iLines 设置的行数并切纸； 
		参数： 
			iPrinterID：打印机句柄，由打开端口的返回值确定；  
			iType：切纸类型 0 全切，1 半切；  
			iLines：进纸行数
	*/


	LONG ret = POS_Control_CutPaper(m_hPrinterID, 0, 5);
	switch (iRet)
	{
	case POS_ES_INVALIDPARA:
		return CPrinterException::ERROR_Printer_PARAMTER_ERROR;
		break;
	case POS_ES_WRITEFAIL:
		return CPrinterException::ERROR_Printer_WRITEFILE;
		break;
	case POS_ES_READFAIL:
		return CPrinterException::ERROR_Printer_READFILE;
		break;
	case POS_ES_OVERTIME:
		return CPrinterException::ERROR_Printer_WAIT_TIMEOUT;
		break;
	case POS_ES_OTHERERRORS:
		return CPrinterException::ERROR_Printer_OTHER_ERROR;
		break;
	default:
		break;
	}

	return iRet;
}