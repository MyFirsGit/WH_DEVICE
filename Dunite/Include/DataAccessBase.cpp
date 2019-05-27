/********************************************************************
创建日期：	2003/07/11
产品名称：	数据访问基类
模块名称：	dataaccessbase
作者：		刘道余

功能说明：	配置数据源访问的基类

===========================本模块历史修改记录==========================
============================历史修改记录完=============================
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


