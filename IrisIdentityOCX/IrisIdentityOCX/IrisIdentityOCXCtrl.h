#pragma once
#include "TestDlg.h"
#include "CameraShowDlg.h"

// IrisIdentityOCXCtrl.h : CIrisIdentityOCXCtrl ActiveX 控件类的声明。


// CIrisIdentityOCXCtrl : 有关实现的信息，请参阅 IrisIdentityOCXCtrl.cpp。

class CIrisIdentityOCXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CIrisIdentityOCXCtrl)

// 构造函数
public:
	CIrisIdentityOCXCtrl();
	CCameraShowDlg cameraShowDlg;

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CIrisIdentityOCXCtrl();

	DECLARE_OLECREATE_EX(CIrisIdentityOCXCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CIrisIdentityOCXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CIrisIdentityOCXCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CIrisIdentityOCXCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidendMatch = 5L,
		dispidstartMatch = 4L,
		dispidsaveIrisTemplates = 3L,
		dispidendEnroll = 2L,
		dispidstartEnroll = 1L
	};
protected:
	void startEnroll();
	void endEnroll();
	void saveIrisTemplates();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	void startMatch();
	void endMatch();
};

