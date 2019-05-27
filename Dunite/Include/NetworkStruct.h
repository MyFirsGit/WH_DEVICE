#ifndef	_NETWORKSTRUCT_H_
#define	_NETWORKSTRUCT_H_

#include "networkdef.h"
#include <winsock2.h>
//===================================================================
// 端口相关数据结构
//===================================================================

struct tDataNode
{
	SOCKET	m_hSocket;		//对客户连接的SOCKET
	int		m_iRecvBytes;	//接收字节数
	char*	m_pcBuf;		//接收的数据
};

typedef struct
{
	int				iSessionID;			// 网络连接编号
	int				iFlag;				// 标志：1-服务器、0-客户端
	int				iPortNo;			// 端口号
	int				iLinkMode;			// 连接方式：1-长连接、0-短连接
	char			acIPAddr[IPADDRSIZE];// IP(***.***.***.***)
} tNetSession;

typedef struct _ipheader
{
	unsigned int   ui_HeaderLen:4;
	unsigned int   ui_Version:4;
	unsigned char  uc_TypeOfService;
	unsigned short us_TotalLen;
	unsigned short us_Identifier;
	unsigned short us_Flags;
	unsigned char  uc_TimeToLive;
	unsigned char  uc_Protocal;
	unsigned short us_Checksum;

	unsigned int   ui_SourceIp;
	unsigned int   ui_DestIp;
} tIPHeader;

typedef struct _icmpheader
{
	BYTE i_type;
	BYTE i_code;
	USHORT i_checksum;
	USHORT i_id;
	USHORT i_seq;
	ULONG  l_timestamp;
} tICMPHeader;

#endif	// #ifndef	_NETWORKSTRUCT_H_