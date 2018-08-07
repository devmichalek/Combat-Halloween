#include "xyquad.h"

XYQuad::XYQuad(XYNode* node)
{
	this->node = node;
	topLeft = nullptr;
	topRight = nullptr;
	botLeft = nullptr;
	botRight = nullptr;
}