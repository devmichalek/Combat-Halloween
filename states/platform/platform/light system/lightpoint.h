// This file is part of game called 'Combat Halloween'
// Author: Adrian Michalek
// Date: 09.11.2018
// Read more about license (MIT) and readme here:
// https://github.com/devmichalek/Combat-Halloween

#pragma once
#include <vector>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>
#include "treedefinitions.h"

namespace pla
{
	struct LightPoint
	{
		float radius;
		//float maxDistance;
		sf::Glsl::Vec4 color;
		//sf::Glsl::Vec2 gposition;

		LightPoint();
		LightPoint(const LightPoint &lp);
		LightPoint(float radius, sf::Glsl::Vec4 color);
		virtual ~LightPoint();
		void free();
	};

	struct StaticLightPoint final : public LightPoint
	{
		sf::Vector2f position;

		StaticLightPoint();
		StaticLightPoint(const LightPoint &lp, const sf::Vector2f &position);
		StaticLightPoint(const float &radius, const sf::Glsl::Vec4 &color, const sf::Vector2f &position);
		~StaticLightPoint();
	};

	class LightUnit
	{
		virtual void free() = 0;
	public:
		LightUnit() {}
		virtual ~LightUnit() {}
		virtual void calculate(const double &elapsedTime) = 0;
	};

	class StaticLightUnit final : public LightUnit // right know empty, maybe new functions in the future?
	{
		void free() {}
	public:
		StaticLightUnit() {}
		~StaticLightUnit() {}
		void calculate(const double &elapsedTime) {}
	};

	class DynamicLightUnit final : public LightUnit
	{
		int current;
		int next;
		size_t length;
		bool direction;
		sf::Vector2f* position;
		std::vector<sf::Vector2f> points;
	public:
		DynamicLightUnit(sf::Vector2f* &address, const std::vector<sf::Vector2f> &points);
		~DynamicLightUnit();
	private:
		void free();
	public:
		void calculate(const double &elapsedTime);

		/*virtual bool operator==(const DynamicLightUnit &dlu) const
		{
			return *position == *dlu.position;
		}*/
	};

	struct DynamicLightPoint final : public LightPoint
	{
		std::vector<sf::Vector2f> points;

		DynamicLightPoint();
		DynamicLightPoint(const LightPoint &lp, const std::vector<sf::Vector2f> &points);
		DynamicLightPoint(const float &radius, const sf::Glsl::Vec4 &color, const std::vector<sf::Vector2f> &points);
		~DynamicLightPoint();
	};
}