// MAC.h:interface for the MAC.cpp.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAC_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)
#define AFX_MAC_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_

int iGetTranMacValue(BYTE *p_pcMAC, BYTE *p_pcSource, int p_iSrcLen,  BYTE *p_pcKey, int p_iKenLen = -1, int p_iDesMode = 1);
// 	��    �ܣ�����8λMACУ�����ݡ�
// 	��    �룺p_pcSource	Դ����
//			  p_iSrcLen		Դ���ݵĳ���
//			  p_pcKey		��Կ������Ҫ�����8��16��
//			  p_iKenLen		������Կ�ĳ��ȣ����ȵ���8ʱ����DES���㣬����16ʱ����3DES���㣬��������ֵ��������ʧ�ܣ�
//			  p_iDesMode	����DES����ʱ�Ĳ���ģʽ��0-ECB, 1-CBC, 2-CFB, 3-OFB��,Ĭ��ΪCBC
// 	��    ����p_pcMAC		�洢������ַ�������
//	�� �� ֵ���ɹ�����0��ʧ�ܷ���1��
//	��    �ߣ�������
//	�������ڣ�2004.5

#endif	//!defined(AFX_MAC_H__F8CC7889_0D4F_48B0_A6A8_0448EF1B835F__INCLUDED_)