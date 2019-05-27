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

// 数据访问基类
class ODataAccessBase
{
public:
	ODataAccessBase();
	~ODataAccessBase();

protected:
	tstring m_strDataFile;		// 配置数据源
	HANDLE m_hLockMutex;

public:
	HRESULT hrLock(long p_lTimeout, short *p_psRet);
	HRESULT hrUnlock();
       
	// 打开配置数据源
	virtual HRESULT hrOpenData( 
		LPCTSTR p_pcFilePath,
		LPCTSTR p_pcExt,
		short p_psCreateNew,
		short *p_psRet) = 0;
        
	// 关闭配置数据源
    virtual HRESULT hrCloseData( 
		short *p_psRet) = 0;
        
	// 创建军一个配置节
	virtual HRESULT hrCreateSection( 
		LPCTSTR p_pcPSec,
		LPCTSTR p_pcNewSec,
		short *p_psRet) = 0;
	
	// 删除一个配置节
	virtual HRESULT hrDeleteSection( 
		LPCTSTR p_pcPSec,
		LPCTSTR p_pcDelSec,
		short *p_psRet) = 0;
	
	// 得到某个键值
	virtual HRESULT hrGetValue( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		tstring *p_pstrValue) = 0;
	
	// 设置某个键值
	virtual HRESULT hrSetValue( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		LPCTSTR p_pcValue,
		CfgDataType p_iType,
		short *p_psRet) = 0;
        
	// 新建一个键
	virtual HRESULT hrCreateKey( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		tstring p_strInitValue,
		short *p_psRet) = 0;
        
	// 删除一个键
	virtual HRESULT hrDeleteKey( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		short *p_psRet) = 0;
        
	// 枚举当前配置节下的所有的节点，包括配置节和配置键值
	virtual HRESULT hrEnumChildNodes( 
		LPCTSTR p_pcPSection,
		vector<tNodeInfo>& p_tvNodes) = 0;
	
	// 确认更新
	virtual HRESULT hrCommit( 
		short *p_psRet) = 0;

	// 得到多个键的值
	virtual HRESULT hrGetValues( 
		LPCTSTR p_pcSection,
		vector<tstring> p_tvKeyNames,
		vector<VARIANT>* p_ptvValue) = 0;
	
	// 设置多个键的值
	virtual HRESULT hrSetValues( 
		LPCTSTR p_pcSection,
		vector<tstring> p_tvKeyNames,
		vector<VARIANT> p_ptvValue, 
		short *p_psRet) = 0;
		
};

#endif