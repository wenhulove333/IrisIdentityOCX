#include "stdafx.h"
#include "IrisIdentityInfo.h"

CIrisIdentityInfo::CIrisIdentityInfo()
{
	infos[0] = L"Sucess";
	infos[1] = L"Parameter error";
	infos[2] = L"Insufficient memory";
	infos[3] = L"Inproper image quality";
	infos[4] = L"Template mismatch";
	infos[5] = L"No eye found in image";
	infos[6] = L"Too many eyes found in image";
	infos[7] = L"Not enough tempaltes for select";
	infos[8] = L"SDK configuration file corrupt";
	infos[9] = L"Error during template generation";
	infos[10] = L"HW no license";
	infos[11] = L"HW error";
	infos[12] = L"License expired";
	//------------------------------------------------------------
	infos[100 + EYE_POS_SUITABLE] = L"position OK";
	infos[100 + EYE_POS_TOO_NEAR] = L"postion too near";
	infos[100 + EYE_POS_TOO_FAR] = L"postion too far";
	infos[100 + EYE_POS_UNKNOWN] = L"postion unknown";
}


CIrisIdentityInfo::~CIrisIdentityInfo()
{
}

wchar_t* CIrisIdentityInfo::getIrisIdentityInfo(int infoCode) {
	return infos[infoCode];
}