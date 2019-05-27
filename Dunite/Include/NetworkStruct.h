#ifndef	_NETWORKSTRUCT_H_
#define	_NETWORKSTRUCT_H_

#include "networkdef.h"
#include <winsock2.h>
//===================================================================
// �˿�������ݽṹ
//===================================================================

struct tDataNode
{
	SOCKET	m_hSocket;		//�Կͻ����ӵ�SOCKET
	int		m_iRecvBytes;	//�����ֽ���
	char*	m_pcBuf;		//���յ�����
};

typedef struct
{
	int				iSessionID;			// �������ӱ��
	int				iFlag;				// ��־��1-��������0-�ͻ���
	int				iPortNo;			// �˿ں�
	int				iLinkMode;			// ���ӷ�ʽ��1-�����ӡ�0-������
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