#pragma once
#include "sprite.h"
#include "kstates.h"
#include "kcoxing.h"
#include "kspecs.h"
#include "eventwindow.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Knight : public KStates
{
	float screen_w;
	float screen_h;
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

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window/*, sf::Shader &shader*/);

	void mechanics(const float &elapsedTime);
	void switchCollision();	// turn on/off drawing collision

	sf::IntRect& getRect();
	const sf::IntRect& getAttackRect();
	//const int& getX() const;
	//const int& getY() const;
	bool isAlive();
	bool isAttack();
	bool isLeftAligned() const;
	const bool &isRightAligned() const;

	bool moveLeft(const float &elapsedTime);	void undoMoveLeft(const float &elapsedTime);
	bool moveRight(const float &elapsedTime);	void undoMoveRight(const float &elapsedTime);
	void idle(const float &elapsedTime);
	bool jump(const float &elapsedTime);		void undoJump(const float &elapsedTime);
	void attack();
	void rest();
	void gravity();								void undoGravity();
	void read(std::string &str);
	void setVolume(float volume);

private:
	void walk(const double &elapsedTime);
	void setPosition();
	void setAlign();
	void setRect();
	void setAttackRect();
};