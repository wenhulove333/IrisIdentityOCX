// IrisIdentityOCXPropPage.cpp : CIrisIdentityOCXPropPage 属性页类的实现。

#include "stdafx.h"
#include "IrisIdentityOCX.h"
#include "IrisIdentityOCXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CIrisIdentityOCXPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CIrisIdentityOCXPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CIrisIdentityOCXPropPage, "IRISIDENTITYOC.IrisIdentityOCPropPage.1",
	0xa8c5fcf8, 0xf951, 0x4ea9, 0x90, 0xd7, 0xd2, 0x3d, 0xb0, 0x65, 0x70, 0x83)

// CIrisIdentityOCXPropPage::CIrisIdentityOCXPropPageFactory::UpdateRegistry -
// 添加或移除 CIrisIdentityOCXPropPage 的系统注册表项

BOOL CIrisIdentityOCXPropPage::CIrisIdentityOCXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_IRISIDENTITYOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CIrisIdentityOCXPropPage::CIrisIdentityOCXPropPage - 构造函数

CIrisIdentityOCXPropPage::CIrisIdentityOCXPropPage() :
	COlePropertyPage(IDD, IDS_IRISIDENTITYOCX_PPG_CAPTION)
{
}

// CIrisIdentityOCXPropPage::DoDataExchange - 在页和属性间移动数据

void CIrisIdentityOCXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CIrisIdentityOCXPropPage 消息处理程序
