#pragma once
#include <vector>
using namespace std;

class CCommonUtils
{
public:
	CCommonUtils();
	~CCommonUtils();

	static wchar_t* joinWString(wchar_t* wstr, ...);
	static void SaveFile(wchar_t* pszFileNam, BYTE* pbyData, int nLen);
};

