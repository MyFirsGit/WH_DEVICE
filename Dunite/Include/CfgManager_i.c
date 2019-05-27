/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 30 15:00:26 2011
 */
/* Compiler settings for D:\BuildWork\Dunite\GrgCfgManager\Src\CfgManager\CfgManager.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ICfgItem = {0xE55C6C2B,0xA185,0x4480,{0xAC,0x36,0xDE,0x43,0xC3,0xD2,0x04,0x71}};


const IID IID_ICfgCollection = {0x44212460,0x79CE,0x43A1,{0x98,0x22,0xBE,0x65,0x77,0x50,0xC5,0x06}};


const IID IID_ICfgAccess = {0xCA09C042,0x1505,0x4955,{0xBA,0x9F,0xF3,0xD1,0x28,0x9F,0x4A,0x40}};


const IID LIBID_CFGMANAGERLib = {0x8FDFFAEC,0xE321,0x4C05,{0xBF,0x7C,0x13,0x1F,0xD3,0x5D,0x2B,0xDF}};


const CLSID CLSID_CfgAccess = {0x548AA8F2,0x6962,0x471B,{0x9F,0x7D,0x35,0x7D,0x0D,0x10,0xD8,0x79}};


#ifdef __cplusplus
}
#endif

