#pragma once
#include "stdafx.h"
#include "Magpie\MagpieApi.h"
#include <map>
using namespace std;

class CIrisIdentityInfo
{
private:
	map<int, wchar_t*> infos;

public:
	CIrisIdentityInfo();
	~CIrisIdentityInfo();

	wchar_t* getIrisIdentityInfo(int infoCode);
};

