#include "stdafx.h"
#include "Image2DC.h"


CImage2DC::CImage2DC()
{
}


CImage2DC::~CImage2DC()
{
}

//************************************
// ��������:    ConvertMat2CImage
// ����Ȩ��:    public 
// ��������:    2017/01/05
// �� �� ��:	    
// ����˵��:    ��cv::Mat���͵�ͼ������ת��ΪCImage���͵�����
// ��������:    const cv::Mat & src_img �����cv::Matͼ������
// ��������:    CImage & dst_img			ת��֮���CImage����
// �� �� ֵ:    BOOL
//************************************
BOOL CImage2DC::ConvertMats2CImage(const cv::Mat& src_img, CImage& dst_img)
{
	if (!src_img.data)
	{
		return FALSE;
	}
	int width = src_img.cols;			//��ȡ����ͼ��Ŀ��
	int height = src_img.rows;			//��ȡ����ͼ��ĸ߶�
	int channels = src_img.channels();	//��ȡ����ͼ���
	int src_type = src_img.type();

	dst_img.Destroy();

	switch (src_type)
	{
	case CV_8UC1:
	{
		dst_img.Create(width, height, 8 * channels * 3);
		unsigned char* dst_data = static_cast<unsigned char*>(dst_img.GetBits());
		int step_size = dst_img.GetPitch();		//��ȡλͼ������֮�������ֽ���
		unsigned char* src_data = nullptr;
		for (int i = 0; i < height; i++)
		{
			src_data = const_cast<unsigned char*>(src_img.ptr<unsigned char>(i));	//��ȡ��ָ��
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
		int step_size = dst_img.GetPitch();		//��ȡλͼ������֮�������ֽ���
		unsigned char* src_data = nullptr;
		for (int i = 0; i < height; i++)
		{
			src_data = const_cast<unsigned char*>(src_img.ptr<unsigned char>(i));	//��ȡ��ָ��
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
		MessageBox(NULL, _T("�����ͼ�����ͳ���"), _T("��ʾ"), MB_ICONINFORMATION | MB_OK);
		break;
	}

	return TRUE;
}

//************************************
// ��������:    GetFixMat
// ����Ȩ��:    private 
// ��������:    2017/01/05
// �� �� ��:	    
// ����˵��:    ������ͼ��������ʺ���DC��ָ��Ĵ�������ʾ
// ��������:    const cv::Mat & src_img		����ͼ��
// ��������:    cv::Mat & dst_img			���ͼ��
// ��������:    unsigned int dc_heigh		DC��ָ�򴰿ڵĸ߶�
// ��������:    unsigned int dc_width		DC��ָ�򴰿ڵĿ��
// �� �� ֵ:    BOOL
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
// ��������:    Show2DC
// ����Ȩ��:    public static 
// ��������:    2017/01/05
// �� �� ��:	    
// ����˵��:    ��Mat�������͵�ͼ��������DCָ��Ĵ�����
// ��������:    const cv::Mat & img				����ͼ������
// ��������:    HDC dst_hdc						���ͼ������
// ��������:    const unsigned int dc_heigh		DC��ָ�򴰿ڵĸ߶�
// ��������:    const unsigned int dc_width		DC��ָ�򴰿ڵĿ��
// �� �� ֵ:    BOOL
//************************************
BOOL CImage2DC::Show2DC(const cv::Mat& img, HDC dst_hdc, const unsigned int dc_heigh, const unsigned int dc_width)
{
	if (!img.data)
	{
		return FALSE;
	}
	CImage dst_img;
	cv::Mat temp;	//�����м����
	this->GetFixMat(img, temp, dc_heigh, dc_width);	//ͼ��ļ��δ�С�任
	this->ConvertMats2CImage(temp, dst_img);			//ͼ��ת��
	int offsetx = (dc_width - temp.cols) / 2;			//����ƫ����
	int offsety = (dc_heigh - temp.rows) / 2;
	BOOL temp1 = dst_img.Draw(dst_hdc, offsetx, offsety, dst_img.GetWidth(), dst_img.GetHeight());	//ͼ����ʾ

	return TRUE;
}