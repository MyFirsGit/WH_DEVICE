// MAC.h:interface for the MAC.cpp.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAC_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)
#define AFX_MAC_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_

int iGetTranMacValue(BYTE *p_pcMAC, BYTE *p_pcSource, int p_iSrcLen,  BYTE *p_pcKey, int p_iKenLen = -1, int p_iDesMode = 1);
// 	功    能：生成8位MAC校验数据。
// 	输    入：p_pcSource	源数据
//			  p_iSrcLen		源数据的长度
//			  p_pcKey		密钥（长度要求等于8或16）
//			  p_iKenLen		输入密钥的长度（长度等于8时进行DES计算，等于16时进行3DES计算，等于其他值函数返回失败）
//			  p_iDesMode	进行DES计算时的操作模式（0-ECB, 1-CBC, 2-CFB, 3-OFB）,默认为CBC
// 	输    出：p_pcMAC		存储结果的字符型数组
//	返 回 值：成功返回0，失败返回1。
//	作    者：王洪月
//	创建日期：2004.5

#endif	//!defined(AFX_MAC_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)