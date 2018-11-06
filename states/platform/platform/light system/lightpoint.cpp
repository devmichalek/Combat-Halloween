#include <lightpoint.h>

LightPoint::LightPoint()
{
	free();
}

LightPoint::~LightPoint()
{
	free();
}

void LightPoint::free()
{
	radius = 0.0f;
	maxDistance = 0.0f;
	color = sf::Glsl::Vec4(1.0f, 1.0f, 1.0f, 2.0f);
	gposition = sf::Glsl::Vec2(0.0f, 0.0f);
}

StaticLightPoint::StaticLightPoint()
{
	position = nullptr;
}

StaticLightPoint::StaticLightPoint(float radius, sf::Glsl::Vec4 color, sf::Vector2f position)
{
	this->radius = radius;
	maxDistance = 0.0f;
	this->color = color;
	this->position = new sf::Vector2f(position);
	gposition = sf::Glsl::Vec2(0.0f, 0.0f);
}

StaticLightPoint::~StaticLightPoint()
{
	if (position)
	{
		delete position;
		position = nullptr;
	}
}