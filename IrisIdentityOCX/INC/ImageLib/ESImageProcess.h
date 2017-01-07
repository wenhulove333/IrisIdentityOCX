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

///ͼ����ROI����
typedef struct  IMG_ROI_RECT
{
	int nX;           ///< �����������Ͻ�ˮƽ����
	int nY;           ///< �����������ϽǴ�ֱ����
	int nWidth;       ///< ��������Ŀ�
	int nHeight;      ///< ��������ĸ�
}IMG_ROI_RECT;

///ͼ����ת����
typedef enum IMAGE_MIRROR_MODE
{
	HORIZONTAL_MIRROR = 0,     ///< ˮƽ����
	VERTICAL_MIRROR   = 1      ///< ��ֱ����
}em_IMAGE_MIRROR_MODE;

///ͼ���ʽ
typedef enum IMG_TYPE
{
	IMAGE_RGB24 = 0,    ///< RGBͼ��
	IMAGE_GRAY  = 1     ///< 8λ�Ҷ�ͼ��
}IMG_TYPE;

///���ŷ���ѡ��
typedef enum RESIZE_METHOD
{
	SCALE_BILINEAR = 0,   ///< ˫���Բ�ֵ
	SCALE_BICUBIC  = 1    ///< ˫���β�ֵ
}RESIZE_METHOD;


///ͼ����״̬��
typedef enum IMG_STATUS
{
	IMG_STATUS_OK                       =  0,    ///< ִ�гɹ�
	IMG_STATUS_PARAMETER_INVALID        = -1,    ///< ������Ч
	IMG_STATUS_PARAMETER_OUT_OF_BOUND   = -2,    ///< ����Խ��
	IMG_STATUS_NOT_ENOUGH_SYSTEM_MEMORY = -3,    ///< ϵͳ�ڴ治��
	IMG_STATUS_NOT_SUPPORTED            = -4     ///< ��֧�ֵķ�ʽ 
}em_IMG_STATUS;


//---------------------------------------------------------------
/**
\brief	 ��ȡԴͼ����ROI������ͼ��
\param   pSrcImg                  [in]������������
\param   nWidth                   [in]ͼ����
\param   nHeight                  [in]ͼ��߶�
\param   pRect                    [in]ROI����
\param   pROIImage                [out]ROI����ͼ��

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESGetROIImage(unsigned char *pSrcImg, int nWidth, int nHeight, IMG_ROI_RECT *pRect, unsigned char *pROIImage);


//-------------------------------------------------------------
/**
\brief  ͼ����ת��������֧��8λRawͼ���8λ�ڰ�ͼ�� 
\param  pInputBuff   	[in] ����ͼ�񻺳�������������СΪW*H�ֽڣ�
\param  pOutputBuf      [out]���ͼ�񻺳�������������СΪW*H�ֽڣ�
\param  nWidth          [in] ͼ����
\param  nHeight         [in] ͼ��߶�
\param  emMirrorMode    [in] ͼ����ģʽ

\return  ״̬����
*/
//-------------------------------------------------------------
int ESDECL ESImageMirror(unsigned char *pInputBuf, unsigned char *pOutputBuf, int nWidth, int nHeight, em_IMAGE_MIRROR_MODE emImageMirrorMode);

//---------------------------------------------------------------
/**
\brief	 ��RGBͼ��ת���ɻҶ�ͼ��
\param   pRgbBuf                  [in]���RGBͼ�񣬳���ΪnWidth * nHeight * 3
\param   nWidth                   [in]ͼ����
\param   nHeight                  [in]ͼ��߶�
\param   pGrayBuf                 [out]�Ҷ�ͼ��,����ΪnWidth * nHeight

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESRgbToGray(unsigned char *pRgbBuf, int nWidth, int nHeight, unsigned char *pGrayBuf);

//------------------------------------------------
/**
\brief  8λͼ��˳ʱ����ת90��
\param  pInputBuffer  	[in]����ͼ�񻺳���
\param  pOutputBuffer	[out]���ͼ�񻺳�����new buffer��  
\param  nWidth        	[in]ͼ����
\param  nHeight       	[in]ͼ��߶�

return  emStatus
*/
//------------------------------------------------
int ESDECL ESRotate90CW8B(unsigned char *pInputBuf, unsigned char *pOutputBuf, int nWidth, int nHeight);

//------------------------------------------------
/**
\brief  8λͼ����ʱ����ת90��
\param  pInputBuffer    [in] ����ͼ�񻺳���
\param  pOutputBuffer	[out]���ͼ�񻺳�����new buffer��  
\param  nWidth          [in] ͼ����
\param  nHeight         [in] ͼ��߶�

return  status
*/
//------------------------------------------------
int ESDECL ESRotate90CCW8B(unsigned char *pInputBuf, unsigned char *pOutputBuf, int nWidth, int nHeight);

//---------------------------------------------------------------
/**
\brief   ��ͼ�񱣴�ΪBMP��ʽ
\param   pImgData               [in]ͼ������buffer
\param   nWidth                 [in]����ͼ����
\param   nHeight                [in]����ͼ��߶�
\param   emType                 [in]ͼ������
\param   pFileName              [in,out]����ļ�����·��

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESSaveImgToBMP(unsigned char *pImgData, int nWidth, int nHeight, IMG_TYPE emType, const char *pFileName);

//---------------------------------------------------------------
/**
\brief   8λͼ������
\param   pSrcImg                [in]����ͼ��buffer
\param   nWidth                 [in]����ͼ����
\param   nHeight                [in]����ͼ��߶�
\param   emMethod               [in]���ŷ���
\param   nResizeWid             [in]���ź�ͼ��Ŀ�
\param   nResizeHei             [in]���ź�ͼ��ĸ�
\param   pResize                [in,out]s���ź�ͼ��


\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESImageResize(const unsigned char *pSrcImg, int nWidth, int nHeight, RESIZE_METHOD emMethod, int nResizeWid, int nResizeHei, unsigned char *pResizeImg);

#ifdef __cplusplus
}

#endif
#endif