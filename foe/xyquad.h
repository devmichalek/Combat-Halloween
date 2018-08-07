#pragma once
#include "xynode.h"

struct XYQuad
{
	XYNode* node;
	XYQuad *topLeft, *topRight;
	XYQuad *botLeft, *botRight;
	XYQuad(XYNode* node = nullptr);
};