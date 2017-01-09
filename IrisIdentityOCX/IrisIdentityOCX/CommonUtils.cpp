#include "stdafx.h"
#include "CommonUtils.h"

CCommonUtils::CCommonUtils()
{
}


CCommonUtils::~CCommonUtils()
{
}

wchar_t* CCommonUtils::joinWString(wchar_t* wstr, ...) {
	va_list argp;
	wchar_t* para;
	vector<wchar_t*> paras;
	int totalLen = 0;

	paras.push_back(wstr);
	totalLen += lstrlenW(wstr) * 2;

	va_start(argp, wstr);

	while (1)
	{
		para = va_arg(argp, wchar_t *);
		totalLen += lstrlenW(para) * 2;
		if (lstrcmpW(para, L"/0") == 0)
			break;
		paras.push_back(para);
		
	}
	va_end(argp);

	wchar_t* joinedStr = (wchar_t*)malloc(totalLen);
	joinedStr[0] = L'\0';

	for (vector<wchar_t*>::iterator iter = paras.begin(); iter != paras.end(); iter++)
	{
		lstrcpyW(joinedStr + lstrlenW(joinedStr), *iter);
	}

	return joinedStr;
}

void CCommonUtils::saveFile(wchar_t* pszFileName, BYTE* pbyData, int nLen)
{
	if (pszFileName && pbyData && nLen > 0 && nLen < 100 * 1024 * 1024)
	{
		HANDLE file = CreateFile(pszFileName, GENERIC_WRITE, 0, NULL,
			CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
		if (file != NULL)
		{
			DWORD dwBytesWriten = 0;
			int nRet = WriteFile(file, pbyData, nLen, &dwBytesWriten, NULL);

			CloseHandle(file);
		}
	}
}

void CCommonUtils::readFile(wchar_t* pszFileName, BYTE* pbyData, int nLen) {
	if (pszFileName && pbyData && nLen > 0 && nLen < 100 * 1024 * 1024)
	{
		HANDLE file = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (file != NULL) {
			DWORD dwBytesRead = 0;
			int nRet = ReadFile(file, pbyData, nLen, &dwBytesRead, NULL);

			CloseHandle(file);
		}
	}
}
