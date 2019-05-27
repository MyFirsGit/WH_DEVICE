#pragma once;

#include <cstdio> 
#include <eh.h> 
#include <exception> 

std::string strGetExceptionCodeInfo(DWORD dwException);

///////////////////////////////////////////////////////////
class seh_exception_base : public std::exception 
{ 
	
public: 
	
	seh_exception_base (const PEXCEPTION_POINTERS pExp, std::string what) 
		
		: m_ExceptionRecord(*pExp->ExceptionRecord), 
		
		m_ContextRecord(*pExp->ContextRecord), 
		
		m_what(what){}; 
	
	~seh_exception_base() throw(){} ; 
	
	virtual const char* what() const throw() 
	{ 
		
		return m_what.c_str(); 
		
	} 
	
	virtual DWORD exception_code() const throw() 
		
	{ 
		
		return m_ExceptionRecord.ExceptionCode; 
		
	} 
	
	virtual const EXCEPTION_RECORD& get_exception_record() const throw() 
		
	{ 
		
		return m_ExceptionRecord; 
		
	} 
	
	virtual const CONTEXT& get_context() const throw() 
		
	{ 
		
		return m_ContextRecord; 
		
	} 
	
	// 初始化函数 
	
	static void initialize_seh_trans_to_ce() 
		
	{ 
		
		_set_se_translator( trans_func ); 
		
	} 
	
	// 系统异常出现时的回调函数 
	
	static void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp ); 
	
	tstring strGetFullDescript();
	
protected: 
	
	std::string m_what; 
	
	EXCEPTION_RECORD m_ExceptionRecord; 
	
	CONTEXT m_ContextRecord; 
	
}; 


//////////////////////////////////////////////////////////////////////////////// 

// 下面是系统异常被转换后的 C++ 类型的异常 

// 篇幅有限，因此只简单设计了对几种常见的系统异常的转换 

//////////////////////////////////////////////////////////////////////////////// 

class seh_exception_access_violation : public seh_exception_base 
{ 
	
public: 
	
	seh_exception_access_violation (const PEXCEPTION_POINTERS pExp, std::string what) 
		
		: seh_exception_base(pExp, what) {}; 
	
	~seh_exception_access_violation() throw(){}; 
	
}; 

//////////////////////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////////////////////////////////////// 

class seh_exception_divide_by_zero : public seh_exception_base 
{ 
	
public: 
	
	seh_exception_divide_by_zero (const PEXCEPTION_POINTERS pExp, std::string what) 
		
		: seh_exception_base(pExp, what) {}; 
	
	~seh_exception_divide_by_zero() throw(){}; 
	
}; 

//////////////////////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////////////////////////////////////// 

class seh_exception_invalid_handle : public seh_exception_base 
{ 
public: 
	
	seh_exception_invalid_handle (const PEXCEPTION_POINTERS pExp, std::string what) 
		
		: seh_exception_base(pExp, what) {}; 
	
	~seh_exception_invalid_handle() throw(){}; 
	
}; 

#ifdef CATCH_EXCEPTION

#define CONDITION_TRY try \
{\


#define CONDITION_CATCH(CLSNAME, FUNNAME) } \
	catch( seh_exception_base& e ) \
{\
	assert(false);\
	TCHAR l_acError[MAX_PATH];\
	tstring l_strError = e.strGetFullDescript();\
	_stprintf(l_acError, _T("%s; At: %s::%s\n"),l_strError.c_str(), CLSNAME, FUNNAME);\
	OutputDebugString(l_acError);\
}\
	catch (exception& e) \
{\
	USES_CONVERSION;\
	assert(false);\
	TCHAR l_acError[MAX_PATH];\
	const char* l_pcWhat = NULL;\
	_stprintf(l_acError, _T("Exception Reason: %s; At: %s::%s\n"), A2CT((l_pcWhat = e.what())==NULL?"":l_pcWhat), CLSNAME, FUNNAME);\
	OutputDebugString(l_acError);\
}\
	catch (...)\
{\
	assert(false);\
	TCHAR l_acError[MAX_PATH];\
	_stprintf(l_acError, _T("Exception At: %s::%s\n"), CLSNAME, FUNNAME);\
	OutputDebugString(l_acError);\
};

#else

#define CONDITION_TRY 

#define CONDITION_CATCH(CLSNAME, FUNNAME) 

#endif



