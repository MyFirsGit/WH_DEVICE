/*****************************************************************
大数运算库头文件：BigInt.h
作者：afanty@vip.sina.com
版本：1.2 (2003.5.13)
说明：适用于MFC，1024位RSA运算
*****************************************************************/
//允许生成1120位（二进制）的中间结果
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
	// 	功    能：获得密钥(公钥和私钥),结果从p_tPublicKey和p_tPrivateKey中传出
	// 	输    入：p_iBitlen			密钥的bit长度(64~2048)
	// 	输    出：p_tPublicKey		公钥
	//			  p_tPrivateKey		私钥
	//	返 回 值：成功返回0，失败返回1
	//	作    者：不祥
	//	创建日期：2004.3

	int iDoRSA(BYTE p_acResult[],unsigned int& p_uiResultLen, BYTE p_acSrc[],unsigned int p_uiSrcLen,tRSAKey p_tKey, int p_iMode = RSAKEY_COMMANMODE);
	// 	功    能：RSA加解密算法,当p_tKey 是私钥时为加密，当p_tKey是公钥时是解密
	// 	输    入：p_acSrc[]			源数据数组,不能以字节0X00开头
	//			  p_uiSrcLen		源数据的长度,要小于密钥的模长
	//			  p_tKey			密钥
	//			  p_iMode			模式
	//				1 RSAPRIVATEKEY_ENCRYPTMODE 
	//				2 RSAPRIVATEKEY_DECRYPTMODE 
	//				3 RSAPUBLICKEY_ENCRYPTMODE  
	//				4 RSAPUBLICKEY_DECRYPTMODE  
	//				5 RSAKEY_COMMANMODE  
	// 	输    出：p_acResult[]		加密/解密后的结果数据数组
	//			  p_uiResultLen		结果数据的长度
	//	返 回 值：成功返回0，否则表示失败
	//	作    者：不祥
	//	创建日期：2004.3

/*****************************************************************
基本操作与运算
Mov，赋值运算，可赋值为大数或普通整数，可重载为运算符“=”
Cmp，比较运算，可重载为运算符“==”、“!=”、“>=”、“<=”等
Add，加，求大数与大数或大数与普通整数的和，可重载为运算符“+”
Sub，减，求大数与大数或大数与普通整数的差，可重载为运算符“-”
Mul，乘，求大数与大数或大数与普通整数的积，可重载为运算符“*”
Div，除，求大数与大数或大数与普通整数的商，可重载为运算符“/”
Mod，模，求大数与大数或大数与普通整数的模，可重载为运算符“%”
*****************************************************************/
private:
//public:
//大数在0x100000000进制下的长度    
    unsigned m_nLength;
//用数组记录大数在0x100000000进制下每一位的值
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
输入输出
Get，从字符串按10进制或16进制格式输入到大数
Put，将大数按10进制或16进制格式输出到字符串
*****************************************************************/
 //   void Get(CString& str, unsigned int system=HEX);
 //   void Put(CString& str, unsigned int system=HEX);

/*****************************************************************
RSA相关运算
Rab，拉宾米勒算法进行素数测试
Euc，欧几里德算法求解同余方程
RsaTrans，反复平方算法进行幂模运算
GetPrime，产生指定长度的随机大素数
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
