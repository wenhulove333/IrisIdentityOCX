#include "stdafx.h"
#include "IrisIdentity.h"
#include "ImageLib/ESImageProcess.h"

int CIrisIdentity::MAXFRAMESINQUEUE = 1;

CIrisIdentity::CIrisIdentity()
{
}

CIrisIdentity::CIrisIdentity(int cameraID) {
	this->cameraID = cameraID;
	returnInfos = new queue<CIrisIdentityReturnInfo*>();
	frameInfos = new queue<CFrameInfo*>();
}

CIrisIdentity::~CIrisIdentity()
{
	TerminateThread(pThread, 0);
	while (!returnInfos->empty()) {
		CIrisIdentityReturnInfo* returnInfo = returnInfos->front();
		delete returnInfo;
		returnInfos->pop();
	}
	while (!frameInfos->empty()) {
		CFrameInfo* frameInfo = frameInfos->front();
		delete frameInfo;
		returnInfos->pop();
	}
	delete returnInfos;
	delete frameInfos;
}

void CIrisIdentity::irisIdentifyEntry(LPVOID n) {
	PreviewImageInfo_t* imageInfo = NULL;
	CFrameInfo* frameInfo = frameInfos->front();
	Mat* frame = frameInfo->getMat();

	int channels = frame->channels();

	uchar* data = new uchar[frame->rows * frame->cols * channels];
	COpenCVProxy::mat2Binary(*frame, data);

	uchar* greyData = new uchar[frame->rows * frame->cols];

	ESRgbToGray(data, frame->cols, frame->rows, greyData);

	EyePos_t* eyePos = (EyePos_t*)malloc(sizeof(EyePos_t));
	if (NULL == eyePos) {
		goto endRelease;
	}

	imageInfo = (PreviewImageInfo_t*)malloc(sizeof(PreviewImageInfo_t));
	if (NULL == imageInfo) {
		free(eyePos);
		goto endRelease;
	}

	imageInfo->pbyData = greyData;
	imageInfo->nWidth = frame->cols;
	imageInfo->nHeight = frame->rows;

	if (!getIrisInfo(frameInfo, imageInfo)) {
		//goto endRelease;
	}

	getIrisTemplates(frameInfo, imageInfo);
	

endRelease:
	if (NULL != imageInfo) {
		free(imageInfo);
	}
	delete[] data;
	delete[] greyData;
	return;
}

bool CIrisIdentity::getIrisInfo(CFrameInfo* frameInfo, PreviewImageInfo_t* imageInfo) {
	CIrisIdentityReturnInfo* returnInfo = new CIrisIdentityReturnInfo();
	if (NULL == returnInfo) {
		return false;
	}

	EyePos_t eyePos;

	int errorCode = MAG_GetIrisInfo(frameInfo->getCameraType(), imageInfo, frameInfo->getMode(), &eyePos, NULL);
	if (errorCode != 0)
	{
		returnInfo->setInfoReadable(irisIdentityInfo.getReadableInfoForCallIrisInfoSDK(errorCode));
		returnInfos->push(returnInfo);
		return false;
	}
	else
	{
		if (eyePos.leftEyePos == EYE_POS_SUITABLE && eyePos.rightEyePos == EYE_POS_SUITABLE)
		{
			
		}

		else if (eyePos.leftEyePos == EYE_POS_TOO_FAR || eyePos.rightEyePos == EYE_POS_TOO_FAR)
		{
			returnInfo->setInfoReadable(L"left or right eys too far");
			returnInfos->push(returnInfo);
			return false;
		}
		else if (eyePos.leftEyePos == EYE_POS_TOO_NEAR || eyePos.rightEyePos == EYE_POS_TOO_NEAR)
		{
			returnInfo->setInfoReadable(L"left or right eys too near");
			returnInfos->push(returnInfo);
			return false;
		}
	}

	returnInfo->setInfoReadable(L"left or right eye both good");
	returnInfos->push(returnInfo);
	return true;
}

void CIrisIdentity::getIrisTemplates(CFrameInfo* frameInfo, PreviewImageInfo_t* imageInfo) {
	CIrisIdentityReturnInfo* returnInfo = new CIrisIdentityReturnInfo();
	if (NULL == returnInfo) {
		return;
	}

	EyePos_t eyePos;

	IrisTemplates_t* irisTemplates = (IrisTemplates_t*)malloc(sizeof(IrisTemplates_t));
	if (NULL == irisTemplates) {
		delete returnInfo;
		return;
	}

	int errorCode = MAG_GetIrisTemplates(frameInfo->getCameraType(), imageInfo, irisTemplates, frameInfo->getMode(), &eyePos, NULL);

	if (errorCode != 0)
	{
		returnInfo->setInfoReadable(irisIdentityInfo.getReadableInfoForCallIrisInfoSDK(errorCode));
		returnInfos->push(returnInfo);
	}
	else
	{
		if (frameInfo->getMode() == MODE_ENROLL && (eyePos.leftEyePos == EYE_POS_SUITABLE && eyePos.rightEyePos == EYE_POS_SUITABLE))
		{
			validIrisTemplatesVec.push_back(irisTemplates);
			if (validIrisTemplatesVec.size() == 5) {
				returnInfo->setInfoReadable(L"template is euqal to 5.");
			}
			else {
				returnInfo->setInfoReadable(L"template is less than 5.");
			}
			returnInfos->push(returnInfo);
			CIrisIdentity::MAXFRAMESINQUEUE = 0;
			return;
		}
		else if (frameInfo->getMode() == MODE_MATCH && (eyePos.leftEyePos == EYE_POS_SUITABLE || eyePos.rightEyePos == EYE_POS_SUITABLE))
		{
			bool result = this->localStorage.compareTemplates(L"test", frameInfo->getCameraType(), irisTemplates, NULL);
			if (result) {
				returnInfo->setInfoReadable(L"Match Procedure: match.");
			}
			else {
				returnInfo->setInfoReadable(L"Match Procedure: can't match.");
			}
			
			returnInfos->push(returnInfo);
		}
		else
		{
			returnInfo->setInfoReadable(L"others");
			returnInfos->push(returnInfo);
		}
	}

	free(irisTemplates);
}

void CIrisIdentity::setCameraID(int id) {
	this->cameraID = id;
}

int CIrisIdentity::getCameraID() {
	return this->cameraID;
}

void CIrisIdentity::setThread(CWinThread* pThread) {
	this->pThread = pThread;
}

CWinThread* CIrisIdentity::getThread() {
	return this->pThread;
}

queue<CIrisIdentityReturnInfo*>*  CIrisIdentity::getReturnInfos() {
	return returnInfos;
}

queue<CFrameInfo*>* CIrisIdentity::getFrameInfos() {
	return frameInfos;
}

void CIrisIdentity::setHWND(HWND hWnd) {
	this->hWnd = hWnd;
}

HWND CIrisIdentity::getHWND() {
	return this->hWnd;
}

vector<IrisTemplates_t*>& CIrisIdentity::getValidIrisTemplatesVec() {
	return this->validIrisTemplatesVec;
}

CLocalStorage& CIrisIdentity::getLocalStorage() {
	return this->localStorage;
}