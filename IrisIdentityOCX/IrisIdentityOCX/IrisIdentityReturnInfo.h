#pragma once
#include "Magpie\MagpieApi.h"

class CIrisIdentityReturnInfo
{
private:
	int errorcode;
	wchar_t* infoReadable;

public:
	CIrisIdentityReturnInfo();
	~CIrisIdentityReturnInfo();

	int getErrorCode();
	void setErrorCode(int errorcode);
	wchar_t* getInfoReadable();
	void setInfoReadable(wchar_t* infoReadable);
};

