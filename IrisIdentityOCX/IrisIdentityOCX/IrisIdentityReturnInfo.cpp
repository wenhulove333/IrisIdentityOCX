#include "stdafx.h"
#include "IrisIdentityReturnInfo.h"


CIrisIdentityReturnInfo::CIrisIdentityReturnInfo()
{
	this->isNeedFreeReturnInfo = false;
}


CIrisIdentityReturnInfo::~CIrisIdentityReturnInfo()
{
	if (this->isNeedFreeReturnInfo) {
		free(this->infoReadable);
	}
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

void CIrisIdentityReturnInfo::setInfoReadable(wchar_t* infoReadable, bool isNeedFree) {
	this->infoReadable = infoReadable;
}