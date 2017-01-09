#pragma once
#include "Image2DC.h"
#include "OpenCVProxy.h"
#include "opencv2/opencv.hpp"
#include "ImageLib/ESImageProcess.h"
#include "IrisIdentity.h"
#include "IrisIdentityInfo.h"

// CCameraShowDlg 对话框

class CCameraShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCameraShowDlg)

public:
	CCameraShowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraShowDlg();

// 对话框数据
	enum { IDD = IDD_CAMERASHOWDLG };

	static vector<CIrisIdentity*>* irisIdentityProcesses;
	static bool isExitCaptureThread;

	CBrush returnInfoBrush;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnUserMsg(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnUserFrameCaptureMsg(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnUserGetValidIrisTemplatesSucc(WPARAM wp, LPARAM lp);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnIdclose();

	void createIrisIdentityThread(int cameraID);
	static UINT captureFrameFunc(LPVOID n);

	static UINT threadFunc(LPVOID n);
	static void commitFrame(int cameraID, CFrameInfo *frameInfo);

	CIrisIdentity* getIrisIdentityByCameraID(int cameraID);

	void startIrisIdentity(ENUM_MODE mode);
	void endIrisIdentity();
	void saveIrisTemplates(wchar_t* name);
	void restoreEntrolledIrisTemplatesFromLocalStorage(wchar_t* path);

private:
	wchar_t currentExecuteDirectory[255];

	void handleFrame(Mat* frame, ENUM_MODE mode);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
