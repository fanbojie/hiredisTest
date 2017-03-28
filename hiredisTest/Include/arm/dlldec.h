#ifndef _DLLDEC_H_
#define _DLLDEC_H_

// 对于不依赖其他库的库来说，可简单地使用_DLL宏来表示编译的是动态库
// 注：若B动态库依赖A动态库，则B库在编译时不能使用_DLL宏，而应使用自定义的宏判断。
#ifdef _DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

// 统一使用_USE_DLL宏表示需要动态库的导入接口
#ifdef _USE_DLL
#define DLL_IMPORT __declspec(dllimport)
#else
#define DLL_IMPORT
#endif

#define DLL_DECLARE		DLL_EXPORT DLL_IMPORT

#endif
