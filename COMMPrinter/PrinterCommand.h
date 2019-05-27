#pragma once
#include "PrinterExp.h"
#include "Command.h"


/**
 @brief  ���ڴ�ӡ������
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
	long ExecuteCommand(void){return 0;}  //ִ������
	long PRT_Open();
	long PRT_Close();
	long PRT_Init();
	long PRT_Reset();
	long PRT_GetStatus();
	long PRT_Print(const WCHAR* strText);
	long PRT_PrintText(CStringArray* sArray, bool bOpenBox);
	long PRT_OpenMoneyBox();

private:
	long PRT_SetAlign(int alignType);				// ���ö��뷽ʽ
	long PRT_FeedLine();							// ��ֽ
	long PRT_CutPaper();							// ��ֽ
	CString SplitAndFormatPrintLine(CString lineMsg);

private:
	HANDLE m_hPrinter;				   // ��ӡ�����
	long m_hPrinterID;				   // ��ӡ�����
	int m_nPort;                       //���ڶ˿ں�
    int m_nBaud;                       //������
	int m_nSize;                       //�ֳ�
};










