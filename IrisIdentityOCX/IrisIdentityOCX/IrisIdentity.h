#pragma once
#include "afxwin.h"
#include "Magpie\MagpieApi.h"
#include "IrisIdentityReturnInfo.h"
#include "IrisIdentityInfo.h"
#include "LocalStorage.h"
#include "FrameInfo.h"
#include "OpenCVProxy.h"
#include <queue>
#include <vector>
using namespace std;

class CIrisIdentity
{
private:
	CWinThread* pThread; //用来做虹膜注册识别的线程
	HWND hWnd; //主窗口句柄
	CIrisIdentityInfo irisIdentityInfo;
	queue<CIrisIdentityReturnInfo*>* returnInfos;
	queue<CFrameInfo*>* frameInfos;
	vector<IrisTemplates_t*> validIrisTemplatesVec;
	int cameraID;
	CLocalStorage localStorage;

public:
	static int MAXFRAMESINQUEUE;

public:
	CIrisIdentity();
	CIrisIdentity(int cameraID);
	~CIrisIdentity();

	bool getIrisInfo(CFrameInfo* frameInfo, PreviewImageInfo_t* imageInfo);
	void getIrisTemplates(CFrameInfo* frameInfo, PreviewImageInfo_t* imageInfo);

	void irisIdentifyEntry(LPVOID n);

	void setCameraID(int id);
	int getCameraID();

	void setHWND(HWND hWnd);
	HWND getHWND();

	void setThread(CWinThread* pThread);
	CWinThread* getThread();
	
	queue<CIrisIdentityReturnInfo*>* getReturnInfos();
	queue<CFrameInfo*>* getFrameInfos();

	vector<IrisTemplates_t*>& getValidIrisTemplatesVec();

	CLocalStorage& getLocalStorage();
};





