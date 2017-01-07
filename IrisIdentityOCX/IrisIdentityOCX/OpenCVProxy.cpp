#include "stdafx.h"
#include "OpenCVProxy.h"


COpenCVProxy::COpenCVProxy()
{
}


COpenCVProxy::~COpenCVProxy()
{
}

//************************************
// ��������:    mat2Binary
// ����Ȩ��:    static public 
// ��������:    2017/01/05
// �� �� ��:	    
// ����˵��:    ��OpenCV����mat��ʾ��ͼ��װ�����ڴ�����
// ��������:    const Mat img	����ͼ��
// ��������:    char* data      �ڴ�����
// �� �� ֵ:    int
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
// ��������:    mat2Binary
// ����Ȩ��:    static public 
// ��������:    2017/01/05
// �� �� ��:	    
// ����˵��:    ��OpenCV����mat��ʾ��ͼ��װ�����ڴ�����
// ��������:    const uchar *data  �ڴ�����
// ��������:    int width  ��
// ��������:    int height ��
// ��������:    Mat& img  mat��ʽ
// �� �� ֵ:    int
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
