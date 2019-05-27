#ifndef	_NETWORKDEF_H_
#define	_NETWORKDEF_H_

//#define	FILE_EMULATE				0
#define SUCCESS							0
#define FAIL							1

#define	SESSION_SERVER					1		// 服务会话
#define	SESSION_CLIENT					0		// 客户会话

#define MAX_SESSION_NUM					5		// 最大网络连接数

#define	NET_SESSION_ALL					-1		// 所有会话

#define	IPADDRSIZE						16		// IP地址长度
#define TRANS_DATA_BUFSIZE				8096	// 交易数据缓冲区大小
#define IP_PACKET_SIZE					32		// IP包头大小
#define MAX_PACKET						1024	// IP包最大长度
#define ICMP_ECHO						8
#define ICMP_ECHOREPLY					0
#define ICMP_MIN						8		// ICMP包的最小长度

//== 系统错误 ====================================================
#define	E_NO_RAM_MEM					102		// 内存不足
//================================================================

//== 串口错误码 ==================================================
#define E_NO_MSG						901		// 队列中没数据
#define	E_SYSTEM_BREAK					903		// 系统主动终止
#define E_TIMEOUT						999		// 超时
#define E_COMM_TIMEOUT					999		// 端口通信超时
//================================================================

//== TCPIP =======================================================
///*
#define E_TCPIP_BASE					7000
//#define E_TCPIP_SUCCESS					E_TCPIP_BASE+0		// 7000
#define E_TCPIP_SUCCESS					SUCCESS				// 0
#define E_TCPIP_WINSOCK_FAILURE			E_TCPIP_BASE+1		// 7001 网络套接字失败
#define E_TCPIP_INVALID_SOCKET			E_TCPIP_BASE+2		// 7002 非法套接字
#define E_TCPIP_SERVER_UNRESOLVE		E_TCPIP_BASE+3		// 7003 服务器无法解析
#define E_TCPIP_CONNECT_CLOSE			E_TCPIP_BASE+4		// 7004 网络连接已被关闭
#define E_TCPIP_WSANOTINITIALISED		E_TCPIP_BASE+5		// 7005 网络连接未完成
#define E_TCPIP_WSAENETDOWN				E_TCPIP_BASE+6		// 7006 网络已断
#define E_TCPIP_WSAEFAULT				E_TCPIP_BASE+7		// 7007 非法网络地址
#define E_TCPIP_WSAEINPROGRESS			E_TCPIP_BASE+8		// 7008 操作资源正被占用
#define E_TCPIP_WSAEINVAL				E_TCPIP_BASE+9		// 7009 非法参数
#define E_TCPIP_WSAENETRESET			E_TCPIP_BASE+10		// 7010 网络连接被断开或重启
#define E_TCPIP_WSAENOPROTOOPT			E_TCPIP_BASE+11		// 7011 非法协议参数
#define E_TCPIP_WSAENOTCONN				E_TCPIP_BASE+12		// 7012 套接字未关联
#define E_TCPIP_WSAENOTSOCK				E_TCPIP_BASE+13		// 7013 在非套接字上进行操作
#define E_TCPIP_WSAEACCES				E_TCPIP_BASE+14		// 7014 访问拒绝
#define E_TCPIP_WSAEINTR				E_TCPIP_BASE+15		// 7015 功能调用失败
#define E_TCPIP_WSAEADDRINUSE			E_TCPIP_BASE+16		// 7016 地址被占用
#define E_TCPIP_WSAEALREADY				E_TCPIP_BASE+17		// 7017 操作资源已被占用
#define E_TCPIP_WSAENOBUFS				E_TCPIP_BASE+18		// 7018 内存空间不足
#define E_TCPIP_WSAEOPNOTSUPP			E_TCPIP_BASE+19		// 7019 非法操作
#define E_TCPIP_WSAESHUTDOWN			E_TCPIP_BASE+20		// 7020 套接字已被关闭
#define E_TCPIP_WSAEWOULDBLOCK			E_TCPIP_BASE+21		// 7021 网络被阻塞
#define E_TCPIP_WSAEMSGSIZE				E_TCPIP_BASE+22		// 7022 错误包大小
#define E_TCPIP_WSAEHOSTUNREACH			E_TCPIP_BASE+23		// 7023 主机不可到达
#define E_TCPIP_WSAECONNABORTED			E_TCPIP_BASE+24		// 7024 连接异常断开
#define E_TCPIP_WSAECONNRESET			E_TCPIP_BASE+25		// 7025 连接被重启
//#define E_TCPIP_WSAETIMEDOUT			E_TCPIP_BASE+26		// 7026 网络超时
#define E_TCPIP_WSAEADDRNOTAVAIL		E_TCPIP_BASE+27		// 7027 网络地址不可用
#define E_TCPIP_WSAEAFNOSUPPORT			E_TCPIP_BASE+28		// 7028 不支持的地址类
#define E_TCPIP_WSAECONNREFUSED			E_TCPIP_BASE+29		// 7029 连接被拒绝
#define E_TCPIP_WSAEISCONN				E_TCPIP_BASE+30		// 7030 套接字已被使用
#define E_TCPIP_WSAENETUNREACH			E_TCPIP_BASE+31		// 7031 网络不可到达
#define E_TCPIP_SENDTIMEOUT				E_TCPIP_BASE+32		// 7032 发送数据前等待超时
#define E_TCPIP_RECEIVETIMEOUT			E_TCPIP_BASE+33		// 7033 接收数据前等待超时
#define E_TCPIP_SETOPT_FAIL				E_TCPIP_BASE+34		// 7034 设置参数失败

#define E_ICMP_HEAPALLOC_FAIL			E_TCPIP_BASE+35		// 7035 堆分配失败
#define E_ICMP_SENDFAIL					E_TCPIP_BASE+36		// 7036 发送ICMP数据失败
#define E_ICMP_RECVFAIL					E_TCPIP_BASE+37		// 7037 接收ICMP数据失败
#define E_PING_FAILURE					E_TCPIP_BASE+38		// 7038 网络PING失败
#define E_PING_SUCCESS					E_TCPIP_BASE+39		// 7039 网络PING成功

#define	E_NET_INITFAILURE				E_TCPIP_BASE+50		// 7050	初始化失败(装入winsock32.dll 2.2失败)
#define	E_NET_ADDNULLSESSION			E_TCPIP_BASE+51		// 7051 增加空会话
#define	E_NET_INVALIDSESSION			E_TCPIP_BASE+52		// 7052 非法会话
#define	E_NET_CREATESESSION				E_TCPIP_BASE+53		// 7053 创建网络会话失败
#define E_NET_CONNECTIONSTAT			E_TCPIP_BASE+54		// 7054 网络连接状态不正常

#define	E_TCPIP_UNKNOWN					E_TCPIP_BASE+98		// 7098 未知错
#define E_TCPIP_WSAETIMEDOUT			E_TCPIP_BASE+99		// 7099 网络超时
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
//缺省可缓存未处理包数目
#define DATAQUEUE_MAXCOUNT 		50
//每一个TCPServer或者TcpClient实例可处理的最大连接数
#define CONNECTION_MAXCOUNT		64


#define RELEASE_PTR(p) {if (NULL != (p)) delete (p); p = NULL; }
#define RELEASE_ARRAY(p) {if (NULL != (p)) delete [] (p); p = NULL;}

#endif	// #ifndef	_NETWORKDEF_H_