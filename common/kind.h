#pragma once

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
			AMOUNT
		};

		explicit Kind() {};
		virtual ~Kind() {};
	};
}
