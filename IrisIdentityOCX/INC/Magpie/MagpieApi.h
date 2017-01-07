#ifndef MAGPIE_API_H
#define MAGPIE_API_H

#define MAGPIE_API __declspec(dllexport)

#define CAM_EQI_38_42_35_55    "CAM_EQI_38_42_35_55"
#define CAM_EQII_30_34_28_38   "CAM_EQII_30_34_28_38"

#define IRIS_TEMPLATE_SIZE              768     // 模板大小
#define IRIS_TEMPLATE_ROTATION_SIZE     (19 * IRIS_TEMPLATE_SIZE)  // 旋转模板大小

typedef enum ENUM_MAG_CODE
{
    MAG_OK                    = 0,              // 成功
    MAG_ERR_PARAM             = 1,              // 参数错误
    MAG_ERR_MEM_SHORTAGE      = 2,              // 内存不足
    MAG_ERR_BLUR              = 3,              // 图片质量不合适
    MAG_ERR_MISMATCH          = 4,              // 模板不匹配
    MAG_ERR_NO_EYE            = 5,              // 预览图中没有眼睛
    MAG_ERR_TOO_MANY_EYES     = 6,              // 预览图中眼睛太多（多余2个）
    MAG_ERR_SELECT_TEMPLATE   = 7,              // 模板选择没有达到最低数量要求
    MAG_ERR_DAT_FILE_CORRUPT  = 8,              // SDK软件配置文件破坏
    MAG_ERR_GENERATE_TEMPLATE = 9,              // 生成模板错误
    MAG_ERR_HW_NO_LICENSED    = 10,             // 没有license授权
    MAG_ERR_HW                = 11,             // 硬件错误
    MAG_ERR_LICENSE_EXPIRED   = 12              // 软件评估到期
} ENUM_MAG_CODE;

typedef struct tagPreviewImageInfo
{
    BYTE    *pbyData;                           // 预览图数据
    int     nWidth;                             // 预览宽度
    int     nHeight;                            // 预览高度
} PreviewImageInfo_t;

typedef struct tagIrisTemplate
{
    BYTE    byTemplate[IRIS_TEMPLATE_SIZE];     // 模板
    BYTE    byMask[IRIS_TEMPLATE_SIZE];         // 模板Mask
} IrisTemplate_t;

typedef struct tagIrisRotTemplate
{
    BYTE    byRotTemplate[IRIS_TEMPLATE_ROTATION_SIZE]; // 旋转模板
    BYTE    byRotMask[IRIS_TEMPLATE_ROTATION_SIZE];     // 旋转模板Mask
} IrisRotTemplate_t;

typedef struct tagIrisTemplates
{
    IrisTemplate_t      leftEye;                // 左眼模板
    IrisTemplate_t      rightEye;               // 右眼模板

    bool                bLeftValid;             // 左眼模板有效标志
    bool                bRightValid;            // 右眼模板有效标志
} IrisTemplates_t;

typedef struct tagIrisRotTemplates
{
    IrisRotTemplate_t   leftEyeRot;             // 左眼旋转模板
    IrisRotTemplate_t   rightEyeRot;            // 右眼旋转模板

    bool                bLeftValid;             // 左眼模板旋转有效标志
    bool                bRightValid;            // 右眼模板旋转有效标志
} IrisRotTemplates_t;

typedef enum ENUM_EYE_POS
{
    EYE_POS_SUITABLE,                           // 距离合适
    EYE_POS_TOO_NEAR,                           // 距离太近
    EYE_POS_TOO_FAR,                            // 距离太远
    EYE_POS_UNKNOWN                             // 距离未知
} ENUM_EYE_POS;

typedef struct tagEyePos_t
{
    ENUM_EYE_POS leftEyePos;                    // 左眼距离位置信息
    ENUM_EYE_POS rightEyePos;                   // 右眼距离位置信息
} EyePos_t;

typedef enum ENUM_MODE
{
    MODE_ENROLL,                                // 注册模式
    MODE_MATCH                                  // 识别模式
} ENUM_MODE;


typedef struct tagEyeImageInfo
{
    BYTE    *pbyData;                           // 预览图数据
    int     nWidth;                             // 预览宽度
    int     nHeight;                            // 预览高度
} EyeImageInfo_t;


//---------------------------------------------------------------
/**
\brief   快速获取远近距离提示
\param   pPreviewImageInfo      [in]预览图片信息
\param   mode                   [in]注册或者识别模式
\param   pEyePos                [OUT]眼睛距离信息
\param   pFuture                [OUT]NULL,未来扩展使用
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_GetIrisInfo(char *pszCameraId, PreviewImageInfo_t *pPreviewImageInfo, ENUM_MODE mode, EyePos_t *pEyePos, void *pFuture);


//---------------------------------------------------------------
/**
\brief   生成模板
\param   pPreviewImageInfo      [in]预览图片信息
\param   pIrisTemplates         [OUT]非旋转模板
\param   mode                   [in]注册或者识别模式
\param   pEyePos                [OUT]眼睛距离信息
\param   pFuture                [OUT]NULL,未来扩展使用
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_GetIrisTemplates(char *pszCameraId, PreviewImageInfo_t *pPreviewImageInfo, IrisTemplates_t *pIrisTemplates, ENUM_MODE mode, EyePos_t *pEyePos, void *pFuture);

//---------------------------------------------------------------
/**
\brief   生成旋转模板
\param   pPreviewImageInfo      [in]预览图片信息
\param   pIrisRotTemplates      [OUT]旋转模板
\param   mode                   [in]注册或者识别模式
\param   pEyePos                [OUT]眼睛距离信息
\param   pFuture                [OUT]NULL,未来扩展使用
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_GetIrisRotTemplates(char *pszCameraId, PreviewImageInfo_t *pPreviewImageInfo, IrisRotTemplates_t *pIrisRotTemplates, ENUM_MODE mode, EyePos_t *pEyePos, void *pFuture);

//---------------------------------------------------------------
/**
\brief   比对模板
\param   pEnrollTemplate        [in]注册模板
\param   pMatchTemplate         [OUT]待匹配模板
\param   pFuture                [OUT]NULL,未来扩展使用
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_CompareTemplate(char *pszCameraId, IrisTemplate_t *pEnrollTemplate, IrisTemplate_t *pMatchTemplate, double *pFuture);

//---------------------------------------------------------------
/**
\brief   比对模板
\param   pEnrollTemplate        [in]注册模板
\param   pMatchRotTemplate      [OUT]待匹配旋转模板
\param   pFuture                [OUT]NULL,未来扩展使用
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_CompareRotTemplate(char *pszCameraId, IrisTemplate_t *pEnrollTemplate, IrisRotTemplate_t *pMatchRotTemplate, void *pFuture);

//---------------------------------------------------------------
/**
\brief   选择模板
\param   templatesArr         [in]模板数组
\param   nTemplateCount       [in]模板数组templatesArr的大小
\param   nSelectNum           [in]需要挑选的模板数量
\param   bResultArr           [OUT]挑选后模板的标志位
\return  ENUM_MAG_CODE
*/
extern "C" MAGPIE_API int MAG_SelectTemplates(char *pszCameraId, IrisTemplate_t templateArr[], int nTemplateCount, int nSelectNum, bool bResultArr[]);

//---------------------------------------------------------------
/**
\brief   旋转模板
\param   pTemplate              [in]模板
\param   pRotTemplate           [in]旋转后的模板
\return  ENUM_MAG_CODE
*/
extern "C" MAGPIE_API int MAG_RotateTemplate(char *pszCameraId, IrisTemplate_t *pTemplate, IrisRotTemplate_t *pRotTemplate);

//---------------------------------------------------------------
/**
\brief   从眼图生成模板
\param   pEyeImageInfo          [in]眼图数据
\param   pIrisTemplates         [OUT]模板数据
\param   pFuture                [OUT]NULL,未来扩展使用
\return  ENUM_MAG_CODE
*/
extern "C" MAGPIE_API int MAG_GetIrisTemplate(char *pszCameraId, EyeImageInfo_t *pEyeImageInfo, IrisTemplate_t *pIrisTemplate, void *pFuture);

#endif
