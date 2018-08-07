#pragma once

struct XYNode
{
	int ID;
	float cX, cY;	// center x, center y

	XYNode(float cX = -1, float cY = -1, int ID = -1);
	virtual ~XYNode();
	void set(float cX = -1, float cY = -1, int ID = -1);
};