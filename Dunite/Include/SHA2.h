/***************************************************************************
* Copyright (c) 2000-2004, Future Systems, Inc. / Seoul, Republic of Korea *
* All Rights Reserved.                                                     *
*                                                                          *
* This document contains proprietary and confidential information.  No     *
* parts of this document or the computer program it embodies may be in     *
* any way copied, duplicated, reproduced, translated into a different      *
* programming language, or distributed to any person, company, or          *
* corporation without the prior written consent of Future Systems, Inc.    *
*                              Hyo Sun Hwang                               *
*                372-2 YangJae B/D 6th Floor, Seoul, Korea                 *
*                           +82-2-578-0581 (552)                           *
***************************************************************************/

/*--------------------- [ Version/Command in detais] ---------------------*\
Description : sha2.h
			(head file) head file for sha2.c : Hash Algorithm SHA2

C0000 : Created by Hyo Sun Hwang (hyosun@future.co.kr) 2000/12/31

C0001 : Modified by Hyo Sun Hwang (hyosun@future.co.kr) 2000/00/00

\*------------------------------------------------------------------------*/

#ifndef _SHA2_H
#define _SHA2_H

#ifdef __cplusplus
extern "C" {
#endif

/*************** Header files *********************************************/
#include <Oaidl.h>

#include <stdlib.h>
#include <memory.h>
#include <string.h>
	
/*************** Assertions ***********************************************/
////////	Define the Endianness	////////
#undef BIG_ENDIAN
#undef LITTLE_ENDIAN

#if defined(USER_BIG_ENDIAN)
	#define BIG_ENDIAN
#elif defined(USER_LITTLE_ENDIAN)
	#define LITTLE_ENDIAN
#else
	#if 0
		#define BIG_ENDIAN		//	Big-Endian machine with pointer casting
	#elif defined(_MSC_VER)
		#define LITTLE_ENDIAN	//	Little-Endian machine with pointer casting
	#else
		#error
	#endif
#endif

/*************** Macros ***************************************************/
////////	rotate by using shift operations	////////
#if defined(_MSC_VER)
	#define ROTL_DWORD(x, n) _lrotl((x), (n))
	#define ROTR_DWORD(x, n) _lrotr((x), (n))
#else
	#define ROTL_DWORD(x, n) ( (DWORD)((x) << (n)) | (DWORD)((x) >> (32-(n))) )
	#define ROTR_DWORD(x, n) ( (DWORD)((x) >> (n)) | (DWORD)((x) << (32-(n))) )
#endif

////////	reverse the uint8_t order of DWORD(DWORD:4-bytes integer) and WORD.
#define ENDIAN_REVERSE_DWORD(dwS)	( (ROTL_DWORD((dwS),  8) & 0x00ff00ff)	\
									 | (ROTL_DWORD((dwS), 24) & 0xff00ff00) )

////////	move DWORD type to uint8_t type and uint8_t type to DWORD type
#if defined(BIG_ENDIAN)		////	Big-Endian machine
	#define BIG_B2D(B, D)		D = *(DWORD *)(B)
	#define BIG_D2B(D, B)		*(DWORD *)(B) = (DWORD)(D)
	#define LITTLE_B2D(B, D)	D = ENDIAN_REVERSE_DWORD(*(DWORD *)(B))
	#define LITTLE_D2B(D, B)	*(DWORD *)(B) = ENDIAN_REVERSE_DWORD(D)
#elif defined(LITTLE_ENDIAN)	////	Little-Endian machine
	#define BIG_B2D(B, D)		D = ENDIAN_REVERSE_DWORD(*(DWORD *)(B))
	#define BIG_D2B(D, B)		*(DWORD *)(B) = ENDIAN_REVERSE_DWORD(D)
	#define LITTLE_B2D(B, D)	D = *(DWORD *)(B)
	#define LITTLE_D2B(D, B)	*(DWORD *)(B) = (DWORD)(D)
#else
	#error ERROR : Invalid DataChangeType
#endif

/*************** Definitions / Macros  ************************************/
////	SHA256俊 包访等 惑荐甸
#define SHA256_DIGEST_BLOCKLEN	64		//	in bytes
#define SHA256_DIGEST_VALUELEN	32		//	in bytes
////	SHA384俊 包访等 惑荐甸
#define SHA384_DIGEST_BLOCKLEN	128		//	in bytes
#define SHA384_DIGEST_VALUELEN	48		//	in bytes
////	SHA512俊 包访等 惑荐甸
#define SHA512_DIGEST_BLOCKLEN	128		//	in bytes
#define SHA512_DIGEST_VALUELEN	64		//	in bytes

/*************** New Data Types *******************************************/
////////	Determine data types depand on the processor and compiler.
#define BOOL	int					//	1-bit data type
#define uint8_t	BYTE				//	unsigned 1-uint8_t data type
#define WORD	unsigned short int	//	unsigned 2-bytes data type
#define DWORD	unsigned int		//	unsigned 4-bytes data type
#if defined(_MSC_VER)
	#define QWORD	unsigned _int64		//	unsigned 8-bytes data type
#else
	#define QWORD	unsigned long long	//	unsigned 8-bytes data type
#endif
#define RET_VAL		DWORD			//	return values

////	SHA256..
typedef struct{
	DWORD		ChainVar[SHA256_DIGEST_VALUELEN/4];	//	Chaining Variable 历厘
	DWORD		Count[4];							//	
	uint8_t		Buffer[SHA256_DIGEST_BLOCKLEN];		//	Buffer for unfilled block
}tSHA256_CTX;

////	SHA384..
typedef struct{
	DWORD		ChainVar[64/4];						//	Chaining Variable 历厘
	DWORD		Count[4];							//	
	uint8_t		Buffer[SHA384_DIGEST_BLOCKLEN];		//	Buffer for unfilled block
} tSHA384_CTX;

////	SHA512..
typedef struct{
	DWORD		ChainVar[SHA512_DIGEST_VALUELEN/4];	//	Chaining Variable 历厘
	DWORD		Count[4];							//	
	uint8_t		Buffer[SHA512_DIGEST_BLOCKLEN];		//	Buffer for unfilled block
} tSHA512_CTX;

class OSHA2 
{
public:
	OSHA2();
	virtual ~OSHA2();
	void vSHA256_Init(tSHA256_CTX *);
	void vSHA384_Init(tSHA384_CTX *);
	void vSHA512_Init(tSHA512_CTX *);
	// 	功    能：初始化tSHA256/384/512_CTX结构类型的变量
	// 	输    入：p_ptContext	tSHA256/384/512_CTX结构类型的变量
	// 	输    出：p_ptContext	tSHA256/384/512_CTX结构类型的变量
	//	返 回 值：无
	//	作    者：王洪月
	//	创建日期：2004.3
	
	void vSHA256_Update(tSHA256_CTX *, const uint8_t *, unsigned int);
	void vSHA384_Update(tSHA384_CTX *, const uint8_t *, unsigned int);
	void vSHA512_Update(tSHA512_CTX *, const uint8_t *, unsigned int);
	// 	功    能：对指定长度（p_uiDataLen）的源文件（p_puiData）与tSHA256/384/512_CTX(p_ptContext)结构中的数据，
	//			  按SHA2算法进行计算，并将结果存储在tSHA256/384/512_CTX结构中
	// 	输    入：p_ptContext	源tSHA256/384/512_CTX结构类型的变量
	//			  p_puiData		源文件
	//			  p_uiDataLen	源文件长度
	// 	输    出：p_ptContext	计算后的tSHA256/384/512_CTX结构类型的变量
	//	返 回 值：无
	//	作    者：王洪月
	//	创建日期：2004.3
	
	void vSHA256_End(tSHA256_CTX *, uint8_t p_aucResult[SHA256_DIGEST_VALUELEN]);
	void vSHA384_End(tSHA384_CTX *, uint8_t p_aucResult[SHA384_DIGEST_VALUELEN]);
	void vSHA512_End(tSHA512_CTX *, uint8_t p_aucResult[SHA512_DIGEST_VALUELEN]);
	// 	功    能：对tSHA256/384/512_CTX结构中的数据进行处理，再以字符串的形式输出
	// 	输    入：p_ptContext	源tSHA256/384/512_CTX结构类型的变量
	// 	输    出：p_cResult		存储结果的字符数组（串）
	//	返 回 值：无
	//	作    者：王洪月
	//	创建日期：2004.3
};

#ifdef	__cplusplus
}
#endif /* __cplusplus */

/*************** END OF FILE **********************************************/
#endif	//	_SHA2_H
