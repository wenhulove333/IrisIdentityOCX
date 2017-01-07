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

///人眼定位方法选择
typedef enum EYE_LOCATION_METHOD
{
	EYE_LOCATION_METHOD1   = 0,     ///< 方法1
	EYE_LOCATION_METHOD2   = 1,     ///< 方法2
	EYE_LOCATION_METHOD3   = 2      ///< 方法3,预留，暂时没有使用
}EYE_LOCATION_METHOD;

///虹膜识别状态
typedef enum EM_STATUS
{
	EM_STATUS_OK                           = 0,    ///< 成功
	EM_STATUS_PARAMETER_INVALID            = -1,   ///< 参数无效
	EM_STATUS_PARAMETER_OUT_OF_BOUND       = -2,   ///< 参数越界
	EM_STATUS_NOT_ENOUGH_SYSTEM_MEMORY     = -3,   ///< 没有足够的系统内存
	EM_STATUS_NOT_MEET_GRADIENT_CONDITION  = -4,   ///< 图像不满足梯度条件，没有任何点被标记
	EM_STATUS_NOT_FIND_CIRCLE              = -5,   ///< 没有找到圆
	EM_STATUS_PUPIL_OUT_OF_BOUND           = -6,   ///< 瞳孔超出图像外
	EM_STATUS_IRIS_OUT_OF_BOUND            = -7,   ///< 虹膜超出图像外
	EM_STATUS_RADIUS_ERROR                 = -8,   ///< 瞳孔半径大于虹膜半径
	EM_STATUS_CIRCLE_OUT_OF_BOUND          = -9,   ///< 圆越界，校验时使用
	EM_STATUS_LOCATION_CIRCLE_ERROR        = -10,  ///< 分割的圆错误，匹配率低
	EM_STATUS_IMAGE_BLUR                   = -11,  ///< 图像不清晰
	EM_STATUS_LOCATION_ERROR               = -12,  ///< 定位眼睛异常
    EM_STATUS_NOT_FIND_EYE                 = -13,  ///< 没有找到眼睛
	EM_STATUS_TOO_MUCH_CANDIDAIT           = -14,  ///< 候选眼过多
	EM_STATUS_PUPIL_BIG_THAN_IRIS          = -15,  ///< 瞳孔比虹膜大
	EM_STATUS_CONCENTRICITY_ERROR          = -16,  ///< 虹膜瞳孔同心率错误
	EM_STATUS_PIS_CONTRAST_ERROR           = -17,  ///< 瞳孔虹膜巩膜对比度错误
	EM_STATUS_EYE_IMAGE_EDGE               = -18   ///< 眼睛太靠近边缘
}EM_STATUS;


///矩形结构体
typedef struct  ROI_RECT
{
	int nX;           ///< 矩形区域左上角水平坐标
	int nY;           ///< 矩形区域左上角垂直坐标
	int nWidth;       ///< 矩形区域的宽
	int nHeight;      ///< 矩形区域的高
}st_ROI_RECT;

///点结构体
typedef struct P_POINT
{
	int nX;          ///< 点的水平坐标
	int nY;          ///< 点的垂直坐标
}stPOINT;

///图像模糊分析
typedef enum IMAGE_ANALYSIS
{
	IMAGE_SHARPNESS  = 0,       ///<图像锐利
	IMAGE_BLUR       = 1,       ///<图像失焦模糊
	MOTION_BLUR      = 2        ///<运动模糊
}IMAGE_ANALYSIS;

///模板比较结果
typedef enum COMPARISON_RESULT
{
	ACCEPT = 0,        ///< 是同一个人，接受
	REJECT = 1         ///< 不是同一个人，拒绝
}COMPARISON_RESULT;

#ifndef CIRCLE_INFO_T
#define CIRCLE_INFO_T

///圆信息结构体
typedef struct CIRCLE_INFO
{
	int      nCenterRow;    ///< 圆心行
	int      nCenterCol;    ///< 圆心列
	int      nCircleR;      ///< 圆半径
	double   dMatch;        ///< 圆的匹配度
}CIRCLE_INFO;

#endif

///是否戴眼镜枚举定义
typedef enum ES_WEAR_GLASSES
{
	ES_GLASS_NO      =  0,              ///< 戴眼镜
	ES_GLASS_YES     =  1,              ///< 没戴眼镜
	ES_GLASS_UNKNOWN =  2               ///< 不知道
}ES_WEAR_GLASSES;

///活体分析结果
typedef enum ES_LIVENESS_TYPE
{
	ES_REAL_IRIS               = 0,         ///< 真虹膜
	ES_FAKE_IRIS               = 1          ///< 假虹膜
}ES_LIVENESS_TYPE;

///模板挑选方法
typedef enum TEMPLATE_CHOISE_METHOD
{
	TEMPLATE_METHOD_1  = 0,         ///< 选模板方法1
	TEMPLATE_METHOD_2  = 1,         ///< 选模板方法2
	TEMPLATE_METHOD_3  = 2          ///< 选模板方法3 
}TEMPLATE_CHOISE_METHOD;

/// 当前亮度状态
typedef enum ES_BRIGHTNESS_ANALYSIS_STATE 
{
	ES_BRIGHT_ANALYSIS_OK         = 0,              ///< 亮度判断OK
	ES_BRIGHT_ANALYSIS_DARK       = 1,              ///< 过暗，需提醒：请靠近并正视摄像头等
	ES_BRIGHT_ANALYSIS_LEFT       = 2,              ///< 脸在图像左边，需提醒：请靠右
	ES_BRIGHT_ANALYSIS_RIGHT      = 3               ///< 脸在图像右边，需提醒：请靠左
}ES_BRIGHTNESS_ANALYSIS_STATE;


//---------------------------------------------------------------
/**
\brief   定位眼睛
\param   pImageBuf              [in] 输入图像
\param   nWidth                 [in] 输入图像宽度
\param   nHeight                [in] 输入图像高度
\param   pParamBuf              [in] 参数buffer
\param   emFunChoice            [in] 选择检测方法(为了扩展，该版本选择了固定的方法)
\param   parrEyeCoordinate      [out]检测到的人眼的坐标数组，长度2
\param   pEyeNum                [out]检测到的人眼数目

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESEyeLocation(const unsigned char *pImgSrc, int nWidth, int nHeight, unsigned char *pParamBuf, EYE_LOCATION_METHOD emFunChoice,stPOINT *parrEyeCoordinate, int *pEyeNum);


//---------------------------------------------------------------
/**
\brief   根据边缘判断图像模糊度
\param   pImgBuf                [in]输入图像buffer
\param   nWidth                 [in]输入图像宽度
\param   nHeight                [in]输入图像高度
\param   pParamBuf              [in]参数buffer
\param   pemImageAnalysis       [out]图像是否模糊


\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESBlurDetection(unsigned char *pImgBuf, int nWidth, int nHeight, unsigned char *pParamBuf, IMAGE_ANALYSIS *pemImageAnalysis);


//---------------------------------------------------------------
/**
\brief   虹膜分割
\param   pImgBuf                [in]输入图像buffer
\param   nWidth                 [in]输入图像宽度
\param   nHeight                [in]输入图像高度
\param   pParamBuf              [in]参数buffer
\param   pstPupil               [out]瞳孔圆信息
\param   pstIris                [out]虹膜圆信息
\param   parrUpEyelid           [out]上眼皮参数（算法调试用,只使用输入NULL）长度3
\param   parrDownEyelid         [out]下眼皮参数（算法调试用,只使用输入NULL）长度3
\param   pPupilContour          [out]非正圆瞳孔拟合结果，长度2 * pParam->PR_HM_nPupilRefineLen
\param   pIrisMask              [out]虹膜Mask，与图像相同大小 

\return  状态参数
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
\brief   归一化
\param   pImgBuf                [in]输入图像buffer
\param   nWidth                 [in]输入图像宽度
\param   nHeight                [in]输入图像高度
\param   pstPupil               [in]瞳孔圆信息
\param   pstIris                [in]虹膜圆信息
\param   pPupilContour          [in]非正圆瞳孔拟合结果(如不使用，输入NULL)
\param   pNormImg               [out]归一化图像(长度为512 * 48)

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESIrisImageNormalize(unsigned char *pImgBuf, int nWidth, int nHeight, CIRCLE_INFO *pstPupil, CIRCLE_INFO *pstIris, double *pPupilContour, unsigned char *pNormImg);


//---------------------------------------------------------------
/**
\brief   对归一化数据进行编码

\param   pNormData              [in]归一化数据
\param   nWidth                 [in]归一化数据的宽
\param   nHeight                [in]归一化数据的高
\param   pTemplateData          [out]采用Log_Gabor编码得到的模板数据，长度为HFVVLEN * HFVUNIT

\return  void
*/
//---------------------------------------------------------------
void ESDECL ESGetIrisTemplate(unsigned char *pNormData, int nWidth, int nHeight, unsigned char *pTemplateData);


//---------------------------------------------------------------
/**
\brief   模板比较，进行比对，输出比对结果

\param   pEnrollTemp            [in]登记（注册）模板
\param   pRecogTemp             [in]待识别模板
\param   pEnrollMask            [in]登记（注册）的Mask标记（如不使用Mask，输入NULL）
\param   pRecogMask             [in]识别的Mask标记（如果不使用Mask，输入NULL）
\param   dTH                    [in]判别阈值
\param   pemResult              [out]判别结果

\return  计算出的汉明距离
*/
//---------------------------------------------------------------
double ESDECL ESTemplateComparision(unsigned char *pEnrollTemp, unsigned char *pRecogTemp, unsigned char *pEnrollMask, unsigned char *pRecogMask, double dTH, COMPARISON_RESULT *pemResult);

//-----------------------------------------------
/**
\brief   截取眼图

\param   pImgSrc                     [in] 输入图像buffer
\param   nWidth                      [in] 输入图像宽度
\param   nHeight                     [in] 输入图像高度
\param   parrEye                     [in] 眼睛位置
\param   nEyeNum                     [in] 眼睛数
\param   nEyeWidth                   [in] 截取眼图的宽（参考：320,640等）
\param   nEyeHeight                  [in] 截取眼图的高（参考：240,480等）
\param   pstEye0                     [out]眼图1
\param   pstEye1                     [out]眼图2,只有一只眼睛，可以置NULL

\return  状态码
*/
//----------------------------------------------
int  ESDECL ESGetEyeImage(unsigned char *pImgSrc, int nWidth, int nHeight, stPOINT *parrEye, int nEyeNum, int nEyeWidth, int nEyeHeight, unsigned char *pEye0, unsigned char *pEye1);


//-----------------------------------------------
/**
\brief   图像质量计算

\param   pImgSrc                     [in] 输入图像buffer
\param   nWidth                      [in] 输入图像宽度
\param   nHeight                     [in] 输入图像高度
\param   pThresh1                    [out] 阈值1
\param   pThresh2                    [out] 阈值2
\param   pThresh3                    [out] 阈值3

\return  状态码
*/
//----------------------------------------------
int ESDECL ESImageQuality(unsigned char *pImgSrc, int nWidth, int nHeight, double *pThresh1, double *pThresh2, double *pThresh3 );

//---------------------------------------------------------------
/**
\brief   模板聚类

\param   parrTemp               [in]待挑选的所有模板组成的buffer
\param   parrMask               [in]待挑选的所有模板对应的Mask组成的buffer （如不使用Mask，输入NULL）
\param   emTempMethod           [in]模板选择方法
\param   nTempCount             [in]待挑选的模板数
\param   nClusterNum            [in]需要聚类出的模板数
\param   dThreshold             [in]聚类的阈值
\param   pIndex                 [out]没有选中的模板索引,长度nTempCount
\param   pLength                [out]没有选中的模板数

\return  模板选择成功标记  1：成功  0：失败
*/
//---------------------------------------------------------------
int ESDECL ESTemplateCluster(unsigned char *parrTemp, unsigned char *parrMask,TEMPLATE_CHOISE_METHOD emTempMethod, int nTempCount, int nClusterNum, double dThreshold, int *pIndex, int *pLength );

//---------------------------------------------------------------
/**
\brief   获取Mask模板

\param   pMaskNorm              [in]归一化Mask
\param   nWidth                 [in]归一化模板的宽
\param   nHeight                [in]归一化模板的高
\param   pMaskTemp              [out]Mask模板，长度为HFVVLEN * HFVUNIT

\return  void
*/
//---------------------------------------------------------------
void ESDECL ESGetMaskTemplate(unsigned char *pMaskNorm, int nWidth, int nHeight, unsigned char *pMaskTemp);


//---------------------------------------------------------------
/**
\brief	 运动模糊检测，单点光源有效

\param   pImgSrc                  [in] 输入图像
\param   nWidth                   [in] 图像宽度
\param   nHeight                  [in] 图像高度
\param   pParamBuf                [in] 参数buffer
\param   pemImageAnalysis         [out]输出结果（清晰或者运动模糊）

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESMotionBlurDetect(unsigned char *pImgSrc, int nWidth, int nHeight, unsigned char *pParamBuf, IMAGE_ANALYSIS *pemImageAnalysis);

//---------------------------------------------------------------
/**
\brief	 运动模糊检测，帧间的方法，适用于多个光斑，且相隔较近的情况(有全局变量，需要加锁)

\param   pImgSrc              [in] 输入眼图
\param   nWidth               [in] 输入眼图宽度
\param   nHeight              [in] 输入眼图高度
\param   pParamBuf            [in] 参数buffer
\param   nLeftOrRight         [in] 左眼和右眼标志
\parm    pemImageAnalysis     [out]输出结果（清晰或者运动模糊）

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESMotionBlurDetectMultiFrame(unsigned char *pImgSrc, int nWidth, int nHeight, unsigned char *pParamBuf, int nLeftOrRight, IMAGE_ANALYSIS *pemImageAnalysis);

//---------------------------------------------------------------
/**
\brief	 获取版本号

\param   pBuf                     [in,out] 版本号
\param   nLen                     [in]存储版本号buffer长度，VERSION_LENGTH

\return  状态参数
*/
//---------------------------------------------------------------
void ESDECL ESGetVersion(char *pBuf, int nLen);

//---------------------------------------------------------------
/**
\brief   对编码后的模板进行平移（等效于对原图进行旋转）

\param   pInTemplate            [in]待旋转的模板数据
\param   nLength                [in]模板数据的长度
\param   nShift                 [in]根据角度计算出来的需要平移的列数（nShift = (int)(旋转角度 * 1.0 / 360 * 归一化图像宽 + 0.5)）
\param   pShiftTemplate         [out]旋转后的数据，长度为（768 * （2 * nShift + 1））

\return  void（数学运算模块，内部控制）
*/
//---------------------------------------------------------------
void ESDECL ESTemplateShift(unsigned char *pInTemplate, int nLength, int nShift, unsigned char *pShiftTemplate );

//---------------------------------------------------------------
/**
\brief   带Mask的模板比对，旋转在外部进行

\param   pRotateTemp            [in]旋转后的模板
\param   pRotateMask            [in]旋转后的Mask
\param   pCompTemp              [in]待比较模板
\param   pCompMask              [in]待比较模板的Mask
\param   dTH                    [in]判别阈值
\param   pemResult              [out]判别结果

\return  当前汉明距离
*/
//---------------------------------------------------------------
double ESDECL ESTempComparisionRotate(unsigned char *pRotateTemp, unsigned char *pRotateMask, unsigned char *pCompTemp, unsigned char *pCompMask, double dTH, COMPARISON_RESULT *pemResult);


//---------------------------------------------------------------
/**
\brief   获取2D Gabor编码模板

\param   pNormData              [in]归一化图像
\param   nWidth                 [in]归一化图像宽(512)
\param   nHeight                [in]归一化图像高(64)
\param   pGaborCode2D           [out]Gabor采样数据（长度192字节）

\return  void（数学运算模块）
*/
//---------------------------------------------------------------
void ESDECL ESGet2DGaborTemple(unsigned char *pNormData, int nWidth, int nHeight, unsigned char *pGaborCode2D);

//---------------------------------------------------------------
/**
\brief   获取2D Gabor Mask模板

\param   pNormData              [in]归一化Mask图像
\param   nWidth                 [in]归一化Mask图像宽(512)
\param   nHeight                [in]归一化Mask图像高(64)
\param   pMasked                [out]编码Mask(192字节)

\return  void（数学运算模块，内部控制）
*/
//---------------------------------------------------------------
void ESDECL ESGet2DMaskTemplate(unsigned char *pMaskNorm, int nWidth, int nHeight, unsigned char *pMaskedCode);

//---------------------------------------------------------------
/**
\brief   2维Gabor模板比较

\param   pEnrollTemp            [in]登记（注册）模板
\param   pRecogTemp             [in]待识别模板
\param   pEnrollMask            [in]注册模板的Mask
\param   pRecogMask             [in]识别模板的Mask
\param   dTH                    [in]判别阈值
\param   pemResult              [out]判别结果

\return  当前汉明距离
*/
//---------------------------------------------------------------
double ESDECL ESGabor2DTempComparison(unsigned char *pEnrollTemp, unsigned char *pRecogTemp, unsigned char *pEnrollMask, unsigned char *pRecogMask, double dTH, COMPARISON_RESULT *pemResult);

//---------------------------------------------------------------
/**
\brief   归一化，二维Gabor编码用，长度不同，为了不修改之前接口，添加新接口

\param   pImgBuf                [in]输入图像buffer
\param   nWidth                 [in]输入图像宽度
\param   nHeight                [in]输入图像高度
\param   pstPupil               [in]瞳孔圆信息
\param   pstIris                [in]虹膜圆信息
\param   pPupilContour          [in]非正圆瞳孔拟合结果(如不使用，输入NULL)
\param   pNormImg               [out]归一化图像(长度为512 * 64)

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESGabor2DIrisNormalize(unsigned char *pImgBuf, int nWidth, int nHeight, CIRCLE_INFO *pstPupil, CIRCLE_INFO *pstIris, double *pPupilContour, unsigned char *pNormImg);

//-----------------------------------------------
/**
\brief   截取眼图,采用补边的方式

\param   pImgSrc                     [in] 输入图像buffer
\param   nWidth                      [in] 输入图像宽度
\param   nHeight                     [in] 输入图像高度
\param   parrEye                     [in] 眼睛位置
\param   nEyeNum                     [in] 眼睛数
\param   nEyeWidth                   [in] 截取眼图的宽（参考：320,640等）
\param   nEyeHeight                  [in] 截取眼图的高（参考：240,480等）
\param   pstEye0                     [out]眼图1
\param   pstEye1                     [out]眼图2，只有一只眼睛，可以置NULL

\return  状态码
*/
//----------------------------------------------
int ESDECL ESGetEyeImageEx(unsigned char *pImgSrc, int nWidth, int nHeight, stPOINT *parrEye, int nEyeNum, int nEyeWidth, int nEyeHeight, unsigned char *pEye0, unsigned char *pEye1);

//-----------------------------------------------
/**
\brief   图像质量打分

\param   pImage                      [in] 图像buffer
\param   nWidth                      [in] 输入图像宽度
\param   nHeight                     [in] 输入图像高度
\param   pParamBuf                   [in] 参数buffer
\param   pScore                      [out] 图像质量分数

\return  状态码
*/
//----------------------------------------------
int ESDECL ESGetImageNIQEScore(unsigned char *pImageBuf, int nWidth, int nHeight, unsigned char *pParamBuf, int *pScore);

//---------------------------------------------------------------
/**
\brief   Mask图像归一化
\param   pImgBuf                [in]输入图像buffer
\param   nWidth                 [in]输入图像宽度
\param   nHeight                [in]输入图像高度
\param   pstPupil               [in]瞳孔圆信息
\param   pstIris                [in]虹膜圆信息
\param   pPupilContour          [in]非正圆瞳孔拟合结果(如不使用，输入NULL)
\param   pNormImg               [out]归一化图像(长度为512 * 48)

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESMaskImageNormalize(unsigned char *pImgBuf, int nWidth, int nHeight, CIRCLE_INFO *pstPupil, CIRCLE_INFO *pstIris, double *pPupilContour, unsigned char *pNormImg);

//---------------------------------------------------------------
/**
\brief	 戴眼镜检测
\param   pImgBuf                  [in]输入图像buffer
\param   nWidth                   [in]图像宽
\param   nHeight                  [in]图像高
\param   nGlassTH                 [in]检测阈值，默认400
\param   pemGlass                 [out]检测结果

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESGlassDetection(unsigned char *pImgBuf, int nWidth, int nHeight, int nGlassTH, ES_WEAR_GLASSES *pemGlass);

//---------------------------------------------------------------
/**
\brief   活体检测
\param   pEyeImg                [in]输入图像buffer
\param   nWidth                 [in]输入图像宽度
\param   nHeight                [in]输入图像高度
\param   pParamBuf              [in]参数buffer
\param   pstPupilInfo           [in]瞳孔信息结构体
\param   pemLiveResult          [out]活体分析结果

\return  状态参数
*/
//---------------------------------------------------------------
int ESDECL ESLivenessDetection(unsigned char *pEyeImg, int nWidth, int nHeight, unsigned char *pParamBuf, CIRCLE_INFO *pstPupilInfo, ES_LIVENESS_TYPE *pemLiveResult);

//---------------------------------------------------------------
/**
\brief   虹膜粗分割
\param   pImgBuf                [in]输入图像buffer
\param   nWidth                 [in]输入图像宽度
\param   nHeight                [in]输入图像高度
\param   pParamBuf              [in]参数buffer
\param   pstPupil               [out]瞳孔圆信息
\param   pstIris                [out]虹膜圆信息
\param   parrUpEyelid           [out]上眼皮参数（算法调试用,只使用输入NULL）长度3
\param   parrDownEyelid         [out]下眼皮参数（算法调试用,只使用输入NULL）长度3
\param   pPupilContour          [out]非正圆瞳孔拟合结果，长度2 * pParam->PR_HM_nPupilRefineLen
\param   pIrisMask              [out]虹膜Mask，与图像相同大小 

\return  状态参数
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
\brief   对图像眼图区域进行透视变换

\param   pImgSrc                         [in]Sensor输出图片（原始图像）
\param   nWidth                          [in]原始Sensor输出图片的宽
\param   nHeight                         [in]原始Sensor输出图片的高
\param   fEye0X                          [in]眼睛1位置的fPointX坐标
\param   fEye0Y                          [in]眼睛1位置的fPointY坐标
\param   fEye1X                          [in]眼睛2位置的fPointX坐标
\param   fEye1Y                          [in]眼睛2位置的fPointY坐标
\param   nEyeNum                         [in]眼睛数
\param   pParamBuf                       [in]参数buffer
\param   pImgDst                         [out]Sensor输出图片在眼睛位置处进行透视变换后的输出图像

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
