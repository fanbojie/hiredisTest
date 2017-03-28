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
			// @desc:	对数据进行AES EBC模式加密
			// @param	src			: 待加密数据
			// 			encKey		: 加密key
			//			encKeyLen	: 加密key的bytes数,only support 16\24\32
			//			resBuf		: 存放加密结果的buff
			//			resLen		: resBuf的初始大小
			//		
			//	@return	加密结果的实际长度: 成功 >0; 失败 =0
			*/
			static int aesECBEnc( const std::string& src, unsigned char *encKey, int encKeyLen, unsigned char* resBuf, int resLen );
			
			/*
			// @desc对数据进行AES EBC模式解密
			// @param	src			: 待解密数据
			//			srcLen		: 待解密数据的长度
			//			encKey		: 加密key
			//			encKeyLen	: 加密key的bytes数,only support 16\24\32
			//		
			//	@return	解密结果: 成功非""; 失败为""
			*/
			static std::string aesECBDec( unsigned char* src, int srcLen, unsigned char *encKey, int encKeyLen );

		};
	}
}

#endif
