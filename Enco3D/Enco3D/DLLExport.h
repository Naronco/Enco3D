#ifndef DLL_EXPORT

#ifdef DLL
#ifdef WIN32
#ifdef ENCO3D_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif
#else
#define DLL_EXPORT
#endif
#endif