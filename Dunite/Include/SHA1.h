/*
*  sha1.h
*
*  Description:
*      This is the header file for code which implements the Secure
*      Hashing Algorithm 1 as defined in FIPS PUB 180-1 published
*      April 17, 1995.
*
*      Many of the variable names in this code, especially the
*      single character names, were used because those were the names
*      used in the publication.
*
*      Please read the file sha1.c for more information.
*
*/

#ifndef _SHA1_H_
#define _SHA1_H_

#include <tchar.h>
#include <Oaidl.h>

//#include <stdint.h>
/*
* If you do not have the ISO standard stdint.h header file, then you
* must typdef the following:
*    name              meaning
*  uint32_t         unsigned 32 bit integer
*  uint8_t          unsigned 8 bit integer (i.e., unsigned char)
*  int_least16_t    integer of >= 16 bits
*
*/
typedef unsigned int	uint32_t;   
typedef BYTE			uint8_t; 
typedef int				int_least16_t;

#ifndef _SHA_enum_
#define _SHA_enum_
enum
{
	shaSuccess = 0,
	shaNull,            /* Null pointer parameter */
	shaInputTooLong,    /* input data too long */
	shaStateError       /* called Input after Result */
};
#endif

#define SHA1HashSize 20

/*
*  This structure will hold context information for the SHA-1
*  hashing operation
*/
typedef struct tSHA1_CTX
{
    uint32_t Intermediate_Hash[SHA1HashSize/4]; /* Message Digest  */
	
    uint32_t Length_Low;            /* Message length in bits      */
    uint32_t Length_High;           /* Message length in bits      */
	
	/* Index into message block array   */
    int_least16_t Message_Block_Index;
    uint8_t Message_Block[64];      /* 512-bit message blocks      */
	
    int Computed;               /* Is the digest computed?         */
    int Corrupted;             /* Is the message digest corrupted? */
} tSHA1_CTX;

class OSHA1
{
public:
    OSHA1();
    ~OSHA1();

	int iSHA1_Init(tSHA1_CTX *);
	// 	功    能：初始化tSHA1_CTX结构类型的变量
	// 	输    入：p_ptContext	tSHA1_CTX结构类型的变量
	// 	输    出：p_ptContext	tSHA1_CTX结构类型的变量
	//	返 回 值：成功返回0，失败返回错误代码
	//	作    者：王洪月
	//	创建日期：2004.3

	int iSHA1_Update(tSHA1_CTX *, const uint8_t *, unsigned int);
	// 	功    能：对指定长度（p_uiDataLen）的源文件（p_puiData）与tSHA1_CTX(p_ptContext)结构中的数据，
	//			  按SHA1算法进行计算，并将结果存储在tSHA1_CTX结构中
	// 	输    入：p_ptContext	源tSHA1_CTX结构类型的变量
	//			  p_puiData		源文件
	//			  p_uiDataLen	源文件长度
	// 	输    出：p_ptContext	计算后的tSHA1_CTX结构类型的变量
	//	返 回 值：成功返回0，失败返回错误代码
	//	作    者：王洪月
	//	创建日期：2004.3

	int iSHA1_End(tSHA1_CTX *, uint8_t p_aucResult[SHA1HashSize]);
	// 	功    能：对tSHA1_CTX结构中的数据进行处理，再以字符串（160-bit）的形式输出
	// 	输    入：p_ptContext	源tSHA256_CTX结构类型的变量
	// 	输    出：p_acResult	存储结果的字符数组（串）
	//	返 回 值：成功返回0，失败返回错误代码
	//	作    者：王洪月
	//	创建日期：2004.3

};
#endif
