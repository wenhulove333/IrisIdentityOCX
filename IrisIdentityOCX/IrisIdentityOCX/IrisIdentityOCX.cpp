// IrisIdentityOCX.cpp : CIrisIdentityOCXApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "IrisIdentityOCX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CIrisIdentityOCXApp theApp;

const GUID CDECL _tlid = { 0x7F35E591, 0xC8DD, 0x4FED, { 0xB1, 0xEB, 0x9D, 0x2A, 0x9A, 0x3C, 0x19, 0xF3 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CIrisIdentityOCXApp::InitInstance - DLL ��ʼ��

BOOL CIrisIdentityOCXApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CIrisIdentityOCXApp::ExitInstance - DLL ��ֹ

int CIrisIdentityOCXApp::ExitInstance()
{
	// TODO:  �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
