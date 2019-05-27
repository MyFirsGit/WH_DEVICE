// OGeneralLib.h: interface for the GeneralLib.
//
//////////////////////////////////////////////////////////////////////
/*<ModuleInfo>
<Comment>��
<��Ʒ����>��������̬��
<��    ��>��V1.0.0
<��������>��2004.2
<��	   ��>��������
<����˵��>���ṩ��������Ҫ�õ��ĸ����������࣬����ϵͳ�������ܡ�����ת�������ֲ�����
			�ַ����������ļ������ȡ�
<����ģ��>����
</Comment>
</ModuleInfo>*/

#if !defined(AFX_GeneralLib_H__C1A33451_2434_11D5_B18A_5254AB1A7D30__INCLUDED_)
#define AFX_GeneralLib_H__C1A33451_2434_11D5_B18A_5254AB1A7D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#pragma warning(disable:4100)

#include <tchar.h>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <stack>
#include <utility>
#include <algorithm>
#include <Oaidl.h>
#include <assert.h>

using namespace std;

#include "stlunicode.h"

//******�궨��******// start

//�ͷ�ָ��ĺ�
#define RELEASE(p) \
	if (p) \
	{ \
		delete p; \
		p = NULL; \
	}

// �����м�˵�������ڱ���ʱ��Build������ʾ��Ӧ���
// ���磺�ڳ�����������磺#pragma PROGMSG(�Ժ�������)�����ڱ���ʱ��Build������ʾ����������˫���Ϳɵ��˴���
#define PROGSTR2(x)	#x
#define PROGSTR(x)	PROGSTR2(x)
#define PROGMSG(desc) message(__FILE__"("PROGSTR(__LINE__)"):"#desc)

#if !defined(FAIL)
#define		FAIL		1
#endif

#if !defined(SUCCESS)
#define		SUCCESS		0
#endif

//******�궨��******// end


//******ϵͳ��������OSysFunc.cpp******// begin

BOOL bShutDown();
// 	��    �ܣ��رջ���(for windows)
// 	��    �룺��
// 	��    ������
//	�� �� ֵ��TRUE - �ɹ���FALSE - ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

BOOL bReBoot();		
// 	��    �ܣ�������������(for windows)
// 	��    �룺��
// 	��    ������
//	�� �� ֵ��TRUE - �ɹ���FALSE - ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

tstring strGetErrMsg(DWORD* p_dwErrCode);	
// 	��    �ܣ��õ���ǰ�̵߳����һ������Ĵ�����������
// 	��    �룺��
// 	��    ����p_dwErrCode	���صĴ���ţ����ΪNULL����ʾ������
//	�� �� ֵ���������ľ�������,���û�д��󣬷��ؿ��ַ���		
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iGetModuleVersionInfo(LPCTSTR p_pcFileName, 
						   HINSTANCE p_hInstance,	
						   tstring& p_pstrName,	
						   tstring& p_pstrInterName, 
						   tstring& p_pstrVersion);
// 	��    �ܣ���ȡĳģ��İ汾��Ϣ
// 	��    �룺p_pcFileName		ģ���������ΪNULL����ʹ��p_hInstance 
//			  p_hInstance		ģ���HINSTANCE
// 	��    ����p_pstrName		��Ʒ��,Version�е�ProductName
//			  p_pstrInterName	Version�е�InterName
//			  p_pstrVersion		Version�е�ProductVerion
//	�� �� ֵ��SUCCESS	�ɹ�
//			  FAIL	ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iGetCPUID(TCHAR *p_pcCPUID);
// 	��    �ܣ���ȡCPU��ID��
// 	��    �룺��
// 	��    ����p_pcCPUID		CPU��ID��
//	�� �� ֵ��SUCCESS	�ɹ�
//			  FAIL		ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iGetMacAddress(TCHAR *p_pcMACAddress);
// 	��    �ܣ���ȡMAC��ַ
// 	��    �룺��
// 	��    ����p_pcMACAddress		MAC��ַ
//	�� �� ֵ��0    �ɹ�
//			  ���� ������
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iGetHardwareID(TCHAR *p_pcHardwareID);
// 	��    �ܣ���ȡӲ�̵���ˮ��
// 	��    �룺��
// 	��    ����p_pcHardwareID		Ӳ�̵���ˮ��
//	�� �� ֵ��SUCCESS	�ɹ�
//			  FAIL	ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

BOOL bControlServices(LPCTSTR lpServiceName, DWORD fdwControl);
// 	��    �ܣ�����ϵͳ����
// 	��    �룺lpServiceName			�������ƣ�����˵���ο�MSDN
//			  fdwControl			�������������˵���ο�MSDN
// 	��    ������
//	�� �� ֵ��SUCCESS	�ɹ�
//			  FAIL	ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

//  BOOL SetEnvironmentVariable(
//	  LPCTSTR lpName,  
//	  LPCTSTR lpValue  
//	  );
// 	��    �ܣ�����ָ����������
// 	��    �룺lpName,  // ����������
//			  lpValue  // �趨�ı���ֵ
// 	��    ������
//	�� �� ֵ����
//	˵    ����API����

//******ϵͳ��������OSysFunc.cpp******// end


//******һ�㸨������OGenericFunc.cpp******// begin

void vDelayMsg(DWORD p_dwTime);
// 	��    �ܣ����������ӳٵȴ�����
// 	��    �룺p_dwTime		�ӳ�ʱ�䣨���룩
// 	��    ������
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

int	iByteArraycmp(PBYTE p_pbArrayOne, long p_lLenOne/* = -1*/,
			 PBYTE p_pbArrayTwo, long p_lLenTwo/* = -1*/);
// 	��    �ܣ�BYTE����ȽϺ���
// 	��    �룺p_pbArrayOne		BYTE����1
//			  p_lLenOne			BYTE����1�ĳ���,�������-1����ֱ��ȡp_pbArrayOne���ַ�������
//			  p_pbArrayTwo		BYTE����2
//			  p_lLenTwo			BYTE����2�ĳ���,�������-1����ֱ��ȡp_pbArrayTwo���ַ�������
// 	��    ������
//	�� �� ֵ��<0	����1С������2
//			  =0	����1��������2
//			  >0	����1��������2
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iGetVerify(BYTE *p_pbDesc, PBYTE p_pbSrc, long p_lSrcLen);
// 	��    �ܣ�����У��λ����
// 	��    �룺p_pbSrc		Դ��������
//			  p_lSrcLen		Դ���ݳ��ȣ����鳤�ȣ�
// 	��    ����p_pbDesc		�������ݽ����������õ���У��λ
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
//	��	  �ߣ�������
//	�������ڣ�2004.2

//******һ�㸨������OGenericFunc.cpp******// end


//******��������ת������ODatatypeCtrl.cpp******// begin

int iFormatNum(TCHAR *p_pcResultNum, TCHAR *p_pcSrcNum, int p_iDotdigit, int p_iNumGrup, bool p_bZeroShow);
//	��    �ܣ����ָ�ʽת�����¿������->����ѡ��->���֣�
//	��    �룺p_pcSrcNum		��ʽת��ǰ�����ִ�
//			  p_iDotdigit		С�����λ��
//			  p_iNumGrup		����������ʾ��ʽ
//				0 �� 123456789
//				1 �� 123,456,789
//				2 �� 12,34,56,789
//			  p_bZeroShow		����ʼ��ʾ
//				true �� .7
//				false �� 0.7
//	��    ����p_pcResultNum	��ʽת��������ִ�
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iFormatCurrency(TCHAR *p_pcResultCurrency, TCHAR *p_pcSrcCurrency, int p_iCurFlag, int p_iDotdigit, int p_iNumGrup, bool p_bZeroShow);
//	��    �ܣ����Ҹ�ʽת�����¿������->����ѡ��->���ң�
//	��    �룺p_pcSrcCurrency		��ʽת��ǰ�Ļ����ַ���
//			  p_iCurFlag			���ҷ���
//				0 �� ����ң�����
//				1 �� ��Ԫ���磩
//				2 �� Ӣ�����꣩
//			  p_iDotdigit			С�����λ��
//			  p_iNumGrup			����������ʾ��ʽ
//			 	0 �� 123456789
//				1 �� 123,456,789
//				2 �� 12,34,56,789
//			  p_bZeroShow			����ʼ��ʾ
//				true �� .7
//				false �� 0.7
//	��    ����p_pcResultCurrency	��ʽת����Ļ����ַ���
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase10Encode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	��    �ܣ�BASE10����(��֧��UNICODE)��
//	��    �룺p_pcSrc		δ����Ķ����ƴ��롣ÿ���ַ���ASCII��Ҫ��0��127֮�䣬���鳤�Ȳ��ɳ���512��
//			  p_iSrcLen		�������ĳ���
//	��    ����p_pcResult	�������Base10����,������ݵ���󳤶ȿɴ�1234�ֽڡ�
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase10Decode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	��    �ܣ�BASE10����(��֧��UNICODE)��
//	��    �룺p_pcSrc		δ�����Base10����,�������ݵ���󳤶Ȳ��ɳ���1234�ֽڡ�
//	��    ����p_pcResult	������Ķ����ƴ���,������ݵ���󳤶ȿɴ�512�ֽڡ�
//			  p_piResultLen	����õ��Ĵ���ĳ���
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase10ExEncode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	��    �ܣ�BASE10Ex����(��֧��UNICODE)��һ�ζ��������ݣ���ÿ8��BIT��Ӧ��һ���ַ�������ASCIIֵ��ʾ����("AB" - "065066")
//	��    �룺p_pcSrc		δ����Ķ����ƴ���
//			  p_iSrcLen		�������ĳ���
//	��    ����p_pcResult	�������Base10Ex����
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase10ExDecode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	��    �ܣ�BASE10Ex����(��֧��UNICODE)��("065066" - "AB")
//	��    �룺p_pcSrc		δ�����Base10Ex����
//	��    ����p_pcResult	������Ķ����ƴ���
//			  p_piResultLen	����õ��Ĵ���ĳ���
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase16Encode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	��    �ܣ�BASE16����(��֧��UNICODE)��
//	��    �룺p_pcSrc		δ����Ķ����ƴ���
//			  p_iSrcLen		�������ĳ���
//	��    ����p_pcResult	�������Base16����
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase16Decode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	��    �ܣ�BASE16����(��֧��UNICODE)��
//	��    �룺p_pcSrc		δ�����Base16����
//	��    ����p_pcResult	������Ķ����ƴ���
//			  p_piResultLen	����õ��Ĵ���ĳ���
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase16ExEncode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	��    �ܣ�BASE16Ex����(��֧��UNICODE)����һ�ζ��������ݣ�ÿ4��BITת��Ϊһ���ַ�(0x01ת��Ϊ0x30,0x31)
//	��    �룺p_pcSrc		δ����Ķ����ƴ���
//			  p_iSrcLen		�������ĳ���
//	��    ����p_pcResult	�������Base16Ex����
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase16ExDecode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	��    �ܣ�BASE16Ex����(��֧��UNICODE)��ÿ�����ַ��ϳ�һ������(0x31,0x32ת��Ϊ0x12)
//	��    �룺p_pcSrc		δ�����Base16Ex����
//	��    ����p_pcResult	������Ķ����ƴ���
//			  p_piResultLen	����õ��Ĵ���ĳ���
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase64Encode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	��    �ܣ�BASE64����(��֧��UNICODE)
//	��    �룺p_pcSrc		δ����Ķ����ƴ���
//			  p_iSrcLen		�������ĳ���
//	��    ����p_pcResult	�������Base64����
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vBase64Decode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	��    �ܣ�BASE64����(��֧��UNICODE)
//	��    �룺p_pcSrc		δ�����Base64����
//	��    ����p_pcResult	������Ķ����ƴ���
//			  p_piResultLen	����õ��Ĵ���ĳ���
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

int	iSglHexCharToInt(TCHAR p_cHexChar);
//	��    �ܣ�ʮ�������ַ�ת����
//	��    �룺p_cHexChar		ʮ�������ַ�('0'~'9','a'~'f','A'~'F')
//	��    ������
//	�� �� ֵ���ַ���Ӧ������(0~15)
//			  -1 ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

TCHAR cSglHexIntToChar(int p_iHexInt);
//	��    �ܣ�ʮ����������ת�ַ�
//	��    �룺p_iHexInt		ʮ����������(0~15)
//	��    ������
//	�� �� ֵ�����ֶ�Ӧ���ַ�('0'~'9','a'~'f','A'~'F')
//			  ='\0' ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

PBYTE pbSafeAryToPByte(SAFEARRAY* p_psa, long* p_plLen);
//	��    �ܣ�SAFEARRAYתΪBYTE����
//	��    �룺p_psa		SAFEARRAY
//	��    ����p_plLen		BYTE���鳤��
//	�� �� ֵ��ת�����BYTE����
//	��	  �ߣ�������
//	�������ڣ�2004.2

SAFEARRAY* saPByteToSafeAry(PBYTE p_pbData, long p_lLen /* = -1*/);
//	��    �ܣ�BYTE����תΪSAFEARRAY
//	��    �룺p_pbData	BYTE����
//			  p_lLen		BYTE���鳤��
//	��    ������
//	�� �� ֵ��ת�����SAFEARRAY
//	��	  �ߣ�������
//	�������ڣ�2004.2

TCHAR* pcSafeAryToChar(SAFEARRAY *p_psa, long *p_plLen);
//	��    �ܣ�SAFEARRAYתΪ�ַ�������
//	��    �룺p_psa		SAFEARRAY
//	��    ����p_plLen		�ַ������鳤��
//	�� �� ֵ��ת������ַ�������
//	��	  �ߣ�������
//	�������ڣ�2004.2

SAFEARRAY* saCharToSafeAry(TCHAR *p_pcData, long p_lLen);
//	��    �ܣ��ַ�������תΪSAFEARRAY
//	��    �룺p_pcData	�ַ�������
//			  p_lLen		�ַ������鳤��
//	��    ������
//	�� �� ֵ��ת�����SAFEARRAY
//	��	  �ߣ�������
//	�������ڣ�2004.2

int* piSafeAryToInt(SAFEARRAY *p_psa, long *p_plLen);
//	��    �ܣ�SAFEARRAYתΪ��������
//	��    �룺p_psa		SAFEARRAY
//	��    ����p_plLen		�������鳤��
//	�� �� ֵ��ת�������������
//	��	  �ߣ�������
//	�������ڣ�2004.2

SAFEARRAY* saIntToSafeAry(int *p_piData, long p_lLen);
//	��    �ܣ���������תΪSAFEARRAY
//	��    �룺p_piData	��������
//			  p_lLen		�������鳤��
//	��    ������
//	�� �� ֵ��ת�����SAFEARRAY
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iNumToChinese(TCHAR *p_pcResult, LPCTSTR p_pcSrc, int p_iChangeFlag);
//	��    �ܣ����������������Ĵ�д��ʾ��ֵ��ת�����������ֽ����Ľ���ת��
//	��    �룺p_pcSrc		���������ֵ��ַ���(С��λ���������λ��ֻ����ǰ��λ)
//			  p_iChangeFlag	ת����־ 1 - {"��","һ","��","��","��","��","��","��","��","��"}
//									 2 - {"��","Ҽ","��","��","��","��","½","��","��","��"}
//	��    ����p_pcResult	���Ĵ�д���ַ���
//	�� �� ֵ��SUCCESS - �ɹ�
//			  FAIL - ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iGetTodayWeek(TCHAR *p_pcResult, int p_iFlag);
//	��    �ܣ���ȡ��ǰ������
//	��    �룺p_iFlag		������ʽ
//				1 - "��һ����������"
//				2 - "SunMonTueWedThuFriSat"
//	��    ����p_pcResult	����ַ���
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iGetTodayMonth(TCHAR *p_pcResult, int p_iFlag);
//	��    �ܣ���ȡ��ǰ���·�
//	��    �룺p_iFlag		������ʽ
//				1 - "һ�����������߰˾�ʮʮһʮ��"
//				2 - "JanFebMarAprMayJunJulAugSepOctNovDec"
//	��    ����p_pcResult	����ַ���
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iGetTodayDate( TCHAR *p_pcResult, int p_iFlag);
//	��    �ܣ���õ���ϵͳ����, ���ַ������� 
//	��    �룺p_iFlag		���ڴ���ʽ 
//				0 - YYYYMMDD					
//				1 - YYYY/MM/DD					
//				2 - YYYY-MM-DD				
//				3 - MMDDYYYY					
//				4 - MM/DD/YYYY					
//				5 - MM-DD-YYYY					
//				6 - DDMMYYYY					
//				7 - DD/MM/YYYY					
//				8 - DD-MM-YYYY					
//				9 - YYYY��MM��DD��				
//	��    ����p_pcResult	����ַ���
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iBCDToChar(TCHAR *p_pcResult, TCHAR p_cBCDBuf);
//	��    �ܣ�BCD��ת��Ϊ�ַ���
//	��    �룺p_cBCDBuf		��Ҫת����BCD�룬�������BCD�벻�Ϸ�ʱ��Ҳһ��������д�������������ֵΪʧ�ܡ�
//	��    ����p_pcResult	ת������ַ���
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
//	��	  �ߣ�������
//	�������ڣ�2004.2

TCHAR cCharToBCD(TCHAR *p_pcCharBuf);	
//	��    �ܣ��ַ���ת��ΪBCD ��
//	��    �룺p_pcCharBuf		�ַ���ָ��
//	��    ������
//	�� �� ֵ��ת�����BCD��,�������ֵ����OXFF����ʾ���벻�Ϸ���ת��ʧ�ܡ�
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iBCDToASCII(TCHAR *p_pcResult, int p_iNum, TCHAR *p_pcBCDBuf);	
//	��    �ܣ�BCD��ת��ΪASCII��
//	��    �룺p_pcASCII		���BCD��ָ�룬�������BCD���в��Ϸ�����ʱ��Ҳһ��������д�������������ֵΪʧ�ܡ�
//			  p_iNum		BCD�볤��
//	��    ����p_pcResult	���ASCII��ָ��
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
//	��	  �ߣ�������
//	�������ڣ�2004.2

int iASCIIToBCD( TCHAR *p_pcResult, TCHAR *p_pcASCII, int p_iNum); 
//	��    �ܣ�ASCII��ת��ΪBCD��
//	��    �룺p_pcASCII		���ASCII��ָ��,��������к��в��Ϸ����ݣ����ڶ��䴦����������ʧ�ܡ�
//			  p_iNum		ASCII�볤��
//	��    ����p_pcResult	���BCD��ָ��
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vHexToASCII(BYTE *p_pcResult, BYTE *p_pcHexBuf, int p_iLen ); 
//	��    �ܣ�ʮ��������ת��ΪASCII��
//	��    �룺p_pcHexBuf		��ת����ʮ�������ַ��� 
//			  p_iLen			ʮ�������ַ����ĳ���
//	��    ����p_pcResult		���ת�����ASCII�룬���ȵ���ʮ�������ַ������ȵ�2��
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vASCIIToHex(BYTE *p_pcResult, BYTE *p_pcASCBuf, int p_iLen);
//	��    �ܣ�ASCII��ת��Ϊʮ��������
//	��    �룺p_pcASCBuf		��ת����ASCII��
//			  p_iLen			ASCII�볤��
//	��    ����p_pcResult		ת�����ʮ�������ַ���
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

int  iBCDToInt( TCHAR p_cBCDBuf);
//	��    �ܣ�BCD��ת��Ϊint��
//	��    �룺p_pcBCDBuf		��ת����BCD��
//	��    ������
//	�� �� ֵ��ת���ɵ�int������,�������Ϊ�Ƿ����ݣ����أ�1��
//	��	  �ߣ�������
//	�������ڣ�2004.2

long lBCDToLong( TCHAR *p_pcBCDBuf, int p_iLen);
//	��    �ܣ�BCD��ת��ΪLONG��
//	��    �룺p_pcBCDBuf		��ת����BCD��
//			  p_iLen			BCD���ֽڳ��ȣ����ɳ���4���ֽڣ�����������ֵ����long���͵���ֵ��Χ������4�ֽڷ���ʧ��
//	��    ������
//	�� �� ֵ��ת���ɵ�Long������,�������Ϊ�Ƿ����ݣ����أ�1��
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vHexToChar( BYTE *p_pcResult, BYTE p_cHexchar );
//	��    �ܣ�ʮ����������ת��Ϊ�ַ���
//	��    �룺p_cHexchar		��Ҫת����ʮ����������
//	��    ����p_pcResult		ת������ַ���
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

int  iDoubleToASCII(TCHAR *p_pcResult,double p_dDouble, int p_iwidth,int p_iFlag, int p_iDec);
//	��    �ܣ�Double��ת��ΪASCII�� 
//	��    �룺p_dDouble		��ת����double������
//			  p_iwidth		���ɴ�����
//			  p_iFlag		0-��С����, 1-����
//			  p_iDec		С�����λ��
//	��    ����p_pcResult	ת������ASCII��
//	�� �� ֵ��>= 0	�ɹ�						
//		      <  0	�򳤶ȵ�ԭ�����ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

int  iIntToASCII(TCHAR *p_pcResult, int p_iSrc, int p_iwidth);
//	��    �ܣ�Int��ת��ΪASCII�� 
//	��    �룺p_iSrc		��ת����Int������
//			  p_iwidth		���ɴ�����
//	��    ����p_pcResult	ת������ASCII��
//	�� �� ֵ��>= 0	�ɹ�						
//		      <  0	�򳤶ȵ�ԭ�����ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

BOOL bByteStream2Variant(PBYTE p_pbSrc,VARIANT& p_varResult,ULONG p_ulSrcLen);
//	��    �ܣ����ֽ�����װΪVARIANT����
//	��    �룺p_pbSrc			��Ҫת�����ֽ�����
//			  p_ulSrcLen 		�ֽ����鳤��
//	��    ����p_varResult		ת�����VARIANT
//	�� �� ֵ��TRUE - �ɹ�	FALSE - ʧ��
//	��	  �ߣ����ı�
//	�������ڣ�2004.10

PBYTE pbyVariant2ByteStream(const VARIANT& p_varSrc,ULONG* p_pulResultLen);
//	��    �ܣ���VARIANT���͵�ת��Ϊ�ֽ���,�û���ʹ���귵�صĵ�ָ�����Ҫ����ɾ��
//	��    �룺p_varSrc			��Ҫת����VARIANT
//	��    ����p_pulResultLen	ת������ֽڳ���
//	�� �� ֵ��ת������ֽ�����
//	��	  �ߣ����ı�
//	�������ڣ�2004.10
//******��������ת������ODatatypeCtrl.cpp******// end


//******���ֲ�������ONumberCtrl.cpp******// begin

int iGetIntersection(float p_fAL, float p_fAH, float p_fBL, float p_fBH, float& p_fCL, float& p_fCH);
// 	��    �ܣ��󼯺�A(p_fAL,p_fAH)�뼯��B(p_fBL,p_fBH)�Ľ���C(p_fCL,p_fCH)
// 	��    �룺����A(p_fAL,p_fAH)
//			  ����B(p_fBL,p_fBH)
// 	��    ��������C(p_fCL,p_fCH)
//	�� �� ֵ��SUCCESS �ɹ�
//			  FAIL    ʧ��
//	��	  �ߣ�������
//	�������ڣ�2004.2

//******���ֲ�������ONumberCtrl.cpp******// end


//******�ļ�������OFileCtrl.cpp******// begin
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "fci.h"
#include "fdi.h"

/*
 * �趨ѹ�����ļ��Ĵ�С�����ڽ�����ļ�ѹ���ָ�������̡�
 * ����ֻ�Ǽ򵥵�ѹ����һ���ļ���������Ϊһ���㹻���ֵ��
 */
#define MEDIA_SIZE			1000000000

/*
 * ��ѹ���ļ��ﵽ��ֵʱ���Զ�FLUSH��
 */
#define FOLDER_THRESHOLD	900000

/*
 * ѹ����ʽ
 */
#define COMPRESSION_TYPE    tcompTYPE_MSZIP

#define		FILENAME_LEN	256
#define		PATH_LEN		1000

struct tFileName{
	TCHAR				cFileName[FILENAME_LEN];
	FILETIME			ftCreationTime; 
	struct tFileName*	pNext; 
};

class OFileCtrl
{
public:

	BOOL bCompress(TCHAR *p_pcSrcName, TCHAR *p_pcCabName);
	//	��    �ܣ��ļ�ѹ��(��֧��UNICODE)
	//	��    �룺p_pcSrcName		��ѹ����ȫ·�����ļ�����ȱʡ·��Ϊ��ǰ·����
	//	          p_pcCabName		ѹ�����γɵ�ѹ���ļ����ļ���
	//	��    ������
	//	�� �� ֵ���ɹ�����TRUE,ʧ�ܷ���FALSE
	//	��	  �ߣ�������
	//	�������ڣ�2004.2

	BOOL bDecompress(TCHAR *p_pcCabName, TCHAR *p_pcDestPath);
	//	��    �ܣ��ļ���ѹ(��֧��UNICODE)
	//	��    �룺p_pcCabName		����ѹ��ȫ·�����ļ�����ȱʡ·��Ϊ��ǰ·����
	//	          p_pcDestPath		��ѹ���γɵ��ļ��Ĵ��·��
	//	��    ������
	//	�� �� ֵ���ɹ�����TRUE,ʧ�ܷ���FALSE
	//	��	  �ߣ�������
	//	�������ڣ�2004.2

	int iFileSplt(const TCHAR* p_pcSrcPath, const TCHAR* p_pcSrcFileName, UINT p_uiNewFileLen);
	//	��    �ܣ��ļ��ָ��һ���ļ�����С�ָ�Ϊ���ɸ����ļ������ļ�����������Ϊ��1_���ļ�����2_���ļ�������
	//	��    �룺p_pcSrcPath		���ָ��ļ����ڵ�·��
	//	          p_pcSrcFileName	���ָ��ļ����ļ���
	//	          p_uiNewFileLen	���ļ��Ĵ�С
	//	��    ������
	//	�� �� ֵ���γ����ļ��ĸ���
	//	��	  �ߣ�������
	//	�������ڣ�2004.2

	int iFileBind(const TCHAR* p_pcSrcPath, const TCHAR* p_pcDescPath, const TCHAR* p_pcDescFileName);
	//	��    �ܣ��ļ��󶨣���ĳĿ¼�µĶ���ļ��ϲ�Ϊһ���ļ�
	//	��    �룺p_pcSrcPath		ԴĿ¼��·�������Ϊ�գ�ֱ�ӷ���ʧ��
	//	          p_pcDescPath		�ϲ����ļ���ŵ�·�������Ϊ�գ�Ĭ��Ϊ��ǰĿ¼
	//	          p_pcDescFileName	�ϲ����ļ����ļ���
	//	��    ������
	//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1
	//	��	  �ߣ�������
	//	�������ڣ�2004.2

	int iListFiles(TCHAR ***p_pppcResult, LPCTSTR p_pcPath, int p_iListBy, int p_iAsceFlag);
	//	��    �ܣ��о�ĳĿ¼�������ļ����ļ���,������,�����ҵ����ļ����洢���ַ���������
	//	��    �룺p_pcPath			Ŀ¼��·��
	//	          p_iListBy			1�����ļ�������2�����ļ�����ʱ������
	//	          p_pAsceFlag		0������1������
	//	��    ����p_pppcResult		�洢������ַ�������
	//	�� �� ֵ������Ĵ�С���ļ���������
	//	��	  �ߣ�������
	//	�������ڣ�2004.2

	int	iSearchFiles(TCHAR ***p_pppcResult, LPCTSTR p_pcPath,  LPCTSTR p_lpFileName);
	//	��    �ܣ���ָ��Ŀ¼�°��ؼ��ֲ����ļ���,�����ҵ����ļ����洢���ַ���������
	//	��    �룺p_pcPath			Ŀ¼��·��
	//	          p_lpFileName		Ҫ���ҵ��ļ��������԰���ͨ���*,?��
	//	��    ����p_pppcResult		�洢������ַ�������
	//	�� �� ֵ������Ĵ�С���ļ���������
	//	��	  �ߣ�������
	//	�������ڣ�2004.2

	BOOL bSetDirectoryAttributes(LPCTSTR p_lpDirectoryName, DWORD p_dwAttributes, int p_iChangeAllFlag);
	//	��    �ܣ�����Ŀ¼������
	//	��    �룺p_lpDirectoryName	Ŀ¼��·��
	//	          p_dwAttributes		Ҫ���õ�����
	//			  p_iChangeAllFlag		�Ƿ�����������ļ��е����ԣ�0����1���ǣ�	  
	//	��    ������
	//	�� �� ֵ��true - �ɹ�
	//			  false - ʧ��
	//	��	  �ߣ�������
	//	�������ڣ�2004.2

	OFileCtrl();
	virtual ~OFileCtrl();

	// ��ȡ��ǰ·��
	// GetCurrentDirectory
	
	// ��ȡϵͳ·��
	// GetSystemDirectory
	
	// ��ȡ��ʱ�ļ���·��
	// GetTempPath

	// ��ȡָ���ļ�������·����
	// GetFullPathName 

	// �����ļ������ԣ�ֻ����ִ�У����أ�ϵͳ��
	// SetFileAttributes

protected:
	HFCI m_hfci;                   // context

private:
	BOOL FlushCab();
	BOOL AddFile2Cab(TCHAR *fileName);
	BOOL CreateCabinet(TCHAR *CABName);
	void vCmpFiles(tFileName* p_ptResultHead, LPCTSTR p_pcPath, int p_iListBy, int p_iAsceFlag, int *p_piFileCount);
	void vFindFile(tFileName* p_ptResultHead, LPCTSTR p_pcPath,  LPCTSTR p_lpFileName, int *p_piFileCount);
	BOOL bIsDirectory(DWORD p_wAttributes);
};

//******�ļ�������OFileCtrl.cpp******// end


//******�ַ�����������OStringCtrl.cpp******// begin

int iNullStrsToArrayStrs(CHAR*** p_pppcDest, CHAR* p_pcSrc, CHAR p_cFlag);
int iNullWStrsToArrayStrs(WCHAR*** p_pppcDest, WCHAR* p_pcSrc, CHAR p_cFlag);
// 	��    �ܣ�����ָ����־�ֿ�����\0�������ַ������е�ÿ���ַ�����ֵ�һ���ַ���������, �������鳤��
// 	��    �룺p_pcSrc		Դ�ַ�����ע���������н�����Դ���������ָ����־�ᱻ�滻Ϊ'\0'��
//			  p_cFlag		ָ����־
// 	��    ����p_pppcDest	ָ���ַ�������
//	�� �� ֵ�������С
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vArrayStrsToNullStrs(LPSTR* p_ppcNullStrs, LPSTR* p_ppcArraySrc, int p_iSize, BOOL p_bDel/* = TRUE*/);
void vArrayWStrsToNullStrs(LPWSTR* p_ppcNullStrs, LPWSTR* p_ppcArraySrc, int p_iSize, BOOL p_bDel/* = TRUE*/);
// 	��    �ܣ����ַ�������ת������\0�ָ�����\0\0��β���ַ���
// 	��    �룺p_ppcArraySrc		�ַ�������
//			  p_iSize			�ַ������С
//			  p_bDel			�Ƿ�ɾ��ԭ����
// 	��    ����p_ppcNullStrs		ָ���ַ���
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vMaptoKVStrs(const map<string, string>& p_tmElements, vector<CHAR>& p_tvKVRet, CHAR p_cFlag);
void vwMaptoKVStrs(const map<wstring, wstring>& p_tmElements, vector<WCHAR>& p_tvKVRet, CHAR p_cFlag);
// 	��    �ܣ���map�е�Ԫ����ϳ�"key=value"��ָ����־�ֿ�����\0�������ַ�����
// 	��    �룺p_tmElements		map
//			  p_cFlag			ָ����־��
// 	��    ����p_tvKVRet			�ַ�����
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

void vKVStrstoMap(CHAR* p_pcStrs, map<string, string>& p_tmElements, CHAR p_cFlag);
void vwKVStrstoMap(WCHAR* p_pwcStrs, map<wstring, wstring>& p_tmElements, CHAR p_cFlag);
// 	��    �ܣ���"key=value"��ָ����־�ֿ�����\0�������ַ����������map��
// 	��    �룺p_pcStrs		Դ�ַ����顣ע���������н�����Դ���������ָ����־�ᱻ�滻Ϊ'\0'��
//			  p_cFlag		ָ����־��
// 	��    ����p_tmElements	map
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

//******�ַ�����������OStringCtrl.cpp******// end


//******ý���������OMediaCtrl.cpp******// begin

void vBeep(UINT p_iFrequency, UINT p_iDuration);
//	��    �ܣ���PC������������һ����Ƶ�ʷ���
//	��    �룺p_iFrequency   ������Ƶ��
//	          p_iDuration    �������ʱ��(�Ժ���Ϊ��λ)
//	��    ������
//	�� �� ֵ����
//	��	  �ߣ�������
//	�������ڣ�2004.2

//******ý���������OMediaCtrl.cpp******// end

#endif	// !defined(AFX_GeneralLib_H__C1A33451_2434_11D5_B18A_5254AB1A7D30__INCLUDED_)