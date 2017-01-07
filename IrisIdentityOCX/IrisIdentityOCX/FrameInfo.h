#pragma once
#include "stdafx.h"
#include "Magpie\MagpieApi.h"
#include "opencv2/opencv.hpp"
using namespace cv;

class CFrameInfo
{
private:
	Mat* mat;
	CHAR* cameraType;
	ENUM_MODE mode;

public:
	CFrameInfo();
	CFrameInfo(Mat* mat, CHAR* cameraType, ENUM_MODE mode);
	~CFrameInfo();

	Mat* getMat();
	CHAR* getCameraType();
	ENUM_MODE getMode();
};

