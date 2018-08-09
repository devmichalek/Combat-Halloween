#include "xynode.h"

XYNode::XYNode(float cX, float cY, int ID)
{
	set(cX, cY, ID);
}

XYNode::~XYNode()
{
	set(-1, -1, -1);
}

void XYNode::set(float cX, float cY, int ID)
{
	this->cX = cX;
	this->cY = cY;
	this->ID = ID;
}