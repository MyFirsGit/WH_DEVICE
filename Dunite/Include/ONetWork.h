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
	 *	功能:初始化网络
		参数：
			p_iFlag			: 已经过时不用
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iInitNetwork(int p_iFlag);							

	/*
	 *	功能:增加网络会话
		参数：
			p_pvParam			: 会话信息参数 
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iAddNetSession(LPVOID p_pvParam);					 


	/*
	 *	功能:删除网络会话
		参数：
			p_iFalg			:	指定会话类型,SESSION_SERVER-服务端,SESSION_CLIENT-客户端 
			p_iSessionID	:	会话标识号,SESSION_ALL(-1)时删除所有指定类型的会话
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iRemoveSession(int p_iFlag, int p_iSessionID);

	/*
	 *	功能:修改网络会话数据
		参数：
			p_pvParam			: 新的会话信息参数 
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iUpdateNetSession(LPVOID p_pvParam);				 

	/*
	 *	功能:启动网络服务
		参数：
			p_iFalg			:	指定会话类型,SESSION_SERVER-服务端,SESSION_CLIENT-客户端 
			p_iSessionID	:	会话标识号,SESSION_ALL(-1)时启动所有指定类型的会话
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iStartNetworkService(int p_iFlag, int p_iSessionID);

	/*
	 *	功能:关闭网络服务
		参数：
			p_iFalg			:	指定会话类型,SESSION_SERVER-服务端,SESSION_CLIENT-客户端 
			p_iSessionID	:	会话标识号,SESSION_ALL(-1)时关闭所有指定类型的会话
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iStopNetworkService(int p_iFlag, int p_iSessionID);	

	/*
	 *	功能:发送数据
		参数：
			p_iFalg			:	指定会话类型,SESSION_SERVER-服务端,SESSION_CLIENT-客户端 
			p_iSessionID	:	会话标识号
			p_dwIndex		:	子连接的标识号，在服务端时用于指定对端连接标识，客户端时没有意义
			p_pcBuf			:	发送数据缓冲区
			p_iLen			:	发送缓冲大小
			p_dwTimeout		:	发送超时时间,以毫秒计
			p_bClearRecvBuf	:	发送前是否清空以前的接收数据,缺省为TRUE
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iSendData(int p_iFlag, int p_iSessionID, DWORD p_dwIndex, char* p_pcBuf, int p_iLen, DWORD p_dwTimeout, BOOL p_bClearRecvBuf = TRUE);

	/*
	 *	功能:接收数据
		参数：
			p_iFalg			:	指定会话类型,SESSION_SERVER-服务端,SESSION_CLIENT-客户端 
			p_iSessionID	:	会话标识号
			p_dwIndex		:	子连接的标识号，在服务端时用于接收对端连接标识，客户端时没有意义
			p_pcBuf			:	接收数据缓冲区
			p_iLen			:	接收缓冲大小
			p_dwTimeout		:	接收超时时间,以毫秒计
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iRecvData(int p_iFlag, int p_iSessionID, DWORD& p_rdwIndex, char* p_pcBuf, int* p_piLen, DWORD p_dwTimeout);

	/*
	 *	功能:获取网络状态
		参数：
			p_iFalg			:	指定会话类型,SESSION_SERVER-服务端,SESSION_CLIENT-客户端 
			p_iSessionID	:	会话标识号
			p_iPing			:	获取状态的方式:0-直接返回成功,1-ping,2-connect,3-判断套接口是否仍然可用
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iGetNetworkStatus(int p_iFlag, int p_iSessionID, int p_iPing = 1);

	/*
	 *	功能:获取网络状态
		参数：
			p_pcAddr		:	对端IP 
			p_iPing			:	获取状态的方式:0-直接返回成功,1-ping,2-connect,3-判断套接口是否仍然可用
			p_shPort		:	对端端口
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iGetNetworkStatus(char* p_pcAddr, int p_iPing = 1, short p_shPort = 0);

	/*
	 *	功能:获取会话信息
		参数：
			p_iFalg			:	指定会话类型,SESSION_SERVER-服务端,SESSION_CLIENT-客户端
			p_iSessionID	:	会话标识号
			p_psNetSession	:	输出的会话信息缓冲
		返回：
			SUCCESS:	成功， FAIL：失败
	 */
	int		iGetNetSession(int p_iFlag, int p_iSessionID,tNetSession* p_psNetSession);
	
private:
	CRITICAL_SECTION	m_csSessionMapLock;
	std::vector<OTcpSession*> m_vecSessions;
	std::vector<OTcpSession*>::iterator itFindSession(int p_iFlag, int p_iSessionID);
};

#endif //  !defined(AFX_ONETWORK_H__279AD538_44DD_11D5_90C7_0000E88A396E__INCLUDED_)
