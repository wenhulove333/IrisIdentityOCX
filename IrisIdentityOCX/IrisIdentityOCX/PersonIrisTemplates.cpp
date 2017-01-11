#include "stdafx.h"
#include "PersonIrisTemplates.h"


CPersonIrisTemplates::CPersonIrisTemplates(wchar_t* name)
{
	lstrcpyW(this->personName, name);
}


CPersonIrisTemplates::~CPersonIrisTemplates()
{
	clearIrisTemplatesVec();
}

bool CPersonIrisTemplates::compareTemplates(char* cameraType, IrisTemplates_t* matchTemplates, wchar_t* result) {
	int leftResult;
	int rightResult;

	for (vector<IrisTemplates_t*>::iterator ite = irisTemplatesVec.begin();
		ite != irisTemplatesVec.end(); ite++) {
		if (matchTemplates->bLeftValid) {
			leftResult = MAG_CompareTemplate(cameraType, &((*ite)->leftEye), &(matchTemplates->leftEye), NULL);
			if (leftResult == MAG_OK) {
				return true;
			}
		}
		if (matchTemplates->bRightValid) {
			rightResult = MAG_CompareTemplate(cameraType, &((*ite)->rightEye), &(matchTemplates->rightEye), NULL);
			if (rightResult == MAG_OK) {
				return true;
			}
		}
	}

	return false;
}

void CPersonIrisTemplates::updateIrisTemplates(IrisTemplates_t* irisTemplates) {
	irisTemplatesVec.push_back(irisTemplates);
}

void CPersonIrisTemplates::clearIrisTemplatesVec() {
	for (vector<IrisTemplates_t*>::iterator ite = irisTemplatesVec.begin();
		ite != irisTemplatesVec.end(); ite++) {
		free(*ite);
	}

	irisTemplatesVec.clear();
}

wchar_t* CPersonIrisTemplates::getPersonName() {
	return personName;
}