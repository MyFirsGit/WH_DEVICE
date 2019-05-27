/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 30 15:00:40 2011
 */
/* Compiler settings for D:\BuildWork\Dunite\GrgLogServer\Src\LogServer\LogServer.idl:
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

const IID IID_ILogServer = {0x783D1E25,0x869B,0x11D7,{0xBC,0xD2,0x00,0x00,0xE8,0x82,0x63,0xA3}};


const IID LIBID_LOGSERVERLib = {0x783D1E15,0x869B,0x11D7,{0xBC,0xD2,0x00,0x00,0xE8,0x82,0x63,0xA3}};


const CLSID CLSID_LogServer = {0x783D1E26,0x869B,0x11D7,{0xBC,0xD2,0x00,0x00,0xE8,0x82,0x63,0xA3}};


#ifdef __cplusplus
}
#endif

