

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Wed Jan 11 21:41:49 2017
 */
/* Compiler settings for IrisIdentityOCX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

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

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_IrisIdentityOCXLib,0x7F35E591,0xC8DD,0x4FED,0xB1,0xEB,0x9D,0x2A,0x9A,0x3C,0x19,0xF3);


MIDL_DEFINE_GUID(IID, DIID__DIrisIdentityOCX,0x936F559C,0x13D0,0x4E46,0xA9,0x12,0x13,0xFA,0x39,0xD3,0x99,0x21);


MIDL_DEFINE_GUID(IID, DIID__DIrisIdentityOCXEvents,0xF13873FB,0xC4AD,0x4D5A,0xBA,0x5A,0xC7,0x75,0xA3,0x2B,0xDC,0x12);


MIDL_DEFINE_GUID(CLSID, CLSID_IrisIdentityOCX,0x76E62D85,0xA6FF,0x4510,0x95,0xA5,0xA8,0x50,0x82,0xB6,0x0E,0x5A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



