/********************************************************************
创建日期：	2003/07/11
产品名称：	
模块名称：	regdataaccess
作者：		刘道余

功能说明：	注册表配置数据源的访问

===========================本模块历史修改记录==========================
============================历史修改记录完=============================
*********************************************************************/

#include "DataAccessBase.h"
#include "regdataaccess.h"

BOOL ORegDataAccess::bGetHKeyFromStr(LPCTSTR p_pcSource, tstring& p_strSubKey, HKEY& p_hKey)
{
	TCHAR l_acHKEY[MAX_PATH];
	TCHAR l_acSubKey[MAX_PATH];
	
	memset(l_acHKEY, 0, sizeof(l_acHKEY));
	memset(l_acSubKey, 0, sizeof(l_acSubKey));

	TCHAR* pcFind = _tcschr(p_pcSource, _T('\\'));
	if (pcFind)
	{
		_tcsncpy(l_acHKEY, p_pcSource, (pcFind - p_pcSource));
		_tcscpy(l_acSubKey, pcFind + 1);
		p_strSubKey = l_acSubKey;
	}
	else
	{
		p_strSubKey = _T("");
		_tcscpy(l_acHKEY, p_pcSource);
	}
	
	if (0 == _tcsicmp(l_acHKEY, _T("HKEY_CLASSES_ROOT")))
	{
		p_hKey = HKEY_CLASSES_ROOT;
	}
	else if (0 == _tcsicmp(l_acHKEY, _T("HKEY_CURRENT_CONFIG")))
	{
		p_hKey = HKEY_CURRENT_CONFIG;
	}
	else if (0 == _tcsicmp(l_acHKEY, _T("HKEY_CURRENT_USER")))
	{
		p_hKey = HKEY_CURRENT_USER;
	}
	else if (0 == _tcsicmp(l_acHKEY, _T("HKEY_LOCAL_MACHINE")))
	{
		p_hKey = HKEY_LOCAL_MACHINE;
	}
	else if (0 == _tcsicmp(l_acHKEY, _T("HKEY_USERS")))
	{
		p_hKey = HKEY_USERS;
	}
	else
	{
		if (_tcslen(l_acSubKey) == 0)
			p_strSubKey = p_pcSource;
	}

	return TRUE;
}

HKEY ORegDataAccess::hOpenParentKey(LPCTSTR p_pcPSec)
{
	tstring l_strSubKey;
	HKEY l_hKey = NULL;
	
	if (p_pcPSec != NULL && _tcslen(p_pcPSec) > 0)
	{
		bGetHKeyFromStr(p_pcPSec, l_strSubKey, l_hKey);
	}
	else
		return m_hKeyOpened;

	HKEY l_hOpenPKey = NULL;
	LONG l_lRet;
	
	if (NULL != l_hKey)
	{
		// 如果p_pcPSec中包含了HKEY_...，则打开它
		if (l_strSubKey.length() > 0)
		{
			l_lRet = RegOpenKeyEx(
				l_hKey,
				l_strSubKey.c_str(),
				0,
				KEY_ALL_ACCESS,
				&l_hOpenPKey
				);
		}
		else
		{
			l_lRet = RegOpenKeyEx(
				l_hKey,
				NULL,
				0,
				KEY_ALL_ACCESS,
				&l_hOpenPKey
				);
		}
		
	}
	else
	{
		l_lRet = RegOpenKeyEx(
			m_hKeyOpened,
			p_pcPSec,
			0,
			KEY_ALL_ACCESS,
			&l_hOpenPKey
			);
	}

	return l_hOpenPKey;
}
//////////////////////////////////////////////////////////////////////
// 
ORegDataAccess::ORegDataAccess()
{
	m_hKeyOpened = NULL;
}

ORegDataAccess::~ORegDataAccess()
{
	short l_sRet;
	hrCloseData(&l_sRet);
}

// 打开配置数据源
HRESULT ORegDataAccess::hrOpenData( 
	LPCTSTR p_pcSource,
	LPCTSTR p_pcExt,
	short p_psCreateNew,
	short *p_psRet)
{
	*p_psRet = CFG_FAIL;
	HRESULT l_hrRet = S_FALSE;
	HRESULT l_hr = S_OK;
	
	if (_tcslen(p_pcSource) == 0)
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}

	tstring l_strSubKey;
	HKEY l_hKey = NULL;
	
	bGetHKeyFromStr(p_pcSource, l_strSubKey, l_hKey);
	if (NULL == l_hKey)
	{
		*p_psRet = CFG_NODATASOURCE;
		return l_hrRet;
	}

	HKEY l_hKeyOpened;
	LONG l_lRet;
	if (p_psCreateNew && l_strSubKey.length() > 0)
	{
		DWORD l_dwCreate;
		l_lRet = RegCreateKeyEx(
					l_hKey,
					l_strSubKey.c_str(),
					0,
					NULL,
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS,
					NULL,
					&l_hKeyOpened,
					&l_dwCreate);
	}
	else
	{
		if (l_strSubKey.length() > 0)
		{
			l_lRet = RegOpenKeyEx(
				l_hKey,
				l_strSubKey.c_str(),
				0,
				KEY_ALL_ACCESS,
				&l_hKeyOpened
				);
		}
		else
		{
			l_lRet = RegOpenKeyEx(
				l_hKey,
				NULL,
				0,
				KEY_ALL_ACCESS,
				&l_hKeyOpened
				);
		}
	}

	if (ERROR_SUCCESS == l_lRet)
	{
		m_hKeyOpened = l_hKeyOpened;
		*p_psRet = CFG_SUCCESS;
		l_hrRet = S_OK;
	}
	else
	{
		*p_psRet = CFG_FAIL;
		l_hrRet = S_FALSE;
		return l_hrRet;
	}
	
	if (m_hLockMutex)
	{
		ReleaseMutex(m_hLockMutex);
		CloseHandle(m_hLockMutex);
		m_hLockMutex = NULL;

		m_hLockMutex = CreateMutex(NULL, FALSE, p_pcSource);
	}

	return l_hrRet;
}

// 关闭配置数据源
HRESULT ORegDataAccess::hrCloseData( 
	short *p_psRet)
{
	*p_psRet = CFG_FAIL;
	HRESULT l_hrRet = S_FALSE;
	
	if (m_hKeyOpened)
	{
		RegCloseKey(m_hKeyOpened);
		m_hKeyOpened = NULL;
		*p_psRet = CFG_SUCCESS;

		if (m_hLockMutex)
		{
			ReleaseMutex(m_hLockMutex);
			CloseHandle(m_hLockMutex);
			m_hLockMutex = NULL;
		}

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
HRESULT ORegDataAccess::hrCreateSection( 
	LPCTSTR p_pcPSec,
	LPCTSTR p_pcNewSec,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;

	LONG l_lRet;
	DWORD l_dwCreate;
	HKEY l_hKeyCreated = NULL;

	HKEY l_hOpenPKey = hOpenParentKey(p_pcPSec);

	if (l_hOpenPKey)
	{
		l_lRet = RegCreateKeyEx(
			l_hOpenPKey,
			p_pcNewSec,
			0,
			NULL,
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			NULL,
			&l_hKeyCreated,
			&l_dwCreate);
		if (l_hOpenPKey != m_hKeyOpened)
		{
			RegCloseKey(l_hOpenPKey);
		}
	}
	else
	{
		*p_psRet = CFG_FAIL;
		l_hrRet = S_FALSE;
		return l_hrRet;
	}

	if (l_lRet == ERROR_SUCCESS)
	{
		*p_psRet = CFG_SUCCESS;
		l_hrRet = S_OK;
		RegCloseKey(l_hKeyCreated);
	}
	else
	{
		*p_psRet = CFG_FAIL;
		l_hrRet = S_FALSE;
	}
	
	return l_hrRet;
}

HRESULT ORegDataAccess::hrDeleteSection( 
	LPCTSTR p_pcPSec,
	LPCTSTR p_pcNewSec,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	LONG l_lRet;
	HKEY l_hKeyCreated = NULL;
	
	HKEY l_hOpenPKey = hOpenParentKey(p_pcPSec);
	
	if (l_hOpenPKey)
	{
		l_lRet = RegDeleteKey(l_hOpenPKey, p_pcNewSec);
		if (l_hOpenPKey != m_hKeyOpened)
		{
			RegCloseKey(l_hOpenPKey);
		}
	}
	else
	{
		*p_psRet = CFG_FAIL;
		l_hrRet = S_FALSE;
		return l_hrRet;
	}
	
	if (l_lRet == ERROR_SUCCESS)
	{
		*p_psRet = CFG_SUCCESS;
		l_hrRet = S_OK;
	}
	else
	{
		*p_psRet = CFG_FAIL;
		l_hrRet = S_FALSE;
	}
	
	return l_hrRet;
}

HRESULT ORegDataAccess::hrGetValue( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	tstring *p_pstrValue)
{
	HRESULT l_hrRet = S_FALSE;

	LONG l_lRet;
	HKEY l_hOpenPKey = hOpenParentKey(p_pcSection);
	if (l_hOpenPKey)
	{
		LPBYTE l_pbData = new BYTE[4096*4];	// 最大16K
		memset(l_pbData, 0, 4096*4);
		DWORD l_dwType, l_dwRetCount = 4096*4;
		l_lRet = RegQueryValueEx(l_hOpenPKey, p_pcKeyName, NULL, &l_dwType, l_pbData, &l_dwRetCount);
		if (ERROR_SUCCESS == l_lRet)
		{
			if (l_dwType == REG_BINARY)
			{
				// 要进行Encoder
				*p_pstrValue = (LPCTSTR)l_pbData;
			}
			else if (l_dwType == REG_DWORD)
			{
				LONG l_lValue = MAKELONG(MAKEWORD(l_pbData[0], l_pbData[1]), MAKEWORD(l_pbData[2], l_pbData[3]));
				TCHAR l_acValue[64];
				memset(l_acValue, 0, 64*sizeof(TCHAR));
				_itot(l_lValue, l_acValue, 10);
				*p_pstrValue = l_acValue;
			}
			else
			{
				*p_pstrValue = (LPCTSTR)l_pbData;
			}

			l_hrRet = S_OK;
		}
		delete []l_pbData;
		
		if (l_hOpenPKey != m_hKeyOpened)
		{
			RegCloseKey(l_hOpenPKey);
		}
	}
	
	return l_hrRet;
}

HRESULT ORegDataAccess::hrSetValue( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	LPCTSTR p_pcValue,
	CfgDataType p_iType,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	LONG l_lRet;
	HKEY l_hOpenPKey = hOpenParentKey(p_pcSection);
	if (l_hOpenPKey)
	{
		if (cfgNumber == p_iType)
		{
			DWORD l_dwValue = _ttoi(p_pcValue);
			l_lRet = RegSetValueEx(l_hOpenPKey, p_pcKeyName, 0, REG_DWORD, (LPBYTE)&l_dwValue, sizeof(DWORD));
		}
		else if (cfgtstring == p_iType) 
		{
			l_lRet = RegSetValueEx(l_hOpenPKey, p_pcKeyName, 0, REG_SZ, (LPBYTE)p_pcValue, (_tcslen(p_pcValue)+1)*sizeof(TCHAR));
		}
		else if (cfgBinary == p_iType)
		{
			// 要进行Decorder
			//REG_BINARY;
			return E_NOTIMPL;
		}
		if (l_hOpenPKey != m_hKeyOpened)
		{
			RegCloseKey(l_hOpenPKey);
		}

		if (ERROR_SUCCESS == l_lRet)
		{
			l_hrRet = S_OK;
			*p_psRet = CFG_SUCCESS;
		}
	}
	
	return l_hrRet;
}

// 创建新的配置键
HRESULT ORegDataAccess::hrCreateKey( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	tstring p_strInitValue,
	short *p_psRet)
{
	return hrSetValue(p_pcSection, p_pcKeyName, p_strInitValue.c_str(), cfgtstring, p_psRet);
}

HRESULT ORegDataAccess::hrDeleteKey( 
	LPCTSTR p_pcSection,
	LPCTSTR p_pcKeyName,
	short *p_psRet)
{
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;

	LONG l_lRet;
	HKEY l_hOpenPKey = hOpenParentKey(p_pcSection);
	if (l_hOpenPKey)
	{
		l_lRet = RegDeleteValue(l_hOpenPKey, p_pcKeyName);
		if (l_hOpenPKey != m_hKeyOpened)
		{
			RegCloseKey(l_hOpenPKey);
		}
		
		if (ERROR_SUCCESS == l_lRet)
		{
			l_hrRet = S_OK;
			*p_psRet = CFG_SUCCESS;
		}
	}
	
	return l_hrRet;
}


HRESULT ORegDataAccess::hrEnumChildNodes( 
	LPCTSTR p_pcPSection,
	vector<tNodeInfo>& p_tvNodes)
{
	USES_CONVERSION;

	tNodeInfo l_sNode;
	HRESULT l_hrRet = S_FALSE;
	VARIANT l_varEmptyValue;
	VariantInit(&l_varEmptyValue);

	
	LONG l_lRet;
	HKEY l_hOpenPKey = hOpenParentKey(p_pcPSection);
	if (l_hOpenPKey)
	{
		// Enum all sections
		DWORD	l_dwIndex, l_dwKeyLen;
		TCHAR	l_acKeyName[MAX_PATH];
		FILETIME l_sft;
		
		for (l_dwIndex = 0, l_lRet = ERROR_SUCCESS; l_lRet == ERROR_SUCCESS; l_dwIndex++) 
		{ 
			memset(l_acKeyName, 0, sizeof(l_acKeyName));
			
			l_dwKeyLen = MAX_PATH;
			VariantInit(&l_sNode.varNodeValue);
			
			l_lRet = RegEnumKeyEx(l_hOpenPKey, l_dwIndex, l_acKeyName, &l_dwKeyLen, NULL, 
				NULL, NULL, &l_sft); 
			if (ERROR_SUCCESS == l_lRet) 
			{
				l_sNode.sNodeType = 0;
				l_sNode.strNodeName = l_acKeyName;
				VariantCopy(&l_sNode.varNodeValue, &l_varEmptyValue);
				p_tvNodes.push_back(l_sNode);
			}
		}
		
		// Enum all keys
		DWORD	l_dwDataType, l_dwDataSize;
		LPBYTE l_pbData = new BYTE[4096*4];	// 最大16K
		
		for (l_dwIndex = 0, l_lRet = ERROR_SUCCESS; l_lRet == ERROR_SUCCESS; l_dwIndex++) 
		{ 
			memset(l_acKeyName, 0, sizeof(l_acKeyName));
			memset(l_pbData, 0, 4096*4);
			
			l_dwKeyLen = MAX_PATH;
			l_dwDataSize = 4096*4;
			VariantInit(&l_sNode.varNodeValue);
			
			l_lRet = RegEnumValue(l_hOpenPKey, l_dwIndex, l_acKeyName, &l_dwKeyLen, NULL, 
				&l_dwDataType, l_pbData, &l_dwDataSize); 
			if (ERROR_SUCCESS == l_lRet) 
			{
				l_sNode.sNodeType = 1;
				l_sNode.strNodeName = l_acKeyName;
				switch (l_dwDataType)
				{
				case REG_SZ:
					l_sNode.varNodeValue.vt = VT_BSTR;
					l_sNode.varNodeValue.bstrVal = T2BSTR((LPCTSTR)l_pbData);
					break;
				case REG_DWORD:
					l_sNode.varNodeValue.vt = VT_I4;
					l_sNode.varNodeValue.lVal = MAKELONG(MAKEWORD(l_pbData[0], l_pbData[1]), MAKEWORD(l_pbData[2], l_pbData[3]));
					break;
				case REG_BINARY:
					//need to do
				default:
					break;
				}
				p_tvNodes.push_back(l_sNode);
			}
		}
		delete []l_pbData;
		
		if (l_hOpenPKey != m_hKeyOpened)
		{
			RegCloseKey(l_hOpenPKey);
		}
		l_hrRet = S_OK;
	}

	return l_hrRet;
}

HRESULT ORegDataAccess::hrCommit( 
	short *p_psRet)
{
	return S_OK;
}

HRESULT ORegDataAccess::hrGetValues( 
	LPCTSTR p_pcSection,
	vector<tstring> p_tvKeyNames,
	vector<VARIANT>* p_ptvValue)
{
	USES_CONVERSION;
	HRESULT l_hrRet = S_FALSE;
	VARIANT l_varEmptyValue;
	VariantInit(&l_varEmptyValue);
	
	LONG l_lRet;
	HKEY l_hOpenPKey = hOpenParentKey(p_pcSection);
	if (l_hOpenPKey)
	{
		LPBYTE l_pbData = new BYTE[4096*4];	// 最大16K
		VARIANT l_varValue;
		for (vector<tstring>::const_iterator it = p_tvKeyNames.begin(); it != p_tvKeyNames.end(); it++)
		{
			tstring l_strKey = *it;
			if (l_strKey.empty())
			{
				p_ptvValue->push_back(l_varEmptyValue);
			}
			else
			{
				memset(l_pbData, 0, 4096*4);
				DWORD l_dwType, l_dwRetCount = 4096*4;
				VariantInit(&l_varValue);

				l_lRet = RegQueryValueEx(l_hOpenPKey, l_strKey.c_str(), NULL, &l_dwType, l_pbData, &l_dwRetCount);
				if (ERROR_SUCCESS == l_lRet)
				{
					if (l_dwType == REG_BINARY)
					{
						// NEED TO DO
					}
					else if (l_dwType == REG_DWORD)
					{
						LONG l_lValue = MAKELONG(MAKEWORD(l_pbData[0], l_pbData[1]), MAKEWORD(l_pbData[2], l_pbData[3]));
						l_varValue.vt = VT_I4;
						l_varValue.lVal = l_lValue;
						p_ptvValue->push_back(l_varValue);
					}
					else
					{
						l_varValue.vt = VT_BSTR;
						l_varValue.bstrVal = T2BSTR((LPCTSTR)l_pbData);
						p_ptvValue->push_back(l_varValue);
					}
					
					l_hrRet = S_OK;
				}

			}
		}
		delete []l_pbData;
	}
	l_hrRet = S_OK;

	return l_hrRet;
}

HRESULT ORegDataAccess::hrSetValues( 
	LPCTSTR p_pcSection,
	vector<tstring> p_tvKeyNames,
	vector<VARIANT> p_ptvValue,
	short *p_psRet)
{
	USES_CONVERSION;
	HRESULT l_hrRet = S_FALSE;
	*p_psRet = CFG_FAIL;
	
	LONG l_lRet;
	HKEY l_hOpenPKey = hOpenParentKey(p_pcSection);
	if (l_hOpenPKey)
	{
	
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
				HRESULT hr;
				CComVariant l_oVar(p_ptvValue[l_iIndex]);
				if (p_ptvValue[l_iIndex].vt == VT_I1
					|| p_ptvValue[l_iIndex].vt == VT_I2
					|| p_ptvValue[l_iIndex].vt == VT_I4
					|| p_ptvValue[l_iIndex].vt == VT_UI2
					|| p_ptvValue[l_iIndex].vt == VT_UI4
					|| p_ptvValue[l_iIndex].vt == VT_UI1)
				{
					hr = l_oVar.ChangeType(VT_I4);
					DWORD l_dwValue = l_oVar.lVal;
					l_lRet = RegSetValueEx(l_hOpenPKey, l_strKey.c_str(), 0, REG_DWORD, (LPBYTE)&l_dwValue, sizeof(DWORD));
				}
				else if (p_ptvValue[l_iIndex].vt == VT_SAFEARRAY)
				{
					// 要进行Decorder
					//REG_BINARY;
					return E_NOTIMPL;
				}
				else
				{
					hr = l_oVar.ChangeType(VT_BSTR);
					LPCTSTR pcValue = OLE2T(l_oVar.bstrVal);
					l_lRet = RegSetValueEx(l_hOpenPKey, l_strKey.c_str(), 0, REG_SZ, (LPBYTE)pcValue, (_tcslen(pcValue)+1)*sizeof(TCHAR));
				}

				if (l_hOpenPKey != m_hKeyOpened)
				{
					RegCloseKey(l_hOpenPKey);
				}
				
				if (ERROR_SUCCESS == l_lRet)
				{
					l_bSuc = TRUE;
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
	}
	return l_hrRet;
}
