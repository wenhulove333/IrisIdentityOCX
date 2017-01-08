#pragma once
#include "Magpie\MagpieApi.h"

class CEnrolledIrisTemplates
{
public:
	CEnrolledIrisTemplates();
	~CEnrolledIrisTemplates();

	virtual bool compareTemplates(void* expandablePara, char* cameraType, IrisTemplates_t* matchTemplates, wchar_t* result) = 0;
};

