#pragma once

// IrisIdentityOCXPropPage.h : CIrisIdentityOCXPropPage ����ҳ���������


// CIrisIdentityOCXPropPage : �й�ʵ�ֵ���Ϣ������� IrisIdentityOCXPropPage.cpp��

class CIrisIdentityOCXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CIrisIdentityOCXPropPage)
	DECLARE_OLECREATE_EX(CIrisIdentityOCXPropPage)

// ���캯��
public:
	CIrisIdentityOCXPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_IRISIDENTITYOCX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

