#pragma once

class UC_LOG
{
public:
	UC_LOG();
	virtual ~UC_LOG();

    void Initialize(const char* tracePath);
	void OpenLog();
	void printf(const char *fmt, ... );
	void print(const char *text);
	void printhex(const BYTE* btContent,const UINT uilen);
	void CloseLog();
    void ClearLog();
private:	
    void MakeFileName(char* fileName,const UINT uisize);
    void MakeFullName(char* strFullName,const UINT uisize);
  
private:
	HANDLE						m_hFile;		// ��־�ļ����
	CRITICAL_SECTION	m_hLock;		// lock for thread-safe access
	char							m_strFileName[MAX_PATH];   // ��־�ļ���
    char							m_strTracePath[MAX_PATH];  // ��־���Ŀ¼
    DWORD						m_dwLineCount;
};
