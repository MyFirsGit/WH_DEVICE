

#include "stdafx.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 预处理
#include "Language.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 语言文件节名和键名
#define LIN_Language			_T("Language")
#define LIN_Description			_T("Description")
#define LIN_FontName			_T("FontName")
#define LIN_FontSize			_T("FontSize")
#define LIN_Text				_T("Text")
#define LIN_String				_T("String")

#define _NumberOf(v)			(sizeof(v) / sizeof(v[0]))
#define _LengthOf(s)			(_NumberOf(s) - 1)

#define _StrEnd(t)				(t + _tcslen(t))

#define _WStrToAStrN(a, w, n)	WideCharToMultiByte(CP_ACP, 0, w, -1, a, n, NULL, NULL)
#define _AStrToWStrN(w, a, n)	MultiByteToWideChar(CP_ACP, 0, a, -1, w, n)

#ifdef _UNICODE
#define _WStrToStrN(t, w, n)	lstrcpyn(t, w, n)
#else // _UNICODE
#define _WStrToStrN(t, w, n)	_WStrToAStrN(t, w, n)
#endif // _UNICODE
#define _WStrToStr(t, w)		_WStrToStrN(t, w, _NumberOf(t))

#ifndef IS_INTRESOURCE
#define IS_INTRESOURCE(r)		(((ULONG) (r) >> 16) == 0)
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLanguage 类静态变量
UINT CLanguage::m_uLang = 0; 
UINT CLanguage::m_uMax = 0; 
UINT CLanguage::m_uDefaultMenuID = 0; 
UINT CLanguage::m_uFirstLangMenuID = 0; 
HMODULE CLanguage::m_hResInst = NULL; 
HFONT CLanguage::m_hFont = NULL;
TCHAR CLanguage::m_tzFileName[MAX_PATH] = {0};

tstring CLanguage::m_strLangFilePath = _T("Language");
tstring CLanguage::m_strLangFileExt = _T(".lng");
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化语言
LANGID CLanguage::Initialize(UINT uDefaultMenuID, UINT uFirstLangID, LPCTSTR pstrLangFilePath, LPCTSTR pstrLangFileExt)
{
	m_uDefaultMenuID = m_uLang = m_uMax = uDefaultMenuID;
	m_uFirstLangMenuID = uFirstLangID;

	if (pstrLangFilePath)
		m_strLangFilePath = pstrLangFilePath;
	if (pstrLangFileExt)
		m_strLangFileExt = pstrLangFileExt;

	HANDLE hFind;
	LANGID liLang;
	LANGID liResult;
	WIN32_FIND_DATA fdFind;
	TCHAR tzPath[MAX_PATH];

#ifdef _MAKELANG
	// 生成语言文件
	hFind = NULL;
	ZeroMemory(&fdFind, sizeof(WIN32_FIND_DATA));
	liLang = GetUserDefaultLangID();
	liResult = liLang;
	//CIni::SetInt(INI_Language, liResult);
	GetModuleFileName(NULL, tzPath, MAX_PATH);
#ifdef _CHS
	_stprintf(_tcsrchr(tzPath, _T('\\')) + 1, _T("%s\\简体中文%s"), m_strLangFilePath.c_str(), m_strLangFileExt.c_str());
	WritePrivateProfileString(LIN_Language, LIN_Language, _T("2052"), tzPath);
	WritePrivateProfileString(LIN_Language, LIN_Description, _T("简体中文"), tzPath);
	WritePrivateProfileString(LIN_Language, LIN_FontName, _T("宋体"), tzPath);
	WritePrivateProfileString(LIN_Language, LIN_FontSize, _T("9"), tzPath);
#else // _CHS
	_stprintf(_tcsrchr(tzPath, _T('\\')) + 1, _T("%s\\English%s") , m_strLangFilePath.c_str(), m_strLangFileExt.c_str());
	WritePrivateProfileString(LIN_Language, LIN_Language, _T("1033"), tzPath);
	WritePrivateProfileString(LIN_Language, LIN_Description, _T("English"), tzPath);
	WritePrivateProfileString(LIN_Language, LIN_FontName, _T("Tahoma"), tzPath);
	WritePrivateProfileString(LIN_Language, LIN_FontSize, _T("8"), tzPath);
#endif // _CHS
	_tcscpy(m_tzFileName, tzPath);

#else // _MAKELANG
	// 获取语言标识
	liResult = 0;
	
	GetModuleFileName(NULL, tzPath, MAX_PATH);
	_stprintf(_tcsrchr(tzPath, _T('\\')) + 1, _T("%s\\Config.ini"), m_strLangFilePath.c_str());

	// 从配置文件中获取语言设置
	liLang = GetPrivateProfileInt(_T("Main"), LIN_Language, GetUserDefaultLangID(), tzPath);
	if (liLang)
	{
		// 查找语言文件
		GetModuleFileName(NULL, tzPath, MAX_PATH);
		_stprintf(_tcsrchr(tzPath, _T('\\')) + 1, _T("%s\\*%s") , m_strLangFilePath.c_str(), m_strLangFileExt.c_str());
		hFind = FindFirstFile(tzPath, &fdFind);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				// 如果是指定的语言
				_tcscpy(_tcsrchr(tzPath, _T('\\')) + 1, fdFind.cFileName);
				if (liLang == GetPrivateProfileInt(LIN_Language, LIN_Language, 0, tzPath))
				{
					// 设置语言文件名
					liResult = liLang;
					_tcscpy(m_tzFileName, tzPath);
					Set(NULL, liResult);
					break;
				}
			}
			while (FindNextFile(hFind, &fdFind));
			FindClose(hFind);
		}
	}
#endif // _MAKELANG

	return liResult;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 列出语言
UINT CLanguage::List(HMENU hMenu)
{
	HANDLE hFind;
	LANGID liLang;
	LANGID liTemp;
	WIN32_FIND_DATA fdFind;
	TCHAR tzPath[MAX_PATH];

	// 先删除掉原来的菜单项
	for(int i = m_uMax; i > m_uDefaultMenuID; i--)
	{
		DeleteMenu(hMenu, i, MF_BYCOMMAND);
	}
	DeleteMenu(hMenu, 1, MF_BYPOSITION);

	GetModuleFileName(NULL, tzPath, MAX_PATH);
	_stprintf(_tcsrchr(tzPath, _T('\\')) + 1, _T("%s\\Config.ini"), m_strLangFilePath.c_str());

	// 从配置文件中获取语言设置
	liLang = GetPrivateProfileInt(_T("Main"), LIN_Language, 0, tzPath);
	//liLang = CIni::GetInt(INI_Language);

	// 查找语言文件	
	GetModuleFileName(NULL, tzPath, MAX_PATH);
	_stprintf(_tcsrchr(tzPath, _T('\\')) + 1, _T("%s\\*%s") , m_strLangFilePath.c_str(), m_strLangFileExt.c_str());
	hFind = FindFirstFile(tzPath, &fdFind);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		m_uMax = m_uDefaultMenuID;
		do
		{
			// 获取语言标识，判断是否为有效
			_tcscpy(_tcsrchr(tzPath, _T('\\')) + 1, fdFind.cFileName);
			liTemp = GetPrivateProfileInt(LIN_Language, LIN_Language, 0, tzPath);
			if (liTemp)
			{
				// 第一次添加，插入分隔符；大于 50 条，跳出
				if (m_uMax == m_uDefaultMenuID)
				{
					AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
				}
				else if (m_uMax >= m_uDefaultMenuID + 50)
				{
					break;
				}

				// 添加菜单项
				m_uMax++;
				fdFind.cFileName[_tcslen(fdFind.cFileName) - m_strLangFileExt.size()] = 0;
				AppendMenu(hMenu, MF_BYCOMMAND, m_uMax, fdFind.cFileName);
				if (liTemp == liLang)
				{
					// 记录指定语言
					m_uLang = m_uMax;
				}
			}
		}
		while (FindNextFile(hFind, &fdFind));
		FindClose(hFind);
	}

	// 选择菜单项
	CheckMenuRadioItem(hMenu, m_uDefaultMenuID, m_uMax, m_uLang, MF_BYCOMMAND);

	return m_uLang;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置语言
VOID CLanguage::Set(HMENU hMenu, UINT uLang)
{
	HDC hDC;
	LANGID liLang;
	LOGFONT lfFont;
	TCHAR tzName[MAX_PATH];

	// 如果是初始化中设置语言
	if (hMenu == NULL)
	{
		liLang = uLang;
	}
	else
	{
		if((uLang <= m_uDefaultMenuID) || (uLang > m_uMax))
		{
			// 切换到默认语言
			liLang = 0;
			m_tzFileName[0] = 0;
			m_uLang = m_uDefaultMenuID;
		}
		else
		{
			// 切换到其它语言
			m_uLang = uLang;
			GetModuleFileName(NULL, m_tzFileName, MAX_PATH);
			GetMenuString(hMenu, uLang, tzName, MAX_PATH, MF_BYCOMMAND);
			_stprintf(_tcsrchr(m_tzFileName, _T('\\')), _T("\\%s\\%s%s"), m_strLangFilePath.c_str(), tzName, m_strLangFileExt.c_str());
			liLang = GetPrivateProfileInt(LIN_Language, LIN_Language, 0, m_tzFileName);
		}

		// 选择菜单项
		CheckMenuRadioItem(hMenu, m_uDefaultMenuID, m_uMax, m_uLang, MF_BYCOMMAND);
	}

	// 下列配置文件名为临时代码，根据需要更改
	TCHAR tzPath[MAX_PATH];
	GetModuleFileName(NULL, tzPath, MAX_PATH);
	_stprintf(_tcsrchr(tzPath, _T('\\')) + 1, _T("%s\\Config.ini"), m_strLangFilePath.c_str());

	// 保存语言标识到配置文件中
	_stprintf(tzName, _T("%d"), liLang);
	liLang = WritePrivateProfileString(_T("Main"), LIN_Language, tzName, tzPath);
	//CIni::SetInt(INI_Language, liLang);

	// 创建字体
	Destroy();
	ZeroMemory(&lfFont, sizeof(LOGFONT));
	if (GetPrivateProfileString(LIN_Language, LIN_FontName, NULL, lfFont.lfFaceName, LF_FACESIZE, m_tzFileName))
	{
		lfFont.lfCharSet = DEFAULT_CHARSET;
		lfFont.lfHeight = GetPrivateProfileInt(LIN_Language, LIN_FontSize, 0, m_tzFileName);
		if (lfFont.lfHeight)
		{
			hDC = CreateIC(_T("DISPLAY"), NULL, NULL, NULL);
			lfFont.lfHeight = -MulDiv(lfFont.lfHeight, GetDeviceCaps(hDC, LOGPIXELSY), 72);
			DeleteDC(hDC);
		}
		m_hFont = CreateFontIndirect(&lfFont);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 从菜单中获取语言文件名
tstring CLanguage::GetDescription(HMENU hMenu, UINT uLang)
{
	TCHAR tzName[MAX_PATH];
	TCHAR l_tcText[1024];
	memset(l_tcText, 0, sizeof(l_tcText));
	
	GetModuleFileName(NULL, l_tcText, MAX_PATH);
	GetMenuString(hMenu, uLang, tzName, MAX_PATH, MF_BYCOMMAND);
	_stprintf(_tcsrchr(l_tcText, _T('\\')), _T("\\%s\\%s%s"), m_strLangFilePath.c_str(), tzName, m_strLangFileExt.c_str());
	if (GetPrivateProfileString(LIN_Language, LIN_Description, NULL, l_tcText, sizeof(l_tcText), l_tcText) == 0)
	{
		TranslateString(m_uFirstLangMenuID);
	}

	return tstring(l_tcText);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 获取常规字符串
tstring CLanguage::TranslateText(PCTSTR ptzName, PCTSTR ptzDefault)
{
	TCHAR l_tcText[1024];
	memset(l_tcText, 0, sizeof(l_tcText));
#ifdef _MAKELANG
	WritePrivateProfileString(LIN_Text, ptzName, ptzDefault, m_tzFileName);
	return ptzDefault;
#else // _MAKELANG
	if ((m_tzFileName[0] == 0) ||
		(GetPrivateProfileString(LIN_Text, ptzName, NULL, l_tcText, sizeof(l_tcText), m_tzFileName) == 0))
	{
		return (PTSTR) ptzDefault;
	}
	return tstring(l_tcText);
#endif // _MAKELANG
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 获取常规字符串，并替换特殊字符
tstring CLanguage::TranslateTextEx(PCTSTR ptzName, PCTSTR ptzDefault)
{
	TCHAR l_tcText[1024];
	memset(l_tcText, 0, sizeof(l_tcText));
#ifdef _MAKELANG
	// 判断是否有两个空字符
	BOOL bDoubleNull = FALSE;
	CopyMemory(l_tcText, ptzDefault, sizeof(l_tcText));
	for (UINT i = 0; i < _LengthOf(l_tcText); i++)
	{
		if ((l_tcText[i] == 0) && (l_tcText[i + 1] == 0))
		{
			bDoubleNull = TRUE;
			break;
		}
	}

	for (PTSTR p = l_tcText; ; p++)
	{
		if (*p == '\n')
		{
			*p = '~';
		}
		else if (*p == 0)
		{
			if (bDoubleNull)
			{
				*p = '`';
				if (*(p + 1) == 0)
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	WritePrivateProfileString(LIN_Text, ptzName, l_tcText, m_tzFileName);
	return (PTSTR) ptzDefault;
#else // _MAKELANG
	if ((m_tzFileName[0] == 0) ||
		(GetPrivateProfileString(LIN_Text, ptzName, NULL, l_tcText, sizeof(l_tcText), m_tzFileName) == 0))
	{
		return (PTSTR) ptzDefault;
	}
	for (PTSTR p = l_tcText; *p; p++)
	{
		if (*p == '~')
		{
			*p = '\n';
		}
		else if (*p == '`')
		{
			*p = 0;
		}
	}
	return tstring(l_tcText);
#endif // _MAKELANG
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 获取资源字符串
tstring CLanguage::TranslateString(UINT uResID)
{
	TCHAR l_tcText[1024];
	memset(l_tcText, 0, sizeof(l_tcText));
	TCHAR tzName[32];
	tstring l_strRet = l_tcText;
	int l_iFind;
	
	_stprintf(tzName, _T("%u"), uResID);

#ifdef _MAKELANG
	LoadString(m_hResInst, uResID, l_tcText, sizeof(l_tcText));
	l_strRet = l_tcText;

	do
	{
		l_iFind = l_strRet.find(_T("\n"));
		if (l_iFind != string::npos)
		{
			l_strRet.replace(l_iFind, 1, _T("\\n"), 2);
		}
		else
		{
			break;
		}
	}while (l_iFind != string::npos);
	
	if (!l_strRet.empty())
	{
		WritePrivateProfileString(LIN_String, tzName, l_strRet.c_str(), m_tzFileName);
	}

#else // _MAKELANG
	if ((m_tzFileName[0] == 0) ||
		(GetPrivateProfileString(LIN_String, tzName, NULL, l_tcText, sizeof(l_tcText), m_tzFileName) == 0))
	{
		if (LoadString(m_hResInst, uResID, l_tcText, sizeof(l_tcText)) == 0)
		{
			return _T("");
		}
	}
	l_strRet = l_tcText;
	do
	{
		l_iFind = l_strRet.find(_T("\\n"));
		if (l_iFind != string::npos)
		{
			l_strRet.replace(l_iFind, 2, _T("\n"), 1);
		}
		else
		{
			break;
		}
	}while (l_iFind != string::npos);
#endif // _MAKELANG

	return 	l_strRet;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 更新菜单
VOID CLanguage::TranslateMenu(HMENU hMenu, PCTSTR ptzResName)
{
	TCHAR tzSection[32];

	if (m_tzFileName[0])
	{
		// 获取节名
		if (IS_INTRESOURCE(ptzResName))
		{
			_stprintf(tzSection, _T("%u"), ptzResName);
		}
		else
		{
			_tcscpy(tzSection, ptzResName);
		}

		// 从语言文件中更新菜单
		UpdateMenuFromLanguage(hMenu, tzSection);
	}
	else
	{
		// 从资源中更新菜单
		UpdateMenuFromResource(hMenu, ptzResName);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 更新对话框
VOID CLanguage::TranslateDialog(HWND hWnd, PCTSTR ptzResName)
{
	TCHAR tzSection[32];

	if (m_tzFileName[0])
	{
		// 获取节名
		if (IS_INTRESOURCE(ptzResName))
		{
			_stprintf(tzSection, _T("%u"), ptzResName);
		}
		else
		{
			_tcscpy(tzSection, ptzResName);
		}

		// 修改对话框字符串
		UpdateDialogFromLanguage(hWnd, tzSection);

#ifndef _TRANSRECUR
		// 枚举并修改子窗口字符串
		EnumChildWindows(hWnd, (WNDENUMPROC) UpdateDialogFromLanguage, (LPARAM) tzSection);
#endif // _TRANSRECUR
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设置菜单字符串
BOOL CLanguage::SetMenuString(HMENU hMenu, UINT uItemID, PCTSTR ptzString, BOOL bByPosition)
{
	MENUITEMINFO miiItem;

	miiItem.cbSize = sizeof(MENUITEMINFO);
#if (_WINVER >= 0x0410)
	miiItem.fMask = MIIM_STRING;
    miiItem.dwTypeData = (PTSTR) ptzString;
#else
	miiItem.fMask = MIIM_TYPE;
    if(_tcslen(ptzString) != 0)
    {
        miiItem.fType = MFT_STRING;
    }
    else
    {
        miiItem.fType = MFT_SEPARATOR;
    }
	miiItem.cch = 0;
	miiItem.dwTypeData = (PTSTR) ptzString;
#endif

	return SetMenuItemInfo(hMenu, uItemID, bByPosition, &miiItem);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 从语言文件中更新菜单
VOID CLanguage::UpdateMenuFromLanguage(HMENU hMenu, PCTSTR ptzSection, PCTSTR ptzPath)
{
	INT i;
	INT iNum;
	TCHAR tzName[256];
	TCHAR tzText[1024];
	MENUITEMINFO miiItem;

	// 初始化变量，获取菜单项数量
	miiItem.cbSize = sizeof(MENUITEMINFO);
	miiItem.fMask = MIIM_SUBMENU | MIIM_ID;
	iNum = GetMenuItemCount(hMenu);
	for (i = 0; i < iNum; i++)
	{
		// 获取弹出菜单句柄和标识
		GetMenuItemInfo(hMenu, i, TRUE, &miiItem);
		if (miiItem.wID)
		{
			// 获取菜单标识文本
			if (miiItem.hSubMenu)
			{
				/*_Assert(ptzPath);
				_Assert(_tcslen(ptzPath) < sizeof(tzName) - 16);*/
				_stprintf(tzName, _T("%s|%u"), ptzPath, i);
			}
			else
			{
				_stprintf(tzName, _T("%u"), miiItem.wID);
			}

	#ifdef _MAKELANG
			// 生成语言文件，递归修改菜单字符串
			if ((miiItem.wID <= m_uDefaultMenuID) || (miiItem.wID >= m_uDefaultMenuID + 50)/* &&
				(miiItem.wID <= IDM_File_Recent) || (miiItem.wID >= IDM_File_Recent + 50)*/)
			{
				GetMenuString(hMenu, i, tzText, _NumberOf(tzText), MF_BYPOSITION);
				WritePrivateProfileString(ptzSection, tzName, tzText, m_tzFileName);
			}
	#else // _MAKELANG
			// 设置菜单字符串
			if (GetPrivateProfileString(ptzSection, tzName, NULL, tzText, sizeof(tzText), m_tzFileName))
			{
				SetMenuString(hMenu, i, tzText, TRUE);
			}
	#endif // _MAKELANG

			// 递归修改菜单字符串
			if (miiItem.hSubMenu)
			{
				UpdateMenuFromLanguage(miiItem.hSubMenu, ptzSection, tzName);
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 从资源中更新菜单
VOID CLanguage::UpdateMenuFromResource(HMENU hMenu, PCTSTR ptzResName)
{
	PBYTE p;
	PBYTE pbEnd;
	BOOL bMenuEx;
	WORD wOptions;
	DWORD dwMenuID;
	HRSRC hResource;
	HGLOBAL hGlobal;
	TCHAR tzText[1024];

	// 菜单层次堆栈，用于更新弹出菜单字符串
	INT i = 0;					// 层次
	INT iPos[32] = {0};			// 位置
	BOOL bHilite[32] = {FALSE};	// 回退
	HMENU hMenus[32] = {hMenu};	// 句柄

	// 载入资源
	hResource = FindResource(m_hResInst, ptzResName, RT_MENU);
	//_Assert(hResource);
	hGlobal = LoadResource(m_hResInst, hResource);
	//_Assert(hGlobal);

	// 获取资源的起始地址、终止地址和版本
	p = (PBYTE) LockResource(hGlobal);
	pbEnd = p + SizeofResource(m_hResInst, hResource);
	bMenuEx = ((PMENUITEMTEMPLATEHEADER) p)->versionNumber;

	// 转到菜单项数据
	p += ((PMENUITEMTEMPLATEHEADER) p)->offset + sizeof(MENUITEMTEMPLATEHEADER);
	if (bMenuEx)
	{
		p += sizeof(DWORD);
	}

	// 更新菜单
	while (p < pbEnd)
	{
		// 获取菜单项标识、参数
		if (bMenuEx)
		{
			p += 3 * sizeof(DWORD);
			dwMenuID =  *((PDWORD) p);
			p += sizeof(DWORD) + sizeof(WORD);
		}
		else
		{
			wOptions = *((PWORD) p);
			p += sizeof(WORD);
			if ((wOptions & MF_POPUP) == FALSE)
			{
				dwMenuID = *((PWORD) p);
				p += sizeof(WORD);
			}
		}

		// 获取菜单项文本，转到下一个菜单项
		for (_WStrToStr(tzText, (PWSTR) p); *((PWSTR) p); p += sizeof(WCHAR));
		p += sizeof(WCHAR);

		if (bMenuEx)
		{
			// 根据命令标识设置菜单文本
			SetMenuString(hMenu, dwMenuID, tzText);
		}
		else
		{
			// 如果是弹出菜单项
			//_Assert(i < _NumberOf(iPos));
			iPos[i]++;
			if (wOptions & MF_POPUP)
			{
				// 根据位置设置菜单文本
                TCHAR chText[256];
                memset(chText, 0, 256);
                MENUITEMINFO miiItem;
                miiItem.cbSize = sizeof(MENUITEMINFO);
                #if (_WINVER >= 0x0410)
                    miiItem.fMask = MIIM_STRING;
                    miiItem.dwTypeData = (PTSTR) chText;
                #else
                    miiItem.fMask = MIIM_TYPE;
                    miiItem.fType = MFT_STRING;
                    miiItem.cch = 256;
                    miiItem.dwTypeData = (PTSTR) chText;
                #endif
                GetMenuItemInfo(hMenus[i], iPos[i] - 1, TRUE, &miiItem);
               if(chText[0] == 0)
               {
                   iPos[i]++;
               }
				SetMenuString(hMenus[i], iPos[i] - 1, tzText, TRUE);

				// 获取下一级菜单，并把相关数据压入堆栈
				bHilite[i] = wOptions & MF_HILITE;
				hMenus[i + 1] = GetSubMenu(hMenus[i], iPos[i] - 1);
				i++;
				iPos[i] = 0;
				//_Assert(hMenus[i]);
			}
			else
			{
				// 根据命令标识设置菜单文本
				SetMenuString(hMenu, dwMenuID, tzText);

				if (wOptions & MF_HILITE)
				{
					// 弹出堆栈，如果已经完成则退出
					for (i--; (i >= 0) && bHilite[i]; i--);
					if (i < 0)
					{
						break;
					}
				}
			}
		}
	}

	FreeResource(hGlobal);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 从语言文件中更新对话框
BOOL CALLBACK CLanguage::UpdateDialogFromLanguage(HWND hWnd, PCTSTR ptzSection)
{
	TCHAR tzText[1024];
	TCHAR tzName[MAX_PATH];
	TCHAR tzWndType[256];

	BOOL l_bUpdateCtrl = TRUE;
	// 因为有很多的类型，包括用户自注册的，这里将所有的编辑框排除
	memset(tzWndType, 0, sizeof(tzWndType));
	GetClassName(hWnd, tzWndType, 256);
	OutputDebugString(tzWndType);
	OutputDebugString(_T("\n"));

	if (_tcsicmp(tzWndType, _T("Edit")) == 0)
	{
		l_bUpdateCtrl = FALSE;
	}
	else if (_tcsicmp(tzWndType, _T("ComboBox")) == 0)
	{
		l_bUpdateCtrl = FALSE;
	}
	else if (_tcsicmp(tzWndType, _T("ListBox")) == 0)
	{
		l_bUpdateCtrl = FALSE;
	}

	if (l_bUpdateCtrl)
	{
		// 获取窗口标识字符串
		_stprintf(tzName, _T("%u"), GetDlgCtrlID(hWnd));

		// 设置窗口标题
	#ifdef _MAKELANG
		GetWindowText(hWnd, tzText, _NumberOf(tzText));
		if (tzText[0] && ((tzText[0] < '0') || (tzText[0] > '9')))
		{
			WritePrivateProfileString(ptzSection, tzName, tzText, m_tzFileName);
		}
	#else // _MAKELANG
		if (GetPrivateProfileString(ptzSection, tzName, NULL, tzText, sizeof(tzText), m_tzFileName))
		{
			SetWindowText(hWnd, tzText);
		}
	#endif // _MAKELANG

	#ifdef _TRANSRECUR
		// 枚举并修改子窗口字符串
		EnumChildWindows(hWnd, (WNDENUMPROC) UpdateDialogFromLanguage, (LPARAM) ptzSection);
	#endif // _TRANSRECUR
	}

	if (m_hFont)
	{
		SendMessage(hWnd, WM_SETFONT, (WPARAM) m_hFont, FALSE);
	}

	return TRUE;
}

tstring CLanguage::TransateMenuItem(UINT uMenuID, UINT uResID, PCTSTR ptzPath)
{
	TCHAR tzSection[32];
	TCHAR tzName[256];
	TCHAR tzText[1024];
	memset(tzText, 0, sizeof(tzText));

	tstring l_strRet;
	if (m_tzFileName[0])
	{
		_stprintf(tzSection, _T("%u"), uMenuID);
		if (uResID == 0 || uResID == -1)
		{
			_stprintf(tzName, _T("%s"), ptzPath);
			
		}
		else
		{
			_stprintf(tzName, _T("%u"), uResID);
		}
		GetPrivateProfileString(tzSection, tzName, NULL, tzText, sizeof(tzText), m_tzFileName);
	}

	l_strRet = tzText;
	return l_strRet;
}

tstring CLanguage::TransateDlgItem(UINT uDlgResID, UINT uDlgCtlID)
{
	TCHAR tzSection[32];
	TCHAR tzName[256];
	TCHAR tzText[1024];
	memset(tzText, 0, sizeof(tzText));
	
	tstring l_strRet;
	if (m_tzFileName[0])
	{
		_stprintf(tzSection, _T("%u"), uDlgResID);
		_stprintf(tzName, _T("%u"), uDlgCtlID);
		GetPrivateProfileString(tzSection, tzName, NULL, tzText, sizeof(tzText), m_tzFileName);
	}
	
	l_strRet = tzText;
	return l_strRet;
}
