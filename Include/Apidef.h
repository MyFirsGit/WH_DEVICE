#ifdef _LIB_EXPORTS
#define AFC_API_DLL_IMP __declspec(dllexport)
#else
#define AFC_API_DLL_IMP __declspec(dllimport)
#endif

