#include "xyquadtree.h"

XYQuadTree::XYQuadTree()
{
	mW = mH = 0
	count = 0;
	damage = 0;
	root = nullptr;
}

XYQuadTree::~XYQuadTree()
{
	count = 0;
	free(root);
}

bool XYQuadTree::empty()
{
	return root == nullptr;
}
/*
void XYQuadTree::remove(XYNode* node)
{
	if (!empty() && node)
	{
		removePrivate(node, root);
	}
}

void XYQuadTree::remove(float x, float y, int ID)
{
	if (!empty())
	{
		XYNode* node = new XYNode(x, y, ID);
		removePrivate(node, root);
		delete node;
	}
}
*/
bool XYQuadTree::insert(XYNode* node)
{
	++count;
	return insertPrivate(node, root);
}

void XYQuadTree::harm(sf::Rect<float> rect, float damage);
{
	if(!empty())
	{
		harmPrivate(rect, damage, root)
	}
}

void XYQuadTree::attack(sf::Rect<float> rect)
{
	if(!empty())
	{
		return harmPrivate(rect, root)
	}

	return false;
}

void XYQuadTree::mechanics(sf::Rect<float> rect, double elapsedTime)
{
	if(!empty())
	{
		int state = -1;
		return mechanicsPrivate(rect, state, elapsedTime, root)
	}
}






float XYQuadTree::getGreatestX()
{
	if (!empty())
	{
		float result = root->node->cX;
		findGreatestX(root, result);
		return result;
	}

	return 0;
}

float XYQuadTree::getGreatestY()
{
	if (!empty())
	{
		float result = root->node->cY;
		findGreatestY(root, result);
		return result;
	}

	return 0;
}

float XYQuadTree::getSmallestX()
{
	if (!empty())
	{
		float result = root->node->cX;
		findSmallestX(root, result);
		return result;
	}

	return 0;
}

float XYQuadTree::getSmallestY()
{
	if (!empty())
	{
		float result = root->node->cY;
		findSmallestY(root, result);
		return result;
	}

	return 0;
}

const int& XYQuadTree::getSize() const
{
	return count;
}

const float& XYQuadTree::getDamage() const
{
	return damage;
}




void XYQuadTree::free(XYQuad* quad)
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
void XYQuadTree::removeRoot()
{
	XYQuad* delQuad = root;

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

void XYQuadTree::removeMatch(XYQuad* parent, XYQuad* match, int dir)
{
	XYQuad* delQuad = match;

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

void XYQuadTree::removePrivate(XYNode* node, XYQuad* quad)
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
bool XYQuadTree::insertPrivate(XYNode* node, XYQuad* quad)
{
	if (empty())
	{
		root = new XYQuad(node);
		return true;
	}

	// top left
	else if (node->cX < quad->node->cX && node->cY > quad->node->cY)
	{
		if (quad->topLeft != nullptr)
			insertPrivate(node, quad->topLeft);
		else
		{
			quad->topLeft = new XYQuad(node);
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
			quad->topRight = new XYQuad(node);
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
			quad->botLeft = new XYQuad(node);
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
			quad->botRight = new XYQuad(node);
			return true;
		}
	}

	return false;
}

void XYQuadTree::harmPrivate(sf::Rect<float> &rect, float &damage, XYQuad* quad)
{
	if(quad->topLeft &&
	   quad->topLeft->node->cX >= rect.left &&
	   quad->topLeft->node->cX <= rect.left + rect.width &&
	   quad->topLeft->node->cY >= rect.top &&
	   quad->topLeft->node->cY <= rect.top + rect.height)
	{
		harmPrivate(rect, damage, quad->topLeft);
	}

	if(quad->topRight &&
	   quad->topRight->node->cX >= rect.left &&
	   quad->topRight->node->cX <= rect.left + rect.width &&
	   quad->topRight->node->cY >= rect.top &&
	   quad->topRight->node->cY <= rect.top + rect.height)
	{
		harmPrivate(rect, damage, quad->topRight);
	}

	if(quad->botLeft &&
	   quad->botLeft->node->cX >= rect.left &&
	   quad->botLeft->node->cX <= rect.left + rect.width &&
	   quad->botLeft->node->cY >= rect.top &&
	   quad->botLeft->node->cY <= rect.top + rect.height)
	{
		harmPrivate(rect, damage, quad->botLeft);
	}

	if(quad->botRight &&
	   quad->botRight->node->cX >= rect.left &&
	   quad->botRight->node->cX <= rect.left + rect.width &&
	   quad->botRight->node->cY >= rect.top &&
	   quad->botRight->node->cY <= rect.top + rect.height)
	{
		harmPrivate(rect, damage, quad->botRight);
	}

	if(!quad->node->isAlive())		return;

	float l = quad->node->getRealX(), w = quad->node->getRealWidth();	// left, width
	float t = quad->node->getRealY(), h = quad->node->getRealHeight();	// top, height

	if(rect.left + rect.width < l)	return;
	if(rect.left > l + w)			return;
	if(rect.top + rect.height < t)	return;
	if(rect.top > t + h)			return;

	quad->node->harm(damage);
}

bool XYQuadTree::attackPrivate(sf::Rect<float> &rect, XYQuad* quad)
{
	if(quad->topLeft &&
	   quad->topLeft->node->cX >= rect.left &&
	   quad->topLeft->node->cX <= rect.left + rect.width &&
	   quad->topLeft->node->cY >= rect.top &&
	   quad->topLeft->node->cY <= rect.top + rect.height)
	{
		return attackPrivate(rect, quad->topLeft);
	}

	if(quad->topRight &&
	   quad->topRight->node->cX >= rect.left &&
	   quad->topRight->node->cX <= rect.left + rect.width &&
	   quad->topRight->node->cY >= rect.top &&
	   quad->topRight->node->cY <= rect.top + rect.height)
	{
		return attackPrivate(rect, quad->topRight);
	}

	if(quad->botLeft &&
	   quad->botLeft->node->cX >= rect.left &&
	   quad->botLeft->node->cX <= rect.left + rect.width &&
	   quad->botLeft->node->cY >= rect.top &&
	   quad->botLeft->node->cY <= rect.top + rect.height)
	{
		return attackPrivate(rect, quad->botLeft);
	}

	if(quad->botRight &&
	   quad->botRight->node->cX >= rect.left &&
	   quad->botRight->node->cX <= rect.left + rect.width &&
	   quad->botRight->node->cY >= rect.top &&
	   quad->botRight->node->cY <= rect.top + rect.height)
	{
		return attackPrivate(rect, quad->botRight);
	}

	if(!quad->node->isAttacking())	return false;

	float l = quad->node->getAttackX(), w = quad->node->getAttackWidth();	// left, width
	float t = quad->node->getAttackY(), h = quad->node->getAttackHeight();	// top, height

	if(rect.left + rect.width < l)	return false;
	if(rect.left > l + w)			return false;
	if(rect.top + rect.height < t)	return false;
	if(rect.top > t + h)			return false;

	damage = quad->node->getDamage();
	return true;
}

void XYQuadTree::mechanicsPrivate(sf::Rect<float> &rect, int &state, double &elapsedTime, XYQuad* quad)
{
	if(quad->topLeft &&
	   quad->topLeft->node->cX >= rect.left &&
	   quad->topLeft->node->cX <= rect.left + rect.width &&
	   quad->topLeft->node->cY >= rect.top &&
	   quad->topLeft->node->cY <= rect.top + rect.height)
	{
		mechanicsPrivate(rect, quad->topLeft);
	}

	if(quad->topRight &&
	   quad->topRight->node->cX >= rect.left &&
	   quad->topRight->node->cX <= rect.left + rect.width &&
	   quad->topRight->node->cY >= rect.top &&
	   quad->topRight->node->cY <= rect.top + rect.height)
	{
		mechanicsPrivate(rect, quad->topRight);
	}

	if(quad->botLeft &&
	   quad->botLeft->node->cX >= rect.left &&
	   quad->botLeft->node->cX <= rect.left + rect.width &&
	   quad->botLeft->node->cY >= rect.top &&
	   quad->botLeft->node->cY <= rect.top + rect.height)
	{
		mechanicsPrivate(rect, quad->botLeft);
	}

	if(quad->botRight &&
	   quad->botRight->node->cX >= rect.left &&
	   quad->botRight->node->cX <= rect.left + rect.width &&
	   quad->botRight->node->cY >= rect.top &&
	   quad->botRight->node->cY <= rect.top + rect.height)
	{
		mechanicsPrivate(rect, quad->botRight);
	}

	if(quad->node->getState() < 0)
		return;

	quad->node->mechanics(elapsedTime);
}

XYNode* XYQuadTree::findSmallest(XYQuad* quad)
{
	if (quad->botLeft)
		return findSmallest(quad->botLeft);

	return quad->node;
}

XYNode* XYQuadTree::findGreatest(XYQuad* quad)
{
	if (quad->topRight)
		return findGreatest(quad->topRight);

	return quad->node;
}

void XYQuadTree::findSmallestX(XYQuad* quad, float& v)
{
	if (quad->topLeft)
		findSmallestX(quad->topLeft, v);

	if (quad->botLeft)
		findSmallestX(quad->botLeft, v);

	if (quad->node->cX < v)
		v = quad->node->cX;
}

void XYQuadTree::findGreatestX(XYQuad* quad, float& v)
{
	if (quad->topRight)
		findGreatestX(quad->topRight, v);

	if (quad->botRight)
		findGreatestX(quad->botRight, v);

	if (quad->node->cX > v)
		v = quad->node->cX;
}

void XYQuadTree::findSmallestY(XYQuad* quad, float& v)
{
	if (quad->botLeft)
		findSmallestY(quad->botLeft, v);

	if (quad->botRight)
		findSmallestY(quad->botRight, v);

	if (quad->node->cY < v)
		v = quad->node->cY;
}

void XYQuadTree::findGreatestY(XYQuad* quad, float& v)
{
	if (quad->topLeft)
		findGreatestY(quad->topLeft, v);

	if (quad->topRight)
		findGreatestY(quad->topRight, v);

	if (quad->node->cY > v)
		v = quad->node->cY;
}