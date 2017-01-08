#pragma once
#include "TestDlg.h"
#include "CameraShowDlg.h"

// IrisIdentityOCXCtrl.h : CIrisIdentityOCXCtrl ActiveX �ؼ����������


// CIrisIdentityOCXCtrl : �й�ʵ�ֵ���Ϣ������� IrisIdentityOCXCtrl.cpp��

class CIrisIdentityOCXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CIrisIdentityOCXCtrl)

// ���캯��
public:
	CIrisIdentityOCXCtrl();
	CCameraShowDlg cameraShowDlg;

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CIrisIdentityOCXCtrl();

	DECLARE_OLECREATE_EX(CIrisIdentityOCXCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CIrisIdentityOCXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CIrisIdentityOCXCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CIrisIdentityOCXCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
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

