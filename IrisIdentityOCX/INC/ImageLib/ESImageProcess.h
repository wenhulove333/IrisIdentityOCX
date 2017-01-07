//-----------------------------------------------------------
/**
\file     ESImageProcess.h
\brief    Image Process Library.
\version  v1.0.1512.9151
\date     2015-12-15
\author   Algorithm Department
<p>Copyright (c) 2015-2020 Beijing EyeSmart Technology </p>
*/
//----------------------------------------------------------

#if !defined(ESIMAGEPROCESS_H)
#define ESIMAGEPROCESS_H                ///< pre-compiled macro define

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include "stdafx.h"
#define ESDECL  __stdcall

#else
#include <stdlib.h>
#include <string.h>
#define ESDECL
#endif

///图像处理ROI区域
typedef struct  IMG_ROI_RECT
{
	int nX;           ///< 矩形区域左上角水平坐标
	int nY;           ///< 矩形区域左上角垂直坐标
	int nWidth;       ///< 矩形区域的宽
	int nHeight;      ///< 矩形区域的高
}IMG_ROI_RECT;

///图像镜像翻转类型
typedef enum IMAGE_MIRROR_MODE
{
	HORIZONTAL_MIRROR = 0,     ///< 水平镜像
	VERTICAL_MIRROR   = 1      ///< 垂直镜像
}em_IMAGE_MIRROR_MODE;

///图像格式
typedef enum IMG_TYPE
{
	IMAGE_RGB24 = 0,    ///< RGB图像
	IMAGE_GRAY  = 1     ///< 8位灰度图像
}IMG_TYPE;

///缩放方法选择
typedef enum RESIZE_METHOD
{
	SCALE_BILINEAR = 0,   ///< 双线性插值
	SCALE_BICUBIC  = 1    ///< 双三次插值
}RESIZE_METHOD;


///图像处理状态码
typedef enum IMG_STATUS
{
	IMG_STATUS_OK                       =  0,    ///< 执行成功
	IMG_STATUS_PARAMETER_INVALID        = -1,    ///< 参数无效
	IMG_STATUS_PARAMETER_OUT_OF_BOUND   = -2,    ///< 参数越界
	IMG_STATUS_NOT_ENOUGH_SYSTEM_MEMORY = -3,    ///< 系统内存不足
	IMG_STATUS_NOT_SUPPORTED            = -4     ///< 不支持的方式 
}em_IMG_STATUS;


//---------------------------------------------------------------
/**
\brief	 获取源图像中ROI区域子图像
\param   pSrcImg                  [in]输入数据数组
\param   nWidth                   [in]图像宽度
\param   nHeight                  [in]图像高度
\param   pRect                    [in]ROI区域
\param   pROIImage                [out]ROI区域图像

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESGetROIImage(unsigned char *pSrcImg, int nWidth, int nHeight, IMG_ROI_RECT *pRect, unsigned char *pROIImage);


//-------------------------------------------------------------
/**
\brief  图像镜像翻转函数（仅支持8位Raw图像和8位黑白图像） 
\param  pInputBuff   	[in] 输入图像缓冲区（缓冲区大小为W*H字节）
\param  pOutputBuf      [out]输出图像缓冲区（缓冲区大小为W*H字节）
\param  nWidth          [in] 图像宽度
\param  nHeight         [in] 图像高度
\param  emMirrorMode    [in] 图像镜像模式

\return  状态参数
*/
//-------------------------------------------------------------
int ESDECL ESImageMirror(unsigned char *pInputBuf, unsigned char *pOutputBuf, int nWidth, int nHeight, em_IMAGE_MIRROR_MODE emImageMirrorMode);

//---------------------------------------------------------------
/**
\brief	 将RGB图像转换成灰度图像
\param   pRgbBuf                  [in]输出RGB图像，长度为nWidth * nHeight * 3
\param   nWidth                   [in]图像宽度
\param   nHeight                  [in]图像高度
\param   pGrayBuf                 [out]灰度图像,长度为nWidth * nHeight

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESRgbToGray(unsigned char *pRgbBuf, int nWidth, int nHeight, unsigned char *pGrayBuf);

//------------------------------------------------
/**
\brief  8位图像顺时针旋转90度
\param  pInputBuffer  	[in]输入图像缓冲区
\param  pOutputBuffer	[out]输出图像缓冲区（new buffer）  
\param  nWidth        	[in]图像宽度
\param  nHeight       	[in]图像高度

return  emStatus
*/
//------------------------------------------------
int ESDECL ESRotate90CW8B(unsigned char *pInputBuf, unsigned char *pOutputBuf, int nWidth, int nHeight);

//------------------------------------------------
/**
\brief  8位图像逆时针旋转90度
\param  pInputBuffer    [in] 输入图像缓冲区
\param  pOutputBuffer	[out]输出图像缓冲区（new buffer）  
\param  nWidth          [in] 图像宽度
\param  nHeight         [in] 图像高度

return  status
*/
//------------------------------------------------
int ESDECL ESRotate90CCW8B(unsigned char *pInputBuf, unsigned char *pOutputBuf, int nWidth, int nHeight);

//---------------------------------------------------------------
/**
\brief   将图像保存为BMP格式
\param   pImgData               [in]图像数据buffer
\param   nWidth                 [in]输入图像宽度
\param   nHeight                [in]输入图像高度
\param   emType                 [in]图像类型
\param   pFileName              [in,out]输出文件名和路径

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESSaveImgToBMP(unsigned char *pImgData, int nWidth, int nHeight, IMG_TYPE emType, const char *pFileName);

//---------------------------------------------------------------
/**
\brief   8位图像缩放
\param   pSrcImg                [in]输入图像buffer
\param   nWidth                 [in]输入图像宽度
\param   nHeight                [in]输入图像高度
\param   emMethod               [in]缩放方法
\param   nResizeWid             [in]缩放后图像的宽
\param   nResizeHei             [in]缩放后图像的高
\param   pResize                [in,out]s缩放后图像


\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESImageResize(const unsigned char *pSrcImg, int nWidth, int nHeight, RESIZE_METHOD emMethod, int nResizeWid, int nResizeHei, unsigned char *pResizeImg);

#ifdef __cplusplus
}

#endif
#endif