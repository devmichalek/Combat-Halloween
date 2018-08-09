#include "xynode.h"

XYNode::XYNode(float cX, float cY, int ID)
{
	setXYID(cX, cY, ID);
}

XYNode::~XYNode()
{
	setXYID(-1, -1, -1);
}

void XYNode::setXYID(float cX, float cY, int ID)
{
	this->cX = cX;
	this->cY = cY;
	this->ID = ID;
}