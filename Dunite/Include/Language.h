

#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

//#define _MAKELANG

#ifndef PCTSTR
#define PCTSTR LPCTSTR
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �궨��
#define _Lang(n, a)				CLanguage::TranslateText(TEXT(#n), TEXT(a)).c_str()
#define _TLang(n, t)			CLanguage::TranslateText(TEXT(#n), t).c_str()
#define _LangEx(n, a)			CLanguage::TranslateTextEx(TEXT(#n), TEXT(a)).c_str()	// �����ı����ַ�����
#define _TLangEx(n, t)			CLanguage::TranslateTextEx(TEXT(#n), t).c_str()
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLanguage ��
class CLanguage
{
public:
	static UINT m_uLang;					// ���Բ˵���
	static TCHAR m_tzFileName[MAX_PATH];	// �����ļ�����
	static HMODULE m_hResInst;

private:
	static UINT m_uMax;						// ��������
	static HFONT m_hFont;					// �Ի�������
	static UINT m_uDefaultMenuID;
	static UINT m_uFirstLangMenuID;
	static tstring m_strLangFilePath;		// �����ļ����ڵ����·����defaultΪLanguage
	static tstring m_strLangFileExt;		// �����ļ��ĺ�׺����defaultΪini

public:

	// ��ʼ������
	static LANGID Initialize(UINT uDefaultMenuID, UINT uFirstLangID, LPCTSTR pstrLangFilePath = NULL, LPCTSTR pstrLangFileExt = NULL);

	// �г�����
	static UINT List(HMENU hMenu);

	// ��������
	static VOID Set(HMENU hMenu, UINT uLang);

	// ��ȡ��������
	static tstring GetDescription(HMENU hMenu, UINT uLang);

	// ��ȡ�����ַ���
	static tstring TranslateText(PCTSTR ptzName, PCTSTR ptzDefault = NULL);

	// ��ȡ�����ַ��������滻�����ַ�
	static tstring TranslateTextEx(PCTSTR ptzName, PCTSTR ptzDefault = NULL);

	// ��ȡ��Դ�ַ���
	static tstring TranslateString(UINT uResID);

	// ���²˵�
	static void TranslateMenu(HMENU hMenu, PCTSTR ptzResName);

	// ���¶Ի���
	static void TranslateDialog(HWND hWnd, PCTSTR ptzResName);

	static tstring TransateMenuItem(UINT uMenuID, UINT uResID, PCTSTR ptzPath = TEXT(""));
	static tstring TransateDlgItem(UINT uDlgResID, UINT uDlgCtlID);

public:
	// ����
	inline static void Destroy()
	{
		if (m_hFont)
		{
			DeleteObject(m_hFont);
			m_hFont = NULL;
		}
	}

private:
	// ���ò˵��ַ���
	static BOOL SetMenuString(HMENU hMenu, UINT uItemID, PCTSTR ptzString, BOOL bByPosition = FALSE);

	// �������ļ��и��²˵�
	static void UpdateMenuFromLanguage(HMENU hMenu, PCTSTR ptzSection, PCTSTR ptzPath = TEXT(""));

	// ����Դ�и��²˵�
	static void UpdateMenuFromResource(HMENU hMenu, PCTSTR ptzResName);

	// �������ļ��и��¶Ի���
	static BOOL CALLBACK UpdateDialogFromLanguage(HWND hWnd, PCTSTR ptzSection);
};

#endif