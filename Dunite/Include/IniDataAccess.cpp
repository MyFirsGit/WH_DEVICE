/********************************************************************
�������ڣ�	2003/07/11
��Ʒ���ƣ�	
ģ�����ƣ�	inidataaccess
���ߣ�		������

����˵����	INI�����ļ��ķ���

===========================��ģ����ʷ�޸ļ�¼==========================
============================��ʷ�޸ļ�¼��=============================
*********************************************************************/

#include "io.h"
#include "DataAccessBase.h"
#include "inidataaccess.h"

// ����\0�ֿ���������\0�������ַ������е�ÿ���ַ�����ֵ�Vector��
void vStrsToVector(LPCTSTR p_pcStrs, vector<tstring>& p_tvStrs, int& p_iLen)
{
	// p_iLen: ���������ַ��ĳ��ȣ��������е�\0
	
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
				// ����0, ��β��
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

// ��"key=value"��\0�ֿ���������\0�������ַ����������map��
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

// ����������Դ
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
			// �����µ������ļ�
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

// �ر���������Դ
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

// ����һ�����ý�
HRESULT OIniDataAccess::hrCreateSection( 
	LPCTSTR p_pcPSec,
	LPCTSTR p_pcNewSec,
	short *p_psRet)
{
	// ����INI�ļ�������p_pcPSec

	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;

	if (m_strIniFile.empty())
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}

	TCHAR l_acbuffer[10];
	
	// Ҫ������Section�Ƿ����
	DWORD l_dwGeted = GetPrivateProfileSection(p_pcNewSec, l_acbuffer, 10*sizeof(TCHAR), m_strIniFile.c_str());
	if (l_dwGeted > 0)
	{
		// �Ѵ���,���سɹ�
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
	
	// Ҫɾ����Section�Ƿ����
	DWORD l_dwGeted = GetPrivateProfileSection(p_pcNewSec, l_acbuffer, 256*sizeof(TCHAR), m_strIniFile.c_str());
	if (l_dwGeted == 0)
	{
		// ������,���سɹ�
		*p_psRet = CFG_SUCCESS;
		l_hrRet = S_OK;
	}
	else
	{
		// ����,�������������key���,������Section,��ΪINI�޷�ɾ��Section
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

	LPTSTR l_pstrRet = new TCHAR[4096*4];	// ���16K
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

// �����µ����ü�
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
	
	LPTSTR l_pstrRet = new TCHAR[4096*4*4];	// ���64K
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
	
	LPTSTR l_pstrRet = new TCHAR[4096*4];	// ���16K
	
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

	// �õ������е�ÿһ����
	for (l_iIndex = 0; l_iIndex < p_tvKeyNames.size(); l_iIndex++)
	{
		// �õ�NODE
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
