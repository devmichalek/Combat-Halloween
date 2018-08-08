#include "foenode.h"

bool FoeNode::contains(Rect* &a, Rect* &b)
{
	if (a->left + a->width < b->left)
		return false;
	if (a->left > b->left + b->width)
		return false;
	if (a->top + a->height < b->top)
		return false;
	if (a->top > b->top + b->height)
		return false;

	return true;
}