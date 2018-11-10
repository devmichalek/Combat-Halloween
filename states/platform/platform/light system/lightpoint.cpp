// This file is part of game called 'Combat Halloween'
// Author: Adrian Michalek
// Date: 09.11.2018
// Read more about license (MIT) and readme here:
// https://github.com/devmichalek/Combat-Halloween

#include <lightpoint.h>
#include <cassert>

pla::LightPoint::LightPoint()
{
	free();
}

pla::LightPoint::LightPoint(const LightPoint &lp)
{
	radius = lp.radius;
	//maxDistance = lp.maxDistance;
	color = lp.color;
	//gposition = lp.gposition;
}

pla::LightPoint::LightPoint(float radius, sf::Glsl::Vec4 color)
{
	this->radius = radius;
	//this->maxDistance = maxDistance;
	this->color = color;
	//this->gposition = gposition;
}

pla::LightPoint::~LightPoint()
{
	free();
}

void pla::LightPoint::free()
{
	radius = 0.0f;
	//maxDistance = 0.0f;
	color = sf::Glsl::Vec4(1.0f, 1.0f, 1.0f, 2.0f);
	//gposition = sf::Glsl::Vec2(0.0f, 0.0f);
}



pla::StaticLightPoint::StaticLightPoint()
{
	position = sf::Glsl::Vec2(0.0f, 0.0f);
}

pla::StaticLightPoint::StaticLightPoint(const LightPoint &lp, const sf::Vector2f &position) : LightPoint(lp)
{
	this->position = position;
}

pla::StaticLightPoint::StaticLightPoint(const float &radius, const sf::Glsl::Vec4 &color, const sf::Vector2f &position)
{
	this->radius = radius;
	//maxDistance = 0.0f;
	this->color = color;
	this->position = sf::Vector2f(position);
	//gposition = sf::Glsl::Vec2(0.0f, 0.0f);
}

pla::StaticLightPoint::~StaticLightPoint()
{
	position = sf::Glsl::Vec2(0.0f, 0.0f);
}



pla::DynamicLightUnit::DynamicLightUnit(sf::Vector2f* &address, const std::vector<sf::Vector2f> &points)
{
	current = 0;
	next = 1;
	direction = true;
	position = address;
	this->points = points;
	this->points.shrink_to_fit();
	length = points.size();
}

pla::DynamicLightUnit::~DynamicLightUnit()
{
	free();
}

void pla::DynamicLightUnit::free()
{
	current = 0;
	next = 1;
	length = 0;
	direction = true;

	if (position) // should never happen...
	{
		delete position;
		position = nullptr;
	}

	if(!points.empty())
		points.clear();
}

void pla::DynamicLightUnit::calculate(const double &elapsedTime)
{
	//...
}



pla::DynamicLightPoint::DynamicLightPoint()
{
	points = {};
}

pla::DynamicLightPoint::DynamicLightPoint(const LightPoint &lp, const std::vector<sf::Vector2f> &points) : LightPoint(lp)
{
	this->points = points;
	this->points.shrink_to_fit();
}

pla::DynamicLightPoint::DynamicLightPoint(const float &radius, const sf::Glsl::Vec4 &color, const std::vector<sf::Vector2f> &points)
{
	this->points = points;
	this->points.shrink_to_fit();
}

pla::DynamicLightPoint::~DynamicLightPoint()
{
	if (!points.empty())
		points.clear();
}
