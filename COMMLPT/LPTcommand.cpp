#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include "LPT.h"
#include "DebugLog.h"
#pragma comment(lib,"Win.lib")

#define theLPT_TRACE CFileLog::GetInstance(_T("LPT_"))
//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      ��

@retval     ��  

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
OpenLPT::OpenLPT(void)
{
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      (��

@retval     ��  

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
OpenLPT::~OpenLPT(void)
{
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      none

@retval     long 0 : �ɹ�  ��0 : ʧ��

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
long OpenLPT::ExecuteCommand(void)
{
	long iRet = 1;
	iRet = ConnectFunction();
	this->OnComplete(iRet);
	return iRet;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ��

@param      (i)��

@retval     int 0 : �ɹ�  ��0 : ʧ��

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
long OpenLPT::ConnectFunction()
{
	// ��ʼ������
	return (InitializeWinIo() == true)?0:1;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      (i)WORD inport   �˿ں�
			(i)int insize    ��С

@retval     ��  

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
ReadLPT::ReadLPT(WORD inport,int insize)
{
	port = inport;
	size = insize;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      (i)��

@retval     ��  

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
ReadLPT::~ReadLPT(void)
{
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      ��

@retval     long  
@retval     long     0:�ɹ�  1:��ȡʧ��

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
long ReadLPT::ExecuteCommand(void)
{
	long iRet = 1;
	iRet = ReadFunction();
	this->OnComplete(iRet);
	return iRet;
}
//////////////////////////////////////////////////////////////////////////
/**
@brief      ������

@param      ��

@retval     long     0:�ɹ�  1:��ȡʧ��

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
long ReadLPT::ReadFunction()
{
	long retCode = 0;	
	//��ȡ����״̬���ݳɹ�
	DWORD tempValue = 0;
	if (GetPortVal(port, &tempValue, size)){
		m_response = LOBYTE(tempValue);
		retCode = 0;			
	}
	//ʧ��
	else{
		retCode = 1;
	}
	CString sLogString(_T(""));
	sLogString.Format(_T("LPTReadFunction: nPort = %d;size = %d;state = %d"),port,size,m_response);

	theLPT_TRACE->WriteData(_T(">")+sLogString,NULL,0);
	return retCode;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ��

@param      ��

@retval     ��
@exception  ��
*/
//////////////////////////////////////////////////////////////////////////
void ReadLPT::GetLPTResponse(BYTE& state)
{
	state = m_response;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ���캯��

@param      (i)��

@retval     ��  

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
CloseLPT::CloseLPT(void)
{
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ��������

@param      (i)��

@retval     ��  

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
CloseLPT::~CloseLPT(void)
{
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      ִ������

@param      (i)��

@retval     long  \n
0 : �ɹ�  ��0 : ʧ��

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
long CloseLPT::ExecuteCommand(void)
{
	long iRet = 0;
	CloseFunction();
	this->OnComplete(iRet);
	return iRet;
}

//////////////////////////////////////////////////////////////////////////
/**
@brief      �رղ���

@param      none

@retval     none

@exception   ��
*/
//////////////////////////////////////////////////////////////////////////
void CloseLPT::CloseFunction()
{
	// �رղ���
	ShutdownWinIo();
}