// stlunicode.h

// STL中的类对UNICODE宏的支持

#ifndef _STLUNICODE_H_
#define _STLUNICODE_H_

#ifdef _UNICODE

	typedef std::wstring tstring;

	typedef std::wistream tistream;

	typedef std::wostream tostream;
	
	typedef std::wifstream tifstream;

	typedef std::wofstream tofstream;

	typedef std::wostringstream tostringstream;
	
	typedef std::wistringstream tistringstream;
#else

	typedef std::string tstring;

	typedef std::istream tistream;

	typedef std::ostream tostream;

	typedef std::ifstream tifstream;
	
	typedef std::ofstream tofstream;

	typedef std::ostringstream tostringstream;
	
	typedef std::istringstream tistringstream;
#endif

#endif	// #ifndef _STLUNICODE_H_

