#pragma once
#include "PrinterExp.h"
#include "Command.h"


/**
 @brief  串口打印机命令
*/
class PRINTER_API CPrinterCommand : public CCommand
{
public:
	typedef enum _enum_align_format{
		ALIGN_LEFT		= 0,
		ALIGN_MID		= 1,
		ALIGN_RIGHT		= 2,
	}ENUM_ALIGN_FORMAT;

	CPrinterCommand(int nPort=1,int nBaud=9600 , int nSize = 8);   
    ~CPrinterCommand(void);
public:
	long ExecuteCommand(void){return 0;}  //执行命令
	long PRT_Open();
	long PRT_Close();
	long PRT_Init();
	long PRT_Reset();
	long PRT_GetStatus();
	long PRT_Print(const WCHAR* strText);
	long PRT_PrintText(CStringArray* sArray, bool bOpenBox);
	long PRT_OpenMoneyBox();

private:
	long PRT_SetAlign(int alignType);				// 设置对齐方式
	long PRT_FeedLine();							// 走纸
	long PRT_CutPaper();							// 切纸
	CString SplitAndFormatPrintLine(CString lineMsg);

private:
	HANDLE m_hPrinter;				   // 打印机句柄
	long m_hPrinterID;				   // 打印机句柄
	int m_nPort;                       //串口端口号
    int m_nBaud;                       //波特率
	int m_nSize;                       //字长
};










