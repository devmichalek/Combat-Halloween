#pragma once

class XYNode
{
public:
	int ID;
	float cX, cY;	// center x, center y

	XYNode(float cX = -1, float cY = -1, int ID = -1);
	virtual ~XYNode();
	void setXYID(float cX = -1, float cY = -1, int ID = -1);
};