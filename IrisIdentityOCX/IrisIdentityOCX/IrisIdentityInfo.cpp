#include "stdafx.h"
#include "IrisIdentityInfo.h"

CIrisIdentityInfo::CIrisIdentityInfo()
{
	resultMappingsOfCallIrisSDK[MAG_OK] = L"Sucess";
	resultMappingsOfCallIrisSDK[MAG_ERR_PARAM] = L"Parameter error";
	resultMappingsOfCallIrisSDK[MAG_ERR_MEM_SHORTAGE] = L"Insufficient memory";
	resultMappingsOfCallIrisSDK[MAG_ERR_BLUR] = L"Inproper image quality";
	resultMappingsOfCallIrisSDK[MAG_ERR_MISMATCH] = L"Template mismatch";
	resultMappingsOfCallIrisSDK[MAG_ERR_NO_EYE] = L"No eye found in image";
	resultMappingsOfCallIrisSDK[MAG_ERR_TOO_MANY_EYES] = L"Too many eyes found in image";
	resultMappingsOfCallIrisSDK[MAG_ERR_SELECT_TEMPLATE] = L"Not enough tempaltes for select";
	resultMappingsOfCallIrisSDK[MAG_ERR_DAT_FILE_CORRUPT] = L"SDK configuration file corrupt";
	resultMappingsOfCallIrisSDK[MAG_ERR_GENERATE_TEMPLATE] = L"Error during template generation";
	resultMappingsOfCallIrisSDK[MAG_ERR_HW_NO_LICENSED] = L"HW no license";
	resultMappingsOfCallIrisSDK[MAG_ERR_HW] = L"HW error";
	resultMappingsOfCallIrisSDK[MAG_ERR_LICENSE_EXPIRED] = L"License expired";

	//------------------------------------------------------------
	resultMappingsOfEyePos[EYE_POS_SUITABLE] = L"position OK";
	resultMappingsOfEyePos[EYE_POS_TOO_NEAR] = L"postion too near";
	resultMappingsOfEyePos[EYE_POS_TOO_FAR] = L"postion too far";
	resultMappingsOfEyePos[EYE_POS_UNKNOWN] = L"postion unknown";
}


CIrisIdentityInfo::~CIrisIdentityInfo()
{
}

wchar_t* CIrisIdentityInfo::getReadableInfoForCallIrisInfoSDK(int infoCode) {
	return resultMappingsOfCallIrisSDK[infoCode];
}