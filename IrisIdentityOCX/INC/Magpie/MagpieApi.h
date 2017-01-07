#ifndef MAGPIE_API_H
#define MAGPIE_API_H

#define MAGPIE_API __declspec(dllexport)

#define CAM_EQI_38_42_35_55    "CAM_EQI_38_42_35_55"
#define CAM_EQII_30_34_28_38   "CAM_EQII_30_34_28_38"

#define IRIS_TEMPLATE_SIZE              768     // ģ���С
#define IRIS_TEMPLATE_ROTATION_SIZE     (19 * IRIS_TEMPLATE_SIZE)  // ��תģ���С

typedef enum ENUM_MAG_CODE
{
    MAG_OK                    = 0,              // �ɹ�
    MAG_ERR_PARAM             = 1,              // ��������
    MAG_ERR_MEM_SHORTAGE      = 2,              // �ڴ治��
    MAG_ERR_BLUR              = 3,              // ͼƬ����������
    MAG_ERR_MISMATCH          = 4,              // ģ�岻ƥ��
    MAG_ERR_NO_EYE            = 5,              // Ԥ��ͼ��û���۾�
    MAG_ERR_TOO_MANY_EYES     = 6,              // Ԥ��ͼ���۾�̫�ࣨ����2����
    MAG_ERR_SELECT_TEMPLATE   = 7,              // ģ��ѡ��û�дﵽ�������Ҫ��
    MAG_ERR_DAT_FILE_CORRUPT  = 8,              // SDK��������ļ��ƻ�
    MAG_ERR_GENERATE_TEMPLATE = 9,              // ����ģ�����
    MAG_ERR_HW_NO_LICENSED    = 10,             // û��license��Ȩ
    MAG_ERR_HW                = 11,             // Ӳ������
    MAG_ERR_LICENSE_EXPIRED   = 12              // �����������
} ENUM_MAG_CODE;

typedef struct tagPreviewImageInfo
{
    BYTE    *pbyData;                           // Ԥ��ͼ����
    int     nWidth;                             // Ԥ�����
    int     nHeight;                            // Ԥ���߶�
} PreviewImageInfo_t;

typedef struct tagIrisTemplate
{
    BYTE    byTemplate[IRIS_TEMPLATE_SIZE];     // ģ��
    BYTE    byMask[IRIS_TEMPLATE_SIZE];         // ģ��Mask
} IrisTemplate_t;

typedef struct tagIrisRotTemplate
{
    BYTE    byRotTemplate[IRIS_TEMPLATE_ROTATION_SIZE]; // ��תģ��
    BYTE    byRotMask[IRIS_TEMPLATE_ROTATION_SIZE];     // ��תģ��Mask
} IrisRotTemplate_t;

typedef struct tagIrisTemplates
{
    IrisTemplate_t      leftEye;                // ����ģ��
    IrisTemplate_t      rightEye;               // ����ģ��

    bool                bLeftValid;             // ����ģ����Ч��־
    bool                bRightValid;            // ����ģ����Ч��־
} IrisTemplates_t;

typedef struct tagIrisRotTemplates
{
    IrisRotTemplate_t   leftEyeRot;             // ������תģ��
    IrisRotTemplate_t   rightEyeRot;            // ������תģ��

    bool                bLeftValid;             // ����ģ����ת��Ч��־
    bool                bRightValid;            // ����ģ����ת��Ч��־
} IrisRotTemplates_t;

typedef enum ENUM_EYE_POS
{
    EYE_POS_SUITABLE,                           // �������
    EYE_POS_TOO_NEAR,                           // ����̫��
    EYE_POS_TOO_FAR,                            // ����̫Զ
    EYE_POS_UNKNOWN                             // ����δ֪
} ENUM_EYE_POS;

typedef struct tagEyePos_t
{
    ENUM_EYE_POS leftEyePos;                    // ���۾���λ����Ϣ
    ENUM_EYE_POS rightEyePos;                   // ���۾���λ����Ϣ
} EyePos_t;

typedef enum ENUM_MODE
{
    MODE_ENROLL,                                // ע��ģʽ
    MODE_MATCH                                  // ʶ��ģʽ
} ENUM_MODE;


typedef struct tagEyeImageInfo
{
    BYTE    *pbyData;                           // Ԥ��ͼ����
    int     nWidth;                             // Ԥ�����
    int     nHeight;                            // Ԥ���߶�
} EyeImageInfo_t;


//---------------------------------------------------------------
/**
\brief   ���ٻ�ȡԶ��������ʾ
\param   pPreviewImageInfo      [in]Ԥ��ͼƬ��Ϣ
\param   mode                   [in]ע�����ʶ��ģʽ
\param   pEyePos                [OUT]�۾�������Ϣ
\param   pFuture                [OUT]NULL,δ����չʹ��
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_GetIrisInfo(char *pszCameraId, PreviewImageInfo_t *pPreviewImageInfo, ENUM_MODE mode, EyePos_t *pEyePos, void *pFuture);


//---------------------------------------------------------------
/**
\brief   ����ģ��
\param   pPreviewImageInfo      [in]Ԥ��ͼƬ��Ϣ
\param   pIrisTemplates         [OUT]����תģ��
\param   mode                   [in]ע�����ʶ��ģʽ
\param   pEyePos                [OUT]�۾�������Ϣ
\param   pFuture                [OUT]NULL,δ����չʹ��
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_GetIrisTemplates(char *pszCameraId, PreviewImageInfo_t *pPreviewImageInfo, IrisTemplates_t *pIrisTemplates, ENUM_MODE mode, EyePos_t *pEyePos, void *pFuture);

//---------------------------------------------------------------
/**
\brief   ������תģ��
\param   pPreviewImageInfo      [in]Ԥ��ͼƬ��Ϣ
\param   pIrisRotTemplates      [OUT]��תģ��
\param   mode                   [in]ע�����ʶ��ģʽ
\param   pEyePos                [OUT]�۾�������Ϣ
\param   pFuture                [OUT]NULL,δ����չʹ��
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_GetIrisRotTemplates(char *pszCameraId, PreviewImageInfo_t *pPreviewImageInfo, IrisRotTemplates_t *pIrisRotTemplates, ENUM_MODE mode, EyePos_t *pEyePos, void *pFuture);

//---------------------------------------------------------------
/**
\brief   �ȶ�ģ��
\param   pEnrollTemplate        [in]ע��ģ��
\param   pMatchTemplate         [OUT]��ƥ��ģ��
\param   pFuture                [OUT]NULL,δ����չʹ��
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_CompareTemplate(char *pszCameraId, IrisTemplate_t *pEnrollTemplate, IrisTemplate_t *pMatchTemplate, double *pFuture);

//---------------------------------------------------------------
/**
\brief   �ȶ�ģ��
\param   pEnrollTemplate        [in]ע��ģ��
\param   pMatchRotTemplate      [OUT]��ƥ����תģ��
\param   pFuture                [OUT]NULL,δ����չʹ��
\return  ENUM_MAG_CODE
*/
//---------------------------------------------------------------
extern "C" MAGPIE_API int MAG_CompareRotTemplate(char *pszCameraId, IrisTemplate_t *pEnrollTemplate, IrisRotTemplate_t *pMatchRotTemplate, void *pFuture);

//---------------------------------------------------------------
/**
\brief   ѡ��ģ��
\param   templatesArr         [in]ģ������
\param   nTemplateCount       [in]ģ������templatesArr�Ĵ�С
\param   nSelectNum           [in]��Ҫ��ѡ��ģ������
\param   bResultArr           [OUT]��ѡ��ģ��ı�־λ
\return  ENUM_MAG_CODE
*/
extern "C" MAGPIE_API int MAG_SelectTemplates(char *pszCameraId, IrisTemplate_t templateArr[], int nTemplateCount, int nSelectNum, bool bResultArr[]);

//---------------------------------------------------------------
/**
\brief   ��תģ��
\param   pTemplate              [in]ģ��
\param   pRotTemplate           [in]��ת���ģ��
\return  ENUM_MAG_CODE
*/
extern "C" MAGPIE_API int MAG_RotateTemplate(char *pszCameraId, IrisTemplate_t *pTemplate, IrisRotTemplate_t *pRotTemplate);

//---------------------------------------------------------------
/**
\brief   ����ͼ����ģ��
\param   pEyeImageInfo          [in]��ͼ����
\param   pIrisTemplates         [OUT]ģ������
\param   pFuture                [OUT]NULL,δ����չʹ��
\return  ENUM_MAG_CODE
*/
extern "C" MAGPIE_API int MAG_GetIrisTemplate(char *pszCameraId, EyeImageInfo_t *pEyeImageInfo, IrisTemplate_t *pIrisTemplate, void *pFuture);

#endif
