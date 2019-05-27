// OLicManager.h: interface for the OLicManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OLICMANAGER_H__156868EB_2330_4FA3_9988_8D81EBC4100D__INCLUDED_)
#define AFX_OLICMANAGER_H__156868EB_2330_4FA3_9988_8D81EBC4100D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "stdafx.h"

#if defined( _WIN32) && !defined(WINNT)
#define WINNT
#endif

#if defined ( _MSC_VER) && ! defined (PC)
#define PC
#endif

#if defined(WINNT) && !defined(PC)
#define PC
#endif

#ifdef PC
#include <windows.h>
#if !defined(WINNT)
#define LM_CALLBACK_TYPE _pascal
#endif /* pc16 */
#ifdef WINNT
#define LM_CALLBACK_TYPE _cdecl
#endif
#else /* defined(PC) */
#define LM_CALLBACK_TYPE
#endif /* PC */

#ifdef PC
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#endif

#include <vector>
#include <string>
using namespace std;
/*
 *	��������
 */

#define MAX_LONGNAME_SIZE	1024
#define MAX_CONFIGLINE_SIZE	1024
#define MAX_FEATURE_LEN		30
#define MAX_VER_LEN			10
#define MAX_DAEMON_NAME		10			/**/
#define DATE_LEN			11			/*date length(format: yyyy-mm-dd)*/
#define MAX_CRYPT_LEN		64			/*license key length*/
#define CUSTOMSTRING_LEN	50
#define MAX_HOSTNAME_LEN	255
#define FEATURE_PERMANENT_DATE	"permanent"
#define FEATURE_ANY_HOST		"any"
#define FEATURE_ANY_USERS		0

//License��������������License�ļ�·��
#define ENV_LICENSEPATH			"GrgLicenseFile"

/*
 *	LicManager version
 */

#define LICMANAGER_VERSION 1
#define LICMANAGER_REVISION 0
#define FLEXLM_PATCH " "
#define LICMANAGER_VERSION_REVISION_STRING "1.0.0"
#define LICMANAGER_COPYRIGHT_YEAR "2005"
#define COPYRIGHT_STRING(firstYear)	"Copyright (c) " #firstYear "-"LICMANAGER_COPYRIGHT_YEAR" by GRGbanking. All rights reserved."


/*
 *	license�ļ�	
 */
struct tLicenseFile
{
	int	iType;		//license�ļ�����:�ļ�,�ַ���,����˵�ַ
#define LF_NOTHING	0		//��
#define LF_FILE		1		//�ļ�
#define LF_STRING	2		//�ַ���
#define LF_SERVER	3		//�����
	union
	{
		FILE*	pfFile;
		char*	pcStr;
		char*	pcServer;
	} ptr;
	char* pcFileName;
};


/*
 *	license�û���Ϣ
 */
struct tLMUsers
{
	char	acName[MAX_LONGNAME_SIZE + 1];
	char	acNode[MAX_LONGNAME_SIZE + 1];
	char	acDisplay[MAX_LONGNAME_SIZE + 1];
	int		nlic;	
};


/*
 *	������ʶ��Ϣ	
 */
struct tHostID
{
//Ԥ�����һЩ������ʶ
#define HOSTID_DEFAULT		-1
#define HOSTID_ANY			0
#define HOSTID_ETHER		1<<0
#define HOSTID_HOSTNAME		1<<1
#define HOSTID_DISKSERIAL	1<<2
#define HOSTID_CPU			1<<3
#define HOSTID_INTERNET		1<<4
//������ʶ����׺
#define HOSTIDTYPE_ETHER		'a'
#define HOSTIDTYPE_HOSTNAME		'b'
#define HOSTIDTYPE_DISKSERIAL	'c'
#define HOSTIDTYPE_CPU			'd'
#define HOSTIDTYPE_INTERNET		'e'

#define HOSTID_TYPE_COUNT		6	//֧�ֵ�HOSTID������Ŀ
#define HOSTIDTYPEINDEX1(t)		(t - 'a' + 1)	//��IDTYPEת������һΪ��������,������ANY����		
//���������ʶ��ķָ���
#define HOSTID_DELIM			'+'
	char	id[MAX_HOSTNAME_LEN];	//�ַ�������ͬʱ֧�ֶ������͵�ID
	short	type;						//��ʶ������(MAC,DiskSerial�ȵ�)
	
};

/*
 *	license�ļ��е�license��������Ϣ
 */
struct tLMServer
{
	char		acName[MAX_LONGNAME_SIZE + 1];	//������
	tHostID*	psHostID;						//����ID
#define COMMTYPE_TCP		0
#define COMMTYPE_UDP		1
	int			iCommType;						//ͨѶ����, TCP/UDP...

#define DEFAULT_SERVERPORT	3801
	short		shPort;							//����˿�	
	long		lIp;							//IP��ַ

	tLMServer();
	tLMServer(const tLMServer& src);
	tLMServer& operator=(const tLMServer& src);
	~tLMServer();
};

/*
 *	Liencse�ļ���
 */
#define SERVER_LINE		0
#define DAEMON_LINE		1
#define FEATURE_LINE	2
#define COMMENT_LINE	10

/*
 *	Feature ��Ϣ
 */
struct tConfig
{
	short		shType;					//feature�е�����,��ֻ֧�ֻ�������0
#define CONFIG_FEATURE		0			//������feature�У�Ĭ��
#define CONFIG_INCREMENT	1			//INCREMENT�У��ݲ���
#define CONFIG_UPGRADE		2			//UPGRADE�У��ݲ���
#define CONFIG_BORROW		3			//BORROW�У��ݲ���
	
	//feature�е������
	char	acFeature[MAX_FEATURE_LEN + 1];	//������
	char	acVersion[MAX_VER_LEN + 1];		//�汾��
	char	acDaemon[MAX_DAEMON_NAME + 1];	//����ID
	char	acDate[DATE_LEN + 1];			//����ʱ��,"permenant"��������
	char	acSdate[DATE_LEN + 1];			//��ʼʱ��
	int		iUsers;							//�����û���,0������
	char	acKey[MAX_CRYPT_LEN + 1];		//license key
	tHostID* psHostID;						//�޶���������ʶ,"any"������
	char	acVendorStr[CUSTOMSTRING_LEN];	//�Զ�����ַ���
	tLMServer* psServer;					//�������Ϣ

	int		iCkout;							//�������
	tConfig();
	~tConfig();
	tConfig(const tConfig& src);
	tConfig& operator=(const tConfig& src);
};

/*
 * license�ĻỰ���,����ָ���Ự��ز���	
 */
struct tLMHandle
{
	int iJobId;			//һ��license��ҵID
	int iStatus;		//��ʼ��״̬
#define STATUS_INIT				1
#define STATUS_LOADLIC			2
};

typedef tLMHandle  LM_HANDLE;

//license��������е�����ֶ�
enum eLicField
{
	FEATURE_NAME = 0,
	VENDOR_NAME,
	FEATURE_VERSION,
	LICDATE,
	USERS,
	LICKEY,
	HOSTID,
	VENDORSTR
};

struct tFieldStr
{
	int		fieldid;
	char*	fieldstr;
};

/*
 *	License����Ļ�����,����license��������к��Ĺ���
 */
class OLicManager  
{
public:
	OLicManager();
	virtual ~OLicManager();
	
	/*
	 *	����: ��ʼ��LicenseManager�Ự
	 */
	int iLInit(LM_HANDLE&);


	/*
	 *	����: �ͷŻỰ��ص���Դ
	 */
	int iLFree(LM_HANDLE);

	/*
	 *	����: װ��License�ļ�
	 */
	int iLLoadLicFile(LM_HANDLE, const char* p_pcEnv = ENV_LICENSEPATH);

	/*
	 *	����: ��װlicense�ļ�·����ϵͳ��������,ȱʡΪENV_LICENSEPATH(��GrgLinceseFile)
	 */
	int iLInstallEnv(LM_HANDLE, const char* p_pcValue, int p_iAppend = 1, const char* p_pcEnv = ENV_LICENSEPATH);

	/*
	 *	����:	���һ��������ܵ�license
	 */
	int iLCheckout(LM_HANDLE, const char* p_pcFeature, const char* p_pcVersion, const int p_iLicNum, int p_iFlag);

	/*
	 *	����:	����һ��������ܵ�license
	 */
	int iLCheckin(LM_HANDLE, const char* p_pcFeature, const char* p_pcVersion);


	/*
	 *	����:	ȡһ��������ܵ�licenseռ���û��б�
	 */
	int iLUserList(LM_HANDLE p_sHandle, char* p_pcFeature, tLMUsers** p_ppsUsers);


	/*
	 *	����:	����һ��license�ļ���������������license
	 */
	int iLAllFeature(LM_HANDLE, FILE*);


	/*
	 *	����:	����һ��license�ļ���
	 */
	int iLParseFeatureLine(LM_HANDLE, char* p_psLine, tConfig* p_psConfig, int* p_piError);


	/*
	 *	����:	�ж������Ƿ���Ч
	 */
	int iLDate(LM_HANDLE, char* p_pcDate, int p_iFlag = 0);

	
	/*
	 *	����:	�жϰ汾��ʽ�Ƿ���Ч
	 */
	int iLVersion(LM_HANDLE, char* p_pcVersion);


	/*
	 *	����:	�ж��Ƿ�Ϊ��Ч��������ʶ
	 */
	int iLHost(LM_HANDLE, tHostID* p_psHostID);

	
	/*
	 *	����:	��һ��license key����
	 */
	int iLDecryptKey(LM_HANDLE p_sHandle, /*IN*/unsigned char* p_pcKey, /*IN*/int p_piKeyLen, /*OUT*/char** pcMsg, /*OUT*/int* p_piMsgLen);

	
	/*
	 *	����:	��һ��tConfig�ṹ��ϳ�һ��license��(SERVER/FEATURE/DAEMON)
	 */
	char* pcFeatureString(LM_HANDLE, const tConfig*, int p_iForKeyGen = 1, int p_iLine = FEATURE_LINE);

	
	/*
	 *	����:	�ж�license key�Ƿ���Ч
	 */
	int iLVLK(LM_HANDLE, tConfig*);

	
	/*
	 *	����:	ȡ������Ϣ
	 */
	int iLGetHostID(/*IN*/LM_HANDLE, /*IN*/int p_iIDType, tHostID* p_psHostID, int p_iSuffix = 1);

	/*
	 *	����:	��ȡһ��������ʶ�������ͣ������������һ������(����ж��)
	 */
	int iLHostIDType(LM_HANDLE, const char* p_pcID, vector<char*>* p_pvecIDs, int& p_iType);

	/*
	 *	����: ��һ����ת����tHostID,���tHostID���Ѿ������ݣ�����ԭ���Ļ�����׷��
	 */
	int iLCatHostID(LM_HANDLE, /*IN*/const char* p_pcID, /*IN*/int p_iType, /*OUT*/tHostID& p_sHostID);
	
	/*
	 *	����:	��һ�����õ�license key
	 */
	int iLCryptStr(LM_HANDLE, char* p_pcMsg, /*OUT*/char** p_pcKey, /*OUT*/int* p_piKeyLen);

	/*
	 *	����:	��һ��tConfig���õõ�license key
	 */
	int iLCryptStr(LM_HANDLE, /*IN*/const tConfig& p_sConfig, /*OUT*/char** p_pcKey, /*OUT*/int* p_piKeyLen);
	
	/*
	 *	����:	Ϊһ���ļ�����ժҪ��Ϣ
	 */
	int iLMsgDigest(LM_HANDLE, char* p_pcMsg, /*OUT*/ unsigned char** p_pcDigest, /*OUT*/int* p_piDigestLen);

	
	/*
	 *	����:	ȡһ�����ܵ�license��Ϣ
	 */
	tConfig* psFindFeature(/*IN*/LM_HANDLE, /*IN*/const char* p_pcFeatureName, const char* p_pcFeatureVersion = NULL);


	/*
	 *	����:	ȡlicense��Ϣ��ĳһ����
	 */
	int iLGetLicField(/*IN*/LM_HANDLE, /*IN*/const char* p_pcFeatureName, /**/const char* p_pcVersion,/*IN*/eLicField p_eLicField, /*OUT*/char* p_pcFieldStr, /*OUT*/int* p_iFieldLen);


	/*
	 *	����:	�Ƚϰ汾
	 */
	int iLCompareVersion(LM_HANDLE, const char* p_pcVer1, const char* p_pcVer2);


	/*
	 *	����:	�ж�license�����Ƿ�����
	 */
	int iLHeartBeat();


	/*
	 *	����:	��ô���������Ϣ
	 */
	char* pcErrorText(int p_iErrorCode);

	/*
	 *	��ȡ���һ��������,������Ϊ�ÿⶨ���ֵ
	 */
	int iLGetLibLastError(void);

private:

	/*
	 *	����:	�ͷ���Դ,�����ڴ�ʹ��
	 */
	int	 iInternalFree();

	//����������ܣ��ڲ�ʹ��
	tConfig* psInternalFindFeature(const char* p_pcFearName, const char* p_pcFeatVer);

	//license�ļ��б�
	vector<tLicenseFile*>	m_vecLicenseFile;

	//����������ܵ�license��Ϣ�б�
	vector<tConfig*>		m_vecAllFeature;

	//��ʱ�õ�license��Ϣ��ŵ�
	tConfig					m_sTmpConfig;

	//��ʼ��״̬
	int						m_iStatus;

	//���һ�������,������Ϊ�Զ���Ĵ���ֵ
	int						m_iLastError;

	//License��ҵID�б�
	vector<int>				m_vecJobs;
};

//ASCII��ת��Ϊʮ��������
int iASCIIToHex(unsigned char* p_pcResult, unsigned char* p_pcASCBuf, int p_iLen);
//ʮ��������ת��ΪASCII��
int iHexToASCII(BYTE *p_pcResult, BYTE *p_pcHexBuf, int p_iLen);

#endif // !defined(AFX_OLICMANAGER_H__156868EB_2330_4FA3_9988_8D81EBC4100D__INCLUDED_)
