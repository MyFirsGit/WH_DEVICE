// des.h: interface for the ODes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DES_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)
#define AFX_DES_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_

#include <tchar.h>
#include <Oaidl.h>

enum    {ENCRYPT,DECRYPT};
enum	{ECB, CBC, CFB, OFB};

/* Type—ENCRYPT:加密,DECRYPT:解密
 本系统会根据密钥长度自动选择加密方案。当密钥长度为8字节时将使用标准DES加密，
 当密钥长度等于16字节时，系统将设置第2密钥，并启用3次DES加密。其密钥长度必须为8或16，
 否则返回失败。
*/

class ODes
{
public:
	ODes();
	virtual	~ODes();
	int iDoDes(BYTE *p_pucResult,BYTE *p_pucSrc,long p_lSrcLen,const BYTE *p_pucKey,int p_iKeyLen,int p_iMode = ECB, bool p_bType = ENCRYPT);
	// 	功    能：DES加密解密算法
	// 	输    入：p_pucSrc			源数据数组
	//			  p_lSrcLen			源数据的长度
	//			  p_pucKey			密钥
	//			  p_iKeyLen			密钥长度
	//			  p_iMode			操作模式（ECB,CBC,CFB,OFB）
	//			  p_bType			类型（ENCRYPT--加密,DECRYPT--解密）
	// 	输    出：p_pucResult		加密/解密后的结果数组
	//	返 回 值：成功返回0，失败返回1。
	//	作    者：王洪月
	//	创建日期：2004.3

};

#endif	// #if !defined(AFX_DES_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)


