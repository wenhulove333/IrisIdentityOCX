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
		if (NULL == expandablePara) {
			bool ret = (*ite)->compareTemplates(cameraType, matchTemplates, result);
			if (ret) {
				if (NULL != result) {
					lstrcpyW(result, (*ite)->getPersonName());
				}
				return ret;
			}
		} else {
			if (0 == lstrcmpW(name, (*ite)->getPersonName())) {
				bool ret = (*ite)->compareTemplates(cameraType, matchTemplates, result);
				if (ret) {
					if (NULL != result) {
						lstrcpyW(result, (*ite)->getPersonName());
					}
					return ret;
				}
			}
		}


	}

	return false;
}

void CLocalStorage::restorePersonIrisTemplatesFromLocalStorage(wchar_t* path) {
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	wchar_t dir[IRIS_IDENTITY_COMMON_BUFFER_LEN];
	wchar_t fileFullPath[IRIS_IDENTITY_COMMON_BUFFER_LEN];
	map<wstring, IrisTemplates_t*> restores;

	wsprintf(dir, L"%s\\*", path);
	
	hFind = FindFirstFile(dir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}

	do
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			wsprintf(fileFullPath, L"%s\\%s", path, ffd.cFileName);
			wstring wst = ffd.cFileName;
			wstring nameWI = wst.substr(0, wst.find_first_of(L"_", wst.find_first_of(L"_") + 1));
			if (restores.find(nameWI) != restores.end()) {
				IrisTemplates_t* irisTemplates = restores[nameWI];
				if (NULL != irisTemplates) {
					if (wst.find(L"EYE_L_T") != wstring::npos) {
						CCommonUtils::readFile(fileFullPath, irisTemplates->leftEye.byTemplate, IRIS_TEMPLATE_SIZE);
					}
					else if (wst.find(L"EYE_L_M") != wstring::npos) {
						CCommonUtils::readFile(fileFullPath, irisTemplates->leftEye.byMask, IRIS_TEMPLATE_SIZE);
					}
					else if (wst.find(L"EYE_R_T") != wstring::npos) {
						CCommonUtils::readFile(fileFullPath, irisTemplates->rightEye.byTemplate, IRIS_TEMPLATE_SIZE);
					}
					else if (wst.find(L"EYE_R_M") != wstring::npos) {
						CCommonUtils::readFile(fileFullPath, irisTemplates->rightEye.byMask, IRIS_TEMPLATE_SIZE);
					}
				}
			}
			else {
				IrisTemplates_t* irisTemplates = (IrisTemplates_t*)malloc(sizeof(IrisTemplates_t));
				if (NULL != irisTemplates) {
					if (wst.find(L"EYE_L_T") != wstring::npos) {
						CCommonUtils::readFile(fileFullPath, irisTemplates->leftEye.byTemplate, IRIS_TEMPLATE_SIZE);
					} else if (wst.find(L"EYE_L_M") != wstring::npos) {
						CCommonUtils::readFile(fileFullPath, irisTemplates->leftEye.byMask, IRIS_TEMPLATE_SIZE);
					} else if (wst.find(L"EYE_R_T") != wstring::npos) {
						CCommonUtils::readFile(fileFullPath, irisTemplates->rightEye.byTemplate, IRIS_TEMPLATE_SIZE);
					} else if (wst.find(L"EYE_R_M") != wstring::npos) {
						CCommonUtils::readFile(fileFullPath, irisTemplates->rightEye.byMask, IRIS_TEMPLATE_SIZE);
					}
					restores[nameWI] = irisTemplates;
				}
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);

	for (map<wstring, IrisTemplates_t*>::iterator ite = restores.begin(); ite != restores.end(); ite++) {
		wstring name = (ite->first).substr(0, (ite->first).find_first_of(L"_"));

		updatePersonIrisTemplates((wchar_t*)name.c_str(), ite->second);
	}
}

void CLocalStorage::saveTemplates(wchar_t* path, wchar_t* name, vector<IrisTemplates_t*>* validIrisTemplates) //save tempaltes
{
	// TODO: 在此添加控件通知处理程序代码
	if (validIrisTemplates->size() == 0) {
		return;
	}

	int i;
	for (i = 0; i < 5; i++)
	{
		int index = i;
		wchar_t szFileName[512];

		wsprintf(szFileName, L"%s\\OUTPUT\\%s_%d_EYE_L_T.BIN", path, name, index);
		DeleteFileW(szFileName);
		wsprintf(szFileName, L"%s\\OUTPUT\\%s_%d_EYE_L_M.BIN", path, name, index);
		DeleteFileW(szFileName);

		wsprintf(szFileName, L"%s\\OUTPUT\\%s_%d_EYE_R_T.BIN", path, name, index);
		DeleteFileW(szFileName);
		wsprintf(szFileName, L"%s\\OUTPUT\\%s_%d_EYE_R_M.BIN", path, name, index);
		DeleteFileW(szFileName);
	}

	int index = 0;

	for (vector<IrisTemplates_t*>::iterator iter = validIrisTemplates->begin();
	iter != validIrisTemplates->end(); iter++)
	{
		wchar_t fileName[512];

		if ((*iter)->bLeftValid) {
			wsprintf(fileName, L"%s\\OUTPUT\\%s_%d_EYE_L_T.BIN", path, name, index);
			CCommonUtils::saveFile(fileName, (*iter)->leftEye.byTemplate, IRIS_TEMPLATE_SIZE);
			wsprintf(fileName, L"%s\\OUTPUT\\%s_%d_EYE_L_M.BIN", path, name, index);
			CCommonUtils::saveFile(fileName, (*iter)->leftEye.byTemplate, IRIS_TEMPLATE_SIZE);
		}

		if ((*iter)->bRightValid) {
			wsprintf(fileName, L"%s\\OUTPUT\\%s_%d_EYE_R_T.BIN", path, name, index);
			CCommonUtils::saveFile(fileName, (*iter)->rightEye.byTemplate, IRIS_TEMPLATE_SIZE);
			wsprintf(fileName, L"%s\\OUTPUT\\%s_%d_EYE_R_M.BIN", path, name, index);
			CCommonUtils::saveFile(fileName, (*iter)->rightEye.byTemplate, IRIS_TEMPLATE_SIZE);
		}

		updatePersonIrisTemplates(name, *iter);
		index++;
	}
}
