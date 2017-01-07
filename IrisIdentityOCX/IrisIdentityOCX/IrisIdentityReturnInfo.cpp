#include "stdafx.h"
#include "IrisIdentityReturnInfo.h"


CIrisIdentityReturnInfo::CIrisIdentityReturnInfo()
{
}


CIrisIdentityReturnInfo::~CIrisIdentityReturnInfo()
{
}

void CIrisIdentityReturnInfo::setErrorCode(int errorcode) {
	this->errorcode = errorcode;
}

int CIrisIdentityReturnInfo::getErrorCode() {
	return this->errorcode;
}


wchar_t* CIrisIdentityReturnInfo::getInfoReadable() {
	return infoReadable;
}

void CIrisIdentityReturnInfo::setInfoReadable(wchar_t* infoReadable) {
	this->infoReadable = infoReadable;
}