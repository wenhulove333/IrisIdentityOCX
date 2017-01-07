#include "stdafx.h"
#include "FrameInfo.h"


CFrameInfo::CFrameInfo()
{
}

CFrameInfo::CFrameInfo(Mat* mat, CHAR* cameraType, ENUM_MODE mode) {
	this->mat = mat;
	this->cameraType = cameraType;
	this->mode = mode;
}

CFrameInfo::~CFrameInfo()
{
	if (NULL != this->mat) {
		delete this->mat;
	}
}

Mat* CFrameInfo::getMat() {
	return this->mat;
}

CHAR* CFrameInfo::getCameraType() {
	return this->cameraType;
}

ENUM_MODE CFrameInfo::getMode() {
	return this->mode;
}