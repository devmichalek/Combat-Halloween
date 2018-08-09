#pragma once

template<class Node>
class XYQuad
{
public:
	Node* node;
	XYQuad *topLeft, *topRight;
	XYQuad *botLeft, *botRight;
	XYQuad(Node* node = nullptr);
};