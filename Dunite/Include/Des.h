// des.h: interface for the ODes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DES_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)
#define AFX_DES_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_

#include <tchar.h>
#include <Oaidl.h>

enum    {ENCRYPT,DECRYPT};
enum	{ECB, CBC, CFB, OFB};

/* Type��ENCRYPT:����,DECRYPT:����
 ��ϵͳ�������Կ�����Զ�ѡ����ܷ���������Կ����Ϊ8�ֽ�ʱ��ʹ�ñ�׼DES���ܣ�
 ����Կ���ȵ���16�ֽ�ʱ��ϵͳ�����õ�2��Կ��������3��DES���ܡ�����Կ���ȱ���Ϊ8��16��
 ���򷵻�ʧ�ܡ�
*/

class ODes
{
public:
	ODes();
	virtual	~ODes();
	int iDoDes(BYTE *p_pucResult,BYTE *p_pucSrc,long p_lSrcLen,const BYTE *p_pucKey,int p_iKeyLen,int p_iMode = ECB, bool p_bType = ENCRYPT);
	// 	��    �ܣ�DES���ܽ����㷨
	// 	��    �룺p_pucSrc			Դ��������
	//			  p_lSrcLen			Դ���ݵĳ���
	//			  p_pucKey			��Կ
	//			  p_iKeyLen			��Կ����
	//			  p_iMode			����ģʽ��ECB,CBC,CFB,OFB��
	//			  p_bType			���ͣ�ENCRYPT--����,DECRYPT--���ܣ�
	// 	��    ����p_pucResult		����/���ܺ�Ľ������
	//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
	//	��    �ߣ�������
	//	�������ڣ�2004.3

};

#endif	// #if !defined(AFX_DES_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)


