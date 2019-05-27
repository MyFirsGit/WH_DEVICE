/*****************************************************************
���������ͷ�ļ���BigInt.h
���ߣ�afanty@vip.sina.com
�汾��1.2 (2003.5.13)
˵����������MFC��1024λRSA����
*****************************************************************/
//��������1120λ�������ƣ����м���
#if !defined AFX_RSA_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_
#define AFX_RSA_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_

#include <tchar.h>
#include <Oaidl.h>

#define RSAPRIVATEKEY_ENCRYPTMODE 1
#define RSAPRIVATEKEY_DECRYPTMODE 2
#define RSAPUBLICKEY_ENCRYPTMODE  3
#define RSAPUBLICKEY_DECRYPTMODE  4
#define RSAKEY_COMMANMODE  5

#define BI_MAXLEN 100
#define DEC 10
#define HEX 16

const int Maxkeylen = BI_MAXLEN << 2 ;


typedef struct
{
	unsigned int modellen ;
	BYTE modelvalue[Maxkeylen] ;
	
	unsigned int keylen ;
	BYTE keyvalue[Maxkeylen] ;

	BYTE prime[2][Maxkeylen];
}tRSAKey ;

class ORSA
{
public:

    ORSA();
	ORSA(unsigned int len,BYTE value[]);
    ~ORSA();

	int iGetKey(int p_iBitlen,tRSAKey& p_tPublicKey,tRSAKey& p_tPrivateKey);
	// 	��    �ܣ������Կ(��Կ��˽Կ),�����p_tPublicKey��p_tPrivateKey�д���
	// 	��    �룺p_iBitlen			��Կ��bit����(64~2048)
	// 	��    ����p_tPublicKey		��Կ
	//			  p_tPrivateKey		˽Կ
	//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1
	//	��    �ߣ�����
	//	�������ڣ�2004.3

	int iDoRSA(BYTE p_acResult[],unsigned int& p_uiResultLen, BYTE p_acSrc[],unsigned int p_uiSrcLen,tRSAKey p_tKey, int p_iMode = RSAKEY_COMMANMODE);
	// 	��    �ܣ�RSA�ӽ����㷨,��p_tKey ��˽ԿʱΪ���ܣ���p_tKey�ǹ�Կʱ�ǽ���
	// 	��    �룺p_acSrc[]			Դ��������,�������ֽ�0X00��ͷ
	//			  p_uiSrcLen		Դ���ݵĳ���,ҪС����Կ��ģ��
	//			  p_tKey			��Կ
	//			  p_iMode			ģʽ
	//				1 RSAPRIVATEKEY_ENCRYPTMODE 
	//				2 RSAPRIVATEKEY_DECRYPTMODE 
	//				3 RSAPUBLICKEY_ENCRYPTMODE  
	//				4 RSAPUBLICKEY_DECRYPTMODE  
	//				5 RSAKEY_COMMANMODE  
	// 	��    ����p_acResult[]		����/���ܺ�Ľ����������
	//			  p_uiResultLen		������ݵĳ���
	//	�� �� ֵ���ɹ�����0�������ʾʧ��
	//	��    �ߣ�����
	//	�������ڣ�2004.3

/*****************************************************************
��������������
Mov����ֵ���㣬�ɸ�ֵΪ��������ͨ������������Ϊ�������=��
Cmp���Ƚ����㣬������Ϊ�������==������!=������>=������<=����
Add���ӣ��������������������ͨ�����ĺͣ�������Ϊ�������+��
Sub�������������������������ͨ�����Ĳ������Ϊ�������-��
Mul���ˣ��������������������ͨ�����Ļ���������Ϊ�������*��
Div�������������������������ͨ�������̣�������Ϊ�������/��
Mod��ģ���������������������ͨ������ģ��������Ϊ�������%��
*****************************************************************/
private:
//public:
//������0x100000000�����µĳ���    
    unsigned m_nLength;
//�������¼������0x100000000������ÿһλ��ֵ
    unsigned long m_ulValue[BI_MAXLEN];
    void Mov(unsigned __int64 A);
    void Mov(ORSA& A);
    ORSA Add(ORSA& A);
    ORSA Sub(ORSA& A);
    ORSA Mul(ORSA& A);
    ORSA Div(ORSA& A);
    ORSA Mod(ORSA& A);
    ORSA Add(unsigned long A);
    ORSA Sub(unsigned long A);
    ORSA Mul(unsigned long A);
    ORSA Div(unsigned long A);
    unsigned long Mod(unsigned long A); 
    int Cmp(ORSA& A); 

/*****************************************************************
�������
Get�����ַ�����10���ƻ�16���Ƹ�ʽ���뵽����
Put����������10���ƻ�16���Ƹ�ʽ������ַ���
*****************************************************************/
 //   void Get(CString& str, unsigned int system=HEX);
 //   void Put(CString& str, unsigned int system=HEX);

/*****************************************************************
RSA�������
Rab�����������㷨������������
Euc��ŷ������㷨���ͬ�෽��
RsaTrans������ƽ���㷨������ģ����
GetPrime������ָ�����ȵ����������
*****************************************************************/
    int Rab();
    ORSA Euc(ORSA& A);
    ORSA RsaTrans(ORSA& A, ORSA& B);
    void GetPrime(int bits);

	int Getchar(unsigned int& len,BYTE value[]);
	int ReadValue(char * filename);
	int WriteValue(char * filename);

private:
	int iInitSrcDataBLock(unsigned int len,BYTE value[], int modulusLen, int p_iMode);
	int Getchar(unsigned int& len, BYTE value[], int p_iModulelen);

};
#endif
