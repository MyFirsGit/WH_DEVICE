//  ONetwork.h: interface for the ONetwork class.
// 
////////////////////////////////////////////////////////////////////// 

#if !defined(AFX_ONETWORK_H__279AD538_44DD_11D5_90C7_0000E88A396E__INCLUDED_)
#define AFX_ONETWORK_H__279AD538_44DD_11D5_90C7_0000E88A396E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif //  _MSC_VER > 1000

#include <vector>
using namespace std;

#ifdef _AFXDLL
	#define NETWORK_DLL AFX_EXT_CLASS
#else
	#ifdef NETWORKDLL_EXPORTS
		#define NETWORK_DLL __declspec(dllexport)
	#else
		#define NETWORK_DLL __declspec(dllimport)
	#endif
#endif

class OTcpSession;
class NETWORK_DLL ONetwork  
{
public:
	ONetwork();
	virtual ~ONetwork();
public:

	/*
	 *	����:��ʼ������
		������
			p_iFlag			: �Ѿ���ʱ����
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iInitNetwork(int p_iFlag);							

	/*
	 *	����:��������Ự
		������
			p_pvParam			: �Ự��Ϣ���� 
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iAddNetSession(LPVOID p_pvParam);					 


	/*
	 *	����:ɾ������Ự
		������
			p_iFalg			:	ָ���Ự����,SESSION_SERVER-�����,SESSION_CLIENT-�ͻ��� 
			p_iSessionID	:	�Ự��ʶ��,SESSION_ALL(-1)ʱɾ������ָ�����͵ĻỰ
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iRemoveSession(int p_iFlag, int p_iSessionID);

	/*
	 *	����:�޸�����Ự����
		������
			p_pvParam			: �µĻỰ��Ϣ���� 
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iUpdateNetSession(LPVOID p_pvParam);				 

	/*
	 *	����:�����������
		������
			p_iFalg			:	ָ���Ự����,SESSION_SERVER-�����,SESSION_CLIENT-�ͻ��� 
			p_iSessionID	:	�Ự��ʶ��,SESSION_ALL(-1)ʱ��������ָ�����͵ĻỰ
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iStartNetworkService(int p_iFlag, int p_iSessionID);

	/*
	 *	����:�ر��������
		������
			p_iFalg			:	ָ���Ự����,SESSION_SERVER-�����,SESSION_CLIENT-�ͻ��� 
			p_iSessionID	:	�Ự��ʶ��,SESSION_ALL(-1)ʱ�ر�����ָ�����͵ĻỰ
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iStopNetworkService(int p_iFlag, int p_iSessionID);	

	/*
	 *	����:��������
		������
			p_iFalg			:	ָ���Ự����,SESSION_SERVER-�����,SESSION_CLIENT-�ͻ��� 
			p_iSessionID	:	�Ự��ʶ��
			p_dwIndex		:	�����ӵı�ʶ�ţ��ڷ����ʱ����ָ���Զ����ӱ�ʶ���ͻ���ʱû������
			p_pcBuf			:	�������ݻ�����
			p_iLen			:	���ͻ����С
			p_dwTimeout		:	���ͳ�ʱʱ��,�Ժ����
			p_bClearRecvBuf	:	����ǰ�Ƿ������ǰ�Ľ�������,ȱʡΪTRUE
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iSendData(int p_iFlag, int p_iSessionID, DWORD p_dwIndex, char* p_pcBuf, int p_iLen, DWORD p_dwTimeout, BOOL p_bClearRecvBuf = TRUE);

	/*
	 *	����:��������
		������
			p_iFalg			:	ָ���Ự����,SESSION_SERVER-�����,SESSION_CLIENT-�ͻ��� 
			p_iSessionID	:	�Ự��ʶ��
			p_dwIndex		:	�����ӵı�ʶ�ţ��ڷ����ʱ���ڽ��նԶ����ӱ�ʶ���ͻ���ʱû������
			p_pcBuf			:	�������ݻ�����
			p_iLen			:	���ջ����С
			p_dwTimeout		:	���ճ�ʱʱ��,�Ժ����
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iRecvData(int p_iFlag, int p_iSessionID, DWORD& p_rdwIndex, char* p_pcBuf, int* p_piLen, DWORD p_dwTimeout);

	/*
	 *	����:��ȡ����״̬
		������
			p_iFalg			:	ָ���Ự����,SESSION_SERVER-�����,SESSION_CLIENT-�ͻ��� 
			p_iSessionID	:	�Ự��ʶ��
			p_iPing			:	��ȡ״̬�ķ�ʽ:0-ֱ�ӷ��سɹ�,1-ping,2-connect,3-�ж��׽ӿ��Ƿ���Ȼ����
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iGetNetworkStatus(int p_iFlag, int p_iSessionID, int p_iPing = 1);

	/*
	 *	����:��ȡ����״̬
		������
			p_pcAddr		:	�Զ�IP 
			p_iPing			:	��ȡ״̬�ķ�ʽ:0-ֱ�ӷ��سɹ�,1-ping,2-connect,3-�ж��׽ӿ��Ƿ���Ȼ����
			p_shPort		:	�Զ˶˿�
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iGetNetworkStatus(char* p_pcAddr, int p_iPing = 1, short p_shPort = 0);

	/*
	 *	����:��ȡ�Ự��Ϣ
		������
			p_iFalg			:	ָ���Ự����,SESSION_SERVER-�����,SESSION_CLIENT-�ͻ���
			p_iSessionID	:	�Ự��ʶ��
			p_psNetSession	:	����ĻỰ��Ϣ����
		���أ�
			SUCCESS:	�ɹ��� FAIL��ʧ��
	 */
	int		iGetNetSession(int p_iFlag, int p_iSessionID,tNetSession* p_psNetSession);
	
private:
	CRITICAL_SECTION	m_csSessionMapLock;
	std::vector<OTcpSession*> m_vecSessions;
	std::vector<OTcpSession*>::iterator itFindSession(int p_iFlag, int p_iSessionID);
};

#endif //  !defined(AFX_ONETWORK_H__279AD538_44DD_11D5_90C7_0000E88A396E__INCLUDED_)
