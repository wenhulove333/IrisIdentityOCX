#include "stdafx.h"
#include "Image2DC.h"


CImage2DC::CImage2DC()
{
}


CImage2DC::~CImage2DC()
{
}

//************************************
// 函数名称:    ConvertMat2CImage
// 访问权限:    public 
// 创建日期:    2017/01/05
// 创 建 人:	    
// 函数说明:    将cv::Mat类型的图像数据转换为CImage类型的数据
// 函数参数:    const cv::Mat & src_img 输入的cv::Mat图像数据
// 函数参数:    CImage & dst_img			转换之后的CImage类型
// 返 回 值:    BOOL
//************************************
BOOL CImage2DC::ConvertMats2CImage(const cv::Mat& src_img, CImage& dst_img)
{
	if (!src_img.data)
	{
		return FALSE;
	}
	int width = src_img.cols;			//获取输入图像的宽度
	int height = src_img.rows;			//获取输入图像的高度
	int channels = src_img.channels();	//获取输入图像的
	int src_type = src_img.type();

	dst_img.Destroy();

	switch (src_type)
	{
	case CV_8UC1:
	{
		dst_img.Create(width, height, 8 * channels * 3);
		unsigned char* dst_data = static_cast<unsigned char*>(dst_img.GetBits());
		int step_size = dst_img.GetPitch();		//获取位图行与行之间相差的字节数
		unsigned char* src_data = nullptr;
		for (int i = 0; i < height; i++)
		{
			src_data = const_cast<unsigned char*>(src_img.ptr<unsigned char>(i));	//获取行指针
			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					*(dst_data + step_size*i + j * 3 + k) = *src_data;
				}
				src_data++;
			}
		}
		break;
	}
	case CV_8UC3:
	{
		dst_img.Create(width, height, 8 * channels);
		unsigned char* dst_data = static_cast<unsigned char*>(dst_img.GetBits());
		int step_size = dst_img.GetPitch();		//获取位图行与行之间相差的字节数
		unsigned char* src_data = nullptr;
		for (int i = 0; i < height; i++)
		{
			src_data = const_cast<unsigned char*>(src_img.ptr<unsigned char>(i));	//获取行指针
			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					*(dst_data + step_size*i + j * 3 + k) = src_data[3 * j + k];
				}
			}
		}
		break;
	}
	default:
		MessageBox(NULL, _T("输入的图像类型出错"), _T("提示"), MB_ICONINFORMATION | MB_OK);
		break;
	}

	return TRUE;
}

//************************************
// 函数名称:    GetFixMat
// 访问权限:    private 
// 创建日期:    2017/01/05
// 创 建 人:	    
// 函数说明:    将输入图像调整到适合在DC所指向的窗口上显示
// 函数参数:    const cv::Mat & src_img		输入图像
// 函数参数:    cv::Mat & dst_img			输出图像
// 函数参数:    unsigned int dc_heigh		DC所指向窗口的高度
// 函数参数:    unsigned int dc_width		DC所指向窗口的宽度
// 返 回 值:    BOOL
//************************************
BOOL CImage2DC::GetFixMat(const cv::Mat& src_img, cv::Mat& dst_img, unsigned int dc_heigh, unsigned int dc_width)
{
	if (!src_img.data)
	{
		return FALSE;
	}
	unsigned int img_rows(src_img.rows);
	unsigned int img_cols(src_img.cols);
	unsigned int fix_heigh(std::min(img_rows, dc_heigh));
	unsigned int fix_width(std::min(img_cols, dc_width));

	float ratio_w = static_cast<float>(fix_width) / static_cast<float>(img_cols);
	float ratio_h = static_cast<float>(fix_heigh) / static_cast<float>(img_rows);
	float ratio = std::min(ratio_w, ratio_h);

	int show_width = static_cast<unsigned int>(ratio * img_cols);
	int show_height = static_cast<unsigned int>(ratio * img_rows);

	cv::resize(src_img, dst_img, cv::Size(show_width, show_height), (0.0), (0.0), cv::INTER_LINEAR);

	return TRUE;
}

//************************************
// 函数名称:    Show2DC
// 访问权限:    public static 
// 创建日期:    2017/01/05
// 创 建 人:	    
// 函数说明:    将Mat数据类型的图像像是在DC指向的窗口上
// 函数参数:    const cv::Mat & img				输入图像数据
// 函数参数:    HDC dst_hdc						输出图像数据
// 函数参数:    const unsigned int dc_heigh		DC所指向窗口的高度
// 函数参数:    const unsigned int dc_width		DC所指向窗口的宽度
// 返 回 值:    BOOL
//************************************
BOOL CImage2DC::Show2DC(const cv::Mat& img, HDC dst_hdc, const unsigned int dc_heigh, const unsigned int dc_width)
{
	if (!img.data)
	{
		return FALSE;
	}
	CImage dst_img;
	cv::Mat temp;	//定义中间变量
	this->GetFixMat(img, temp, dc_heigh, dc_width);	//图像的几何大小变换
	this->ConvertMats2CImage(temp, dst_img);			//图像转换
	int offsetx = (dc_width - temp.cols) / 2;			//调整偏移量
	int offsety = (dc_heigh - temp.rows) / 2;
	BOOL temp1 = dst_img.Draw(dst_hdc, offsetx, offsety, dst_img.GetWidth(), dst_img.GetHeight());	//图像显示

	return TRUE;
}