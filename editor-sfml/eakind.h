#pragma once

class EAKind
{
protected:
	enum KIND
	{
		VOID = -1,
		KNIGHT,
		TILE,
		UNVISIBLE_TILE,
		LANDSCAPE,
		FOE,
		LIGHTPOINT,
		AMOUNT
	};

	int type;
	int chosen;
public:
};