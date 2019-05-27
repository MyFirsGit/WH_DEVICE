// Rand.h:interface for the Rand.cpp.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Rand_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)
#define AFX_Rand_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_

#include <tchar.h>
#include <Oaidl.h>

int	iGetRandIntArray(int p_aiResult[], int p_iNum, int p_iMax);
// 	功    能：在一个数值范围（0 ~ p_iMax）之间，生成有限个一系列非重复的整型随机数。
// 	输    入：p_iNum		随机数的个数
//			  p_iMax		随机数的最大值
// 	输    出：p_aiResult		存储随机数的整型数组
//	返 回 值：成功返回0，失败返回1。
//	作    者：王洪月
//	创建日期：2004.3

int	iGetRandCharArray(BYTE p_aucResult[], int p_iNum);
// 	功    能：生成有限个一系列非重复的字符型随机数，ASCII值在0～7F之间。
// 	输    入：p_iNum		随机数的个数,最大为127,大于127直接返回失败
// 	输    出：p_aucResult	存储随机数的字符型数组
//	返 回 值：成功返回0，失败返回1。
//	作    者：王洪月
//	创建日期：2004.3

#endif	//!defined(AFX_Rand_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)