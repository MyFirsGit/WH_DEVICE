/********************************************************************
创建日期：	2003/07/11
产品名称：	
模块名称：	xmldataaccess
作者：		刘道余

功能说明：	XML配置数据源的访问
注：使用MSXML SDK无法实现存储有\0的二进制数组，所以XML配置数据不提供对
二进制数据的配置
===========================本模块历史修改记录==========================
============================历史修改记录完=============================
*********************************************************************/

#include "DataAccessBase.h"
#include "xmldataaccess.h"
#include "io.h"

#pragma comment(lib,"msxml2.lib")
const TCHAR CINITFILE[] = _T("<?xml version=\"1.0\"?>\n<Configs></Configs>\n");

//////////////////////////////////////////////////////////////////////
// 
OXmlDataAccess::OXmlDataAccess()
{
	m_pIXMLDoc = NULL;
}

OXmlDataAccess::~OXmlDataAccess()
{
	short l_sRet;
	hrCloseData(&l_sRet);
}

// 找到名字匹配的子项
IXMLDOMElement* OXmlDataAccess::piFindChildElement(IXMLDOMElement* p_piPElement, LPCTSTR p_pcName)
{
	USES_CONVERSION;
	HRESULT l_hr = S_OK;
	IXMLDOMNode *l_pIChild = NULL;
	BSTR l_bstrName;
	DOMNodeType l_eType;
	
	// 只能在当前目录下循环查找
	IXMLDOMNodeList* l_pINodeList = NULL;
	p_piPElement->get_childNodes(&l_pINodeList);
	if (l_pINodeList)
	{
		long l_lCount = 0;
		l_pINodeList->get_length(&l_lCount);
		for (int i = 0; i < l_lCount; i++)
		{
			l_pINodeList->get_item(i, &l_pIChild);
			if (l_pIChild)
			{
				l_pIChild->get_nodeType(&l_eType);
				if (NODE_ELEMENT == l_eType)
				{
					l_pIChild->get_nodeName(&l_bstrName);
					ATLTRACE(OLE2CA(l_bstrName));
					ATLTRACE("\n");
					
					// 判断名字是否一样
					if(0 == _tcsicmp(OLE2CT(l_bstrName), p_pcName))
					{
						// 找到了
						IXMLDOMElement* l_pChildElement = NULL;
						l_hr = l_pIChild->QueryInterface(IID_IXMLDOMElement, (void**)&l_pChildElement);
						if (SUCCEEDED(l_hr))
							return l_pChildElement;
						else
							return NULL;
					}
				}
				l_pIChild->Release();
				l_pIChild = NULL;
			}
		}
		l_pINodeList->Release();
	}
	return NULL;
}

// 得到一个元素的文本值，之所以不直接使用
BOOL OXmlDataAccess::bGetElementText(IXMLDOMNode* p_pIEle, tstring& p_strRet)
{
	USES_CONVERSION;
	HRESULT l_hr = S_OK;
	BOOL	l_bRet = FALSE;
	IXMLDOMNode *l_pIChild = NULL;
	DOMNodeType l_eType;
	
	// 只能在当前目录下循环查找
	IXMLDOMNodeList* l_pINodeList = NULL;
	p_pIEle->get_childNodes(&l_pINodeList);
	if (l_pINodeList)
	{
		long l_lCount = 0;
		l_pINodeList->get_length(&l_lCount);
		for (int i = 0; i < l_lCount; i++)
		{
			l_pINodeList->get_item(i, &l_pIChild);
			if (l_pIChild)
			{
				l_pIChild->get_nodeType(&l_eType);
				if (NODE_TEXT == l_eType)
				{
					BSTR l_bstrText;
					l_hr = l_pIChild->get_text(&l_bstrText);
					if (SUCCEEDED(l_hr))
					{
						p_strRet = OLE2CT(l_bstrText);
						l_bRet = TRUE;
						l_pIChild->Release();
						l_pIChild = NULL;
						break;
					}
				}
				l_pIChild->Release();
				l_pIChild = NULL;
			}
		}
		l_pINodeList->Release();
	}
	return l_bRet;
}

// 根据给定的"..\..\"等的格式路径名找到相对应的元素
IXMLDOMElement* OXmlDataAccess::piGetElement(LPCTSTR p_pcPath)
{
	tstring l_strSrc = p_pcPath;
	unsigned int l_iPos = 0;
	tstring l_strName;
	unsigned int l_iToken = tstring::npos;
	
	IXMLDOMElement* l_piElement = NULL;
	m_pIXMLDoc->get_documentElement(&l_piElement);
	
	do 
	{
		l_iToken = l_strSrc.find('\\', l_iPos);
		if (l_iToken != tstring::npos)
		{
			l_strName = l_strSrc.substr(l_iPos, l_iToken - l_iPos);
			l_iPos = l_iToken + 1;
		}
		else
		{
			l_strName = l_strSrc.substr(l_iPos);
		}
		
		if (!l_strName.empty())
		{
			l_piElement = piFindChildElement(l_piElement, l_strName.c_str());
		}
	}while (l_iToken != tstring::npos && l_piElement != NULL);
	
	return l_piElement;
}

// 如果已存在，则返回已有的，如果没有则新建
IXMLDOMElement* OXmlDataAccess::piCreateNewElement(LPCTSTR p_pcKeyName, IXMLDOMElement* p_pIParent)
{
	// 新的子Section是否已存在
	IXMLDOMElement* l_pIChild = piFindChildElement(p_pIParent, p_pcKeyName);
	if (!l_pIChild)
	{
		// 不存在,加入新的
		IXMLDOMElement* l_piNewEle = NULL;
		HRESULT hr = m_pIXMLDoc->createElement(CComBSTR(p_pcKeyName), &l_piNewEle);
		if (SUCCEEDED(hr))
		{
			IXMLDOMNode* l_piAppendNode = NULL;
			p_pIParent->appendChild(l_piNewEle, &l_piAppendNode);
			if (l_piAppendNode)
			{
				l_piAppendNode->QueryInterface(IID_IXMLDOMElement, (void**)&l_pIChild);
				l_piAppendNode->Release();
			}
			l_piNewEle->Release();
		}
	}
	return l_pIChild;
}

// 打开配置数据源
HRESULT OXmlDataAccess::hrOpenData( 
	LPCTSTR p_pcSource,
	LPCTSTR p_pcExt,
	short p_psCreateNew,
	short *p_psRet)
{
	USES_CONVERSION;

	*p_psRet = CFG_FAIL;
	HRESULT l_hrRet = S_FALSE;
	HRESULT l_hr = S_OK;

	if (!m_pIXMLDoc)
	{
		// 得到XMLDocment的实例
		l_hr = CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER, 
			IID_IXMLDOMDocument, (void**)&m_pIXMLDoc);
		if(FAILED(l_hr)) 
			return l_hrRet ;
	}

	if(m_pIXMLDoc) 
	{
		VARIANT_BOOL l_bResult = VARIANT_TRUE;
		if (0 != _taccess(p_pcSource, 0))
		{
			if (1 == p_psCreateNew)
			{
				// 创建新的配置文件
				BSTR l_bstrFile = T2BSTR(CINITFILE);
				l_hr = m_pIXMLDoc->loadXML(l_bstrFile, &l_bResult);
				SysFreeString(l_bstrFile);
				if (FAILED(l_hr) || VARIANT_TRUE != l_bResult)
					return l_hrRet;

				l_hr = m_pIXMLDoc->save(CComVariant(p_pcSource));
				if (FAILED(l_hr))
					return l_hrRet;
			}
			else
				return l_hrRet;
		}
		else
		{
			l_hr = m_pIXMLDoc->load(CComVariant(p_pcSource), &l_bResult);
			if (FAILED(l_hr) || VARIANT_TRUE != l_bResult)
				return l_hrRet;
		}
		m_strDataFile = p_pcSource;

		if (m_hLockMutex)
		{
			ReleaseMutex(m_hLockMutex);
			CloseHandle(m_hLockMutex);
			m_hLockMutex = NULL;

			m_hLockMutex = CreateMutex(NULL, FALSE, m_strDataFile.c_str());
		}

		*p_psRet = CFG_SUCCESS;
		l_hrRet = S_OK;
	}
	return l_hrRet;
}

// 关闭配置数据源
HRESULT OXmlDataAccess::hrCloseData( 
	short *p_psRet)
{
	*p_psRet = CFG_FAIL;
	HRESULT l_hrRet = S_FALSE;
	
	if (m_pIXMLDoc)
	{
		if (!m_strDataFile.empty())
		{
			// 先储存
			HRESULT hr = m_pIXMLDoc->save(CComVariant(m_strDataFile.c_str()));
			if (FAILED(hr))
			{
				return l_hrRet;
			}
		}
		m_pIXMLDoc->Release();
		m_pIXMLDoc = NULL;
		*p_psRet = CFG_SUCCESS;

		if (m_hLockMutex)
		{
			ReleaseMutex(m_hLockMutex);
			CloseHandle(m_hLockMutex);
			m_hLockMutex = NULL;
		}

		m_strDataFile = _T("");
		l_hrRet = S_OK;
	}
	else
	{
		*p_psRet = CFG_NODATASOURCE;
		l_hrRet = S_FALSE;
	}
	return l_hrRet;
}

// 创建一个配置节
HRESULT OXmlDataAccess::hrCreateSection( 
	LPCTSTR p_pcPSec,
	LPCTSTR p_pcNewSec,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;

	if (!m_pIXMLDoc || m_strDataFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}

	// 得到指定的父配置节
	IXMLDOMElement* l_pIElement = piGetElement(p_pcPSec);
	if (l_pIElement)
	{
		// 新的子Section是否已存在
		IXMLDOMElement* l_pIChild = piCreateNewElement(p_pcNewSec, l_pIElement);
		if (l_pIChild)
		{
			l_pIChild->Release();
			*p_psRet = CFG_UPDATENEEDCOMMIT;
			l_hrRet = S_OK;
		}
		l_pIElement->Release();
	}
	else
	{
		*p_psRet = CFG_INVALIDSECTION;
		l_hrRet = S_FALSE;
	}
	return l_hrRet;
}

HRESULT OXmlDataAccess::hrDeleteSection( 
	LPCTSTR p_pcPSec,
	LPCTSTR p_pcNewSec,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (!m_pIXMLDoc || m_strDataFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}
	
	IXMLDOMElement* l_pIElement = piGetElement(p_pcPSec);
	if (l_pIElement)
	{
		// Section是否已存在
		IXMLDOMElement* l_pIChild = piFindChildElement(l_pIElement, p_pcNewSec);
		if (l_pIChild)
		{
			IXMLDOMNode* l_piNewNode = NULL;
			l_pIElement->removeChild(l_pIChild, &l_piNewNode);
			l_piNewNode->Release();
			l_pIChild->Release();
			*p_psRet = CFG_UPDATENEEDCOMMIT;
			l_hrRet = S_OK;
		}
		else
		{
			*p_psRet = CFG_INVALIDSECTION;
		}
		l_pIElement->Release();
	}
	else
	{
		*p_psRet = CFG_INVALIDSECTION;
	}
	return l_hrRet;
}

HRESULT OXmlDataAccess::hrGetValue( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	tstring *p_pstrValue)
{
	HRESULT l_hrRet = S_FALSE;
	
	if (!m_pIXMLDoc || m_strDataFile.empty())
	{
		return S_FALSE;
	}
	
	IXMLDOMElement* l_pIElement = piGetElement(p_pcSection);
	if (l_pIElement)
	{
		IXMLDOMElement* l_pIKeyEle = NULL;
		if (NULL == p_pcKeyName || (p_pcKeyName && 0 == _tcslen(p_pcKeyName)))
		{
			l_pIKeyEle = l_pIElement;
			l_pIKeyEle->AddRef();
		}
		else
		{
			// Key是否已存在
			l_pIKeyEle = piFindChildElement(l_pIElement, p_pcKeyName);
		}

		if (l_pIKeyEle)
		{
			tstring l_strText;
			if (bGetElementText(l_pIKeyEle, l_strText))
			{
				*p_pstrValue  = l_strText;
				l_hrRet = S_OK;
			}
			l_pIKeyEle->Release();
		}
		l_pIElement->Release();
	}
	return l_hrRet;
}

HRESULT OXmlDataAccess::hrSetValue( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	LPCTSTR p_pcValue,
	CfgDataType p_iType,
	short *p_psRet)
{
	USES_CONVERSION;
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (!m_pIXMLDoc || m_strDataFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}
	
	// 得到指定的父配置节
	IXMLDOMElement* l_pIElement = piGetElement(p_pcSection);
	if (l_pIElement)
	{
		IXMLDOMElement* l_pIKey = NULL;
		if (NULL == p_pcKeyName || (p_pcKeyName && 0 == _tcslen(p_pcKeyName)))
		{
			l_pIKey = l_pIElement;
			l_pIKey->AddRef();
		}
		else
		{
			// 得到键值，如果不存在，则新建一个
			l_pIKey = piCreateNewElement(p_pcKeyName, l_pIElement);
		}

		if (l_pIKey)
		{
			// 设置此Element的值
			BSTR bstrVal = T2BSTR(p_pcValue);
			l_pIKey->put_text(bstrVal);
			l_hrRet = S_OK;
			*p_psRet = CFG_UPDATENEEDCOMMIT;

			SysFreeString(bstrVal);
			l_pIKey->Release();
		}

		l_pIElement->Release();
	}
	else
	{
		*p_psRet = CFG_INVALIDSECTION;
		l_hrRet = S_FALSE;
	}
	return l_hrRet;
}

// 创建新的配置键
HRESULT OXmlDataAccess::hrCreateKey( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	tstring p_strInitValue,
	short *p_psRet)
{
	USES_CONVERSION;
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (!m_pIXMLDoc || m_strDataFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}
	
	// 得到指定的父配置节
	IXMLDOMElement* l_pIElement = piGetElement(p_pcSection);
	if (l_pIElement)
	{
		IXMLDOMElement* l_pIKeyEle = piCreateNewElement(p_pcKeyName, l_pIElement);

		// 设置此Element的初始值,类型
		if (!p_strInitValue.empty())
		{
			BSTR bstrVal = T2BSTR(p_strInitValue.c_str());
			l_pIKeyEle->put_text(bstrVal);
			SysFreeString(bstrVal);
		}
		l_hrRet = S_OK;
		*p_psRet = CFG_UPDATENEEDCOMMIT;
		l_pIElement->Release();
	}
	else
	{
		*p_psRet = CFG_INVALIDSECTION;
		l_hrRet = S_FALSE;
	}
	return l_hrRet;
}

HRESULT OXmlDataAccess::hrDeleteKey( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (!m_pIXMLDoc || m_strDataFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}
	
	// 得到指定的父配置节
	IXMLDOMElement* l_pIElement = piGetElement(p_pcSection);
	if (l_pIElement)
	{
		// 得到当前键
		IXMLDOMElement* l_pIKeyEle = piFindChildElement(l_pIElement, p_pcKeyName);
		if (l_pIKeyEle)
		{
			// 存在
			IXMLDOMNode* l_pINode = NULL;
			l_pIKeyEle->QueryInterface(IID_IXMLDOMNode, (LPVOID*)&l_pINode);
			if (l_pINode)
			{
				IXMLDOMNode* l_pIOldNode = NULL;
				l_pIElement->removeChild(l_pINode, &l_pIOldNode);
				if (l_pIOldNode)
				{
					l_pIOldNode->Release();
					*p_psRet = CFG_UPDATENEEDCOMMIT;
					l_hrRet = S_OK;
				}
				l_pINode->Release();
			}
			l_pIKeyEle->Release();
		}
		else
		{
			*p_psRet = CFG_INVALIDSECTION;
		}
		l_pIElement->Release();
	}
	else
	{
		*p_psRet = CFG_INVALIDSECTION;
	}
	return l_hrRet;
}

HRESULT OXmlDataAccess::hrEnumChildNodes( 
	LPCTSTR p_pcPSection,
	vector<tNodeInfo>& p_tvNodes)
{
	USES_CONVERSION;

	HRESULT l_hrRet = S_FALSE;
	VARIANT l_varEmptyValue;
	VariantInit(&l_varEmptyValue);
	
	if (!m_pIXMLDoc || m_strDataFile.empty())
	{
		return l_hrRet;
	}
	
	IXMLDOMElement* l_pIElement = piGetElement(p_pcPSection);
	if (l_pIElement)
	{
		// 当前的所有的子键
		IXMLDOMNodeList* l_pINodeList = NULL;

		l_pIElement->get_childNodes(&l_pINodeList);
		if (l_pINodeList)
		{
			long l_lCount = 0;
			IXMLDOMNode *l_pIChild = NULL;
			DOMNodeType l_eType;
			BSTR l_bstrName;
			tNodeInfo l_sNode;
			
			l_pINodeList->get_length(&l_lCount);
			for (int i = 0; i < l_lCount; i++)
			{
				memset(&l_sNode, 0, sizeof(l_sNode));
				l_pINodeList->get_item(i, &l_pIChild);
				if (l_pIChild)
				{
					l_pIChild->get_nodeType(&l_eType);
					l_pIChild->get_baseName(&l_bstrName);

					l_sNode.strNodeName = OLE2CT(l_bstrName);

					if (NODE_ELEMENT == l_eType)
					{
						// 为了简单，只能将有值的当作KEY，没值的当作Section
						tstring l_strText;
						l_sNode.sNodeType = 1;
						if (bGetElementText(l_pIChild, l_strText))
						{
							if (l_strText.empty())
								l_sNode.sNodeType = 0;
							CComVariant l_var(l_strText.c_str());
							l_var.ChangeType(VT_I4);
							l_var.Detach(&(l_sNode.varNodeValue));
							p_tvNodes.push_back(l_sNode);
						}
						else
						{
							l_sNode.sNodeType = 0;
							VariantCopy(&(l_sNode.varNodeValue), &l_varEmptyValue);
							p_tvNodes.push_back(l_sNode);
						}
					}
					l_pIChild->Release();
					l_pIChild = NULL;
				}
			}
			l_pINodeList->Release();
			l_hrRet = S_OK;
		}
	}
	return l_hrRet;
}

HRESULT OXmlDataAccess::hrCommit( 
	short *p_psRet)
{
	*p_psRet = CFG_SUCCESS;
	if (m_pIXMLDoc)
	{
		if (!m_strDataFile.empty())
		{
			m_pIXMLDoc->save(CComVariant(m_strDataFile.c_str()));
		}
		else
		{
			*p_psRet = CFG_NODATASOURCE;
		}
	}
	else
	{
		*p_psRet = CFG_NODATASOURCE;
	}
	return S_OK;
}

HRESULT OXmlDataAccess::hrGetValues( 
	LPCTSTR p_pcSection,
	vector<tstring> p_tvKeyNames,
	vector<VARIANT>* p_ptvValue)
{
	USES_CONVERSION;
	HRESULT l_hrRet = S_FALSE;
	VARIANT l_varEmptyValue;
	VariantInit(&l_varEmptyValue);
	
	if (!m_pIXMLDoc || m_strDataFile.empty())
	{
		return S_FALSE;
	}
	
	IXMLDOMElement* l_pIElement = piGetElement(p_pcSection);
	if (l_pIElement)
	{
		for (vector<tstring>::const_iterator it = p_tvKeyNames.begin(); it != p_tvKeyNames.end(); it++)
		{
			IXMLDOMElement* l_pIKey = NULL;
			tstring l_strKey = *it;
			if (l_strKey.empty())
			{
				l_pIKey = l_pIElement;
				l_pIKey->AddRef();
			}
			else
			{
				l_pIKey = piFindChildElement(l_pIElement, l_strKey.c_str());
			}
			
			if (l_pIKey)
			{
				tstring l_strText;
				if (bGetElementText(l_pIKey, l_strText))
				{
					CComVariant l_var(l_strText.c_str());
					l_var.ChangeType(VT_I4);
					VARIANT l_varValue;
					VariantInit(&l_varValue);
					l_var.Detach(&l_varValue);
					p_ptvValue->push_back(l_varValue);
				}
				else
				{
					p_ptvValue->push_back(l_varEmptyValue);
				}
				l_pIKey->Release();
			}
			else
			{
				p_ptvValue->push_back(l_varEmptyValue);
			}
		}
		l_pIElement->Release();
		l_hrRet = S_OK;
	}
	return l_hrRet;
}

HRESULT OXmlDataAccess::hrSetValues( 
	LPCTSTR p_pcSection,
	vector<tstring> p_tvKeyNames,
	vector<VARIANT> p_ptvValue,
	short *p_psRet)
{
	USES_CONVERSION;
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (!m_pIXMLDoc || m_strDataFile.empty())
	{
		return S_FALSE;
	}
	
	IXMLDOMElement* l_pIElement = piGetElement(p_pcSection);
	if (l_pIElement)
	{
		HRESULT hr = S_OK;
		BOOL l_bSuc = FALSE;
		int l_iIndex = 0;

		// 得到数组中的每一个键
		for (l_iIndex = 0; l_iIndex < p_tvKeyNames.size(); l_iIndex++)
		{
			// 得到NODE
			IXMLDOMElement* l_pIKey = NULL;
			tstring l_strKey = p_tvKeyNames[l_iIndex];
			if (l_strKey.empty())
			{
				l_pIKey = l_pIElement;
				l_pIKey->AddRef();
			}
			else
			{
				l_pIKey = piCreateNewElement(l_strKey.c_str(), l_pIElement);
			}
			
			if (l_pIKey)
			{
				// 设置值
				if (l_iIndex < p_ptvValue.size())
				{
					if (VT_EMPTY != p_ptvValue[l_iIndex].vt)
					{
						CComVariant l_oVar(p_ptvValue[l_iIndex]);
						HRESULT hr = l_oVar.ChangeType(VT_BSTR);
						if (SUCCEEDED(hr))
						{
							hr = l_pIKey->put_text(l_oVar.bstrVal);
							l_bSuc = TRUE;
						}
					}
				}
				l_pIKey->Release();
			}
		}

		if (l_bSuc)
		{
			l_hrRet = S_OK;
			*p_psRet = CFG_UPDATENEEDCOMMIT;
		}

		l_pIElement->Release();
	}
	else
	{
		*p_psRet = CFG_INVALIDSECTION;
		l_hrRet = S_FALSE;
	}
	return l_hrRet;
}
