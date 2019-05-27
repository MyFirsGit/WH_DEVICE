

#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

//#define _MAKELANG

#ifndef PCTSTR
#define PCTSTR LPCTSTR
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 宏定义
#define _Lang(n, a)				CLanguage::TranslateText(TEXT(#n), TEXT(a)).c_str()
#define _TLang(n, t)			CLanguage::TranslateText(TEXT(#n), t).c_str()
#define _LangEx(n, a)			CLanguage::TranslateTextEx(TEXT(#n), TEXT(a)).c_str()	// 多行文本或字符串组
#define _TLangEx(n, t)			CLanguage::TranslateTextEx(TEXT(#n), t).c_str()
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLanguage 类
class CLanguage
{
public:
	static UINT m_uLang;					// 语言菜单号
	static TCHAR m_tzFileName[MAX_PATH];	// 语言文件名称
	static HMODULE m_hResInst;

private:
	static UINT m_uMax;						// 语言最大号
	static HFONT m_hFont;					// 对话框字体
	static UINT m_uDefaultMenuID;
	static UINT m_uFirstLangMenuID;
	static tstring m_strLangFilePath;		// 语言文件所在的相对路经，default为Language
	static tstring m_strLangFileExt;		// 语言文件的后缀名，default为ini

public:

	// 初始化语言
	static LANGID Initialize(UINT uDefaultMenuID, UINT uFirstLangID, LPCTSTR pstrLangFilePath = NULL, LPCTSTR pstrLangFileExt = NULL);

	// 列出语言
	static UINT List(HMENU hMenu);

	// 设置语言
	static VOID Set(HMENU hMenu, UINT uLang);

	// 获取语言描述
	static tstring GetDescription(HMENU hMenu, UINT uLang);

	// 获取常规字符串
	static tstring TranslateText(PCTSTR ptzName, PCTSTR ptzDefault = NULL);

	// 获取常规字符串，并替换特殊字符
	static tstring TranslateTextEx(PCTSTR ptzName, PCTSTR ptzDefault = NULL);

	// 获取资源字符串
	static tstring TranslateString(UINT uResID);

	// 更新菜单
	static void TranslateMenu(HMENU hMenu, PCTSTR ptzResName);

	// 更新对话框
	static void TranslateDialog(HWND hWnd, PCTSTR ptzResName);

	static tstring TransateMenuItem(UINT uMenuID, UINT uResID, PCTSTR ptzPath = TEXT(""));
	static tstring TransateDlgItem(UINT uDlgResID, UINT uDlgCtlID);

public:
	// 销毁
	inline static void Destroy()
	{
		if (m_hFont)
		{
			DeleteObject(m_hFont);
			m_hFont = NULL;
		}
	}

private:
	// 设置菜单字符串
	static BOOL SetMenuString(HMENU hMenu, UINT uItemID, PCTSTR ptzString, BOOL bByPosition = FALSE);

	// 从语言文件中更新菜单
	static void UpdateMenuFromLanguage(HMENU hMenu, PCTSTR ptzSection, PCTSTR ptzPath = TEXT(""));

	// 从资源中更新菜单
	static void UpdateMenuFromResource(HMENU hMenu, PCTSTR ptzResName);

	// 从语言文件中更新对话框
	static BOOL CALLBACK UpdateDialogFromLanguage(HWND hWnd, PCTSTR ptzSection);
};

#endif