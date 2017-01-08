#pragma once
#include "stdafx.h"
#include "Magpie\MagpieApi.h"
#include <map>
using namespace std;

class CIrisIdentityInfo
{
private:
	map<int, wchar_t*> resultMappingsOfCallIrisSDK;
	map<int, wchar_t*> resultMappingsOfEyePos;

public:
	CIrisIdentityInfo();
	~CIrisIdentityInfo();

	wchar_t* getReadableInfoForCallIrisInfoSDK(int infoCode);
};

