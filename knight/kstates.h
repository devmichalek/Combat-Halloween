#pragma once

struct KStates // Knight States
{
protected:
	enum STATES
	{
		VOID = -1,
		IDLE = 0,
		WALK,
		RUN,
		JUMP,
		ATTACK,
		JUMP_ATTACK,
		DIE,
		SIZE
	};

	int state;
	float offset;
	int offset_max;
	int OPS; // offsets per second

	enum ALIGN
	{
		LEFT = 0,
		RIGHT
	};

	bool align;

public:
	KStates();
	~KStates();
	void resetState();
};
