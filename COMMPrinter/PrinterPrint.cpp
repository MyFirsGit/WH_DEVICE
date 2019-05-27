#include "stdafx.h"
#include "PrinterCommand.h"
#include "PrinterException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define  MAX_PTINT_LEN  1000
//////////////////////////////////////////////////////////////////////////
/**
 @brief      构造函数
                                                                 
 @param      (i)CStringArray* sArray 打印内容字符串数组
 @param      (i)bool   bOpenBox 是否在打印的同时打开钱箱，默认：false(不打开)

 @retval      无

 @exception   无
*/
//////////////////////////////////////////////////////////////////////////
CPrinterPrint::CPrinterPrint(CStringArray* sArray, bool bOpenBox){

	m_sArrPrinter = NULL;
	if ( sArray != NULL) {
		if ( sArray->GetSize() > 0 ) {
			m_sArrPrinter = new CStringArray();
			for (int i= 0;i < sArray->GetSize();i++) {
				CString sOne = sArray->GetAt(i);
				m_sArrPrinter->Add(sOne);
			}
		}
	}
	m_bOpenBox = bOpenBox;
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief      析构函数
                                                                
 @param      (i)无

 @retval      无

 @exception   无
*/
//////////////////////////////////////////////////////////////////////////
CPrinterPrint::~CPrinterPrint(void){
	delete m_sArrPrinter;
    m_sArrPrinter = NULL;
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief      打印函数
                                                                 
 @param      (i)无

 @retval      int   \n
                0 : 成功  非0 : 失败

 @exception   无
*/
//////////////////////////////////////////////////////////////////////////
int CPrinterPrint::PrintFunction()
{
	int iRet = 1;
	if (m_hPrinter == NULL || m_hPrinter == INVALID_HANDLE_VALUE) 
	{
		iRet = CPrinterException::ERROR_Printer_NOTOPEN;
		return iRet;
	}
	// 打印内容为空并且不打开钱柜
	if (m_sArrPrinter == NULL && m_bOpenBox == false) {
		return  CPrinterException::ERROR_Printer_WRITEFILE;
	}

	DWORD  dwTotalLen = 0 ;
	char* buff = NULL;
	// 行打印指令
	char cCmdRowPrint=0X0A;
	// 走纸指令
	char cCmdPageGo[]={0x1B,0x4A,0x60};
	// 开钱箱指令--------zhong 接口文档中没有，后期待验证
	char cCmdOpenbox[] = {0x1B,0x70,0x30,0x08,0x09};
	// 打印机初试化指令
	char cInit[]={0x1B,0x40};
	// 切纸指令
	char cCutPaper[]={0x1D,0x56,0x42,0x12};

	// 选择多字节编码字符模式(即选择汉字字符模式)
	char cCmdSelectMultiByteMode[] = {0x1C,0x26};
	// 取消多字节编码字符模式
	char cCmdCancleMultiByteMode[] = {0x1C,0x2E};
	// 选择葡萄牙文字符编码表
	char cCmdSelectPortuguese[] = {0x1B,0x74,0x03};

	// 选择字符字体  A (9 × 9)   B (7 × 9)
	char cCmdSelectFontA[3] = {0x1B,0x21,0x00};
	char cCmdSelectFontB[3] = {0x1B,0x4D,0x01};
	// 选择缺省行间距(当前行间距约4.23 毫米即1/6英寸)
	char cCmdSelectDefaultLineHight[2] = {0x1B,0x32};
	// 设置自定义行间距（缺省值为24，约4.23 毫米即1/6英寸)）
	char cCmdSetLineHight[3] = {0x1B,0x33,0x26};
	
	// 设置单向打印--------zhong 接口文档中没有，后期待验证
	char cCmdSetSingleDirection[3] = {0x1B,0x55,0x1};
    int cnt = 0;
	if(m_sArrPrinter != NULL){
		cnt = (int)m_sArrPrinter->GetCount();
		int iSize = cnt*100 + 25; 
		buff = new char[iSize];
		memset(buff,0,iSize);

		// 开钱箱指令
		if (m_bOpenBox == true) {
			memcpy(buff,cCmdOpenbox,sizeof(cCmdOpenbox));
			dwTotalLen += sizeof(cCmdOpenbox);
		}

		// 初试化打印机
		memcpy(buff + dwTotalLen,cInit,sizeof(cInit));
		dwTotalLen += sizeof(cInit);

		// 设置打印汉字
		memcpy(buff + dwTotalLen,cCmdSelectMultiByteMode,sizeof(cCmdSelectMultiByteMode));
		dwTotalLen += sizeof(cCmdSelectMultiByteMode);

		// 设置单向打印
		memcpy(buff + dwTotalLen,cCmdSetSingleDirection,sizeof(cCmdSetSingleDirection));
		dwTotalLen += sizeof(cCmdSetSingleDirection);


		//// 取得打印内容及打印指令
		//for (int i=0;i<cnt;i++) {
		//	CString msg = m_sArrPrinter->GetAt(i);	// 获取当前打印内容
		//	bool isPor = false;						// 是否葡萄牙文
		//	int codePage = 0;						// 编码页
		//	int fontType = 1;						// 字符字体标志

			//// 繁体中文
			//if(msg.Find(_T("[CN]")) >= 0){
			//	isPor = false;
			//	msg.Replace(_T("[CN]"),_T(""));
			//	codePage = 54936;
			//	fontType = 0;
			//	// 缺省行间距
			//	memcpy(buff + dwTotalLen,cCmdSelectDefaultLineHight,sizeof(cCmdSelectDefaultLineHight));
			//	dwTotalLen += sizeof(cCmdSelectDefaultLineHight);
			//}
			//// 葡萄牙文
			//else if(msg.Find(_T("[PN]")) >= 0){
			//	isPor = true;
			//	msg.Replace(_T("[PN]"),_T(""));
			//	codePage = 860;
			//	fontType = 1;
			//	// 自定义行间距
			//	memcpy(buff + dwTotalLen,cCmdSetLineHight,sizeof(cCmdSetLineHight));
			//	dwTotalLen += sizeof(cCmdSetLineHight);
			//}
			//// 英文
			//else if(msg.Find(_T("[EN]")) >= 0){
			//	isPor = false;
			//	msg.Replace(_T("[EN]"),_T(""));
			//	codePage = 54936;
			//	fontType = 1;				
			//}

			// 设置字体大小
			//if (fontType ==0 ){
			//	memcpy(buff + dwTotalLen,cCmdSelectFontA,sizeof(cCmdSelectFontA));
			//}
			//else{
			//	memcpy(buff + dwTotalLen,cCmdSelectFontB,sizeof(cCmdSelectFontB));
			//}			
			//dwTotalLen += sizeof(cCmdSelectFontA);

			//// 当前打印内容编码转换
			//CString sOne = _T(" ") + msg;
			//char* pUtf8 = NULL;
			//int utf8Len=WideCharToMultiByte(codePage,NULL,sOne,-1,pUtf8,0,NULL,NULL); 
			//pUtf8 = new char[utf8Len+1];
			//memset(pUtf8,0,utf8Len+1);
			//WideCharToMultiByte(codePage,NULL,sOne,-1,pUtf8,utf8Len,NULL,NULL);

			//// 默认选择多字节编码字符模式
			//memcpy(buff + dwTotalLen,cCmdSelectMultiByteMode,sizeof(cCmdSelectMultiByteMode));
			//dwTotalLen += sizeof(cCmdSelectMultiByteMode);
			//if(isPor){
			//	// 取消多字节编码字符模式
			//	memcpy(buff + dwTotalLen,cCmdCancleMultiByteMode,sizeof(cCmdCancleMultiByteMode));
			//	dwTotalLen += sizeof(cCmdCancleMultiByteMode);
			//	// 选择葡萄牙文字符编码表
			//	memcpy(buff + dwTotalLen,cCmdSelectPortuguese,sizeof(cCmdSelectPortuguese));
			//	dwTotalLen += sizeof(cCmdSelectPortuguese);
			//}

			// 添加当前打印内容
		//	memcpy(buff + dwTotalLen,pUtf8,utf8Len);
		//	dwTotalLen += utf8Len;

		//	delete [] pUtf8;
		//	pUtf8 = NULL;			

		//	if (i < cnt -1) {
		//		memcpy(buff + dwTotalLen,&cCmdRowPrint,1);
		//		dwTotalLen += 1;
		//	}
		//}

		//取得打印内容及打印指令
		for (int i=0;i<cnt;i++) {
			CString sOne =  m_sArrPrinter->GetAt(i);
			USES_CONVERSION;
			char* pMessage = T2A(sOne);
			memcpy(buff + dwTotalLen,pMessage,GetAactualCharacterMemarySize(sOne));
			dwTotalLen += sOne.GetLength()+GetAactualCharacterMemarySize(sOne);
			if (i < cnt -1) {
				memcpy(buff + dwTotalLen,&cCmdRowPrint,1);
				dwTotalLen += 1;
			}
		};
		if (cnt > 0) {
			// 设置走纸指令
			memcpy(buff + dwTotalLen,cCmdPageGo,sizeof(cCmdPageGo));
			dwTotalLen += sizeof(cCmdPageGo);
			// 设置切纸指令
			memcpy(buff + dwTotalLen,cCutPaper,sizeof(cCutPaper));
			dwTotalLen += sizeof(cCutPaper);
		}
	}
	else{
		if(m_bOpenBox == true){
			buff = new char[sizeof(cCmdOpenbox)];
			memset(buff,0,sizeof(cCmdOpenbox));
			//开钱箱指令
			memcpy(buff,cCmdOpenbox,sizeof(cCmdOpenbox));
			dwTotalLen = sizeof(cCmdOpenbox);
		}
	}

	int nTimes = dwTotalLen/MAX_PTINT_LEN;
	int nRemainder = dwTotalLen%MAX_PTINT_LEN;

	for (int i = 0;i<nTimes;i++)
	{	
		char szWriteBuff[MAX_PTINT_LEN];
		memset(szWriteBuff,0,MAX_PTINT_LEN);
		memcpy(szWriteBuff,buff + i*MAX_PTINT_LEN,MAX_PTINT_LEN);
		iRet = WriteToPrint(MAX_PTINT_LEN,szWriteBuff);
	}
	if (nRemainder != 0)
	{
		char szWriteBuff[MAX_PTINT_LEN];
		memset(szWriteBuff,0,MAX_PTINT_LEN);
		memcpy(szWriteBuff,buff + nTimes*MAX_PTINT_LEN,dwTotalLen - nTimes *MAX_PTINT_LEN);
		iRet = WriteToPrint(dwTotalLen - nTimes *MAX_PTINT_LEN,szWriteBuff);
	}

	if (NULL != buff) {
		delete [] buff;
		buff = NULL;
	}	

	Sleep((cnt/2)*800);
	return iRet;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      发送命令到打印机

@param      (i)DWORD dwTotalLen命令长度
@param      (i)char *buff 命令内容

@retval      long   \n
0 : 成功  非0 : 失败

@exception   无
*/
//////////////////////////////////////////////////////////////////////////
int CPrinterPrint::WriteToPrint(DWORD dwTotalLen,char *buff)
{
	int iRet = 1;
	//串口打印机的OVERLAPPED 结构
	OVERLAPPED overlapped;
	//生成OVERLAPPED事件
	memset(&overlapped,0,sizeof(OVERLAPPED));
	overlapped.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	if (overlapped.hEvent == NULL || overlapped.hEvent == INVALID_HANDLE_VALUE)
	{
		CloseHandle(overlapped.hEvent);
		iRet = CPrinterException::ERROR_Printer_OVERLAPPED_EVENT;
		return iRet;
	}
	//输出到打印机
	DWORD dwBytesWritten = 0;
	BOOL bWriteState = WriteFile(m_hPrinter,buff,dwTotalLen,&dwBytesWritten,&overlapped);  
	if(bWriteState != TRUE) {
		if (GetLastError() == ERROR_IO_PENDING) {
			iRet = WaitForSingleObject(overlapped.hEvent,Printer_WAIT_TIME);  //等待信号
			switch( iRet) {
			  case WAIT_ABANDONED :
				  iRet = CPrinterException::ERROR_Printer_WAIT_ABANDONED ;
				  break;
			  case WAIT_OBJECT_0 : 
				  iRet = 0;
				  break;
			  case WAIT_TIMEOUT : 
				  iRet = CPrinterException::ERROR_Printer_WAIT_TIMEOUT;
				  ::CancelIo(m_hPrinter);
				  break;
			  case WAIT_FAILED :
				  iRet =  CPrinterException::ERROR_Printer_WRITEFILE;
				  break;
			}
		}
		else{
			iRet = CPrinterException::ERROR_Printer_WRITEFILE;
		}
	}
	else{
		iRet = 0;
	}
	CloseHandle(overlapped.hEvent);
	return iRet;
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief      执行命令
                                                                 
 @param      (i)无

 @retval      long   \n
                 0 : 成功  非0 : 失败

 @exception   无
*/
//////////////////////////////////////////////////////////////////////////
long CPrinterPrint::ExecuteCommand(void){
   long iRet = 1;
   iRet = PrintFunction();
   this->OnComplete(iRet);
   return iRet;
}