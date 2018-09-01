#include "kstates.h"

KStates::KStates()
{
	resetState();
}

KStates::~KStates()
{
	resetState();
}

void KStates::resetState()
{
	state = STATES::IDLE;
	offset = 0;
	offset_max = 10;
	OPS = 22;
	align = ALIGN::RIGHT;
}