// This file is part of game called 'Combat Halloween'
// Author: Adrian Michalek
// Date: 09.11.2018
// Read more about license (MIT) and readme here:
// https://github.com/devmichalek/Combat-Halloween

#pragma once
#include "lightpoint.h"

namespace pla
{
	class LightSystem final
	{
		float screen_w;
		float screen_h;

		// maxDistances, gpositions and subcolors are "local" they are vectors to speed up calculations
		// previously they were part of every light point, right know they are dynamicly set and prepared

		std::vector<float> radii;
		std::vector<float> maxDistances;		// calculated every frame
		std::vector<sf::Glsl::Vec4> colors;
		std::vector<sf::Glsl::Vec4> subcolors;
		std::vector<sf::Vector2f*> positions;	// updated if there is a need
		std::vector<sf::Glsl::Vec2> gpositions;	// calculated every frame
		std::vector<LightUnit*> units;

		using LightPointBox = std::pair<Box, int>; // box, id
		typedef bgi::rtree<LightPointBox, bgi::quadratic<16>> StaticLPTree;
		typedef bgi::rtree<LightPointBox, bgi::quadratic<16>> DynamicLPTree;
		StaticLPTree* staticLPTree;
		DynamicLPTree* dynamicLPTree;
		std::vector<LightPointBox> lightPointResult;

		size_t length;
		size_t ssize, dsize;
		sf::Shader* shader;
		sf::Clock clock;
		sf::Time time, frameTime;

	public:
		LightSystem();
		~LightSystem();
	private:
		void free();
	public:
		void reset();

		// 0. init()
		// 1. addStaticLightPoint() / addDynamicLightPoint()
		// 2. prepare()
		// 3. reset() -> 1. or destroy -> free() -> 0.

		void init(const float &screen_w, const float &screen_h);
		void prepare(const int &count);

	private:
		void add(LightPoint lp);
		void addStaticLightPoint(StaticLightPoint &slp);
		void addDynamicLightPoint(DynamicLightPoint &dlp);
	public:
		void read(std::vector<std::string> &vec);

		void mechanics(const double &elapsedTime, const float &x, const float &y);
		sf::Shader* &getShader();
	};

	// To do:
	// Mutexes and threads -> thread calculates and predicts the values for shader.
	// Risk -> while reading values for shader the thread may use it at the same time.
}