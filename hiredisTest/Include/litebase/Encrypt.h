#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_
#include <string>

namespace litebase
{

	namespace utility
	{
		class CEncrypt
		{
		public:
			/*
			// @desc:	�����ݽ���AES EBCģʽ����
			// @param	src			: ����������
			// 			encKey		: ����key
			//			encKeyLen	: ����key��bytes��,only support 16\24\32
			//			resBuf		: ��ż��ܽ����buff
			//			resLen		: resBuf�ĳ�ʼ��С
			//		
			//	@return	���ܽ����ʵ�ʳ���: �ɹ� >0; ʧ�� =0
			*/
			static int aesECBEnc( const std::string& src, unsigned char *encKey, int encKeyLen, unsigned char* resBuf, int resLen );
			
			/*
			// @desc�����ݽ���AES EBCģʽ����
			// @param	src			: ����������
			//			srcLen		: ���������ݵĳ���
			//			encKey		: ����key
			//			encKeyLen	: ����key��bytes��,only support 16\24\32
			//		
			//	@return	���ܽ��: �ɹ���""; ʧ��Ϊ""
			*/
			static std::string aesECBDec( unsigned char* src, int srcLen, unsigned char *encKey, int encKeyLen );

		};
	}
}

#endif
