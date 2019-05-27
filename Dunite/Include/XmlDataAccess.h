// xmldataaccess.h

#pragma once

#include <msxml2.h>

class OXmlDataAccess: public ODataAccessBase
{
public:
	OXmlDataAccess();
	~OXmlDataAccess();
	
private:
	IXMLDOMDocument *m_pIXMLDoc;
	
	IXMLDOMElement* piFindChildElement(IXMLDOMElement* p_piPElement, LPCTSTR p_pcName);
	IXMLDOMElement* piGetElement(LPCTSTR p_pcPath);
	IXMLDOMElement* piCreateNewElement(LPCTSTR p_pcKeyName, IXMLDOMElement* p_pIParent);
	BOOL bGetElementText(IXMLDOMNode* p_pIEle, tstring& p_strRet);
	
public:

	// 打开配置数据源
	HRESULT hrOpenData( 
		LPCTSTR p_pcSource,
		LPCTSTR p_pcExt,
		short p_psCreateNew,
		short *p_psRet);
	
	// 关闭配置数据源
    HRESULT hrCloseData( 
		short *p_psRet);
	
	// 创建军一个配置节
	HRESULT hrCreateSection( 
		LPCTSTR p_pcPSec,
		LPCTSTR p_pcNewSec,
		short *p_psRet);
	
	// 删除一个配置节
	HRESULT hrDeleteSection( 
		LPCTSTR p_pcPSec,
		LPCTSTR p_pcDelSec,
		short *p_psRet);
	
	// 得到某个键值
	HRESULT hrGetValue( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		tstring *p_pstrValue);
	
	// 设置某个键值
	HRESULT hrSetValue( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		LPCTSTR p_pcValue,
		CfgDataType p_iType,
		short *p_psRet);
	
	// 新建一个键
	HRESULT hrCreateKey( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		tstring p_strInitValue,
		short *p_psRet);
	
	// 删除一个键
	HRESULT hrDeleteKey( 
		LPCTSTR p_pcSection,
		LPCTSTR p_pcKeyName,
		short *p_psRet);
	
	// 枚举当前配置节下的所有的节点，包括配置节和配置键值
	HRESULT hrEnumChildNodes( 
		LPCTSTR p_pcPSection,
		vector<tNodeInfo>& p_tvNodes);

	// 确认更新
	HRESULT hrCommit( 
		short *p_psRet);
	
	// 得到多个键的值
	HRESULT hrGetValues( 
		LPCTSTR p_pcSection,
		vector<tstring> p_tvKeyNames,
		vector<VARIANT>* p_ptvValue);
	
	// 设置多个键的值
	HRESULT hrSetValues( 
		LPCTSTR p_pcSection,
		vector<tstring> p_tvKeyNames,
		vector<VARIANT> p_ptvValue, 
		short *p_psRet);
	
};

