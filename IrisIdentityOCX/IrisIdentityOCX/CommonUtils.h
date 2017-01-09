#pragma once
#include <vector>
using namespace std;

class CCommonUtils
{
public:
	CCommonUtils();
	~CCommonUtils();

	static wchar_t* joinWString(wchar_t* wstr, ...);
	static void saveFile(wchar_t* pszFileName, BYTE* pbyData, int nLen);
	static void readFile(wchar_t* pszFileName, BYTE* pbyData, int nLen);
};

