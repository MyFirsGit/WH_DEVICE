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
	// 	��    �ܣ���ʼ��tSHA1_CTX�ṹ���͵ı���
	// 	��    �룺p_ptContext	tSHA1_CTX�ṹ���͵ı���
	// 	��    ����p_ptContext	tSHA1_CTX�ṹ���͵ı���
	//	�� �� ֵ���ɹ�����0��ʧ�ܷ��ش������
	//	��    �ߣ�������
	//	�������ڣ�2004.3

	int iSHA1_Update(tSHA1_CTX *, const uint8_t *, unsigned int);
	// 	��    �ܣ���ָ�����ȣ�p_uiDataLen����Դ�ļ���p_puiData����tSHA1_CTX(p_ptContext)�ṹ�е����ݣ�
	//			  ��SHA1�㷨���м��㣬��������洢��tSHA1_CTX�ṹ��
	// 	��    �룺p_ptContext	ԴtSHA1_CTX�ṹ���͵ı���
	//			  p_puiData		Դ�ļ�
	//			  p_uiDataLen	Դ�ļ�����
	// 	��    ����p_ptContext	������tSHA1_CTX�ṹ���͵ı���
	//	�� �� ֵ���ɹ�����0��ʧ�ܷ��ش������
	//	��    �ߣ�������
	//	�������ڣ�2004.3

	int iSHA1_End(tSHA1_CTX *, uint8_t p_aucResult[SHA1HashSize]);
	// 	��    �ܣ���tSHA1_CTX�ṹ�е����ݽ��д��������ַ�����160-bit������ʽ���
	// 	��    �룺p_ptContext	ԴtSHA256_CTX�ṹ���͵ı���
	// 	��    ����p_acResult	�洢������ַ����飨����
	//	�� �� ֵ���ɹ�����0��ʧ�ܷ��ش������
	//	��    �ߣ�������
	//	�������ڣ�2004.3

};
#endif
