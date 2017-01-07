#pragma once
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace ATL;

class CImage2DC
{
private:
	BOOL GetFixMat(const cv::Mat& src_img, cv::Mat& dst_img, unsigned int dc_heigh, unsigned int dc_width);

public:
	CImage2DC();
	~CImage2DC();

	BOOL ConvertMats2CImage(const cv::Mat& src_img, CImage& dst_img);
	BOOL Show2DC(const cv::Mat& img, HDC dst_hdc, const unsigned int dc_heigh, const unsigned int dc_width);
};

