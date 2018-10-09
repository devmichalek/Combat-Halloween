#include "kstates.h"

pla::KStates::KStates()
{
	resetState();
}

pla::KStates::~KStates()
{
	resetState();
}

void pla::KStates::resetState()
{
	state = STATES::IDLE;
	offset = 0;
	offset_max = 10;
	OPS = 22;
	align = ALIGN::RIGHT;
}