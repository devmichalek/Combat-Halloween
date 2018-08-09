#pragma once

template<class Node>
struct XYQuad
{
	Node* node;
	XYQuad *topLeft, *topRight;
	XYQuad *botLeft, *botRight;
	XYQuad(Node* node = nullptr);
};