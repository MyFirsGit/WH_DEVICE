// LicClient.h: interface for the OLicClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LICCLIENT_H__28125779_3E41_4981_B98F_23B66FF955BB__INCLUDED_)
#define AFX_LICCLIENT_H__28125779_3E41_4981_B98F_23B66FF955BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//license feature行的各个域
enum eLicenseField
{
	FEATURENAME = 0,		//软件功能名
	VENDORNAME,				//厂商ID
	FEATUREVERSION,			//软件功能版本
	EXPIREDATE,				//过期时间
	MAXUSERS,				//最大用户数
	LICENSEKEY,				//license key
	VENDORSTRING,			//厂商自定义串
	LOCKHOSTID				//主机名
};

//License客户端
class OLicClient  
{
public:
	//构造与析构函数
	OLicClient();
	virtual ~OLicClient();

	/*
		功能: 取错误码对应的描述信息
		参数:
			[输入]p_iErrorCode		错误号
		返回:
			描述字符串,如果不存在则返回NULL
	 */
	char* pcLcErrorString(int p_iErrorCode);

	/*
		功能: 取一个软件功能License信息的相关域
		参数:
			[输入]p_pcFeatureName		软件功能名
			[输入]p_pcFeatureVersion	软件功能版本
			[输入]p_eLicField			License信息域
			[输出]p_pcOutValue			输出结果		
			[输出]p_iOutLen				输出结果长度
		返回:
			1 : 成功	<1:失败
	 */
	int iLcGetField(const char* p_pcFeatureName, const char* p_pcFeatureVersion, eLicenseField p_eLicField, char* p_pcOutValue, int& p_iOutLen);

	/*
		功能: 检出一个软件功能的License
		参数:
			[输入]p_pcFeatureName		软件功能名
			[输入]p_pcFeatureVersion	软件功能版本
			[输入]p_iUserCount			需要检出的License用户数，在多用户License下才有意义
		返回:
			1 : 成功	<1:失败
	 */
	int iLcCheckout(const char* p_pcFeatureName, const char* p_pcFeatureVersion, int p_iUserCount);

	/*
		功能: 检入一个软件功能的License
		参数:
			[输入]p_pcFeatureName		软件功能名
			[输入]p_pcFeatureVersion	软件功能版本
		返回:
			1 : 成功	<1:失败
	 */
	int iLcCheckin(const char* p_pcFeatureName, const char* p_pcFeatureVersion);

	/*
		功能: 安装license文件路径到系统环境变量,一次调用只能装一个license文件
		参数:
			[输入]p_pcFilePath			license文件路径
			[输入]p_iAppend				是否追加到现有环境变量值串的后边以";"隔开，缺省为追加,=0时则替换现有环境变量的值
			[输入]p_pcEnvVar			环境变量名,缺省为GrgLicenseFile
		返回:
			1 : 成功	<1:失败
	 */
	int iLcInstallLicPath(const char* p_pcFilePath, int p_iAppend = 1, const char* p_pcEnvVar = "GrgLicenseFile");

private:

	//License基础库是否初始化成功
	int		m_iInitLicenseOK;
};

#endif // !defined(AFX_LICCLIENT_H__28125779_3E41_4981_B98F_23B66FF955BB__INCLUDED_)
