#include "stdafx.h"
#include "LocalStorage.h"


CLocalStorage::CLocalStorage()
{
}


CLocalStorage::~CLocalStorage()
{
	clearPersonIrisTemplatesVec();
}

void CLocalStorage::updatePersonIrisTemplates(wchar_t* name, IrisTemplates_t* irisTemplates) {
	bool isExist = false;
	for (vector<CPersonIrisTemplates*>::iterator ite = personIrisTemplatesVec.begin();
		ite != personIrisTemplatesVec.end(); ite++) {
		if (0 == lstrcmpW(name, (*ite)->getPersonName())) {
			isExist = true;
			(*ite)->updateIrisTemplates(irisTemplates);
			return;
		}
	}

	CPersonIrisTemplates* personIrisTemplates = new CPersonIrisTemplates(name);
	if (NULL != personIrisTemplates) {
		personIrisTemplates->updateIrisTemplates(irisTemplates);
		personIrisTemplatesVec.push_back(personIrisTemplates);
	}
}

void CLocalStorage::clearPersonIrisTemplatesVec() {
	for (vector<CPersonIrisTemplates*>::iterator ite = personIrisTemplatesVec.begin();
		ite != personIrisTemplatesVec.end(); ite++) {
		delete *ite;
	}

	personIrisTemplatesVec.clear();
}

bool CLocalStorage::compareTemplates(void* expandablePara, char* cameraType,IrisTemplates_t* matchTemplates, wchar_t* result) {
	wchar_t* name = (wchar_t*)expandablePara;

	for (vector<CPersonIrisTemplates*>::iterator ite = personIrisTemplatesVec.begin();
		ite != personIrisTemplatesVec.end(); ite++) {
		if (0 == lstrcmpW(name, (*ite)->getPersonName())) {
			return (*ite)->compareTemplates(cameraType, matchTemplates, result);
		}
	}

	return false;
}
