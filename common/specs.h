#pragma once
#include <vector>

namespace cmm
{
	struct Specs
	{
		enum FEATURES
		{
			HEART_POINTS = 0,
			MAGIC_POINTS,
			ARMOUR,
			MAGIC_RESISTANT,
			MOVEMENT_SPEED,
			DAMAGE,
			MAGIC_DAMAGE,
			LUCK,
			EXPERIENCE,
			LEVEL,
			SIZE
		};
	protected:
		static std::vector<int> features;

	public:
		explicit Specs();
		virtual ~Specs();
	};
}