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
	// 	��    �ܣ�CRC16У���㷨
	// 	��    �룺p_pucSrcData		Դ��������
	//			  p_iSrcSize		Դ���ݵĳ��ȣ����С�ڵ���0����ȡԴ����������ַ�������
	// 	��    ������
	//	�� �� ֵ���������õ�У�����ݵ�ֵ
	//	��    �ߣ�������
	//	�������ڣ�2004.3

	int iGetCRC32(BYTE *p_pucSrcData, int p_iSrcSize);
	// 	��    �ܣ�CRC32У���㷨
	// 	��    �룺p_pucSrcData		Դ��������
	//			  p_iSrcSize		Դ���ݵĳ��ȣ����С�ڵ���0����ȡԴ����������ַ�������
	// 	��    ������
	//	�� �� ֵ���������õ�У�����ݵ�ֵ
	//	��    �ߣ�������
	//	�������ڣ�2004.3

private:
	unsigned long	m_crc32Table[256];	// Lookup table arrays
	int		iUpdCrc16(int p_iTempCrc, int p_iSrcSize);
	void	vInitCRC32Table();	// Builds Lookup table array
	inline  unsigned long	Reflect(unsigned long p_ulRef, TCHAR p_cChar); // Reflects CRC bits in the lookup table
};

#endif // !defined(AFX_CRC32_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)
