// IrisIdentityOCXPropPage.cpp : CIrisIdentityOCXPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "IrisIdentityOCX.h"
#include "IrisIdentityOCXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CIrisIdentityOCXPropPage, COlePropertyPage)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CIrisIdentityOCXPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CIrisIdentityOCXPropPage, "IRISIDENTITYOC.IrisIdentityOCPropPage.1",
	0xa8c5fcf8, 0xf951, 0x4ea9, 0x90, 0xd7, 0xd2, 0x3d, 0xb0, 0x65, 0x70, 0x83)

// CIrisIdentityOCXPropPage::CIrisIdentityOCXPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CIrisIdentityOCXPropPage ��ϵͳע�����

BOOL CIrisIdentityOCXPropPage::CIrisIdentityOCXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_IRISIDENTITYOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CIrisIdentityOCXPropPage::CIrisIdentityOCXPropPage - ���캯��

CIrisIdentityOCXPropPage::CIrisIdentityOCXPropPage() :
	COlePropertyPage(IDD, IDS_IRISIDENTITYOCX_PPG_CAPTION)
{
}

// CIrisIdentityOCXPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CIrisIdentityOCXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CIrisIdentityOCXPropPage ��Ϣ�������
