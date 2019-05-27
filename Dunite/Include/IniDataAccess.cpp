/********************************************************************
创建日期：	2003/07/11
产品名称：	
模块名称：	inidataaccess
作者：		刘道余

功能说明：	INI配置文件的访问

===========================本模块历史修改记录==========================
============================历史修改记录完=============================
*********************************************************************/

#include "io.h"
#include "DataAccessBase.h"
#include "inidataaccess.h"

// 将以\0分开，以两个\0结束的字符串组中的每个字符串拆分到Vector中
void vStrsToVector(LPCTSTR p_pcStrs, vector<tstring>& p_tvStrs, int& p_iLen)
{
	// p_iLen: 返回所有字符的长度，包含所有的\0
	
	if (!p_pcStrs)
		return;
	
	LPCTSTR l_pcSubStr = p_pcStrs;
	p_iLen = 0;
	
	while (TRUE)
	{
		int l_i_tcslen = _tcslen(l_pcSubStr);
		if (l_i_tcslen > 0)
		{
			tstring l_strSub = l_pcSubStr;
			p_tvStrs.push_back(l_strSub);
			
			l_pcSubStr += l_i_tcslen;
			p_iLen += l_i_tcslen;
			
			if (0 == l_pcSubStr[0] == l_pcSubStr[1])
			{
				// 两个0, 到尾了
				p_iLen +=2;
				break;
			}
			else
			{
				p_iLen++;
				l_pcSubStr++;
			}
		}
		else
			break;
	}
}

// 将"key=value"以\0分开，以两个\0结束的字符串组解析到map中
void vKVStrstoMap(LPCTSTR p_pcStrs, map<tstring, tstring>& p_tmElements)
{
	if (!p_pcStrs)
		return;
	
	vector<tstring> l_tvElements;
	int l_iLen;
	vStrsToVector(p_pcStrs, l_tvElements, l_iLen);
	
	for (vector<tstring>::const_iterator it = l_tvElements.begin(); it != l_tvElements.end(); it++)
	{
		tstring l_strKey;
		tstring l_strValue;
		tstring::size_type l_pos = (*it).find('=');
		if (tstring::npos != l_pos)
		{
			l_strKey = (*it).substr(0, l_pos);
			l_strValue = (*it).substr(l_pos + 1);
			p_tmElements.insert(make_pair(l_strKey, l_strValue));
		}
	}
}


//////////////////////////////////////////////////////////////////////
// 
OIniDataAccess::OIniDataAccess()
{
	m_strIniFile = _T("");
}

OIniDataAccess::~OIniDataAccess()
{
	short l_sRet;
	hrCloseData(&l_sRet);
}

// 打开配置数据源
HRESULT OIniDataAccess::hrOpenData( 
	LPCTSTR p_pcSource,
	LPCTSTR p_pcExt,
	short p_psCreateNew,
	short *p_psRet)
{
	*p_psRet = CFG_FAIL;
	HRESULT l_hrRet = S_FALSE;
	HRESULT l_hr = S_OK;

	if (0 != _taccess(p_pcSource, 0))
	{
		if (1 == p_psCreateNew)
		{
			// 创建新的配置文件
			FILE* hfile = _tfopen(p_pcSource, _T("a"));
			if (NULL == hfile)
				return S_FALSE;
			fclose(hfile);
		}
		else
			return l_hrRet;
	}

	m_strIniFile = p_pcSource;
	
	if (m_hLockMutex)
	{
		ReleaseMutex(m_hLockMutex);
		CloseHandle(m_hLockMutex);
		m_hLockMutex = NULL;

		m_hLockMutex = CreateMutex(NULL, FALSE, m_strIniFile.c_str());
	}

	*p_psRet = CFG_SUCCESS;
	l_hrRet = S_OK;
	return l_hrRet;
}

// 关闭配置数据源
HRESULT OIniDataAccess::hrCloseData( 
	short *p_psRet)
{
	*p_psRet = CFG_FAIL;
	HRESULT l_hrRet = S_FALSE;
	
	if (!m_strIniFile.empty())
	{
		*p_psRet = CFG_SUCCESS;

		if (m_hLockMutex)
		{
			ReleaseMutex(m_hLockMutex);
			CloseHandle(m_hLockMutex);
			m_hLockMutex = NULL;
		}

		m_strIniFile = _T("");
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
HRESULT OIniDataAccess::hrCreateSection( 
	LPCTSTR p_pcPSec,
	LPCTSTR p_pcNewSec,
	short *p_psRet)
{
	// 对于INI文件，忽略p_pcPSec

	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;

	if (m_strIniFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}

	TCHAR l_acbuffer[10];
	
	// 要创建的Section是否存在
	DWORD l_dwGeted = GetPrivateProfileSection(p_pcNewSec, l_acbuffer, 10*sizeof(TCHAR), m_strIniFile.c_str());
	if (l_dwGeted > 0)
	{
		// 已存在,返回成功
		*p_psRet = CFG_SUCCESS;
		l_hrRet = S_OK;
	}
	else
	{
		BOOL l_bRet = WritePrivateProfileSection(p_pcNewSec, _T(""), m_strIniFile.c_str());
		if (l_bRet)
		{
			*p_psRet = CFG_SUCCESS;
			l_hrRet = S_OK;
		}
		else
		{
			*p_psRet = CFG_FAIL;
			l_hrRet = S_FALSE;
		}
	}
	
	return l_hrRet;
}

HRESULT OIniDataAccess::hrDeleteSection( 
	LPCTSTR p_pcPSec,
	LPCTSTR p_pcNewSec,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (m_strIniFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}
	
	TCHAR l_acbuffer[256];
	
	// 要删除的Section是否存在
	DWORD l_dwGeted = GetPrivateProfileSection(p_pcNewSec, l_acbuffer, 256*sizeof(TCHAR), m_strIniFile.c_str());
	if (l_dwGeted == 0)
	{
		// 不存在,返回成功
		*p_psRet = CFG_SUCCESS;
		l_hrRet = S_OK;
	}
	else
	{
		// 存在,将其下面的所有key清空,但保持Section,因为INI无法删除Section
		BOOL l_bRet = WritePrivateProfileSection(p_pcNewSec, _T(""), m_strIniFile.c_str());
		if (l_bRet)
		{
			*p_psRet = CFG_SUCCESS;
			l_hrRet = S_OK;
		}
		else
		{
			*p_psRet = CFG_FAIL;
			l_hrRet = S_FALSE;
		}
	}
	
	return l_hrRet;
}

HRESULT OIniDataAccess::hrGetValue( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	tstring *p_pstrValue)
{
	HRESULT l_hrRet = S_FALSE;
	
	if (m_strIniFile.empty())
	{
		return l_hrRet;
	}

	LPTSTR l_pstrRet = new TCHAR[4096*4];	// 最大16K
	memset(l_pstrRet, 0, 4096*4*sizeof(TCHAR));

	DWORD l_dwRet = GetPrivateProfileString(p_pcSection, p_pcKeyName, NULL, l_pstrRet, 4096*4*sizeof(TCHAR), m_strIniFile.c_str());
	if (l_dwRet > 0)
	{
		*p_pstrValue = l_pstrRet;
		l_hrRet = S_OK;
	}
	else
	{
		*p_pstrValue = _T("");
	}
	delete []l_pstrRet;

	return l_hrRet;
}

HRESULT OIniDataAccess::hrSetValue( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	LPCTSTR p_pcValue,
	CfgDataType p_iType,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (m_strIniFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}
	
	BOOL l_bRet = WritePrivateProfileString(p_pcSection, p_pcKeyName, p_pcValue, m_strIniFile.c_str());
	if (l_bRet)
	{
		l_hrRet = S_OK;
		*p_psRet = CFG_SUCCESS;
	}
	else
	{
		*p_psRet = CFG_FAIL;
		l_hrRet = S_FALSE;
	}
	return l_hrRet;
}

// 创建新的配置键
HRESULT OIniDataAccess::hrCreateKey( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	tstring p_strInitValue,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (m_strIniFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}

	BOOL l_bRet = WritePrivateProfileString(p_pcSection, p_pcKeyName, p_strInitValue.c_str(), m_strIniFile.c_str());
	if (l_bRet)
	{
		l_hrRet = S_OK;
		*p_psRet = CFG_SUCCESS;
	}
	else
	{
		*p_psRet = CFG_FAIL;
		l_hrRet = S_FALSE;
	}
	
	return l_hrRet;
}

HRESULT OIniDataAccess::hrDeleteKey( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (m_strIniFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}
	
	BOOL l_bRet = WritePrivateProfileString(p_pcSection, p_pcKeyName, NULL, m_strIniFile.c_str());
	if (l_bRet)
	{
		l_hrRet = S_OK;
		*p_psRet = CFG_SUCCESS;
	}
	else
	{
		*p_psRet = CFG_FAIL;
		l_hrRet = S_FALSE;
	}
	
	return l_hrRet;
}


HRESULT OIniDataAccess::hrEnumChildNodes( 
	LPCTSTR p_pcPSection,
	vector<tNodeInfo>& p_tvNodes)
{
	USES_CONVERSION;

	HRESULT l_hrRet = S_FALSE;
	VARIANT l_varEmptyValue;
	VariantInit(&l_varEmptyValue);

	
	if (m_strIniFile.empty())
	{
		return l_hrRet;
	}
	
	LPTSTR l_pstrRet = new TCHAR[4096*4*4];	// 最大64K
	memset(l_pstrRet, 0, 4096*4*4*sizeof(TCHAR));
	DWORD l_dwRet;

	tNodeInfo l_sNode;
	if (_tcslen(p_pcPSection) == 0)
	{
		// all sections
		l_dwRet = GetPrivateProfileSectionNames(l_pstrRet, 4096*4*4*sizeof(TCHAR), m_strIniFile.c_str());
		if (l_dwRet > 0)
		{
			vector<tstring> l_tvSections;
			int l_iLen = 0;
			vStrsToVector(l_pstrRet, l_tvSections, l_iLen);
			for (vector<tstring>::const_iterator it = l_tvSections.begin(); it != l_tvSections.end(); it++)
			{
				l_sNode.sNodeType = 0;
				l_sNode.strNodeName = (*it).c_str();
				VariantCopy(&(l_sNode.varNodeValue), &l_varEmptyValue);
				p_tvNodes.push_back(l_sNode);
			}
			l_hrRet = S_OK;
		}
			
	}
	else
	{
		// keys and values
		l_dwRet = GetPrivateProfileSection(p_pcPSection, l_pstrRet, 4096*4*4, m_strIniFile.c_str());
		if (l_dwRet > 0)
		{
			map<tstring, tstring> l_tmKeyValues;
			vKVStrstoMap(l_pstrRet, l_tmKeyValues);
			for (map<tstring, tstring>::const_iterator it = l_tmKeyValues.begin(); it != l_tmKeyValues.end(); it++)
			{
				l_sNode.sNodeType = 1;
				l_sNode.strNodeName = (*it).first.c_str();
				VariantInit(&(l_sNode.varNodeValue));
				l_sNode.varNodeValue.vt = VT_BSTR;
				l_sNode.varNodeValue.bstrVal = T2BSTR((*it).second.c_str());
				p_tvNodes.push_back(l_sNode);
			}
			l_hrRet = S_OK;
		}
	}
	
	delete []l_pstrRet;

	return l_hrRet;
}

HRESULT OIniDataAccess::hrCommit( 
	short *p_psRet)
{
	return S_OK;
}

HRESULT OIniDataAccess::hrGetValues( 
	LPCTSTR p_pcSection,
	vector<tstring> p_tvKeyNames,
	vector<VARIANT>* p_ptvValue)
{
	USES_CONVERSION;
	HRESULT l_hrRet = S_FALSE;
	VARIANT l_varEmptyValue;
	VariantInit(&l_varEmptyValue);
	
	if (m_strIniFile.empty())
	{
		return l_hrRet;
	}
	
	LPTSTR l_pstrRet = new TCHAR[4096*4];	// 最大16K
	
	for (vector<tstring>::const_iterator it = p_tvKeyNames.begin(); it != p_tvKeyNames.end(); it++)
	{
		tstring l_strKey = *it;
		if (l_strKey.empty())
		{
			p_ptvValue->push_back(l_varEmptyValue);
		}
		else
		{
			memset(l_pstrRet, 0, 4096*4*sizeof(TCHAR));
			DWORD l_dwRet = GetPrivateProfileString(p_pcSection, l_strKey.c_str(), NULL, l_pstrRet, 4096*4*sizeof(TCHAR), m_strIniFile.c_str());
			
			if (l_dwRet > 0)
			{
				VARIANT l_varValue;
				VariantInit(&l_varValue);
				CComVariant l_var(l_pstrRet);
				l_var.Detach(&l_varValue);
				p_ptvValue->push_back(l_varValue);
			}
			else
			{
				p_ptvValue->push_back(l_varEmptyValue);
			}
		}
	}
	l_hrRet = S_OK;

	delete []l_pstrRet;
	
	return l_hrRet;
}

HRESULT OIniDataAccess::hrSetValues( 
	LPCTSTR p_pcSection,
	vector<tstring> p_tvKeyNames,
	vector<VARIANT> p_ptvValue,
	short *p_psRet)
{
	USES_CONVERSION;
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	if (m_strIniFile.empty())
	{
		return l_hrRet;
	}
	
	BOOL l_bSuc = FALSE;
	int l_iIndex = 0;

	// 得到数组中的每一个键
	for (l_iIndex = 0; l_iIndex < p_tvKeyNames.size(); l_iIndex++)
	{
		// 得到NODE
		tstring l_strKey = p_tvKeyNames[l_iIndex];
		if (l_strKey.empty())
		{
		}
		else
		{
			CComVariant l_oVar(p_ptvValue[l_iIndex]);
			HRESULT hr = l_oVar.ChangeType(VT_BSTR);
			if (SUCCEEDED(hr))
			{
				BOOL l_bRet = WritePrivateProfileString(p_pcSection, l_strKey.c_str(), OLE2T(l_oVar.bstrVal), m_strIniFile.c_str());
				if (l_bRet)
				{
					l_bSuc = TRUE;
				}
			}
		}
	}
	if (l_bSuc)
	{
		l_hrRet = S_OK;
		*p_psRet = CFG_SUCCESS;
	}
	else
	{
		*p_psRet = CFG_FAIL;
		l_hrRet = S_FALSE;
	}
	return l_hrRet;
}
