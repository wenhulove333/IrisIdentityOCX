#pragma once

// IrisIdentityOCXPropPage.h : CIrisIdentityOCXPropPage 属性页类的声明。


// CIrisIdentityOCXPropPage : 有关实现的信息，请参阅 IrisIdentityOCXPropPage.cpp。

class CIrisIdentityOCXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CIrisIdentityOCXPropPage)
	DECLARE_OLECREATE_EX(CIrisIdentityOCXPropPage)

// 构造函数
public:
	CIrisIdentityOCXPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_IRISIDENTITYOCX };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

