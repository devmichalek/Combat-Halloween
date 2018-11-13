#pragma once
#include <vector>

namespace cmm
{
	class Specs
	{
	protected:
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

		static std::vector<int> features;

	public:
		explicit Specs();
		virtual ~Specs();
	};
}