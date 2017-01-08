#pragma once
#include "CommonDef.h"
#include "Magpie\MagpieApi.h"
#include <vector>
using namespace std;

class CPersonIrisTemplates
{
private:
	vector<IrisTemplates_t*> irisTemplatesVec;
	wchar_t personName[IRIS_IDENTITY_COMMON_BUFFER_LEN];

public:
	CPersonIrisTemplates(wchar_t* name);
	~CPersonIrisTemplates();

	bool compareTemplates(char* cameraType, IrisTemplates_t* matchTemplates, wchar_t* result);
	void updateIrisTemplates(IrisTemplates_t* irisTemplates);
	void clearIrisTemplatesVec();
	wchar_t* getPersonName();
};

