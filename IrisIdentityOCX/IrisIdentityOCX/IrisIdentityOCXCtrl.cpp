// IrisIdentityOCXCtrl.cpp : CIrisIdentityOCXCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "IrisIdentityOCX.h"
#include "IrisIdentityOCXCtrl.h"
#include "IrisIdentityOCXPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CIrisIdentityOCXCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CIrisIdentityOCXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CIrisIdentityOCXCtrl, COleControl)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "startEnroll", dispidstartEnroll, startEnroll, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "endEnroll", dispidendEnroll, endEnroll, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "saveIrisTemplates", dispidsaveIrisTemplates, saveIrisTemplates, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "startMatch", dispidstartMatch, startMatch, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "endMatch", dispidendMatch, endMatch, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CIrisIdentityOCXCtrl, "saveIrisTemplatesWithName", dispidsaveIrisTemplatesWithName, saveIrisTemplatesWithName, VT_EMPTY, VTS_BSTR)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CIrisIdentityOCXCtrl, COleControl)
END_EVENT_MAP()

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CIrisIdentityOCXCtrl, 1)
	PROPPAGEID(CIrisIdentityOCXPropPage::guid)
END_PROPPAGEIDS(CIrisIdentityOCXCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CIrisIdentityOCXCtrl, "IRISIDENTITYOCX.IrisIdentityOCXCtrl.1",
	0x76e62d85, 0xa6ff, 0x4510, 0x95, 0xa5, 0xa8, 0x50, 0x82, 0xb6, 0xe, 0x5a)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CIrisIdentityOCXCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DIrisIdentityOCX = { 0x936F559C, 0x13D0, 0x4E46, { 0xA9, 0x12, 0x13, 0xFA, 0x39, 0xD3, 0x99, 0x21 } };
const IID IID_DIrisIdentityOCXEvents = { 0xF13873FB, 0xC4AD, 0x4D5A, { 0xBA, 0x5A, 0xC7, 0x75, 0xA3, 0x2B, 0xDC, 0x12 } };

// 控件类型信息

static const DWORD _dwIrisIdentityOCXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CIrisIdentityOCXCtrl, IDS_IRISIDENTITYOCX, _dwIrisIdentityOCXOleMisc)

// CIrisIdentityOCXCtrl::CIrisIdentityOCXCtrlFactory::UpdateRegistry -
// 添加或移除 CIrisIdentityOCXCtrl 的系统注册表项

BOOL CIrisIdentityOCXCtrl::CIrisIdentityOCXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

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


// CIrisIdentityOCXCtrl::CIrisIdentityOCXCtrl - 构造函数

CIrisIdentityOCXCtrl::CIrisIdentityOCXCtrl()
{
	InitializeIIDs(&IID_DIrisIdentityOCX, &IID_DIrisIdentityOCXEvents);
	// TODO:  在此初始化控件的实例数据。
}

// CIrisIdentityOCXCtrl::~CIrisIdentityOCXCtrl - 析构函数

CIrisIdentityOCXCtrl::~CIrisIdentityOCXCtrl()
{
	// TODO:  在此清理控件的实例数据。
}

// CIrisIdentityOCXCtrl::OnDraw - 绘图函数

void CIrisIdentityOCXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	cameraShowDlg.MoveWindow(rcBounds, TRUE);
}

// CIrisIdentityOCXCtrl::DoPropExchange - 持久性支持

void CIrisIdentityOCXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// CIrisIdentityOCXCtrl::OnResetState - 将控件重置为默认状态

void CIrisIdentityOCXCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CIrisIdentityOCXCtrl::AboutBox - 向用户显示“关于”框

void CIrisIdentityOCXCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_IRISIDENTITYOCX);
	dlgAbout.DoModal();
}


// CIrisIdentityOCXCtrl 消息处理程序


void CIrisIdentityOCXCtrl::startEnroll()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	cameraShowDlg.endIrisIdentity();
	cameraShowDlg.startIrisIdentity(MODE_ENROLL);
}


void CIrisIdentityOCXCtrl::endEnroll()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	cameraShowDlg.endIrisIdentity();
}


void CIrisIdentityOCXCtrl::saveIrisTemplates()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	cameraShowDlg.saveIrisTemplates(L"test");
}


int CIrisIdentityOCXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	cameraShowDlg.Create(IDD_CAMERASHOWDLG, this);
	return 0;
}


void CIrisIdentityOCXCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	RECT activeXRect;
	GetClientRect(&activeXRect);
	cameraShowDlg.MoveWindow(&activeXRect);
}


void CIrisIdentityOCXCtrl::startMatch()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	cameraShowDlg.endIrisIdentity();
	cameraShowDlg.startIrisIdentity(MODE_MATCH);
}


void CIrisIdentityOCXCtrl::endMatch()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	cameraShowDlg.endIrisIdentity();
}


void CIrisIdentityOCXCtrl::saveIrisTemplatesWithName(BSTR name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	cameraShowDlg.saveIrisTemplates(name);
}
