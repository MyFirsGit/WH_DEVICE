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
 *	常量定义
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

//License环境变量，保存License文件路径
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
 *	license文件	
 */
struct tLicenseFile
{
	int	iType;		//license文件类型:文件,字符串,服务端地址
#define LF_NOTHING	0		//空
#define LF_FILE		1		//文件
#define LF_STRING	2		//字符串
#define LF_SERVER	3		//服务端
	union
	{
		FILE*	pfFile;
		char*	pcStr;
		char*	pcServer;
	} ptr;
	char* pcFileName;
};


/*
 *	license用户信息
 */
struct tLMUsers
{
	char	acName[MAX_LONGNAME_SIZE + 1];
	char	acNode[MAX_LONGNAME_SIZE + 1];
	char	acDisplay[MAX_LONGNAME_SIZE + 1];
	int		nlic;	
};


/*
 *	主机标识信息	
 */
struct tHostID
{
//预定义的一些主机标识
#define HOSTID_DEFAULT		-1
#define HOSTID_ANY			0
#define HOSTID_ETHER		1<<0
#define HOSTID_HOSTNAME		1<<1
#define HOSTID_DISKSERIAL	1<<2
#define HOSTID_CPU			1<<3
#define HOSTID_INTERNET		1<<4
//主机标识类别后缀
#define HOSTIDTYPE_ETHER		'a'
#define HOSTIDTYPE_HOSTNAME		'b'
#define HOSTIDTYPE_DISKSERIAL	'c'
#define HOSTIDTYPE_CPU			'd'
#define HOSTIDTYPE_INTERNET		'e'

#define HOSTID_TYPE_COUNT		6	//支持的HOSTID类型数目
#define HOSTIDTYPEINDEX1(t)		(t - 'a' + 1)	//将IDTYPE转换成以一为起点的序数,不包括ANY类型		
//多个主机标识间的分隔符
#define HOSTID_DELIM			'+'
	char	id[MAX_HOSTNAME_LEN];	//字符串，以同时支持多个项复合型的ID
	short	type;						//标识的类型(MAC,DiskSerial等等)
	
};

/*
 *	license文件中的license服务器信息
 */
struct tLMServer
{
	char		acName[MAX_LONGNAME_SIZE + 1];	//主机名
	tHostID*	psHostID;						//主机ID
#define COMMTYPE_TCP		0
#define COMMTYPE_UDP		1
	int			iCommType;						//通讯类型, TCP/UDP...

#define DEFAULT_SERVERPORT	3801
	short		shPort;							//服务端口	
	long		lIp;							//IP地址

	tLMServer();
	tLMServer(const tLMServer& src);
	tLMServer& operator=(const tLMServer& src);
	~tLMServer();
};

/*
 *	Liencse文件行
 */
#define SERVER_LINE		0
#define DAEMON_LINE		1
#define FEATURE_LINE	2
#define COMMENT_LINE	10

/*
 *	Feature 信息
 */
struct tConfig
{
	short		shType;					//feature行的类型,现只支持基本类型0
#define CONFIG_FEATURE		0			//基本的feature行，默认
#define CONFIG_INCREMENT	1			//INCREMENT行，暂不用
#define CONFIG_UPGRADE		2			//UPGRADE行，暂不用
#define CONFIG_BORROW		3			//BORROW行，暂不用
	
	//feature行的相关域
	char	acFeature[MAX_FEATURE_LEN + 1];	//功能名
	char	acVersion[MAX_VER_LEN + 1];		//版本号
	char	acDaemon[MAX_DAEMON_NAME + 1];	//厂商ID
	char	acDate[DATE_LEN + 1];			//过期时间,"permenant"永不过期
	char	acSdate[DATE_LEN + 1];			//开始时间
	int		iUsers;							//限制用户数,0不限制
	char	acKey[MAX_CRYPT_LEN + 1];		//license key
	tHostID* psHostID;						//限定的主机标识,"any"不限制
	char	acVendorStr[CUSTOMSTRING_LEN];	//自定义的字符串
	tLMServer* psServer;					//服务端信息

	int		iCkout;							//检出次数
	tConfig();
	~tConfig();
	tConfig(const tConfig& src);
	tConfig& operator=(const tConfig& src);
};

/*
 * license的会话句柄,用于指定会话相关参数	
 */
struct tLMHandle
{
	int iJobId;			//一个license作业ID
	int iStatus;		//初始化状态
#define STATUS_INIT				1
#define STATUS_LOADLIC			2
};

typedef tLMHandle  LM_HANDLE;

//license软件功能行的组成字段
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
 *	License处理的基本类,包含license处理的所有核心过程
 */
class OLicManager  
{
public:
	OLicManager();
	virtual ~OLicManager();
	
	/*
	 *	功能: 初始化LicenseManager会话
	 */
	int iLInit(LM_HANDLE&);


	/*
	 *	功能: 释放会话相关的资源
	 */
	int iLFree(LM_HANDLE);

	/*
	 *	功能: 装载License文件
	 */
	int iLLoadLicFile(LM_HANDLE, const char* p_pcEnv = ENV_LICENSEPATH);

	/*
	 *	功能: 安装license文件路径的系统环境变量,缺省为ENV_LICENSEPATH(即GrgLinceseFile)
	 */
	int iLInstallEnv(LM_HANDLE, const char* p_pcValue, int p_iAppend = 1, const char* p_pcEnv = ENV_LICENSEPATH);

	/*
	 *	功能:	检出一个软件功能的license
	 */
	int iLCheckout(LM_HANDLE, const char* p_pcFeature, const char* p_pcVersion, const int p_iLicNum, int p_iFlag);

	/*
	 *	功能:	检入一个软件功能的license
	 */
	int iLCheckin(LM_HANDLE, const char* p_pcFeature, const char* p_pcVersion);


	/*
	 *	功能:	取一个软件功能的license占用用户列表
	 */
	int iLUserList(LM_HANDLE p_sHandle, char* p_pcFeature, tLMUsers** p_ppsUsers);


	/*
	 *	功能:	解析一个license文件里的所有软件功能license
	 */
	int iLAllFeature(LM_HANDLE, FILE*);


	/*
	 *	功能:	分析一个license文件行
	 */
	int iLParseFeatureLine(LM_HANDLE, char* p_psLine, tConfig* p_psConfig, int* p_piError);


	/*
	 *	功能:	判断日期是否有效
	 */
	int iLDate(LM_HANDLE, char* p_pcDate, int p_iFlag = 0);

	
	/*
	 *	功能:	判断版本格式是否有效
	 */
	int iLVersion(LM_HANDLE, char* p_pcVersion);


	/*
	 *	功能:	判断是否为有效的主机标识
	 */
	int iLHost(LM_HANDLE, tHostID* p_psHostID);

	
	/*
	 *	功能:	将一个license key解密
	 */
	int iLDecryptKey(LM_HANDLE p_sHandle, /*IN*/unsigned char* p_pcKey, /*IN*/int p_piKeyLen, /*OUT*/char** pcMsg, /*OUT*/int* p_piMsgLen);

	
	/*
	 *	功能:	将一个tConfig结构组合成一个license行(SERVER/FEATURE/DAEMON)
	 */
	char* pcFeatureString(LM_HANDLE, const tConfig*, int p_iForKeyGen = 1, int p_iLine = FEATURE_LINE);

	
	/*
	 *	功能:	判断license key是否有效
	 */
	int iLVLK(LM_HANDLE, tConfig*);

	
	/*
	 *	功能:	取主机信息
	 */
	int iLGetHostID(/*IN*/LM_HANDLE, /*IN*/int p_iIDType, tHostID* p_psHostID, int p_iSuffix = 1);

	/*
	 *	功能:	获取一个主机标识串的类型，并将其解析成一个数组(如果有多个)
	 */
	int iLHostIDType(LM_HANDLE, const char* p_pcID, vector<char*>* p_pvecIDs, int& p_iType);

	/*
	 *	功能: 将一个串转换成tHostID,如果tHostID里已经有数据，将在原来的基础上追加
	 */
	int iLCatHostID(LM_HANDLE, /*IN*/const char* p_pcID, /*IN*/int p_iType, /*OUT*/tHostID& p_sHostID);
	
	/*
	 *	功能:	由一个串得到license key
	 */
	int iLCryptStr(LM_HANDLE, char* p_pcMsg, /*OUT*/char** p_pcKey, /*OUT*/int* p_piKeyLen);

	/*
	 *	功能:	由一个tConfig配置得到license key
	 */
	int iLCryptStr(LM_HANDLE, /*IN*/const tConfig& p_sConfig, /*OUT*/char** p_pcKey, /*OUT*/int* p_piKeyLen);
	
	/*
	 *	功能:	为一串文件生成摘要信息
	 */
	int iLMsgDigest(LM_HANDLE, char* p_pcMsg, /*OUT*/ unsigned char** p_pcDigest, /*OUT*/int* p_piDigestLen);

	
	/*
	 *	功能:	取一个功能的license信息
	 */
	tConfig* psFindFeature(/*IN*/LM_HANDLE, /*IN*/const char* p_pcFeatureName, const char* p_pcFeatureVersion = NULL);


	/*
	 *	功能:	取license信息的某一个域
	 */
	int iLGetLicField(/*IN*/LM_HANDLE, /*IN*/const char* p_pcFeatureName, /**/const char* p_pcVersion,/*IN*/eLicField p_eLicField, /*OUT*/char* p_pcFieldStr, /*OUT*/int* p_iFieldLen);


	/*
	 *	功能:	比较版本
	 */
	int iLCompareVersion(LM_HANDLE, const char* p_pcVer1, const char* p_pcVer2);


	/*
	 *	功能:	判断license服务是否在线
	 */
	int iLHeartBeat();


	/*
	 *	功能:	获得错误描述信息
	 */
	char* pcErrorText(int p_iErrorCode);

	/*
	 *	获取最后一个错误编号,错误编号为该库定义的值
	 */
	int iLGetLibLastError(void);

private:

	/*
	 *	功能:	释放资源,仅供内存使用
	 */
	int	 iInternalFree();

	//查找软件功能，内部使用
	tConfig* psInternalFindFeature(const char* p_pcFearName, const char* p_pcFeatVer);

	//license文件列表
	vector<tLicenseFile*>	m_vecLicenseFile;

	//所有软件功能的license信息列表
	vector<tConfig*>		m_vecAllFeature;

	//临时用的license信息存放地
	tConfig					m_sTmpConfig;

	//初始化状态
	int						m_iStatus;

	//最后一个错误号,错误编号为自定义的错误值
	int						m_iLastError;

	//License作业ID列表
	vector<int>				m_vecJobs;
};

//ASCII码转换为十六进制型
int iASCIIToHex(unsigned char* p_pcResult, unsigned char* p_pcASCBuf, int p_iLen);
//十六进制型转换为ASCII码
int iHexToASCII(BYTE *p_pcResult, BYTE *p_pcHexBuf, int p_iLen);

#endif // !defined(AFX_OLICMANAGER_H__156868EB_2330_4FA3_9988_8D81EBC4100D__INCLUDED_)
