#pragma once
#include "EnrolledIrisTemplates.h"
#include "PersonIrisTemplates.h"
#include <vector>
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
};

