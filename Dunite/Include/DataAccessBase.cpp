/********************************************************************
�������ڣ�	2003/07/11
��Ʒ���ƣ�	���ݷ��ʻ���
ģ�����ƣ�	dataaccessbase
���ߣ�		������

����˵����	��������Դ���ʵĻ���

===========================��ģ����ʷ�޸ļ�¼==========================
============================��ʷ�޸ļ�¼��=============================
*********************************************************************/

#include "DataAccessBase.h"

//////////////////////////////////////////////////////////////////////
// 
ODataAccessBase::ODataAccessBase()
{
	m_hLockMutex = NULL;
}

ODataAccessBase::~ODataAccessBase()
{
	if (m_hLockMutex)
	{
		SetEvent(m_hLockMutex);
		CloseHandle(m_hLockMutex);
		m_hLockMutex = NULL;
	}
}

HRESULT ODataAccessBase::hrLock(long p_lTimeout, short *p_psRet)
{
	*p_psRet = CFG_FAIL;
	if (m_hLockMutex)
	{
		DWORD l_dwWaitResult = WaitForSingleObject(m_hLockMutex, p_lTimeout);
		if (WAIT_OBJECT_0 == l_dwWaitResult)
		{
			*p_psRet = CFG_SUCCESS;
			return S_OK;
		}
	}
	return S_FALSE;
}

HRESULT ODataAccessBase::hrUnlock()
{
	if (m_hLockMutex)
	{
		if (ReleaseMutex(m_hLockMutex))
		{
			return S_OK;
		}
	}
	return S_FALSE;
}


