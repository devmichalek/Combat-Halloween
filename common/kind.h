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
			WORLDTITLE = static_cast<int>(MAX_ALPHA) - 1,
			WORLDDESCRIPTION = static_cast<int>(MAX_ALPHA),
			AMOUNT
		};

		explicit Kind() {};
		virtual ~Kind() {};
	};
}
