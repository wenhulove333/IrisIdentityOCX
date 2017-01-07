#include "stdafx.h"
#include "OpenCVProxy.h"


COpenCVProxy::COpenCVProxy()
{
}


COpenCVProxy::~COpenCVProxy()
{
}

//************************************
// 函数名称:    mat2Binary
// 访问权限:    static public 
// 创建日期:    2017/01/05
// 创 建 人:	    
// 函数说明:    将OpenCV里面mat表示的图像装换成内存序列
// 函数参数:    const Mat img	输入图像
// 函数参数:    char* data      内存序列
// 返 回 值:    int
//************************************
int COpenCVProxy::mat2Binary(const Mat img, uchar* data) {
	int width = img.cols;
	int height = img.rows;
	int channels = img.channels();
	int line_byte = img.cols * channels;
	uchar value;
	Vec3b valueRGB;

	uchar *p = data;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col<width; col++) {
			if (channels == 1) {
				value = img.at<uchar>(row, col);
				data[row * line_byte + col] = value;
			}
			else if (channels == 3) {
				valueRGB = img.at<Vec3b>(row, col);
				data[row * line_byte + col * 3] = valueRGB[0];
				data[row * line_byte + col * 3 + 1] = valueRGB[1];
				data[row * line_byte + col * 3 + 2] = valueRGB[2];
			}
		}
	}
	return 0;
}

//************************************
// 函数名称:    mat2Binary
// 访问权限:    static public 
// 创建日期:    2017/01/05
// 创 建 人:	    
// 函数说明:    将OpenCV里面mat表示的图像装换成内存序列
// 函数参数:    const uchar *data  内存序列
// 函数参数:    int width  宽
// 函数参数:    int height 高
// 函数参数:    Mat& img  mat格式
// 返 回 值:    int
//************************************
int COpenCVProxy::binary2Mat(const uchar *data, int width, int height, Mat& img) {
	int channels = img.channels();
	uchar value;
	Vec3b valueRGB;

	const uchar *p = data;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col<width; col++) {
			if (channels == 3) {
				img.at<Vec3b>(row, col)[0] = p[0];
				img.at<Vec3b>(row, col)[1] = p[1];
				img.at<Vec3b>(row, col)[2] = p[2];
				p += 3;
			}
			else if (channels == 1) {
				img.at<uchar>(row, col) = p[0];
				p += 1;
			}
			else {
				return -1;
			}
		}
	}
	return 0;
}
