#pragma once
#include "colors.h"

namespace cmm
{
	struct Kind
	{
		enum KIND
		{
			VOID = -1,
			KNIGHT,
			TILE,
			UNVISIBLE_TILE,
			LANDSCAPE,
			FOE,
			LIGHTPOINT,
			LAST,
			WORLDTITLE = 0xFF,
			WORLDDESCRIPTION = 0xFE,
			AMOUNT
		};

		explicit Kind() {};
		virtual ~Kind() {};
	};
}
