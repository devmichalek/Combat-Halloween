#pragma once
#include <vector>
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>

struct LightPoint
{
	float radius;
	float maxDistance;
	sf::Glsl::Vec4 color;
	sf::Glsl::Vec2 gposition;

	LightPoint();
	virtual ~LightPoint();
	void free();
};

struct StaticLightPoint : public LightPoint
{
	sf::Vector2f* position;

	StaticLightPoint();
	StaticLightPoint(float radius, sf::Glsl::Vec4 color, sf::Vector2f position);
	~StaticLightPoint();
};

struct DynamicLightPoint : public LightPoint
{
	int current;
	int next, length;
	bool direction;
	sf::Vector2f* position;
	std::vector<sf::Vector2f> points;

	DynamicLightPoint();
	DynamicLightPoint(float radius, sf::Glsl::Vec4 color, std::vector<sf::Vector2f> points);
	~DynamicLightPoint();
	void calculate(const double &elapsedTime);
};

class LightPoints
{
	std::vector<float> radii;
	std::vector<float> maxDistances;		// calculated every frame
	std::vector<sf::Glsl::Vec4> colors;
	std::vector<sf::Vector2f*> positions;	// updated if there is a need
	std::vector<sf::Glsl::Vec2> gpositions;	// calculated every frame

	sf::Shader shader;
	sf::Clock clock;
	sf::Time frameTime, time;

public:
	LightPoints();
	~LightPoints();
	void free();
	void reset();

	void addStaticLightPoint(const StaticLightPoint &slp);
	void addDynamicLightPoint(const DynamicLightPoint &dlp);

	void mechanics(const double &elapsedTime);
	const sf::Shader &getShader() const;
};