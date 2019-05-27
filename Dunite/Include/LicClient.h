// LicClient.h: interface for the OLicClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LICCLIENT_H__28125779_3E41_4981_B98F_23B66FF955BB__INCLUDED_)
#define AFX_LICCLIENT_H__28125779_3E41_4981_B98F_23B66FF955BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//license feature�еĸ�����
enum eLicenseField
{
	FEATURENAME = 0,		//���������
	VENDORNAME,				//����ID
	FEATUREVERSION,			//������ܰ汾
	EXPIREDATE,				//����ʱ��
	MAXUSERS,				//����û���
	LICENSEKEY,				//license key
	VENDORSTRING,			//�����Զ��崮
	LOCKHOSTID				//������
};

//License�ͻ���
class OLicClient  
{
public:
	//��������������
	OLicClient();
	virtual ~OLicClient();

	/*
		����: ȡ�������Ӧ��������Ϣ
		����:
			[����]p_iErrorCode		�����
		����:
			�����ַ���,����������򷵻�NULL
	 */
	char* pcLcErrorString(int p_iErrorCode);

	/*
		����: ȡһ���������License��Ϣ�������
		����:
			[����]p_pcFeatureName		���������
			[����]p_pcFeatureVersion	������ܰ汾
			[����]p_eLicField			License��Ϣ��
			[���]p_pcOutValue			������		
			[���]p_iOutLen				����������
		����:
			1 : �ɹ�	<1:ʧ��
	 */
	int iLcGetField(const char* p_pcFeatureName, const char* p_pcFeatureVersion, eLicenseField p_eLicField, char* p_pcOutValue, int& p_iOutLen);

	/*
		����: ���һ��������ܵ�License
		����:
			[����]p_pcFeatureName		���������
			[����]p_pcFeatureVersion	������ܰ汾
			[����]p_iUserCount			��Ҫ�����License�û������ڶ��û�License�²�������
		����:
			1 : �ɹ�	<1:ʧ��
	 */
	int iLcCheckout(const char* p_pcFeatureName, const char* p_pcFeatureVersion, int p_iUserCount);

	/*
		����: ����һ��������ܵ�License
		����:
			[����]p_pcFeatureName		���������
			[����]p_pcFeatureVersion	������ܰ汾
		����:
			1 : �ɹ�	<1:ʧ��
	 */
	int iLcCheckin(const char* p_pcFeatureName, const char* p_pcFeatureVersion);

	/*
		����: ��װlicense�ļ�·����ϵͳ��������,һ�ε���ֻ��װһ��license�ļ�
		����:
			[����]p_pcFilePath			license�ļ�·��
			[����]p_iAppend				�Ƿ�׷�ӵ����л�������ֵ���ĺ����";"������ȱʡΪ׷��,=0ʱ���滻���л���������ֵ
			[����]p_pcEnvVar			����������,ȱʡΪGrgLicenseFile
		����:
			1 : �ɹ�	<1:ʧ��
	 */
	int iLcInstallLicPath(const char* p_pcFilePath, int p_iAppend = 1, const char* p_pcEnvVar = "GrgLicenseFile");

private:

	//License�������Ƿ��ʼ���ɹ�
	int		m_iInitLicenseOK;
};

#endif // !defined(AFX_LICCLIENT_H__28125779_3E41_4981_B98F_23B66FF955BB__INCLUDED_)
