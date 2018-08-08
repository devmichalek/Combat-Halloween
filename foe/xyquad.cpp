#include "xyquad.h"

// includes of classes that would use XYQuad
#include "foenode.h"

template<class Node>
XYQuad<Node>::XYQuad(Node* node)
{
	this->node = node;
	topLeft = nullptr;
	topRight = nullptr;
	botLeft = nullptr;
	botRight = nullptr;
}

// definitions of classes that would use XYQuad
template class XYQuad <FoeNode>;