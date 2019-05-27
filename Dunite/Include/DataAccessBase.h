// DataAccessBase.h

#if !defined(_DATAACCESSBASE_H)
#define _DATAACCESSBASE_H

#if _MSC_VER > 1000
#pragma once
#endif 

struct tNodeInfo
{
	tstring strNodeName;
	VARIANT varNodeValue;
	short sNodeType;		// 0: Section, 1: Key
};

enum CfgDataType
{
	cfgNumber,
	cfgtstring,
	cfgBinary
};

// ���ݷ��ʻ���
class ODataAccessBase
{
public:
	ODataAccessBase();
	~ODataAccessBase();

protected:
	tstring m_strDataFile;		// ��������Դ
	HANDLE m_hLockMutex;

public:
	HRESULT hrLock(long p_lTimeout, short *p_psRet);
	HRESULT hrUnlock();
       
	// ����������Դ
	virtual HRESULT hrOpenData( 
		LPCTSTR p_pcFilePath,
		LPCTSTR p_pcExt,
		short p_psCreateNew,
		short *p_psRet) = 0;
        
	// �ر���������Դ
    virtual HRESULT hrCloseData( 
		short *p_psRet) = 0;
        
	// ������һ�����ý�
	virtual HRESULT hrCreateSection( 
		LPCTSTR p_pcPSec,
		LPCTSTR p_pcNewSec,
		short *p_psRet) = 0;
	
	// ɾ��һ�����ý�
	virtual HRESULT hrDeleteSection( 
		LPCTSTR p_pcPSec,
		LPCTSTR p_pcDelSec,
		short *p_psRet) = 0;
	
	// �õ�ĳ����ֵ
	virtual HRESULT hrGetValue( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		tstring *p_pstrValue) = 0;
	
	// ����ĳ����ֵ
	virtual HRESULT hrSetValue( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		LPCTSTR p_pcValue,
		CfgDataType p_iType,
		short *p_psRet) = 0;
        
	// �½�һ����
	virtual HRESULT hrCreateKey( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		tstring p_strInitValue,
		short *p_psRet) = 0;
        
	// ɾ��һ����
	virtual HRESULT hrDeleteKey( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		short *p_psRet) = 0;
        
	// ö�ٵ�ǰ���ý��µ����еĽڵ㣬�������ýں����ü�ֵ
	virtual HRESULT hrEnumChildNodes( 
		LPCTSTR p_pcPSection,
		vector<tNodeInfo>& p_tvNodes) = 0;
	
	// ȷ�ϸ���
	virtual HRESULT hrCommit( 
		short *p_psRet) = 0;

	// �õ��������ֵ
	virtual HRESULT hrGetValues( 
		LPCTSTR p_pcSection,
		vector<tstring> p_tvKeyNames,
		vector<VARIANT>* p_ptvValue) = 0;
	
	// ���ö������ֵ
	virtual HRESULT hrSetValues( 
		LPCTSTR p_pcSection,
		vector<tstring> p_tvKeyNames,
		vector<VARIANT> p_ptvValue, 
		short *p_psRet) = 0;
		
};

#endif