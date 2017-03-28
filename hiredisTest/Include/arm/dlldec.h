#ifndef _DLLDEC_H_
#define _DLLDEC_H_

// ���ڲ�����������Ŀ���˵���ɼ򵥵�ʹ��_DLL������ʾ������Ƕ�̬��
// ע����B��̬������A��̬�⣬��B���ڱ���ʱ����ʹ��_DLL�꣬��Ӧʹ���Զ���ĺ��жϡ�
#ifdef _DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

// ͳһʹ��_USE_DLL���ʾ��Ҫ��̬��ĵ���ӿ�
#ifdef _USE_DLL
#define DLL_IMPORT __declspec(dllimport)
#else
#define DLL_IMPORT
#endif

#define DLL_DECLARE		DLL_EXPORT DLL_IMPORT

#endif
