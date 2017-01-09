// IrisIdentityOCXCtrl.cpp : CIrisIdentityOCXCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "IrisIdentityOCX.h"
#include "IrisIdentityOCXCtrl.h"
#include "IrisIdentityOCXPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CIrisIdentityOCXCtrl, COleControl)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CIrisIdentityOCXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// ����ӳ��

BEGIN_DISPATCH_MAP(CIrisIdentityOCXCtrl, COleControl)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "startEnroll", dispidstartEnroll, startEnroll, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "endEnroll", dispidendEnroll, endEnroll, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "saveIrisTemplates", dispidsaveIrisTemplates, saveIrisTemplates, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "startMatch", dispidstartMatch, startMatch, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "endMatch", dispidendMatch, endMatch, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "saveIrisTemplatesWithName", dispidsaveIrisTemplatesWithName, saveIrisTemplatesWithName, VT_EMPTY, VTS_BSTR)
END_DISPATCH_MAP()

// �¼�ӳ��

BEGIN_EVENT_MAP(CIrisIdentityOCXCtrl, COleControl)
END_EVENT_MAP()

// ����ҳ

// TODO: ������Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CIrisIdentityOCXCtrl, 1)
	PROPPAGEID(CIrisIdentityOCXPropPage::guid)
END_PROPPAGEIDS(CIrisIdentityOCXCtrl)

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CIrisIdentityOCXCtrl, "IRISIDENTITYOCX.IrisIdentityOCXCtrl.1",
	0x76e62d85, 0xa6ff, 0x4510, 0x95, 0xa5, 0xa8, 0x50, 0x82, 0xb6, 0xe, 0x5a)

// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CIrisIdentityOCXCtrl, _tlid, _wVerMajor, _wVerMinor)

// �ӿ� ID

const IID IID_DIrisIdentityOCX = { 0x936F559C, 0x13D0, 0x4E46, { 0xA9, 0x12, 0x13, 0xFA, 0x39, 0xD3, 0x99, 0x21 } };
const IID IID_DIrisIdentityOCXEvents = { 0xF13873FB, 0xC4AD, 0x4D5A, { 0xBA, 0x5A, 0xC7, 0x75, 0xA3, 0x2B, 0xDC, 0x12 } };

// �ؼ�������Ϣ

static const DWORD _dwIrisIdentityOCXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CIrisIdentityOCXCtrl, IDS_IRISIDENTITYOCX, _dwIrisIdentityOCXOleMisc)

// CIrisIdentityOCXCtrl::CIrisIdentityOCXCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CIrisIdentityOCXCtrl ��ϵͳע�����

BOOL CIrisIdentityOCXCtrl::CIrisIdentityOCXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_IRISIDENTITYOCX,
			IDB_IRISIDENTITYOCX,
			afxRegApartmentThreading,
			_dwIrisIdentityOCXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CIrisIdentityOCXCtrl::CIrisIdentityOCXCtrl - ���캯��

CIrisIdentityOCXCtrl::CIrisIdentityOCXCtrl()
{
	InitializeIIDs(&IID_DIrisIdentityOCX, &IID_DIrisIdentityOCXEvents);
	// TODO:  �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}

// CIrisIdentityOCXCtrl::~CIrisIdentityOCXCtrl - ��������

CIrisIdentityOCXCtrl::~CIrisIdentityOCXCtrl()
{
	// TODO:  �ڴ�����ؼ���ʵ�����ݡ�
}

// CIrisIdentityOCXCtrl::OnDraw - ��ͼ����

void CIrisIdentityOCXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	cameraShowDlg.MoveWindow(rcBounds, TRUE);
}

// CIrisIdentityOCXCtrl::DoPropExchange - �־���֧��

void CIrisIdentityOCXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}


// CIrisIdentityOCXCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CIrisIdentityOCXCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO:  �ڴ��������������ؼ�״̬��
}


// CIrisIdentityOCXCtrl::AboutBox - ���û���ʾ�����ڡ���

void CIrisIdentityOCXCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_IRISIDENTITYOCX);
	dlgAbout.DoModal();
}


// CIrisIdentityOCXCtrl ��Ϣ�������


void CIrisIdentityOCXCtrl::startEnroll()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	cameraShowDlg.endIrisIdentity();
	cameraShowDlg.startIrisIdentity(MODE_ENROLL);
}


void CIrisIdentityOCXCtrl::endEnroll()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	cameraShowDlg.endIrisIdentity();
}


void CIrisIdentityOCXCtrl::saveIrisTemplates()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	cameraShowDlg.saveIrisTemplates(L"test");
}


int CIrisIdentityOCXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	cameraShowDlg.Create(IDD_CAMERASHOWDLG, this);
	return 0;
}


void CIrisIdentityOCXCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	RECT activeXRect;
	GetClientRect(&activeXRect);
	cameraShowDlg.MoveWindow(&activeXRect);
}


void CIrisIdentityOCXCtrl::startMatch()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	cameraShowDlg.endIrisIdentity();
	cameraShowDlg.startIrisIdentity(MODE_MATCH);
}


void CIrisIdentityOCXCtrl::endMatch()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	cameraShowDlg.endIrisIdentity();
}


void CIrisIdentityOCXCtrl::saveIrisTemplatesWithName(BSTR name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	cameraShowDlg.saveIrisTemplates(name);
}
