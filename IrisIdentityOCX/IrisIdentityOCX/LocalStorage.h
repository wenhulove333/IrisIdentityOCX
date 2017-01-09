#pragma once
#include "EnrolledIrisTemplates.h"
#include "PersonIrisTemplates.h"
#include "CommonUtils.h"
#include <vector>
#include <map>
using namespace std;

class CLocalStorage :
	public CEnrolledIrisTemplates
{
private:
	vector<CPersonIrisTemplates*> personIrisTemplatesVec;

public:
	CLocalStorage();
	~CLocalStorage();

	void updatePersonIrisTemplates(wchar_t* name, IrisTemplates_t* irisTemplates);
	void clearPersonIrisTemplatesVec();
	bool compareTemplates(void* expandablePara, char* cameraType, IrisTemplates_t* matchTemplates, wchar_t* result);
	void restorePersonIrisTemplatesFromLocalStorage(wchar_t* path);
	void saveTemplates(wchar_t* path, wchar_t* name, vector<IrisTemplates_t*>* validIrisTemplates);
};

