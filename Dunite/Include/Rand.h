// Rand.h:interface for the Rand.cpp.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Rand_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)
#define AFX_Rand_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_

#include <tchar.h>
#include <Oaidl.h>

int	iGetRandIntArray(int p_aiResult[], int p_iNum, int p_iMax);
// 	��    �ܣ���һ����ֵ��Χ��0 ~ p_iMax��֮�䣬�������޸�һϵ�з��ظ��������������
// 	��    �룺p_iNum		������ĸ���
//			  p_iMax		����������ֵ
// 	��    ����p_aiResult		�洢���������������
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
//	��    �ߣ�������
//	�������ڣ�2004.3

int	iGetRandCharArray(BYTE p_aucResult[], int p_iNum);
// 	��    �ܣ��������޸�һϵ�з��ظ����ַ����������ASCIIֵ��0��7F֮�䡣
// 	��    �룺p_iNum		������ĸ���,���Ϊ127,����127ֱ�ӷ���ʧ��
// 	��    ����p_aucResult	�洢��������ַ�������
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
//	��    �ߣ�������
//	�������ڣ�2004.3

#endif	//!defined(AFX_Rand_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)