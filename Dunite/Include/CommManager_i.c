/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 30 15:01:34 2011
 */
/* Compiler settings for D:\BuildWork\Dunite\GrgCommManager\Src\new_commmanager\CommManager.idl:
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

const IID IID_IComm = {0xF5857230,0x7094,0x11D7,{0x9D,0xD6,0x00,0x10,0xB5,0x4D,0x67,0x38}};


const IID IID_ICommEvents = {0xDA66DED1,0xA165,0x11d7,{0x9E,0x16,0x00,0x10,0xB5,0x4D,0x67,0x38}};


const IID LIBID_COMMMANAGERLib = {0xF5857224,0x7094,0x11D7,{0x9D,0xD6,0x00,0x10,0xB5,0x4D,0x67,0x38}};


const CLSID CLSID_Comm = {0xF5857231,0x7094,0x11D7,{0x9D,0xD6,0x00,0x10,0xB5,0x4D,0x67,0x38}};


#ifdef __cplusplus
}
#endif

