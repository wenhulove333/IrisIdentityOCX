//-----------------------------------------------------------
/**
\file     EyeMatrix.h
\brief    Iris Recognition Library.
\version  v1.0.1510.9261
\date     2015-10-26
\author   Algorithm Department
<p>Copyright (c) 2015-2020 Beijing EyeSmart Technology </p>
*/
//----------------------------------------------------------

#if !defined(_EYEMATRIX_H)
#define _EYEMATRIX_H                ///< pre-compiled macro define

#define  VERSION_LENGTH       128

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

///���۶�λ����ѡ��
typedef enum EYE_LOCATION_METHOD
{
	EYE_LOCATION_METHOD1   = 0,     ///< ����1
	EYE_LOCATION_METHOD2   = 1,     ///< ����2
	EYE_LOCATION_METHOD3   = 2      ///< ����3,Ԥ������ʱû��ʹ��
}EYE_LOCATION_METHOD;

///��Ĥʶ��״̬
typedef enum EM_STATUS
{
	EM_STATUS_OK                           = 0,    ///< �ɹ�
	EM_STATUS_PARAMETER_INVALID            = -1,   ///< ������Ч
	EM_STATUS_PARAMETER_OUT_OF_BOUND       = -2,   ///< ����Խ��
	EM_STATUS_NOT_ENOUGH_SYSTEM_MEMORY     = -3,   ///< û���㹻��ϵͳ�ڴ�
	EM_STATUS_NOT_MEET_GRADIENT_CONDITION  = -4,   ///< ͼ�������ݶ�������û���κε㱻���
	EM_STATUS_NOT_FIND_CIRCLE              = -5,   ///< û���ҵ�Բ
	EM_STATUS_PUPIL_OUT_OF_BOUND           = -6,   ///< ͫ�׳���ͼ����
	EM_STATUS_IRIS_OUT_OF_BOUND            = -7,   ///< ��Ĥ����ͼ����
	EM_STATUS_RADIUS_ERROR                 = -8,   ///< ͫ�װ뾶���ں�Ĥ�뾶
	EM_STATUS_CIRCLE_OUT_OF_BOUND          = -9,   ///< ԲԽ�磬У��ʱʹ��
	EM_STATUS_LOCATION_CIRCLE_ERROR        = -10,  ///< �ָ��Բ����ƥ���ʵ�
	EM_STATUS_IMAGE_BLUR                   = -11,  ///< ͼ������
	EM_STATUS_LOCATION_ERROR               = -12,  ///< ��λ�۾��쳣
    EM_STATUS_NOT_FIND_EYE                 = -13,  ///< û���ҵ��۾�
	EM_STATUS_TOO_MUCH_CANDIDAIT           = -14,  ///< ��ѡ�۹���
	EM_STATUS_PUPIL_BIG_THAN_IRIS          = -15,  ///< ͫ�ױȺ�Ĥ��
	EM_STATUS_CONCENTRICITY_ERROR          = -16,  ///< ��Ĥͫ��ͬ���ʴ���
	EM_STATUS_PIS_CONTRAST_ERROR           = -17,  ///< ͫ�׺�Ĥ��Ĥ�Աȶȴ���
	EM_STATUS_EYE_IMAGE_EDGE               = -18   ///< �۾�̫������Ե
}EM_STATUS;


///���νṹ��
typedef struct  ROI_RECT
{
	int nX;           ///< �����������Ͻ�ˮƽ����
	int nY;           ///< �����������ϽǴ�ֱ����
	int nWidth;       ///< ��������Ŀ�
	int nHeight;      ///< ��������ĸ�
}st_ROI_RECT;

///��ṹ��
typedef struct P_POINT
{
	int nX;          ///< ���ˮƽ����
	int nY;          ///< ��Ĵ�ֱ����
}stPOINT;

///ͼ��ģ������
typedef enum IMAGE_ANALYSIS
{
	IMAGE_SHARPNESS  = 0,       ///<ͼ������
	IMAGE_BLUR       = 1,       ///<ͼ��ʧ��ģ��
	MOTION_BLUR      = 2        ///<�˶�ģ��
}IMAGE_ANALYSIS;

///ģ��ȽϽ��
typedef enum COMPARISON_RESULT
{
	ACCEPT = 0,        ///< ��ͬһ���ˣ�����
	REJECT = 1         ///< ����ͬһ���ˣ��ܾ�
}COMPARISON_RESULT;

#ifndef CIRCLE_INFO_T
#define CIRCLE_INFO_T

///Բ��Ϣ�ṹ��
typedef struct CIRCLE_INFO
{
	int      nCenterRow;    ///< Բ����
	int      nCenterCol;    ///< Բ����
	int      nCircleR;      ///< Բ�뾶
	double   dMatch;        ///< Բ��ƥ���
}CIRCLE_INFO;

#endif

///�Ƿ���۾�ö�ٶ���
typedef enum ES_WEAR_GLASSES
{
	ES_GLASS_NO      =  0,              ///< ���۾�
	ES_GLASS_YES     =  1,              ///< û���۾�
	ES_GLASS_UNKNOWN =  2               ///< ��֪��
}ES_WEAR_GLASSES;

///����������
typedef enum ES_LIVENESS_TYPE
{
	ES_REAL_IRIS               = 0,         ///< ���Ĥ
	ES_FAKE_IRIS               = 1          ///< �ٺ�Ĥ
}ES_LIVENESS_TYPE;

///ģ����ѡ����
typedef enum TEMPLATE_CHOISE_METHOD
{
	TEMPLATE_METHOD_1  = 0,         ///< ѡģ�巽��1
	TEMPLATE_METHOD_2  = 1,         ///< ѡģ�巽��2
	TEMPLATE_METHOD_3  = 2          ///< ѡģ�巽��3 
}TEMPLATE_CHOISE_METHOD;

/// ��ǰ����״̬
typedef enum ES_BRIGHTNESS_ANALYSIS_STATE 
{
	ES_BRIGHT_ANALYSIS_OK         = 0,              ///< �����ж�OK
	ES_BRIGHT_ANALYSIS_DARK       = 1,              ///< �����������ѣ��뿿������������ͷ��
	ES_BRIGHT_ANALYSIS_LEFT       = 2,              ///< ����ͼ����ߣ������ѣ��뿿��
	ES_BRIGHT_ANALYSIS_RIGHT      = 3               ///< ����ͼ���ұߣ������ѣ��뿿��
}ES_BRIGHTNESS_ANALYSIS_STATE;


//---------------------------------------------------------------
/**
\brief   ��λ�۾�
\param   pImageBuf              [in] ����ͼ��
\param   nWidth                 [in] ����ͼ����
\param   nHeight                [in] ����ͼ��߶�
\param   pParamBuf              [in] ����buffer
\param   emFunChoice            [in] ѡ���ⷽ��(Ϊ����չ���ð汾ѡ���˹̶��ķ���)
\param   parrEyeCoordinate      [out]��⵽�����۵��������飬����2
\param   pEyeNum                [out]��⵽��������Ŀ

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESEyeLocation(const unsigned char *pImgSrc, int nWidth, int nHeight, unsigned char *pParamBuf, EYE_LOCATION_METHOD emFunChoice,stPOINT *parrEyeCoordinate, int *pEyeNum);


//---------------------------------------------------------------
/**
\brief   ���ݱ�Ե�ж�ͼ��ģ����
\param   pImgBuf                [in]����ͼ��buffer
\param   nWidth                 [in]����ͼ����
\param   nHeight                [in]����ͼ��߶�
\param   pParamBuf              [in]����buffer
\param   pemImageAnalysis       [out]ͼ���Ƿ�ģ��


\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESBlurDetection(unsigned char *pImgBuf, int nWidth, int nHeight, unsigned char *pParamBuf, IMAGE_ANALYSIS *pemImageAnalysis);


//---------------------------------------------------------------
/**
\brief   ��Ĥ�ָ�
\param   pImgBuf                [in]����ͼ��buffer
\param   nWidth                 [in]����ͼ����
\param   nHeight                [in]����ͼ��߶�
\param   pParamBuf              [in]����buffer
\param   pstPupil               [out]ͫ��Բ��Ϣ
\param   pstIris                [out]��ĤԲ��Ϣ
\param   parrUpEyelid           [out]����Ƥ�������㷨������,ֻʹ������NULL������3
\param   parrDownEyelid         [out]����Ƥ�������㷨������,ֻʹ������NULL������3
\param   pPupilContour          [out]����Բͫ����Ͻ��������2 * pParam->PR_HM_nPupilRefineLen
\param   pIrisMask              [out]��ĤMask����ͼ����ͬ��С 

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESIrisSegment(unsigned char        *pImgBuf, 
	                     int                   nWidth, 
						 int                   nHeight,
						 unsigned char        *pParamBuf,
						 CIRCLE_INFO          *pstPupil, 
						 CIRCLE_INFO          *pstIris,
						 double               *parrUpEyelid,
						 double               *parrDownEyelid,
						 double               *pPupilContour,
						 unsigned char        *pIrisMask
						 );


//---------------------------------------------------------------
/**
\brief   ��һ��
\param   pImgBuf                [in]����ͼ��buffer
\param   nWidth                 [in]����ͼ����
\param   nHeight                [in]����ͼ��߶�
\param   pstPupil               [in]ͫ��Բ��Ϣ
\param   pstIris                [in]��ĤԲ��Ϣ
\param   pPupilContour          [in]����Բͫ����Ͻ��(�粻ʹ�ã�����NULL)
\param   pNormImg               [out]��һ��ͼ��(����Ϊ512 * 48)

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESIrisImageNormalize(unsigned char *pImgBuf, int nWidth, int nHeight, CIRCLE_INFO *pstPupil, CIRCLE_INFO *pstIris, double *pPupilContour, unsigned char *pNormImg);


//---------------------------------------------------------------
/**
\brief   �Թ�һ�����ݽ��б���

\param   pNormData              [in]��һ������
\param   nWidth                 [in]��һ�����ݵĿ�
\param   nHeight                [in]��һ�����ݵĸ�
\param   pTemplateData          [out]����Log_Gabor����õ���ģ�����ݣ�����ΪHFVVLEN * HFVUNIT

\return  void
*/
//---------------------------------------------------------------
void ESDECL ESGetIrisTemplate(unsigned char *pNormData, int nWidth, int nHeight, unsigned char *pTemplateData);


//---------------------------------------------------------------
/**
\brief   ģ��Ƚϣ����бȶԣ�����ȶԽ��

\param   pEnrollTemp            [in]�Ǽǣ�ע�ᣩģ��
\param   pRecogTemp             [in]��ʶ��ģ��
\param   pEnrollMask            [in]�Ǽǣ�ע�ᣩ��Mask��ǣ��粻ʹ��Mask������NULL��
\param   pRecogMask             [in]ʶ���Mask��ǣ������ʹ��Mask������NULL��
\param   dTH                    [in]�б���ֵ
\param   pemResult              [out]�б���

\return  ������ĺ�������
*/
//---------------------------------------------------------------
double ESDECL ESTemplateComparision(unsigned char *pEnrollTemp, unsigned char *pRecogTemp, unsigned char *pEnrollMask, unsigned char *pRecogMask, double dTH, COMPARISON_RESULT *pemResult);

//-----------------------------------------------
/**
\brief   ��ȡ��ͼ

\param   pImgSrc                     [in] ����ͼ��buffer
\param   nWidth                      [in] ����ͼ����
\param   nHeight                     [in] ����ͼ��߶�
\param   parrEye                     [in] �۾�λ��
\param   nEyeNum                     [in] �۾���
\param   nEyeWidth                   [in] ��ȡ��ͼ�Ŀ��ο���320,640�ȣ�
\param   nEyeHeight                  [in] ��ȡ��ͼ�ĸߣ��ο���240,480�ȣ�
\param   pstEye0                     [out]��ͼ1
\param   pstEye1                     [out]��ͼ2,ֻ��һֻ�۾���������NULL

\return  ״̬��
*/
//----------------------------------------------
int  ESDECL ESGetEyeImage(unsigned char *pImgSrc, int nWidth, int nHeight, stPOINT *parrEye, int nEyeNum, int nEyeWidth, int nEyeHeight, unsigned char *pEye0, unsigned char *pEye1);


//-----------------------------------------------
/**
\brief   ͼ����������

\param   pImgSrc                     [in] ����ͼ��buffer
\param   nWidth                      [in] ����ͼ����
\param   nHeight                     [in] ����ͼ��߶�
\param   pThresh1                    [out] ��ֵ1
\param   pThresh2                    [out] ��ֵ2
\param   pThresh3                    [out] ��ֵ3

\return  ״̬��
*/
//----------------------------------------------
int ESDECL ESImageQuality(unsigned char *pImgSrc, int nWidth, int nHeight, double *pThresh1, double *pThresh2, double *pThresh3 );

//---------------------------------------------------------------
/**
\brief   ģ�����

\param   parrTemp               [in]����ѡ������ģ����ɵ�buffer
\param   parrMask               [in]����ѡ������ģ���Ӧ��Mask��ɵ�buffer ���粻ʹ��Mask������NULL��
\param   emTempMethod           [in]ģ��ѡ�񷽷�
\param   nTempCount             [in]����ѡ��ģ����
\param   nClusterNum            [in]��Ҫ�������ģ����
\param   dThreshold             [in]�������ֵ
\param   pIndex                 [out]û��ѡ�е�ģ������,����nTempCount
\param   pLength                [out]û��ѡ�е�ģ����

\return  ģ��ѡ��ɹ����  1���ɹ�  0��ʧ��
*/
//---------------------------------------------------------------
int ESDECL ESTemplateCluster(unsigned char *parrTemp, unsigned char *parrMask,TEMPLATE_CHOISE_METHOD emTempMethod, int nTempCount, int nClusterNum, double dThreshold, int *pIndex, int *pLength );

//---------------------------------------------------------------
/**
\brief   ��ȡMaskģ��

\param   pMaskNorm              [in]��һ��Mask
\param   nWidth                 [in]��һ��ģ��Ŀ�
\param   nHeight                [in]��һ��ģ��ĸ�
\param   pMaskTemp              [out]Maskģ�壬����ΪHFVVLEN * HFVUNIT

\return  void
*/
//---------------------------------------------------------------
void ESDECL ESGetMaskTemplate(unsigned char *pMaskNorm, int nWidth, int nHeight, unsigned char *pMaskTemp);


//---------------------------------------------------------------
/**
\brief	 �˶�ģ����⣬�����Դ��Ч

\param   pImgSrc                  [in] ����ͼ��
\param   nWidth                   [in] ͼ����
\param   nHeight                  [in] ͼ��߶�
\param   pParamBuf                [in] ����buffer
\param   pemImageAnalysis         [out]�����������������˶�ģ����

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESMotionBlurDetect(unsigned char *pImgSrc, int nWidth, int nHeight, unsigned char *pParamBuf, IMAGE_ANALYSIS *pemImageAnalysis);

//---------------------------------------------------------------
/**
\brief	 �˶�ģ����⣬֡��ķ����������ڶ����ߣ�������Ͻ������(��ȫ�ֱ�������Ҫ����)

\param   pImgSrc              [in] ������ͼ
\param   nWidth               [in] ������ͼ���
\param   nHeight              [in] ������ͼ�߶�
\param   pParamBuf            [in] ����buffer
\param   nLeftOrRight         [in] ���ۺ����۱�־
\parm    pemImageAnalysis     [out]�����������������˶�ģ����

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESMotionBlurDetectMultiFrame(unsigned char *pImgSrc, int nWidth, int nHeight, unsigned char *pParamBuf, int nLeftOrRight, IMAGE_ANALYSIS *pemImageAnalysis);

//---------------------------------------------------------------
/**
\brief	 ��ȡ�汾��

\param   pBuf                     [in,out] �汾��
\param   nLen                     [in]�洢�汾��buffer���ȣ�VERSION_LENGTH

\return  ״̬����
*/
//---------------------------------------------------------------
void ESDECL ESGetVersion(char *pBuf, int nLen);

//---------------------------------------------------------------
/**
\brief   �Ա�����ģ�����ƽ�ƣ���Ч�ڶ�ԭͼ������ת��

\param   pInTemplate            [in]����ת��ģ������
\param   nLength                [in]ģ�����ݵĳ���
\param   nShift                 [in]���ݽǶȼ����������Ҫƽ�Ƶ�������nShift = (int)(��ת�Ƕ� * 1.0 / 360 * ��һ��ͼ��� + 0.5)��
\param   pShiftTemplate         [out]��ת������ݣ�����Ϊ��768 * ��2 * nShift + 1����

\return  void����ѧ����ģ�飬�ڲ����ƣ�
*/
//---------------------------------------------------------------
void ESDECL ESTemplateShift(unsigned char *pInTemplate, int nLength, int nShift, unsigned char *pShiftTemplate );

//---------------------------------------------------------------
/**
\brief   ��Mask��ģ��ȶԣ���ת���ⲿ����

\param   pRotateTemp            [in]��ת���ģ��
\param   pRotateMask            [in]��ת���Mask
\param   pCompTemp              [in]���Ƚ�ģ��
\param   pCompMask              [in]���Ƚ�ģ���Mask
\param   dTH                    [in]�б���ֵ
\param   pemResult              [out]�б���

\return  ��ǰ��������
*/
//---------------------------------------------------------------
double ESDECL ESTempComparisionRotate(unsigned char *pRotateTemp, unsigned char *pRotateMask, unsigned char *pCompTemp, unsigned char *pCompMask, double dTH, COMPARISON_RESULT *pemResult);


//---------------------------------------------------------------
/**
\brief   ��ȡ2D Gabor����ģ��

\param   pNormData              [in]��һ��ͼ��
\param   nWidth                 [in]��һ��ͼ���(512)
\param   nHeight                [in]��һ��ͼ���(64)
\param   pGaborCode2D           [out]Gabor�������ݣ�����192�ֽڣ�

\return  void����ѧ����ģ�飩
*/
//---------------------------------------------------------------
void ESDECL ESGet2DGaborTemple(unsigned char *pNormData, int nWidth, int nHeight, unsigned char *pGaborCode2D);

//---------------------------------------------------------------
/**
\brief   ��ȡ2D Gabor Maskģ��

\param   pNormData              [in]��һ��Maskͼ��
\param   nWidth                 [in]��һ��Maskͼ���(512)
\param   nHeight                [in]��һ��Maskͼ���(64)
\param   pMasked                [out]����Mask(192�ֽ�)

\return  void����ѧ����ģ�飬�ڲ����ƣ�
*/
//---------------------------------------------------------------
void ESDECL ESGet2DMaskTemplate(unsigned char *pMaskNorm, int nWidth, int nHeight, unsigned char *pMaskedCode);

//---------------------------------------------------------------
/**
\brief   2άGaborģ��Ƚ�

\param   pEnrollTemp            [in]�Ǽǣ�ע�ᣩģ��
\param   pRecogTemp             [in]��ʶ��ģ��
\param   pEnrollMask            [in]ע��ģ���Mask
\param   pRecogMask             [in]ʶ��ģ���Mask
\param   dTH                    [in]�б���ֵ
\param   pemResult              [out]�б���

\return  ��ǰ��������
*/
//---------------------------------------------------------------
double ESDECL ESGabor2DTempComparison(unsigned char *pEnrollTemp, unsigned char *pRecogTemp, unsigned char *pEnrollMask, unsigned char *pRecogMask, double dTH, COMPARISON_RESULT *pemResult);

//---------------------------------------------------------------
/**
\brief   ��һ������άGabor�����ã����Ȳ�ͬ��Ϊ�˲��޸�֮ǰ�ӿڣ�����½ӿ�

\param   pImgBuf                [in]����ͼ��buffer
\param   nWidth                 [in]����ͼ����
\param   nHeight                [in]����ͼ��߶�
\param   pstPupil               [in]ͫ��Բ��Ϣ
\param   pstIris                [in]��ĤԲ��Ϣ
\param   pPupilContour          [in]����Բͫ����Ͻ��(�粻ʹ�ã�����NULL)
\param   pNormImg               [out]��һ��ͼ��(����Ϊ512 * 64)

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESGabor2DIrisNormalize(unsigned char *pImgBuf, int nWidth, int nHeight, CIRCLE_INFO *pstPupil, CIRCLE_INFO *pstIris, double *pPupilContour, unsigned char *pNormImg);

//-----------------------------------------------
/**
\brief   ��ȡ��ͼ,���ò��ߵķ�ʽ

\param   pImgSrc                     [in] ����ͼ��buffer
\param   nWidth                      [in] ����ͼ����
\param   nHeight                     [in] ����ͼ��߶�
\param   parrEye                     [in] �۾�λ��
\param   nEyeNum                     [in] �۾���
\param   nEyeWidth                   [in] ��ȡ��ͼ�Ŀ��ο���320,640�ȣ�
\param   nEyeHeight                  [in] ��ȡ��ͼ�ĸߣ��ο���240,480�ȣ�
\param   pstEye0                     [out]��ͼ1
\param   pstEye1                     [out]��ͼ2��ֻ��һֻ�۾���������NULL

\return  ״̬��
*/
//----------------------------------------------
int ESDECL ESGetEyeImageEx(unsigned char *pImgSrc, int nWidth, int nHeight, stPOINT *parrEye, int nEyeNum, int nEyeWidth, int nEyeHeight, unsigned char *pEye0, unsigned char *pEye1);

//-----------------------------------------------
/**
\brief   ͼ���������

\param   pImage                      [in] ͼ��buffer
\param   nWidth                      [in] ����ͼ����
\param   nHeight                     [in] ����ͼ��߶�
\param   pParamBuf                   [in] ����buffer
\param   pScore                      [out] ͼ����������

\return  ״̬��
*/
//----------------------------------------------
int ESDECL ESGetImageNIQEScore(unsigned char *pImageBuf, int nWidth, int nHeight, unsigned char *pParamBuf, int *pScore);

//---------------------------------------------------------------
/**
\brief   Maskͼ���һ��
\param   pImgBuf                [in]����ͼ��buffer
\param   nWidth                 [in]����ͼ����
\param   nHeight                [in]����ͼ��߶�
\param   pstPupil               [in]ͫ��Բ��Ϣ
\param   pstIris                [in]��ĤԲ��Ϣ
\param   pPupilContour          [in]����Բͫ����Ͻ��(�粻ʹ�ã�����NULL)
\param   pNormImg               [out]��һ��ͼ��(����Ϊ512 * 48)

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESMaskImageNormalize(unsigned char *pImgBuf, int nWidth, int nHeight, CIRCLE_INFO *pstPupil, CIRCLE_INFO *pstIris, double *pPupilContour, unsigned char *pNormImg);

//---------------------------------------------------------------
/**
\brief	 ���۾����
\param   pImgBuf                  [in]����ͼ��buffer
\param   nWidth                   [in]ͼ���
\param   nHeight                  [in]ͼ���
\param   nGlassTH                 [in]�����ֵ��Ĭ��400
\param   pemGlass                 [out]�����

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESGlassDetection(unsigned char *pImgBuf, int nWidth, int nHeight, int nGlassTH, ES_WEAR_GLASSES *pemGlass);

//---------------------------------------------------------------
/**
\brief   ������
\param   pEyeImg                [in]����ͼ��buffer
\param   nWidth                 [in]����ͼ����
\param   nHeight                [in]����ͼ��߶�
\param   pParamBuf              [in]����buffer
\param   pstPupilInfo           [in]ͫ����Ϣ�ṹ��
\param   pemLiveResult          [out]����������

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESLivenessDetection(unsigned char *pEyeImg, int nWidth, int nHeight, unsigned char *pParamBuf, CIRCLE_INFO *pstPupilInfo, ES_LIVENESS_TYPE *pemLiveResult);

//---------------------------------------------------------------
/**
\brief   ��Ĥ�ַָ�
\param   pImgBuf                [in]����ͼ��buffer
\param   nWidth                 [in]����ͼ����
\param   nHeight                [in]����ͼ��߶�
\param   pParamBuf              [in]����buffer
\param   pstPupil               [out]ͫ��Բ��Ϣ
\param   pstIris                [out]��ĤԲ��Ϣ
\param   parrUpEyelid           [out]����Ƥ�������㷨������,ֻʹ������NULL������3
\param   parrDownEyelid         [out]����Ƥ�������㷨������,ֻʹ������NULL������3
\param   pPupilContour          [out]����Բͫ����Ͻ��������2 * pParam->PR_HM_nPupilRefineLen
\param   pIrisMask              [out]��ĤMask����ͼ����ͬ��С 

\return  ״̬����
*/
//---------------------------------------------------------------
int ESDECL ESIrisRoughSegment(unsigned char        *pImgBuf, 
	int                   nWidth, 
	int                   nHeight,
	unsigned char        *pParamBuf,
	CIRCLE_INFO          *pstPupil, 
	CIRCLE_INFO          *pstIris,
	double               *parrUpEyelid,
	double               *parrDownEyelid,
	double               *pPupilContour,
	unsigned char        *pIrisMask
	);


//---------------------------------------------------------------
/**
\brief   ��ͼ����ͼ�������͸�ӱ任

\param   pImgSrc                         [in]Sensor���ͼƬ��ԭʼͼ��
\param   nWidth                          [in]ԭʼSensor���ͼƬ�Ŀ�
\param   nHeight                         [in]ԭʼSensor���ͼƬ�ĸ�
\param   fEye0X                          [in]�۾�1λ�õ�fPointX����
\param   fEye0Y                          [in]�۾�1λ�õ�fPointY����
\param   fEye1X                          [in]�۾�2λ�õ�fPointX����
\param   fEye1Y                          [in]�۾�2λ�õ�fPointY����
\param   nEyeNum                         [in]�۾���
\param   pParamBuf                       [in]����buffer
\param   pImgDst                         [out]Sensor���ͼƬ���۾�λ�ô�����͸�ӱ任������ͼ��

\return  void
*/
//---------------------------------------------------------------
int ESDECL ESPerspectiveTrans(unsigned char *pImgSrc, 
	                          int   nWidth, 
							  int   nHeight, 
							  float fEye0X, 
							  float fEye0Y, 
							  float fEye1X, 
							  float fEye1Y, 
							  int   nEyeNum, 
							  unsigned char *pParamBuf,
							  unsigned char *pImgDst);

#ifdef __cplusplus
}
#endif
#endif
