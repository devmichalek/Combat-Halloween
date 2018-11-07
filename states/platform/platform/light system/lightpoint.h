#pragma once
#include <vector>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>

#define _SCL_SECURE_NO_WARNINGS
#include "treedefinitions.h"

struct LightPoint
{
	float radius;
	float maxDistance;
	sf::Glsl::Vec4 color;
	sf::Glsl::Vec2 gposition;

	LightPoint();
	LightPoint(const LightPoint &lp);
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

class DynamicLightUnit final
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

	virtual bool operator==(const DynamicLightUnit &dlu) const
	{
		return *position == *dlu.position;
	}
};

struct DynamicLightPoint final : public LightPoint
{
	std::vector<sf::Vector2f> points;

	DynamicLightPoint();
	DynamicLightPoint(const LightPoint &lp, const std::vector<sf::Vector2f> &points);
	DynamicLightPoint(const float &radius, const sf::Glsl::Vec4 &color, const std::vector<sf::Vector2f> &points);
	~DynamicLightPoint();
};



class LightPoints final
{
	float screen_w;
	float screen_h;

	std::vector<float> radii;
	std::vector<float> maxDistances;		// calculated every frame
	std::vector<sf::Glsl::Vec4> colors;
	std::vector<sf::Vector2f*> positions;	// updated if there is a need
	std::vector<sf::Glsl::Vec2> gpositions;	// calculated every frame

	using StaticLPBox = Box;
	using DynamicLPBox = std::pair<Box, DynamicLightUnit>;
	typedef bgi::rtree<StaticLPBox, bgi::quadratic<16>> StaticLPTree;
	typedef bgi::rtree<DynamicLPBox, bgi::quadratic<16>> DynamicLPTree;
	StaticLPTree* staticLPTree;
	DynamicLPTree* dynamicLPTree;
	std::vector<StaticLPTree> staticLPResult;
	std::vector<DynamicLPTree> dynamicLPResult;

	size_t length;
	size_t ssize, dsize;
	sf::Shader* shader;
	sf::Clock clock;
	sf::Time time, frameTime;

public:
	LightPoints();
	~LightPoints();
private:
	void free();
public:
	void reset();

	// 0. init
	// 1. addStaticLightPoint / addDynamicLightPoint
	// 2. prepare
	// 3. reset -> 1. / free -> 0.

	void init(const float &screen_w, const float &screen_h);
	void prepare(const int &count);

private:
	void add(LightPoint lp);
public:
	void addStaticLightPoint(StaticLightPoint &slp);
	void addDynamicLightPoint(DynamicLightPoint &dlp);

	void mechanics(const double &elapsedTime, const float &x, const float &y);
	sf::Shader* &getShader();
};