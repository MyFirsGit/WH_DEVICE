// OGeneralLib.h: interface for the GeneralLib.
//
//////////////////////////////////////////////////////////////////////
/*<ModuleInfo>
<Comment>：
<产品名称>：基础静态库
<版    本>：V1.0.0
<创建日期>：2004.2
<作	   者>：王洪月
<功能说明>：提供各程序需要用到的辅助函数或类，包括系统辅助功能、各种转换、数字操作、
			字符串操作、文件操作等。
<调用模块>：无
</Comment>
</ModuleInfo>*/

#if !defined(AFX_GeneralLib_H__C1A33451_2434_11D5_B18A_5254AB1A7D30__INCLUDED_)
#define AFX_GeneralLib_H__C1A33451_2434_11D5_B18A_5254AB1A7D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)
#pragma warning(disable:4100)

#include <tchar.h>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <stack>
#include <utility>
#include <algorithm>
#include <Oaidl.h>
#include <assert.h>

using namespace std;

#include "stlunicode.h"

//******宏定义******// start

//释放指针的宏
#define RELEASE(p) \
	if (p) \
	{ \
		delete p; \
		p = NULL; \
	}

// 程序中加说明，将在编译时在Build窗口显示相应语句
// 例如：在程序中用语句如：#pragma PROGMSG(以后再完善)，将在编译时在Build窗口显示此语句出处，双击就可到此处。
#define PROGSTR2(x)	#x
#define PROGSTR(x)	PROGSTR2(x)
#define PROGMSG(desc) message(__FILE__"("PROGSTR(__LINE__)"):"#desc)

#if !defined(FAIL)
#define		FAIL		1
#endif

#if !defined(SUCCESS)
#define		SUCCESS		0
#endif

//******宏定义******// end


//******系统辅助函数OSysFunc.cpp******// begin

BOOL bShutDown();
// 	功    能：关闭机器(for windows)
// 	输    入：无
// 	输    出：无
//	返 回 值：TRUE - 成功，FALSE - 失败
//	作	  者：王洪月
//	创建日期：2004.2

BOOL bReBoot();		
// 	功    能：重新启动机器(for windows)
// 	输    入：无
// 	输    出：无
//	返 回 值：TRUE - 成功，FALSE - 失败
//	作	  者：王洪月
//	创建日期：2004.2

tstring strGetErrMsg(DWORD* p_dwErrCode);	
// 	功    能：得到当前线程的最后一个错误的错误代码和描述
// 	输    入：无
// 	输    出：p_dwErrCode	返回的错误号，如果为NULL，表示不返回
//	返 回 值：错误代码的具体描述,如果没有错误，返回空字符串		
//	作	  者：刘道余
//	创建日期：2004.2

int iGetModuleVersionInfo(LPCTSTR p_pcFileName, 
						   HINSTANCE p_hInstance,	
						   tstring& p_pstrName,	
						   tstring& p_pstrInterName, 
						   tstring& p_pstrVersion);
// 	功    能：获取某模块的版本信息
// 	输    入：p_pcFileName		模块名，如果为NULL，则使用p_hInstance 
//			  p_hInstance		模块的HINSTANCE
// 	输    出：p_pstrName		产品名,Version中的ProductName
//			  p_pstrInterName	Version中的InterName
//			  p_pstrVersion		Version中的ProductVerion
//	返 回 值：SUCCESS	成功
//			  FAIL	失败
//	作	  者：刘道余
//	创建日期：2004.2

int iGetCPUID(TCHAR *p_pcCPUID);
// 	功    能：获取CPU的ID号
// 	输    入：无
// 	输    出：p_pcCPUID		CPU的ID号
//	返 回 值：SUCCESS	成功
//			  FAIL		失败
//	作	  者：王洪月
//	创建日期：2004.2

int iGetMacAddress(TCHAR *p_pcMACAddress);
// 	功    能：获取MAC地址
// 	输    入：无
// 	输    出：p_pcMACAddress		MAC地址
//	返 回 值：0    成功
//			  其他 错误码
//	作	  者：王洪月
//	创建日期：2004.2

int iGetHardwareID(TCHAR *p_pcHardwareID);
// 	功    能：获取硬盘的流水号
// 	输    入：无
// 	输    出：p_pcHardwareID		硬盘的流水号
//	返 回 值：SUCCESS	成功
//			  FAIL	失败
//	作	  者：王洪月
//	创建日期：2004.2

BOOL bControlServices(LPCTSTR lpServiceName, DWORD fdwControl);
// 	功    能：控制系统服务
// 	输    入：lpServiceName			服务名称，具体说明参考MSDN
//			  fdwControl			服务参数，具体说明参考MSDN
// 	输    出：无
//	返 回 值：SUCCESS	成功
//			  FAIL	失败
//	作	  者：王洪月
//	创建日期：2004.2

//  BOOL SetEnvironmentVariable(
//	  LPCTSTR lpName,  
//	  LPCTSTR lpValue  
//	  );
// 	功    能：设置指定环境变量
// 	输    入：lpName,  // 环境变量名
//			  lpValue  // 设定的变量值
// 	输    出：无
//	返 回 值：无
//	说    明：API函数

//******系统辅助函数OSysFunc.cpp******// end


//******一般辅助函数OGenericFunc.cpp******// begin

void vDelayMsg(DWORD p_dwTime);
// 	功    能：非阻塞性延迟等待函数
// 	输    入：p_dwTime		延迟时间（毫秒）
// 	输    出：无
//	返 回 值：无
//	作	  者：刘道余
//	创建日期：2004.2

int	iByteArraycmp(PBYTE p_pbArrayOne, long p_lLenOne/* = -1*/,
			 PBYTE p_pbArrayTwo, long p_lLenTwo/* = -1*/);
// 	功    能：BYTE数组比较函数
// 	输    入：p_pbArrayOne		BYTE数组1
//			  p_lLenOne			BYTE数组1的长度,如果等于-1，则直接取p_pbArrayOne的字符串长度
//			  p_pbArrayTwo		BYTE数组2
//			  p_lLenTwo			BYTE数组2的长度,如果等于-1，则直接取p_pbArrayTwo的字符串长度
// 	输    出：无
//	返 回 值：<0	数组1小于数组2
//			  =0	数组1等于数组2
//			  >0	数组1大于数组2
//	作	  者：王洪月
//	创建日期：2004.2

int iGetVerify(BYTE *p_pbDesc, PBYTE p_pbSrc, long p_lSrcLen);
// 	功    能：产生校验位函数
// 	输    入：p_pbSrc		源数据数组
//			  p_lSrcLen		源数据长度（数组长度）
// 	输    出：p_pbDesc		所有数据进行与运算后得到的校验位
//	返 回 值：成功返回0，失败返回1。
//	作	  者：王洪月
//	创建日期：2004.2

//******一般辅助函数OGenericFunc.cpp******// end


//******数据类型转换函数ODatatypeCtrl.cpp******// begin

int iFormatNum(TCHAR *p_pcResultNum, TCHAR *p_pcSrcNum, int p_iDotdigit, int p_iNumGrup, bool p_bZeroShow);
//	功    能：数字格式转换（仿控制面板->区域选项->数字）
//	输    入：p_pcSrcNum		格式转换前的数字串
//			  p_iDotdigit		小数点的位数
//			  p_iNumGrup		整数分组显示格式
//				0 － 123456789
//				1 － 123,456,789
//				2 － 12,34,56,789
//			  p_bZeroShow		零起始显示
//				true － .7
//				false － 0.7
//	输    出：p_pcResultNum	格式转换后的数字串
//	返 回 值：成功返回0，失败返回1。
//	作	  者：王洪月
//	创建日期：2004.2

int iFormatCurrency(TCHAR *p_pcResultCurrency, TCHAR *p_pcSrcCurrency, int p_iCurFlag, int p_iDotdigit, int p_iNumGrup, bool p_bZeroShow);
//	功    能：货币格式转换（仿控制面板->区域选项->货币）
//	输    入：p_pcSrcCurrency		格式转换前的货币字符串
//			  p_iCurFlag			货币符号
//				0 － 人民币（￥）
//				1 － 美元（＄）
//				2 － 英镑（￡）
//			  p_iDotdigit			小数点的位数
//			  p_iNumGrup			整数分组显示格式
//			 	0 － 123456789
//				1 － 123,456,789
//				2 － 12,34,56,789
//			  p_bZeroShow			零起始显示
//				true － .7
//				false － 0.7
//	输    出：p_pcResultCurrency	格式转换后的货币字符串
//	返 回 值：成功返回0，失败返回1。
//	作	  者：王洪月
//	创建日期：2004.2

void vBase10Encode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	功    能：BASE10编码(不支持UNICODE)。
//	输    入：p_pcSrc		未编码的二进制代码。每个字符的ASCII码要在0～127之间，数组长度不可超过512。
//			  p_iSrcLen		输入代码的长度
//	输    出：p_pcResult	编码过的Base10代码,输出数据的最大长度可达1234字节。
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

void vBase10Decode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	功    能：BASE10解码(不支持UNICODE)。
//	输    入：p_pcSrc		未解码的Base10代码,输入数据的最大长度不可超过1234字节。
//	输    出：p_pcResult	解码过的二进制代码,输出数据的最大长度可达512字节。
//			  p_piResultLen	解码得到的代码的长度
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

void vBase10ExEncode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	功    能：BASE10Ex编码(不支持UNICODE)。一段二进制数据，将每8个BIT对应的一个字符用它的ASCII值表示出来("AB" - "065066")
//	输    入：p_pcSrc		未编码的二进制代码
//			  p_iSrcLen		输入代码的长度
//	输    出：p_pcResult	编码过的Base10Ex代码
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

void vBase10ExDecode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	功    能：BASE10Ex解码(不支持UNICODE)。("065066" - "AB")
//	输    入：p_pcSrc		未解码的Base10Ex代码
//	输    出：p_pcResult	解码过的二进制代码
//			  p_piResultLen	解码得到的代码的长度
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

void vBase16Encode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	功    能：BASE16编码(不支持UNICODE)。
//	输    入：p_pcSrc		未编码的二进制代码
//			  p_iSrcLen		输入代码的长度
//	输    出：p_pcResult	编码过的Base16代码
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

void vBase16Decode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	功    能：BASE16解码(不支持UNICODE)。
//	输    入：p_pcSrc		未解码的Base16代码
//	输    出：p_pcResult	解码过的二进制代码
//			  p_piResultLen	解码得到的代码的长度
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

void vBase16ExEncode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	功    能：BASE16Ex编码(不支持UNICODE)。对一段二进制数据，每4个BIT转换为一个字符(0x01转换为0x30,0x31)
//	输    入：p_pcSrc		未编码的二进制代码
//			  p_iSrcLen		输入代码的长度
//	输    出：p_pcResult	编码过的Base16Ex代码
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

void vBase16ExDecode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	功    能：BASE16Ex解码(不支持UNICODE)。每两个字符合成一个数据(0x31,0x32转换为0x12)
//	输    入：p_pcSrc		未解码的Base16Ex代码
//	输    出：p_pcResult	解码过的二进制代码
//			  p_piResultLen	解码得到的代码的长度
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

void vBase64Encode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int p_iSrcLen = -1);
//	功    能：BASE64编码(不支持UNICODE)
//	输    入：p_pcSrc		未编码的二进制代码
//			  p_iSrcLen		输入代码的长度
//	输    出：p_pcResult	编码过的Base64代码
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

void vBase64Decode(TCHAR *p_pcResult, TCHAR *p_pcSrc, int *p_piResultLen);
//	功    能：BASE64解码(不支持UNICODE)
//	输    入：p_pcSrc		未解码的Base64代码
//	输    出：p_pcResult	解码过的二进制代码
//			  p_piResultLen	解码得到的代码的长度
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

int	iSglHexCharToInt(TCHAR p_cHexChar);
//	功    能：十六进制字符转数字
//	输    入：p_cHexChar		十六进制字符('0'~'9','a'~'f','A'~'F')
//	输    出：无
//	返 回 值：字符对应的数字(0~15)
//			  -1 失败
//	作	  者：刘道余
//	创建日期：2004.2

TCHAR cSglHexIntToChar(int p_iHexInt);
//	功    能：十六进制数字转字符
//	输    入：p_iHexInt		十六进制数字(0~15)
//	输    出：无
//	返 回 值：数字对应的字符('0'~'9','a'~'f','A'~'F')
//			  ='\0' 失败
//	作	  者：刘道余
//	创建日期：2004.2

PBYTE pbSafeAryToPByte(SAFEARRAY* p_psa, long* p_plLen);
//	功    能：SAFEARRAY转为BYTE数组
//	输    入：p_psa		SAFEARRAY
//	输    出：p_plLen		BYTE数组长度
//	返 回 值：转换后的BYTE数组
//	作	  者：刘道余
//	创建日期：2004.2

SAFEARRAY* saPByteToSafeAry(PBYTE p_pbData, long p_lLen /* = -1*/);
//	功    能：BYTE数组转为SAFEARRAY
//	输    入：p_pbData	BYTE数组
//			  p_lLen		BYTE数组长度
//	输    出：无
//	返 回 值：转换后的SAFEARRAY
//	作	  者：刘道余
//	创建日期：2004.2

TCHAR* pcSafeAryToChar(SAFEARRAY *p_psa, long *p_plLen);
//	功    能：SAFEARRAY转为字符串数组
//	输    入：p_psa		SAFEARRAY
//	输    出：p_plLen		字符串数组长度
//	返 回 值：转换后的字符串数组
//	作	  者：刘道余
//	创建日期：2004.2

SAFEARRAY* saCharToSafeAry(TCHAR *p_pcData, long p_lLen);
//	功    能：字符串数组转为SAFEARRAY
//	输    入：p_pcData	字符串数组
//			  p_lLen		字符串数组长度
//	输    出：无
//	返 回 值：转换后的SAFEARRAY
//	作	  者：刘道余
//	创建日期：2004.2

int* piSafeAryToInt(SAFEARRAY *p_psa, long *p_plLen);
//	功    能：SAFEARRAY转为整型数组
//	输    入：p_psa		SAFEARRAY
//	输    出：p_plLen		整型数组长度
//	返 回 值：转换后的整型数组
//	作	  者：刘道余
//	创建日期：2004.2

SAFEARRAY* saIntToSafeAry(int *p_piData, long p_lLen);
//	功    能：整型数组转为SAFEARRAY
//	输    入：p_piData	整型数组
//			  p_lLen		整型数组长度
//	输    出：无
//	返 回 值：转换后的SAFEARRAY
//	作	  者：刘道余
//	创建日期：2004.2

int iNumToChinese(TCHAR *p_pcResult, LPCTSTR p_pcSrc, int p_iChangeFlag);
//	功    能：阿拉伯数字与中文大写表示的值的转换，用于数字金额到中文金额的转换
//	输    入：p_pcSrc		阿拉伯数字的字符串(小数位如果超过两位，只处理前两位)
//			  p_iChangeFlag	转换标志 1 - {"○","一","二","三","四","五","六","七","八","九"}
//									 2 - {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"}
//	输    出：p_pcResult	中文大写的字符串
//	返 回 值：SUCCESS - 成功
//			  FAIL - 失败
//	作	  者：王洪月
//	创建日期：2004.2

int iGetTodayWeek(TCHAR *p_pcResult, int p_iFlag);
//	功    能：获取当前的星期
//	输    入：p_iFlag		数据形式
//				1 - "日一二三四五六"
//				2 - "SunMonTueWedThuFriSat"
//	输    出：p_pcResult	结果字符串
//	返 回 值：成功返回0，失败返回1
//	作	  者：刘道余
//	创建日期：2004.2

int iGetTodayMonth(TCHAR *p_pcResult, int p_iFlag);
//	功    能：获取当前的月份
//	输    入：p_iFlag		数据形式
//				1 - "一二三四五六七八九十十一十二"
//				2 - "JanFebMarAprMayJunJulAugSepOctNovDec"
//	输    出：p_pcResult	结果字符串
//	返 回 值：成功返回0，失败返回1
//	作	  者：刘道余
//	创建日期：2004.2

int iGetTodayDate( TCHAR *p_pcResult, int p_iFlag);
//	功    能：获得当日系统日期, 以字符串返回 
//	输    入：p_iFlag		日期串格式 
//				0 - YYYYMMDD					
//				1 - YYYY/MM/DD					
//				2 - YYYY-MM-DD				
//				3 - MMDDYYYY					
//				4 - MM/DD/YYYY					
//				5 - MM-DD-YYYY					
//				6 - DDMMYYYY					
//				7 - DD/MM/YYYY					
//				8 - DD-MM-YYYY					
//				9 - YYYY年MM月DD日				
//	输    出：p_pcResult	结果字符串
//	返 回 值：成功返回0，失败返回1
//	作	  者：刘道余
//	创建日期：2004.2

int iBCDToChar(TCHAR *p_pcResult, TCHAR p_cBCDBuf);
//	功    能：BCD码转换为字符串
//	输    入：p_cBCDBuf		需要转换的BCD码，当输入的BCD码不合法时，也一样对其进行处理，但函数返回值为失败。
//	输    出：p_pcResult	转换后的字符串
//	返 回 值：成功返回0，失败返回1。
//	作	  者：刘道余
//	创建日期：2004.2

TCHAR cCharToBCD(TCHAR *p_pcCharBuf);	
//	功    能：字符串转换为BCD 码
//	输    入：p_pcCharBuf		字符串指针
//	输    出：无
//	返 回 值：转换后的BCD码,如果返回值等于OXFF，表示输入不合法，转换失败。
//	作	  者：刘道余
//	创建日期：2004.2

int iBCDToASCII(TCHAR *p_pcResult, int p_iNum, TCHAR *p_pcBCDBuf);	
//	功    能：BCD码转换为ASCII码
//	输    入：p_pcASCII		存放BCD码指针，当输入的BCD码有不合法数据时，也一样对其进行处理，但函数返回值为失败。
//			  p_iNum		BCD码长度
//	输    出：p_pcResult	存放ASCII码指针
//	返 回 值：成功返回0，失败返回1。
//	作	  者：刘道余
//	创建日期：2004.2

int iASCIIToBCD( TCHAR *p_pcResult, TCHAR *p_pcASCII, int p_iNum); 
//	功    能：ASCII码转换为BCD码
//	输    入：p_pcASCII		存放ASCII码指针,如果输入中含有不合法数据，不在对其处理，函数返回失败。
//			  p_iNum		ASCII码长度
//	输    出：p_pcResult	存放BCD码指针
//	返 回 值：成功返回0，失败返回1。
//	作	  者：刘道余
//	创建日期：2004.2

void vHexToASCII(BYTE *p_pcResult, BYTE *p_pcHexBuf, int p_iLen ); 
//	功    能：十六进制型转换为ASCII码
//	输    入：p_pcHexBuf		待转换的十六进制字符串 
//			  p_iLen			十六进制字符串的长度
//	输    出：p_pcResult		存放转换后的ASCII码，长度等于十六进制字符串长度的2倍
//	返 回 值：无
//	作	  者：刘道余
//	创建日期：2004.2

void vASCIIToHex(BYTE *p_pcResult, BYTE *p_pcASCBuf, int p_iLen);
//	功    能：ASCII码转换为十六进制型
//	输    入：p_pcASCBuf		待转换的ASCII码
//			  p_iLen			ASCII码长度
//	输    出：p_pcResult		转换后的十六进制字符串
//	返 回 值：无
//	作	  者：刘道余
//	创建日期：2004.2

int  iBCDToInt( TCHAR p_cBCDBuf);
//	功    能：BCD码转换为int型
//	输    入：p_pcBCDBuf		待转换的BCD码
//	输    出：无
//	返 回 值：转换成的int型数字,如果输入为非法数据，返回－1。
//	作	  者：刘道余
//	创建日期：2004.2

long lBCDToLong( TCHAR *p_pcBCDBuf, int p_iLen);
//	功    能：BCD码转换为LONG型
//	输    入：p_pcBCDBuf		待转换的BCD码
//			  p_iLen			BCD码字节长度，不可超过4个字节，以免所得数值超过long类型的数值范围，超过4字节返回失败
//	输    出：无
//	返 回 值：转换成的Long型数字,如果输入为非法数据，返回－1。
//	作	  者：刘道余
//	创建日期：2004.2

void vHexToChar( BYTE *p_pcResult, BYTE p_cHexchar );
//	功    能：十六进制数据转换为字符串
//	输    入：p_cHexchar		需要转换的十六进制数据
//	输    出：p_pcResult		转换后的字符串
//	返 回 值：无
//	作	  者：刘道余
//	创建日期：2004.2

int  iDoubleToASCII(TCHAR *p_pcResult,double p_dDouble, int p_iwidth,int p_iFlag, int p_iDec);
//	功    能：Double型转换为ASCII码 
//	输    入：p_dDouble		待转换的double型数字
//			  p_iwidth		生成串长度
//			  p_iFlag		0-含小数点, 1-不含
//			  p_iDec		小数点后位数
//	输    出：p_pcResult	转换出的ASCII码
//	返 回 值：>= 0	成功						
//		      <  0	因长度等原因造成失败
//	作	  者：刘道余
//	创建日期：2004.2

int  iIntToASCII(TCHAR *p_pcResult, int p_iSrc, int p_iwidth);
//	功    能：Int型转换为ASCII码 
//	输    入：p_iSrc		待转换的Int型数字
//			  p_iwidth		生成串长度
//	输    出：p_pcResult	转换出的ASCII码
//	返 回 值：>= 0	成功						
//		      <  0	因长度等原因造成失败
//	作	  者：刘道余
//	创建日期：2004.2

BOOL bByteStream2Variant(PBYTE p_pbSrc,VARIANT& p_varResult,ULONG p_ulSrcLen);
//	功    能：将字节流包装为VARIANT类型
//	输    入：p_pbSrc			需要转换的字节数组
//			  p_ulSrcLen 		字节数组长度
//	输    出：p_varResult		转换后的VARIANT
//	返 回 值：TRUE - 成功	FALSE - 失败
//	作	  者：刘文斌
//	创建日期：2004.10

PBYTE pbyVariant2ByteStream(const VARIANT& p_varSrc,ULONG* p_pulResultLen);
//	功    能：将VARIANT类型的转换为字节流,用户在使用完返回的的指针后需要负责删除
//	输    入：p_varSrc			需要转换的VARIANT
//	输    出：p_pulResultLen	转换后的字节长度
//	返 回 值：转换后的字节数组
//	作	  者：刘文斌
//	创建日期：2004.10
//******数据类型转换函数ODatatypeCtrl.cpp******// end


//******数字操作函数ONumberCtrl.cpp******// begin

int iGetIntersection(float p_fAL, float p_fAH, float p_fBL, float p_fBH, float& p_fCL, float& p_fCH);
// 	功    能：求集合A(p_fAL,p_fAH)与集合B(p_fBL,p_fBH)的交集C(p_fCL,p_fCH)
// 	输    入：集合A(p_fAL,p_fAH)
//			  集合B(p_fBL,p_fBH)
// 	输    出：交集C(p_fCL,p_fCH)
//	返 回 值：SUCCESS 成功
//			  FAIL    失败
//	作	  者：刘道余
//	创建日期：2004.2

//******数字操作函数ONumberCtrl.cpp******// end


//******文件操作类OFileCtrl.cpp******// begin
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "fci.h"
#include "fdi.h"

/*
 * 设定压缩后文件的大小，用于将大的文件压缩分割到几张软盘。
 * 这里只是简单地压缩到一个文件，所以设为一个足够大的值。
 */
#define MEDIA_SIZE			1000000000

/*
 * 当压缩文件达到此值时会自动FLUSH。
 */
#define FOLDER_THRESHOLD	900000

/*
 * 压缩格式
 */
#define COMPRESSION_TYPE    tcompTYPE_MSZIP

#define		FILENAME_LEN	256
#define		PATH_LEN		1000

struct tFileName{
	TCHAR				cFileName[FILENAME_LEN];
	FILETIME			ftCreationTime; 
	struct tFileName*	pNext; 
};

class OFileCtrl
{
public:

	BOOL bCompress(TCHAR *p_pcSrcName, TCHAR *p_pcCabName);
	//	功    能：文件压缩(不支持UNICODE)
	//	输    入：p_pcSrcName		待压缩的全路径或文件名（缺省路径为当前路径）
	//	          p_pcCabName		压缩后形成的压缩文件的文件名
	//	输    出：无
	//	返 回 值：成功返回TRUE,失败返回FALSE
	//	作	  者：王洪月
	//	创建日期：2004.2

	BOOL bDecompress(TCHAR *p_pcCabName, TCHAR *p_pcDestPath);
	//	功    能：文件解压(不支持UNICODE)
	//	输    入：p_pcCabName		待解压的全路径或文件名（缺省路径为当前路径）
	//	          p_pcDestPath		解压后形成的文件的存放路径
	//	输    出：无
	//	返 回 值：成功返回TRUE,失败返回FALSE
	//	作	  者：王洪月
	//	创建日期：2004.2

	int iFileSplt(const TCHAR* p_pcSrcPath, const TCHAR* p_pcSrcFileName, UINT p_uiNewFileLen);
	//	功    能：文件分割，将一个文件按大小分割为若干个子文件，子文件的命名规则为：1_父文件名，2_父文件名……
	//	输    入：p_pcSrcPath		待分割文件所在的路径
	//	          p_pcSrcFileName	待分割文件的文件名
	//	          p_uiNewFileLen	新文件的大小
	//	输    出：无
	//	返 回 值：形成新文件的个数
	//	作	  者：王洪月
	//	创建日期：2004.2

	int iFileBind(const TCHAR* p_pcSrcPath, const TCHAR* p_pcDescPath, const TCHAR* p_pcDescFileName);
	//	功    能：文件绑定，将某目录下的多个文件合并为一个文件
	//	输    入：p_pcSrcPath		源目录的路径，如果为空，直接返回失败
	//	          p_pcDescPath		合并后文件存放的路径，如果为空，默认为当前目录
	//	          p_pcDescFileName	合并后文件的文件名
	//	输    出：无
	//	返 回 值：成功返回0，失败返回1
	//	作	  者：王洪月
	//	创建日期：2004.2

	int iListFiles(TCHAR ***p_pppcResult, LPCTSTR p_pcPath, int p_iListBy, int p_iAsceFlag);
	//	功    能：列举某目录下所有文件的文件名,并排序,将查找到的文件名存储在字符串数组中
	//	输    入：p_pcPath			目录的路径
	//	          p_iListBy			1－按文件名排序、2－按文件生成时间排序
	//	          p_pAsceFlag		0－降序、1－升序
	//	输    出：p_pppcResult		存储结果的字符串数组
	//	返 回 值：数组的大小（文件的数量）
	//	作	  者：王洪月
	//	创建日期：2004.2

	int	iSearchFiles(TCHAR ***p_pppcResult, LPCTSTR p_pcPath,  LPCTSTR p_lpFileName);
	//	功    能：在指定目录下按关键字查找文件名,将查找到的文件名存储在字符串数组中
	//	输    入：p_pcPath			目录的路径
	//	          p_lpFileName		要查找的文件名（可以包含通配符*,?）
	//	输    出：p_pppcResult		存储结果的字符串数组
	//	返 回 值：数组的大小（文件的数量）
	//	作	  者：王洪月
	//	创建日期：2004.2

	BOOL bSetDirectoryAttributes(LPCTSTR p_lpDirectoryName, DWORD p_dwAttributes, int p_iChangeAllFlag);
	//	功    能：设置目录的属性
	//	输    入：p_lpDirectoryName	目录的路径
	//	          p_dwAttributes		要设置的属性
	//			  p_iChangeAllFlag		是否更改所有子文件夹的属性（0－否，1－是）	  
	//	输    出：无
	//	返 回 值：true - 成功
	//			  false - 失败
	//	作	  者：王洪月
	//	创建日期：2004.2

	OFileCtrl();
	virtual ~OFileCtrl();

	// 获取当前路径
	// GetCurrentDirectory
	
	// 获取系统路径
	// GetSystemDirectory
	
	// 获取临时文件夹路径
	// GetTempPath

	// 获取指定文件的完整路径名
	// GetFullPathName 

	// 更改文件的属性（只读，执行，隐藏，系统）
	// SetFileAttributes

protected:
	HFCI m_hfci;                   // context

private:
	BOOL FlushCab();
	BOOL AddFile2Cab(TCHAR *fileName);
	BOOL CreateCabinet(TCHAR *CABName);
	void vCmpFiles(tFileName* p_ptResultHead, LPCTSTR p_pcPath, int p_iListBy, int p_iAsceFlag, int *p_piFileCount);
	void vFindFile(tFileName* p_ptResultHead, LPCTSTR p_pcPath,  LPCTSTR p_lpFileName, int *p_piFileCount);
	BOOL bIsDirectory(DWORD p_wAttributes);
};

//******文件操作类OFileCtrl.cpp******// end


//******字符串操作函数OStringCtrl.cpp******// begin

int iNullStrsToArrayStrs(CHAR*** p_pppcDest, CHAR* p_pcSrc, CHAR p_cFlag);
int iNullWStrsToArrayStrs(WCHAR*** p_pppcDest, WCHAR* p_pcSrc, CHAR p_cFlag);
// 	功    能：将以指定标志分开，以\0结束的字符串组中的每个字符串拆分到一个字符串数组中, 返回数组长度
// 	输    入：p_pcSrc		源字符串。注：函数运行结束后，源数据数组的指定标志会被替换为'\0'。
//			  p_cFlag		指定标志
// 	输    出：p_pppcDest	指定字符串数组
//	返 回 值：数组大小
//	作	  者：刘道余
//	创建日期：2004.2

void vArrayStrsToNullStrs(LPSTR* p_ppcNullStrs, LPSTR* p_ppcArraySrc, int p_iSize, BOOL p_bDel/* = TRUE*/);
void vArrayWStrsToNullStrs(LPWSTR* p_ppcNullStrs, LPWSTR* p_ppcArraySrc, int p_iSize, BOOL p_bDel/* = TRUE*/);
// 	功    能：将字符串数组转换成以\0分隔，以\0\0结尾的字符串
// 	输    入：p_ppcArraySrc		字符串数组
//			  p_iSize			字符数组大小
//			  p_bDel			是否删除原数组
// 	输    出：p_ppcNullStrs		指定字符串
//	返 回 值：无
//	作	  者：刘道余
//	创建日期：2004.2

void vMaptoKVStrs(const map<string, string>& p_tmElements, vector<CHAR>& p_tvKVRet, CHAR p_cFlag);
void vwMaptoKVStrs(const map<wstring, wstring>& p_tmElements, vector<WCHAR>& p_tvKVRet, CHAR p_cFlag);
// 	功    能：将map中的元素组合成"key=value"以指定标志分开，以\0结束的字符串组
// 	输    入：p_tmElements		map
//			  p_cFlag			指定标志符
// 	输    出：p_tvKVRet			字符串组
//	返 回 值：无
//	作	  者：刘道余
//	创建日期：2004.2

void vKVStrstoMap(CHAR* p_pcStrs, map<string, string>& p_tmElements, CHAR p_cFlag);
void vwKVStrstoMap(WCHAR* p_pwcStrs, map<wstring, wstring>& p_tmElements, CHAR p_cFlag);
// 	功    能：将"key=value"以指定标志分开，以\0结束的字符串组解析到map中
// 	输    入：p_pcStrs		源字符串组。注：函数运行结束后，源数据数组的指定标志会被替换为'\0'。
//			  p_cFlag		指定标志符
// 	输    出：p_tmElements	map
//	返 回 值：无
//	作	  者：刘道余
//	创建日期：2004.2

//******字符串操作函数OStringCtrl.cpp******// end


//******媒体操作函数OMediaCtrl.cpp******// begin

void vBeep(UINT p_iFrequency, UINT p_iDuration);
//	功    能：让PC机的扬声器按一定的频率发声
//	输    入：p_iFrequency   发声的频率
//	          p_iDuration    发声后的时间(以毫秒为单位)
//	输    出：无
//	返 回 值：无
//	作	  者：王洪月
//	创建日期：2004.2

//******媒体操作函数OMediaCtrl.cpp******// end

#endif	// !defined(AFX_GeneralLib_H__C1A33451_2434_11D5_B18A_5254AB1A7D30__INCLUDED_)