// CameraShowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IrisIdentityOCX.h"
#include "CameraShowDlg.h"
#include "afxdialogex.h"
#include "CommonUtils.h"

VideoCapture * capture = NULL;
CWinThread* captureThread = NULL;
CRect rect;
CDC *pDC;
HDC hDC;
CWnd *pwnd;

CvVideoWriter* writer = 0;

vector<CIrisIdentity*>* CCameraShowDlg::irisIdentityProcesses = new vector<CIrisIdentity*>();
bool CCameraShowDlg::isExitCaptureThread = false;

#define WM_USER_MSG (WM_USER + 1)
#define WM_USER_FRAME_CAPTURE_MSG (WM_USER + 2)

#define CIRISIDENTITY_CAMERA_NO (1)

// CCameraShowDlg 对话框

IMPLEMENT_DYNAMIC(CCameraShowDlg, CDialogEx)

CCameraShowDlg::CCameraShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAMERASHOWDLG, pParent)
{

}

CCameraShowDlg::~CCameraShowDlg()
{
}

void CCameraShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCameraShowDlg, CDialogEx)
	ON_WM_TIMER()
	ON_COMMAND(IDCLOSE, &CCameraShowDlg::OnIdclose)
	ON_MESSAGE(WM_USER_MSG, &CCameraShowDlg::OnUserMsg)
	ON_MESSAGE(WM_USER_FRAME_CAPTURE_MSG, &CCameraShowDlg::OnUserFrameCaptureMsg)
END_MESSAGE_MAP()


// CCameraShowDlg 消息处理程序

void CCameraShowDlg::startEnroll()
{
	capture = new VideoCapture(CIRISIDENTITY_CAMERA_NO);

	if (!capture)
	{
		return;
	}

	if (!capture->isOpened())
	{
		return;
	}

	capture->set(CV_CAP_PROP_FRAME_WIDTH, 1920);
	capture->set(CV_CAP_PROP_FRAME_HEIGHT, 1080);

	isExitCaptureThread = false;

	captureThread = AfxBeginThread(captureFrameFunc, this->GetSafeHwnd());
	if (NULL == captureThread) {
		return;
	}
}

void CCameraShowDlg::endEnroll() {
	if (NULL != captureThread) {
		isExitCaptureThread = true;
		::WaitForSingleObject(captureThread, INFINITE);
		captureThread = NULL;
	}

	if (NULL != capture) {
		capture->release();
		capture = NULL;
	}
}

void CCameraShowDlg::saveIrisTemplates() //save teTempaltempaltes
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	for (i = 0; i < 5; i++)
	{
		int index = i;
		wchar_t szFileName[512];

		wsprintf(szFileName, L"%s\\OUTPUT\\%d_EYE_L_T.BIN", currentExecuteDirectory, index);
		DeleteFileW(szFileName);
		wsprintf(szFileName, L"%s\\OUTPUT\\%d_EYE_L_M.BIN", currentExecuteDirectory, index);
		DeleteFileW(szFileName);

		wsprintf(szFileName, L"%s\\OUTPUT\\%d_EYE_R_T.BIN", currentExecuteDirectory, index);
		DeleteFileW(szFileName);
		wsprintf(szFileName, L"%s\OU\TPUT\\%d_EYE_R_M.BIN", currentExecuteDirectory, index);
		DeleteFileW(szFileName);
	}

	CIrisIdentity* irisIdentity = getIrisIdentityByCameraID(CIRISIDENTITY_CAMERA_NO);

	vector<IrisTemplates_t*>* validIrisTemplates = &irisIdentity->getValidIrisTemplatesVec();

	int index = 0;

	for (vector<IrisTemplates_t*>::iterator iter = validIrisTemplates->begin();
		iter != validIrisTemplates->end(); iter++)
	{
		wchar_t fileName[512];

		if ((*iter)->bLeftValid) {
			wsprintf(fileName, L"%s\\OUTPUT\\%d_EYE_L_T.BIN", currentExecuteDirectory, index);
			CCommonUtils::SaveFile(fileName, (*iter)->leftEye.byTemplate, IRIS_TEMPLATE_SIZE);
			wsprintf(fileName, L"%s\\OUTPUT\\%d_EYE_L_M.BIN", currentExecuteDirectory, index);
			CCommonUtils::SaveFile(fileName, (*iter)->leftEye.byMask, IRIS_TEMPLATE_SIZE);
		}

		if ((*iter)->bRightValid) {
			wsprintf(fileName, L"%s\\OUTPUT\\%d_EYE_R_T.BIN", currentExecuteDirectory, index);
			CCommonUtils::SaveFile(fileName, (*iter)->rightEye.byTemplate, IRIS_TEMPLATE_SIZE);
			wsprintf(fileName, L"%s\\OUTPUT\\%d_EYE_R_M.BIN", currentExecuteDirectory, index);
			CCommonUtils::SaveFile(fileName, (*iter)->rightEye.byMask, IRIS_TEMPLATE_SIZE);
		}

		index++;

		free(*iter);
	}

	validIrisTemplates->clear();
}

BOOL CCameraShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pwnd = GetDlgItem(IDC_ShowImage);
	pDC = pwnd->GetDC();
	hDC = pDC->GetSafeHdc();
	pwnd->GetClientRect(&rect);

	createIrisIdentityThread(CIRISIDENTITY_CAMERA_NO);

	GetCurrentDirectoryW(255, currentExecuteDirectory);
	SetDlgItemText(IDC_RETURNINFO, currentExecuteDirectory);

	wchar_t* connStr = CCommonUtils::joinWString(currentExecuteDirectory, L"\\OUTPUT", L"/0");
	CreateDirectory(connStr, NULL);
	free(connStr);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CCameraShowDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}


void CCameraShowDlg::OnIdclose()
{
	// TODO: 在此添加命令处理程序代码
	if (NULL != captureThread) {
		isExitCaptureThread = true;
		::WaitForSingleObject(captureThread, INFINITE);
		captureThread = NULL;
	}

	if (NULL != capture) {
		capture->release();
		capture = NULL;
	}

	CDialogEx::OnClose();
}

LRESULT CCameraShowDlg::OnUserMsg(WPARAM wp, LPARAM lp) {
	CIrisIdentityReturnInfo* returnInfo = (CIrisIdentityReturnInfo*)wp;

	SetDlgItemText(IDC_RETURNINFO, returnInfo->getInfoReadable());

	delete returnInfo;

	return 1L;
}

LRESULT CCameraShowDlg::OnUserFrameCaptureMsg(WPARAM wp, LPARAM lp) {
	Mat* frame = (Mat*)wp;

	handleFrame(frame);

	return 1L;
}

UINT CCameraShowDlg::threadFunc(LPVOID n) {
	CIrisIdentity* irisIdentity = (CIrisIdentity*)n;

	while (true) {
		if (!irisIdentity->getReturnInfos()->empty()) {
			CIrisIdentityReturnInfo* returnInfo = irisIdentity->getReturnInfos()->front();
			::PostMessage(irisIdentity->getHWND(), WM_USER_MSG, WPARAM(returnInfo), LPARAM(0));
			irisIdentity->getReturnInfos()->pop();
		}

		if (irisIdentity->getFrameInfos()->empty()) {
			Sleep(30);
		}
		else {
			irisIdentity->irisIdentifyEntry(n);

			CFrameInfo* frameInfo = irisIdentity->getFrameInfos()->front();
			delete frameInfo;
			irisIdentity->getFrameInfos()->pop();
		}
	}
}

UINT CCameraShowDlg::captureFrameFunc(LPVOID n) {
	HWND hWnd = (HWND)n;
	while (true) {
		Mat* frame = new Mat();
		*capture >> *frame;
		waitKey(30);
		::PostMessage(hWnd, WM_USER_FRAME_CAPTURE_MSG, WPARAM(frame), LPARAM(0));

		if (isExitCaptureThread) {
			break;
		}
	}

	return 1L;
}

void CCameraShowDlg::createIrisIdentityThread(int cameraID) {
	CIrisIdentity* irisIdentity = new CIrisIdentity(cameraID);
	irisIdentity->setHWND(this->GetSafeHwnd());

	CWinThread* thread = AfxBeginThread(threadFunc, irisIdentity);
	if (NULL == thread) {
		return;
	}

	irisIdentity->setThread(thread);

	irisIdentityProcesses->push_back(irisIdentity);
}

void CCameraShowDlg::commitFrame(int cameraID, CFrameInfo *frameInfo) {
	for (size_t i = 0; i < irisIdentityProcesses->size(); i++) {
		if (irisIdentityProcesses->at(i)->getCameraID() == cameraID
			&& irisIdentityProcesses->at(i)->getFrameInfos()->size() < CIrisIdentity::MAXFRAMESINQUEUE) {
			irisIdentityProcesses->at(i)->getFrameInfos()->push(frameInfo);
		}
		else {
			delete frameInfo;
		}
	}
}

void CCameraShowDlg::handleFrame(Mat* frame) {
	CImage2DC image2DC;
	image2DC.Show2DC(*frame, hDC, rect.Height(), rect.Width());

	CFrameInfo* frameInfo = new CFrameInfo(frame, CAM_EQII_30_34_28_38, MODE_ENROLL);

	commitFrame(1, frameInfo);
}

CIrisIdentity* CCameraShowDlg::getIrisIdentityByCameraID(int cameraID) {
	for (size_t i = 0; i < irisIdentityProcesses->size(); i++) {
		if (irisIdentityProcesses->at(i)->getCameraID() == cameraID) {
			return irisIdentityProcesses->at(i);
		}
	}

	return NULL;
}