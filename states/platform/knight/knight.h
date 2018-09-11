#pragma once
#include "sprite.h"
#include "kstates.h"
#include "kcoxing.h"
#include "kspecs.h"

class Knight : public KStates
{
	KCoxing coxing;
	KSpecs specs;
	std::vector<cmm::Sprite*> sprites;

	sf::Vector2f xy;	// represent x center and bot
	sf::IntRect rect;
	sf::IntRect attackRect;

	// --- TEST ---
	bool collisionMode;
	sf::RectangleShape shape;
	sf::RectangleShape attackShape;
	// ---      ---

public:
	Knight();
	~Knight();
private:
	void free();
public:
	void reset();

	void set(const float &x, const float &y);	// set xy start position
	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window/*, sf::Shader &shader*/);

	void mechanics(const double &elapsedTime);
	void switchCollision();	// turn on/off drawing collision

	const sf::IntRect& getRect();
	const sf::IntRect& getAttackRect();
	bool isAlive();
	bool isAttack();

	void gravity();
	void undoGravity();

private:
	void walk(const double &elapsedTime);
	void setPosition();
	void setAlign();
	void setRect();
	void setAttackRect();
};