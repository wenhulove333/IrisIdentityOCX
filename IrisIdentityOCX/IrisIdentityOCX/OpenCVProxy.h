#pragma once
#include "opencv2/opencv.hpp"

using namespace cv;

class COpenCVProxy
{
public:
	COpenCVProxy();
	~COpenCVProxy();

	static int mat2Binary(const Mat img, uchar* data);
	static int binary2Mat(const uchar *data, int width, int height, Mat& img);
};

