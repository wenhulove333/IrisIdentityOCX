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

typedef struct tagCaptureThreadParas
{
	HWND hWnd;
	ENUM_MODE mode;
} CaptureThreadParas_t;

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
	ON_MESSAGE(WM_USER_GET_VALID_IRIS_TEMPLATES_SUCC, &CCameraShowDlg::OnUserGetValidIrisTemplatesSucc)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCameraShowDlg 消息处理程序

void CCameraShowDlg::startIrisIdentity(ENUM_MODE mode)
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

	CaptureThreadParas_t* captureThreadParas = (CaptureThreadParas_t*)malloc(sizeof(CaptureThreadParas_t));
	if (NULL == captureThreadParas) {
		return;
	}

	captureThreadParas->hWnd = GetSafeHwnd();
	captureThreadParas->mode = mode;

	captureThread = AfxBeginThread(captureFrameFunc, captureThreadParas);
	if (NULL == captureThread) {
		free(captureThreadParas);
		return;
	}

	SetDlgItemText(IDC_NUMBER_OF_VALID_IRISTEMPLATES, L"   0");

	CIrisIdentity::MAXFRAMESINQUEUE = 1;
	CIrisIdentity* irisIdentity = getIrisIdentityByCameraID(CIRISIDENTITY_CAMERA_NO);
	if (NULL != irisIdentity) {
		irisIdentity->resetIrisIdentity();
	}

	returnInfoBrush.DeleteObject();
	returnInfoBrush.CreateSolidBrush(RGB(255, 255, 255));
	((CStatic*)GetDlgItem(IDC_RETURNINFO))->RedrawWindow();
}

void CCameraShowDlg::endIrisIdentity() {
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

void CCameraShowDlg::saveIrisTemplates(wchar_t* name) //save teTempaltempaltes
{
	CIrisIdentity* irisIdentity = (CIrisIdentity*)getIrisIdentityByCameraID(CIRISIDENTITY_CAMERA_NO);
	if (NULL != irisIdentity) {
		irisIdentity->getLocalStorage().saveTemplates(currentExecuteDirectory, name, &irisIdentity->getValidIrisTemplatesVec());
		irisIdentity->clearValidIrisTemplatesVec();
	}
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
	restoreEntrolledIrisTemplatesFromLocalStorage(connStr);
	free(connStr);

	returnInfoBrush.DeleteObject();
	returnInfoBrush.CreateSolidBrush(RGB(255, 255, 255));
	((CStatic*)GetDlgItem(IDC_RETURNINFO))->RedrawWindow();

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

	if (0 == StrStrW(returnInfo->getInfoReadable(), L"Match Procedure: match")) {
		returnInfoBrush.DeleteObject();
		returnInfoBrush.CreateSolidBrush(CIRISIDENTITY_PASS_COLOUR);
		((CStatic*)GetDlgItem(IDC_RETURNINFO))->RedrawWindow();
	}

	delete returnInfo;

	return 1L;
}

LRESULT CCameraShowDlg::OnUserFrameCaptureMsg(WPARAM wp, LPARAM lp) {
	Mat* frame = (Mat*)wp;
	ENUM_MODE mode = (ENUM_MODE)lp;

	handleFrame(frame, mode);

	return 1L;
}

LRESULT CCameraShowDlg::OnUserGetValidIrisTemplatesSucc(WPARAM wp, LPARAM lp) {
	wchar_t amounts[IRIS_IDENTITY_COMMON_BUFFER_LEN];

	CIrisIdentity* irisIdentity = (CIrisIdentity*)getIrisIdentityByCameraID(CIRISIDENTITY_CAMERA_NO);
	if (NULL != irisIdentity) {
		int amountsValue = irisIdentity->getValidIrisTemplatesVec().size();

		swprintf_s(amounts, L"   %d", amountsValue);

		SetDlgItemText(IDC_NUMBER_OF_VALID_IRISTEMPLATES, amounts);

		if (5 == amountsValue) {
			returnInfoBrush.DeleteObject();
			returnInfoBrush.CreateSolidBrush(CIRISIDENTITY_PASS_COLOUR);
			((CStatic*)GetDlgItem(IDC_RETURNINFO))->RedrawWindow();
		}
	}

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
	CaptureThreadParas_t* captureThreadParas = (CaptureThreadParas_t*)n;
	while (true) {
		Mat* frame = new Mat();
		*capture >> *frame;
		waitKey(30);
		::PostMessage(captureThreadParas->hWnd, WM_USER_FRAME_CAPTURE_MSG, WPARAM(frame), LPARAM(captureThreadParas->mode));

		if (isExitCaptureThread) {
			free(n);
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

void CCameraShowDlg::handleFrame(Mat* frame, ENUM_MODE mode) {
	CImage2DC image2DC;
	image2DC.Show2DC(*frame, hDC, rect.Height(), rect.Width());

	CFrameInfo* frameInfo = new CFrameInfo(frame, CAM_EQII_30_34_28_38, mode);

	commitFrame(CIRISIDENTITY_CAMERA_NO, frameInfo);
}

CIrisIdentity* CCameraShowDlg::getIrisIdentityByCameraID(int cameraID) {
	for (size_t i = 0; i < irisIdentityProcesses->size(); i++) {
		if (irisIdentityProcesses->at(i)->getCameraID() == cameraID) {
			return irisIdentityProcesses->at(i);
		}
	}

	return NULL;
}

void CCameraShowDlg::restoreEntrolledIrisTemplatesFromLocalStorage(wchar_t* path) {
	CIrisIdentity* irisIdentity = getIrisIdentityByCameraID(CIRISIDENTITY_CAMERA_NO);

	if (NULL != irisIdentity) {
		irisIdentity->getLocalStorage().restorePersonIrisTemplatesFromLocalStorage(path);
	}
}

HBRUSH CCameraShowDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (IDC_RETURNINFO == pWnd->GetDlgCtrlID()) {
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)returnInfoBrush.GetSafeHandle();
	}
	else if (IDC_NUMBER_OF_VALID_IRISTEMPLATES == pWnd->GetDlgCtrlID()) {
		pDC->SetTextColor(CIRISIDENTITY_PASS_COLOUR);
		return hbr;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
