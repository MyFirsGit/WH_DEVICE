// Crc.h: interface for the OCrc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRC32_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)
#define AFX_CRC32_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_

#include <tchar.h>
#include <Oaidl.h>
#include <string>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OCrc  
{
public:
	OCrc();
	virtual ~OCrc();
	int iGetCRC16(BYTE *p_pucSrcData, int p_iSrcSize);
	// 	功    能：CRC16校验算法
	// 	输    入：p_pucSrcData		源数据数组
	//			  p_iSrcSize		源数据的长度，如果小于等于0，则取源数据数组的字符串长度
	// 	输    出：无
	//	返 回 值：计算所得的校验数据的值
	//	作    者：王洪月
	//	创建日期：2004.3

	int iGetCRC32(BYTE *p_pucSrcData, int p_iSrcSize);
	// 	功    能：CRC32校验算法
	// 	输    入：p_pucSrcData		源数据数组
	//			  p_iSrcSize		源数据的长度，如果小于等于0，则取源数据数组的字符串长度
	// 	输    出：无
	//	返 回 值：计算所得的校验数据的值
	//	作    者：王洪月
	//	创建日期：2004.3

private:
	unsigned long	m_crc32Table[256];	// Lookup table arrays
	int		iUpdCrc16(int p_iTempCrc, int p_iSrcSize);
	void	vInitCRC32Table();	// Builds Lookup table array
	inline  unsigned long	Reflect(unsigned long p_ulRef, TCHAR p_cChar); // Reflects CRC bits in the lookup table
};

#endif // !defined(AFX_CRC32_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)
