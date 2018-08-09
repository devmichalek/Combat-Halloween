#include "xyquadtree.h"

// includes of classes that would use XYQuadTree
#include "xyquad.h"
#include "foenode.h"

template<class Node, class Quad>
XYQuadTree<Node, Quad>::XYQuadTree()
{
	count = 0;
	root = nullptr;
}

template<class Node, class Quad>
XYQuadTree<Node, Quad>::~XYQuadTree()
{
	count = 0;
	free(root);
}

template<class Node, class Quad>
void XYQuadTree<Node, Quad>::incinerate()
{
	count = 0;
	free(root);
}

template<class Node, class Quad>
bool XYQuadTree<Node, Quad>::empty()
{
	return root == nullptr;
}
/*
template<class Node, class Quad>
void XYQuadTree<Node, Quad>::remove(Node* node)
{
	if (!empty() && node)
	{
		removePrivate(node, root);
	}
}

template<class Node, class Quad>
void XYQuadTree<Node, Quad>::remove(float x, float y, int ID)
{
	if (!empty())
	{
		Node* node = new Node(x, y, ID);
		removePrivate(node, root);
		delete node;
	}
}
*/

template<class Node, class Quad>
bool XYQuadTree<Node, Quad>::insert(Node* node)
{
	++count;
	return insertPrivate(node, root);
}



template<class Node, class Quad>
float XYQuadTree<Node, Quad>::getGreatestX()
{
	if (!empty())
	{
		float result = root->node->cX;
		findGreatestX(root, result);
		return result;
	}

	return 0;
}

template<class Node, class Quad>
float XYQuadTree<Node, Quad>::getGreatestY()
{
	if (!empty())
	{
		float result = root->node->cY;
		findGreatestY(root, result);
		return result;
	}

	return 0;
}

template<class Node, class Quad>
float XYQuadTree<Node, Quad>::getSmallestX()
{
	if (!empty())
	{
		float result = root->node->cX;
		findSmallestX(root, result);
		return result;
	}

	return 0;
}

template<class Node, class Quad>
float XYQuadTree<Node, Quad>::getSmallestY()
{
	if (!empty())
	{
		float result = root->node->cY;
		findSmallestY(root, result);
		return result;
	}

	return 0;
}

template<class Node, class Quad>
const int& XYQuadTree<Node, Quad>::getSize() const
{
	return count;
}






template<class Node, class Quad>
void XYQuadTree<Node, Quad>::free(Quad* quad)
{
	if (quad)
	{
		if (quad->topLeft)	free(quad->topLeft);
		if (quad->topRight)	free(quad->topRight);
		if (quad->botLeft)	free(quad->botLeft);
		if (quad->botRight)	free(quad->botRight);

		delete quad;
		quad = nullptr;
	}
}
/*
template<class Node, class Quad>
void XYQuadTree<Node, Quad>::removeRoot()
{
	Quad* delQuad = root;

	// No children.
	if (!root->topLeft && !root->topRight && !root->botLeft && !root->botRight)
	{
		--count;
		root = nullptr;
		delete delQuad;
	}

	// One child.
	else if (root->topLeft && !root->topRight && !root->botLeft && !root->botRight) // top left
	{
		--count;
		root = root->topLeft;
		delete delQuad;
	}
	else if (!root->topLeft && root->topRight && !root->botLeft && !root->botRight) // top right
	{
		--count;
		root = root->topRight;
		delete delQuad;
	}
	else if (!root->topLeft && !root->topRight && root->botLeft && !root->botRight) // bot left
	{
		--count;
		root = root->botLeft;
		delete delQuad;
	}
	else if (!root->topLeft && !root->topRight && !root->botLeft && root->botRight) // bot right
	{
		--count;
		root = root->botRight;
		delete delQuad;
	}

	// 4, 3 or 2 children
	//else
	//{
	//	// Smallest in the top left subtree.
	//	int smallest = *findSmallest(root->right);
	//	removePrivate(smallest, root);
	//	root->key = smallest;
	//}
}

template<class Node, class Quad>
void XYQuadTree<Node, Quad>::removeMatch(Quad* parent, Quad* match, int dir)
{
	Quad* delQuad = match;

	int childrenCount = 0;
	if (match->topLeft)		++childrenCount;
	if (match->topRight)	++childrenCount;
	if (match->botLeft)		++childrenCount;
	if (match->botRight)	++childrenCount;

	// No children.
	if (childrenCount == 0)
	{
		--count;
		switch (dir)
		{
		case 0: parent->topLeft = nullptr;	break;
		case 1: parent->topRight = nullptr; break;
		case 2: parent->botLeft = nullptr;	break;
		case 3: parent->botRight = nullptr; break;
		}
		match = nullptr;
		delete delQuad;
	}

	// One child.
	else if(childrenCount == 1)
	{
		if (match->topLeft) // top left
		{
			switch (dir)
			{
			case 0: parent->topLeft = match->topLeft;	break;
			case 1: parent->topRight = match->topLeft; break;
			case 2: parent->botLeft = match->topLeft;	break;
			case 3: parent->botRight = match->topLeft; break;
			}
			match->topLeft = nullptr;
		}
		else if (match->topRight) // top right
		{
			switch (dir)
			{
			case 0: parent->topLeft = match->topRight;	break;
			case 1: parent->topRight = match->topRight; break;
			case 2: parent->botLeft = match->topRight;	break;
			case 3: parent->botRight = match->topRight; break;
			}
			match->topRight = nullptr;
		}
		else if (match->botLeft) // bot left
		{
			switch (dir)
			{
			case 0: parent->topLeft = match->botLeft;	break;
			case 1: parent->topRight = match->botLeft; break;
			case 2: parent->botLeft = match->botLeft;	break;
			case 3: parent->botRight = match->botLeft; break;
			}
			match->botLeft = nullptr;
		}
		else // bot right
		{
			switch (dir)
			{
			case 0: parent->topLeft = match->botRight;	break;
			case 1: parent->topRight = match->botRight; break;
			case 2: parent->botLeft = match->botRight;	break;
			case 3: parent->botRight = match->botRight; break;
			}
			match->botRight = nullptr;
		}

		--count;
		match = nullptr;
		delete delQuad;
	}

	// Two children
	else if (childrenCount == 2)
	{

	}

	// Three children
	else if (childrenCount == 3)
	{

	}

	// Four children
	else
	{

	}

	// 2 children.
	else
	{
		int smallest = *findSmallest(match->right);
		removePrivate(smallest, match);
		match->key = smallest;
	}
}

template<class Node, class Quad>
void XYQuadTree<Node, Quad>::removePrivate(Node* node, Quad* quad)
{
	if (root->node->ID == node->ID)
	{
		removeRoot();
	}
	else
	{
		if (node->cX < quad->node->cX && node->cY > quad->node->cY)			// top left
		{
			if (quad->node->ID == node->ID)	removeMatch(quad, quad->topLeft, 0);
			else							removePrivate(node, quad->topLeft);
		}
		else if (node->cX >= quad->node->cX && node->cY >= quad->node->cY)	// top right
		{
			if (quad->node->ID == node->ID)	removeMatch(quad, quad->topRight, 1);
			else							removePrivate(node, quad->topRight);
		}
		else if (node->cX < quad->node->cX && node->cY < quad->node->cY)	// bot left
		{
			if (quad->node->ID == node->ID)	removeMatch(quad, quad->botLeft, 2);
			else							removePrivate(node, quad->botLeft);
		}
		else if (node->cX >= quad->node->cX && node->cY <= quad->node->cY)	// bot right
		{
			if (quad->node->ID == node->ID)	removeMatch(quad, quad->botRight, 3);
			else							removePrivate(node, quad->botRight);
		}
	}
}
*/

template<class Node, class Quad>
bool XYQuadTree<Node, Quad>::insertPrivate(Node* node, Quad* quad)
{
	if (empty())
	{
		root = new Quad(node);
		return true;
	}

	// top left
	else if (node->cX < quad->node->cX && node->cY > quad->node->cY)
	{
		if (quad->topLeft != nullptr)
			insertPrivate(node, quad->topLeft);
		else
		{
			quad->topLeft = new Quad(node);
			return true;
		}
	}

	// top right
	else if (node->cX >= quad->node->cX && node->cY >= quad->node->cY)
	{
		if (quad->topRight != nullptr)
			insertPrivate(node, quad->topRight);
		else
		{
			quad->topRight = new Quad(node);
			return true;
		}
	}

	// bot left
	else if (node->cX < quad->node->cX && node->cY < quad->node->cY)
	{
		if (quad->botLeft != nullptr)
			insertPrivate(node, quad->botLeft);
		else
		{
			quad->botLeft = new Quad(node);
			return true;
		}
	}

	// bot right
	else if (node->cX >= quad->node->cX && node->cY <= quad->node->cY)
	{
		if (quad->botRight != nullptr)
			insertPrivate(node, quad->botRight);
		else
		{
			quad->botRight = new Quad(node);
			return true;
		}
	}

	return false;
}

/*
template<class Node, class Quad>
Node* XYQuadTree<Node, Quad>::findSmallest(Quad* quad)
{
	if (quad->botLeft)
		return findSmallest(quad->botLeft);

	return quad->node;
}

template<class Node, class Quad>
Node* XYQuadTree<Node, Quad>::findGreatest(Quad* quad)
{
	if (quad->topRight)
		return findGreatest(quad->topRight);

	return quad->node;
}
*/

template<class Node, class Quad>
void XYQuadTree<Node, Quad>::findSmallestX(Quad* quad, float& v)
{
	if (quad->topLeft)
		findSmallestX(quad->topLeft, v);

	if (quad->botLeft)
		findSmallestX(quad->botLeft, v);

	if (quad->node->cX < v)
		v = quad->node->cX;
}

template<class Node, class Quad>
void XYQuadTree<Node, Quad>::findGreatestX(Quad* quad, float& v)
{
	if (quad->topRight)
		findGreatestX(quad->topRight, v);

	if (quad->botRight)
		findGreatestX(quad->botRight, v);

	if (quad->node->cX > v)
		v = quad->node->cX;
}

template<class Node, class Quad>
void XYQuadTree<Node, Quad>::findSmallestY(Quad* quad, float& v)
{
	if (quad->botLeft)
		findSmallestY(quad->botLeft, v);

	if (quad->botRight)
		findSmallestY(quad->botRight, v);

	if (quad->node->cY < v)
		v = quad->node->cY;
}

template<class Node, class Quad>
void XYQuadTree<Node, Quad>::findGreatestY(Quad* quad, float& v)
{
	if (quad->topLeft)
		findGreatestY(quad->topLeft, v);

	if (quad->topRight)
		findGreatestY(quad->topRight, v);

	if (quad->node->cY > v)
		v = quad->node->cY;
}

/*
Example
template<class Node, class Quad>
bool XYQuadTree<Node, Quad>::containsPrivate(Quad* quad, Rect* rect)
{
	if (!quad)										return false;	// quad does not exist
	if (quad->node->cX < rect->left)				return false;	// point is on the left outside of area
	if (quad->node->cX > rect->left + rect->width)	return false;	// point is on the right outside of area
	if (quad->node->cY < rect->top)					return false;	// point is above the area
	if (quad->node->cY > rect->top + rect->height)	return false;	// point is below the area
	return true;
}
*/

// definitions of classes that would use XYQuadTree
template class XYQuadTree <FoeNode, XYQuad<FoeNode>>;