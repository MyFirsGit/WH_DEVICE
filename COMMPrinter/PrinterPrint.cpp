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
 @brief      ���캯��
                                                                 
 @param      (i)CStringArray* sArray ��ӡ�����ַ�������
 @param      (i)bool   bOpenBox �Ƿ��ڴ�ӡ��ͬʱ��Ǯ�䣬Ĭ�ϣ�false(����)

 @retval      ��

 @exception   ��
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
 @brief      ��������
                                                                
 @param      (i)��

 @retval      ��

 @exception   ��
*/
//////////////////////////////////////////////////////////////////////////
CPrinterPrint::~CPrinterPrint(void){
	delete m_sArrPrinter;
    m_sArrPrinter = NULL;
}

//////////////////////////////////////////////////////////////////////////
/**
 @brief      ��ӡ����
                                                                 
 @param      (i)��

 @retval      int   \n
                0 : �ɹ�  ��0 : ʧ��

 @exception   ��
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
	// ��ӡ����Ϊ�ղ��Ҳ���Ǯ��
	if (m_sArrPrinter == NULL && m_bOpenBox == false) {
		return  CPrinterException::ERROR_Printer_WRITEFILE;
	}

	DWORD  dwTotalLen = 0 ;
	char* buff = NULL;
	// �д�ӡָ��
	char cCmdRowPrint=0X0A;
	// ��ָֽ��
	char cCmdPageGo[]={0x1B,0x4A,0x60};
	// ��Ǯ��ָ��--------zhong �ӿ��ĵ���û�У����ڴ���֤
	char cCmdOpenbox[] = {0x1B,0x70,0x30,0x08,0x09};
	// ��ӡ�����Ի�ָ��
	char cInit[]={0x1B,0x40};
	// ��ָֽ��
	char cCutPaper[]={0x1D,0x56,0x42,0x12};

	// ѡ����ֽڱ����ַ�ģʽ(��ѡ�����ַ�ģʽ)
	char cCmdSelectMultiByteMode[] = {0x1C,0x26};
	// ȡ�����ֽڱ����ַ�ģʽ
	char cCmdCancleMultiByteMode[] = {0x1C,0x2E};
	// ѡ�����������ַ������
	char cCmdSelectPortuguese[] = {0x1B,0x74,0x03};

	// ѡ���ַ�����  A (9 �� 9)   B (7 �� 9)
	char cCmdSelectFontA[3] = {0x1B,0x21,0x00};
	char cCmdSelectFontB[3] = {0x1B,0x4D,0x01};
	// ѡ��ȱʡ�м��(��ǰ�м��Լ4.23 ���׼�1/6Ӣ��)
	char cCmdSelectDefaultLineHight[2] = {0x1B,0x32};
	// �����Զ����м�ࣨȱʡֵΪ24��Լ4.23 ���׼�1/6Ӣ��)��
	char cCmdSetLineHight[3] = {0x1B,0x33,0x26};
	
	// ���õ����ӡ--------zhong �ӿ��ĵ���û�У����ڴ���֤
	char cCmdSetSingleDirection[3] = {0x1B,0x55,0x1};
    int cnt = 0;
	if(m_sArrPrinter != NULL){
		cnt = (int)m_sArrPrinter->GetCount();
		int iSize = cnt*100 + 25; 
		buff = new char[iSize];
		memset(buff,0,iSize);

		// ��Ǯ��ָ��
		if (m_bOpenBox == true) {
			memcpy(buff,cCmdOpenbox,sizeof(cCmdOpenbox));
			dwTotalLen += sizeof(cCmdOpenbox);
		}

		// ���Ի���ӡ��
		memcpy(buff + dwTotalLen,cInit,sizeof(cInit));
		dwTotalLen += sizeof(cInit);

		// ���ô�ӡ����
		memcpy(buff + dwTotalLen,cCmdSelectMultiByteMode,sizeof(cCmdSelectMultiByteMode));
		dwTotalLen += sizeof(cCmdSelectMultiByteMode);

		// ���õ����ӡ
		memcpy(buff + dwTotalLen,cCmdSetSingleDirection,sizeof(cCmdSetSingleDirection));
		dwTotalLen += sizeof(cCmdSetSingleDirection);


		//// ȡ�ô�ӡ���ݼ���ӡָ��
		//for (int i=0;i<cnt;i++) {
		//	CString msg = m_sArrPrinter->GetAt(i);	// ��ȡ��ǰ��ӡ����
		//	bool isPor = false;						// �Ƿ���������
		//	int codePage = 0;						// ����ҳ
		//	int fontType = 1;						// �ַ������־

			//// ��������
			//if(msg.Find(_T("[CN]")) >= 0){
			//	isPor = false;
			//	msg.Replace(_T("[CN]"),_T(""));
			//	codePage = 54936;
			//	fontType = 0;
			//	// ȱʡ�м��
			//	memcpy(buff + dwTotalLen,cCmdSelectDefaultLineHight,sizeof(cCmdSelectDefaultLineHight));
			//	dwTotalLen += sizeof(cCmdSelectDefaultLineHight);
			//}
			//// ��������
			//else if(msg.Find(_T("[PN]")) >= 0){
			//	isPor = true;
			//	msg.Replace(_T("[PN]"),_T(""));
			//	codePage = 860;
			//	fontType = 1;
			//	// �Զ����м��
			//	memcpy(buff + dwTotalLen,cCmdSetLineHight,sizeof(cCmdSetLineHight));
			//	dwTotalLen += sizeof(cCmdSetLineHight);
			//}
			//// Ӣ��
			//else if(msg.Find(_T("[EN]")) >= 0){
			//	isPor = false;
			//	msg.Replace(_T("[EN]"),_T(""));
			//	codePage = 54936;
			//	fontType = 1;				
			//}

			// ���������С
			//if (fontType ==0 ){
			//	memcpy(buff + dwTotalLen,cCmdSelectFontA,sizeof(cCmdSelectFontA));
			//}
			//else{
			//	memcpy(buff + dwTotalLen,cCmdSelectFontB,sizeof(cCmdSelectFontB));
			//}			
			//dwTotalLen += sizeof(cCmdSelectFontA);

			//// ��ǰ��ӡ���ݱ���ת��
			//CString sOne = _T(" ") + msg;
			//char* pUtf8 = NULL;
			//int utf8Len=WideCharToMultiByte(codePage,NULL,sOne,-1,pUtf8,0,NULL,NULL); 
			//pUtf8 = new char[utf8Len+1];
			//memset(pUtf8,0,utf8Len+1);
			//WideCharToMultiByte(codePage,NULL,sOne,-1,pUtf8,utf8Len,NULL,NULL);

			//// Ĭ��ѡ����ֽڱ����ַ�ģʽ
			//memcpy(buff + dwTotalLen,cCmdSelectMultiByteMode,sizeof(cCmdSelectMultiByteMode));
			//dwTotalLen += sizeof(cCmdSelectMultiByteMode);
			//if(isPor){
			//	// ȡ�����ֽڱ����ַ�ģʽ
			//	memcpy(buff + dwTotalLen,cCmdCancleMultiByteMode,sizeof(cCmdCancleMultiByteMode));
			//	dwTotalLen += sizeof(cCmdCancleMultiByteMode);
			//	// ѡ�����������ַ������
			//	memcpy(buff + dwTotalLen,cCmdSelectPortuguese,sizeof(cCmdSelectPortuguese));
			//	dwTotalLen += sizeof(cCmdSelectPortuguese);
			//}

			// ��ӵ�ǰ��ӡ����
		//	memcpy(buff + dwTotalLen,pUtf8,utf8Len);
		//	dwTotalLen += utf8Len;

		//	delete [] pUtf8;
		//	pUtf8 = NULL;			

		//	if (i < cnt -1) {
		//		memcpy(buff + dwTotalLen,&cCmdRowPrint,1);
		//		dwTotalLen += 1;
		//	}
		//}

		//ȡ�ô�ӡ���ݼ���ӡָ��
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
			// ������ָֽ��
			memcpy(buff + dwTotalLen,cCmdPageGo,sizeof(cCmdPageGo));
			dwTotalLen += sizeof(cCmdPageGo);
			// ������ָֽ��
			memcpy(buff + dwTotalLen,cCutPaper,sizeof(cCutPaper));
			dwTotalLen += sizeof(cCutPaper);
		}
	}
	else{
		if(m_bOpenBox == true){
			buff = new char[sizeof(cCmdOpenbox)];
			memset(buff,0,sizeof(cCmdOpenbox));
			//��Ǯ��ָ��
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
@brief      ���������ӡ��

@param      (i)DWORD dwTotalLen�����
@param      (i)char *buff ��������

@retval      long   \n
0 : �ɹ�  ��0 : ʧ��

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
int CPrinterPrint::WriteToPrint(DWORD dwTotalLen,char *buff)
{
	int iRet = 1;
	//���ڴ�ӡ����OVERLAPPED �ṹ
	OVERLAPPED overlapped;
	//����OVERLAPPED�¼�
	memset(&overlapped,0,sizeof(OVERLAPPED));
	overlapped.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	if (overlapped.hEvent == NULL || overlapped.hEvent == INVALID_HANDLE_VALUE)
	{
		CloseHandle(overlapped.hEvent);
		iRet = CPrinterException::ERROR_Printer_OVERLAPPED_EVENT;
		return iRet;
	}
	//�������ӡ��
	DWORD dwBytesWritten = 0;
	BOOL bWriteState = WriteFile(m_hPrinter,buff,dwTotalLen,&dwBytesWritten,&overlapped);  
	if(bWriteState != TRUE) {
		if (GetLastError() == ERROR_IO_PENDING) {
			iRet = WaitForSingleObject(overlapped.hEvent,Printer_WAIT_TIME);  //�ȴ��ź�
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
 @brief      ִ������
                                                                 
 @param      (i)��

 @retval      long   \n
                 0 : �ɹ�  ��0 : ʧ��

 @exception   ��
*/
//////////////////////////////////////////////////////////////////////////
long CPrinterPrint::ExecuteCommand(void){
   long iRet = 1;
   iRet = PrintFunction();
   this->OnComplete(iRet);
   return iRet;
}