// regdataaccess.h

#pragma once

class ORegDataAccess: public ODataAccessBase
{
public:
	ORegDataAccess();
	~ORegDataAccess();
	
private:
	BOOL bGetHKeyFromStr(LPCTSTR p_pcSource, tstring& p_strSubKey, HKEY& p_hKey);
	HKEY hOpenParentKey(LPCTSTR p_pcPSec);
		
	HKEY m_hKeyOpened;

public:
	// ����������Դ
	HRESULT hrOpenData( 
		LPCTSTR p_pcSource,
		LPCTSTR p_pcExt,
		short p_psCreateNew,
		short *p_psRet);
	
	// �ر���������Դ
    HRESULT hrCloseData( 
		short *p_psRet);
	
	// ������һ�����ý�
	HRESULT hrCreateSection( 
		LPCTSTR p_pcPSec,
		LPCTSTR p_pcNewSec,
		short *p_psRet);
	
	// ɾ��һ�����ý�
	HRESULT hrDeleteSection( 
		LPCTSTR p_pcPSec,
		LPCTSTR p_pcDelSec,
		short *p_psRet);
	
	// �õ�ĳ����ֵ
	HRESULT hrGetValue( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		tstring *p_pstrValue);
	
	// ����ĳ����ֵ
	HRESULT hrSetValue( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		LPCTSTR p_pcValue,
		CfgDataType p_iType,
		short *p_psRet);
	
	// �½�һ����
	HRESULT hrCreateKey( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		tstring p_strInitValue,
		short *p_psRet);
	
	// ɾ��һ����
	HRESULT hrDeleteKey( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		short *p_psRet);
	
	// ö�ٵ�ǰ���ý��µ����еĽڵ㣬�������ýں����ü�ֵ
	HRESULT hrEnumChildNodes( 
		LPCTSTR p_pcPSection,
		vector<tNodeInfo>& p_tvNodes);
	
	// ȷ�ϸ���
	HRESULT hrCommit( 
		short *p_psRet);
	
	// �õ��������ֵ
	HRESULT hrGetValues( 
		LPCTSTR p_pcSection,
		vector<tstring> p_tvKeyNames,
		vector<VARIANT>* p_ptvValue);
	
	// ���ö������ֵ
	HRESULT hrSetValues( 
		LPCTSTR p_pcSection,
		vector<tstring> p_tvKeyNames,
		vector<VARIANT> p_ptvValue, 
		short *p_psRet);
};