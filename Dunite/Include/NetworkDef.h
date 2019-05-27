#ifndef	_NETWORKDEF_H_
#define	_NETWORKDEF_H_

//#define	FILE_EMULATE				0
#define SUCCESS							0
#define FAIL							1

#define	SESSION_SERVER					1		// ����Ự
#define	SESSION_CLIENT					0		// �ͻ��Ự

#define MAX_SESSION_NUM					5		// �������������

#define	NET_SESSION_ALL					-1		// ���лỰ

#define	IPADDRSIZE						16		// IP��ַ����
#define TRANS_DATA_BUFSIZE				8096	// �������ݻ�������С
#define IP_PACKET_SIZE					32		// IP��ͷ��С
#define MAX_PACKET						1024	// IP����󳤶�
#define ICMP_ECHO						8
#define ICMP_ECHOREPLY					0
#define ICMP_MIN						8		// ICMP������С����

//== ϵͳ���� ====================================================
#define	E_NO_RAM_MEM					102		// �ڴ治��
//================================================================

//== ���ڴ����� ==================================================
#define E_NO_MSG						901		// ������û����
#define	E_SYSTEM_BREAK					903		// ϵͳ������ֹ
#define E_TIMEOUT						999		// ��ʱ
#define E_COMM_TIMEOUT					999		// �˿�ͨ�ų�ʱ
//================================================================

//== TCPIP =======================================================
///*
#define E_TCPIP_BASE					7000
//#define E_TCPIP_SUCCESS					E_TCPIP_BASE+0		// 7000
#define E_TCPIP_SUCCESS					SUCCESS				// 0
#define E_TCPIP_WINSOCK_FAILURE			E_TCPIP_BASE+1		// 7001 �����׽���ʧ��
#define E_TCPIP_INVALID_SOCKET			E_TCPIP_BASE+2		// 7002 �Ƿ��׽���
#define E_TCPIP_SERVER_UNRESOLVE		E_TCPIP_BASE+3		// 7003 �������޷�����
#define E_TCPIP_CONNECT_CLOSE			E_TCPIP_BASE+4		// 7004 ���������ѱ��ر�
#define E_TCPIP_WSANOTINITIALISED		E_TCPIP_BASE+5		// 7005 ��������δ���
#define E_TCPIP_WSAENETDOWN				E_TCPIP_BASE+6		// 7006 �����Ѷ�
#define E_TCPIP_WSAEFAULT				E_TCPIP_BASE+7		// 7007 �Ƿ������ַ
#define E_TCPIP_WSAEINPROGRESS			E_TCPIP_BASE+8		// 7008 ������Դ����ռ��
#define E_TCPIP_WSAEINVAL				E_TCPIP_BASE+9		// 7009 �Ƿ�����
#define E_TCPIP_WSAENETRESET			E_TCPIP_BASE+10		// 7010 �������ӱ��Ͽ�������
#define E_TCPIP_WSAENOPROTOOPT			E_TCPIP_BASE+11		// 7011 �Ƿ�Э�����
#define E_TCPIP_WSAENOTCONN				E_TCPIP_BASE+12		// 7012 �׽���δ����
#define E_TCPIP_WSAENOTSOCK				E_TCPIP_BASE+13		// 7013 �ڷ��׽����Ͻ��в���
#define E_TCPIP_WSAEACCES				E_TCPIP_BASE+14		// 7014 ���ʾܾ�
#define E_TCPIP_WSAEINTR				E_TCPIP_BASE+15		// 7015 ���ܵ���ʧ��
#define E_TCPIP_WSAEADDRINUSE			E_TCPIP_BASE+16		// 7016 ��ַ��ռ��
#define E_TCPIP_WSAEALREADY				E_TCPIP_BASE+17		// 7017 ������Դ�ѱ�ռ��
#define E_TCPIP_WSAENOBUFS				E_TCPIP_BASE+18		// 7018 �ڴ�ռ䲻��
#define E_TCPIP_WSAEOPNOTSUPP			E_TCPIP_BASE+19		// 7019 �Ƿ�����
#define E_TCPIP_WSAESHUTDOWN			E_TCPIP_BASE+20		// 7020 �׽����ѱ��ر�
#define E_TCPIP_WSAEWOULDBLOCK			E_TCPIP_BASE+21		// 7021 ���类����
#define E_TCPIP_WSAEMSGSIZE				E_TCPIP_BASE+22		// 7022 �������С
#define E_TCPIP_WSAEHOSTUNREACH			E_TCPIP_BASE+23		// 7023 �������ɵ���
#define E_TCPIP_WSAECONNABORTED			E_TCPIP_BASE+24		// 7024 �����쳣�Ͽ�
#define E_TCPIP_WSAECONNRESET			E_TCPIP_BASE+25		// 7025 ���ӱ�����
//#define E_TCPIP_WSAETIMEDOUT			E_TCPIP_BASE+26		// 7026 ���糬ʱ
#define E_TCPIP_WSAEADDRNOTAVAIL		E_TCPIP_BASE+27		// 7027 �����ַ������
#define E_TCPIP_WSAEAFNOSUPPORT			E_TCPIP_BASE+28		// 7028 ��֧�ֵĵ�ַ��
#define E_TCPIP_WSAECONNREFUSED			E_TCPIP_BASE+29		// 7029 ���ӱ��ܾ�
#define E_TCPIP_WSAEISCONN				E_TCPIP_BASE+30		// 7030 �׽����ѱ�ʹ��
#define E_TCPIP_WSAENETUNREACH			E_TCPIP_BASE+31		// 7031 ���粻�ɵ���
#define E_TCPIP_SENDTIMEOUT				E_TCPIP_BASE+32		// 7032 ��������ǰ�ȴ���ʱ
#define E_TCPIP_RECEIVETIMEOUT			E_TCPIP_BASE+33		// 7033 ��������ǰ�ȴ���ʱ
#define E_TCPIP_SETOPT_FAIL				E_TCPIP_BASE+34		// 7034 ���ò���ʧ��

#define E_ICMP_HEAPALLOC_FAIL			E_TCPIP_BASE+35		// 7035 �ѷ���ʧ��
#define E_ICMP_SENDFAIL					E_TCPIP_BASE+36		// 7036 ����ICMP����ʧ��
#define E_ICMP_RECVFAIL					E_TCPIP_BASE+37		// 7037 ����ICMP����ʧ��
#define E_PING_FAILURE					E_TCPIP_BASE+38		// 7038 ����PINGʧ��
#define E_PING_SUCCESS					E_TCPIP_BASE+39		// 7039 ����PING�ɹ�

#define	E_NET_INITFAILURE				E_TCPIP_BASE+50		// 7050	��ʼ��ʧ��(װ��winsock32.dll 2.2ʧ��)
#define	E_NET_ADDNULLSESSION			E_TCPIP_BASE+51		// 7051 ���ӿջỰ
#define	E_NET_INVALIDSESSION			E_TCPIP_BASE+52		// 7052 �Ƿ��Ự
#define	E_NET_CREATESESSION				E_TCPIP_BASE+53		// 7053 ��������Ựʧ��
#define E_NET_CONNECTIONSTAT			E_TCPIP_BASE+54		// 7054 ��������״̬������

#define	E_TCPIP_UNKNOWN					E_TCPIP_BASE+98		// 7098 δ֪��
#define E_TCPIP_WSAETIMEDOUT			E_TCPIP_BASE+99		// 7099 ���糬ʱ
//*/
//================================================================
#define PING_ERROR                      SOCKET_ERROR

// Chen Bin 2003-11-28 add for log
#define LOG_TYPE_ERROR			0
#define LOG_TYPE_ATTENTION		1
#define LOG_TYPE_MESSAGE		2
#define LOG_TYPE_HEXADEMICAL	3

// End 2003-11-28.

#define DEFAULT_SENDBUF_SIZE	4096
#define DEFAULT_RECVBUF_SIZE	4096
//ȱʡ�ɻ���δ�������Ŀ
#define DATAQUEUE_MAXCOUNT 		50
//ÿһ��TCPServer����TcpClientʵ���ɴ�������������
#define CONNECTION_MAXCOUNT		64


#define RELEASE_PTR(p) {if (NULL != (p)) delete (p); p = NULL; }
#define RELEASE_ARRAY(p) {if (NULL != (p)) delete [] (p); p = NULL;}

#endif	// #ifndef	_NETWORKDEF_H_