#pragma once
#include "sprite.h"
#include "kstates.h"
#include "kcoxing.h"
#include "kspecs.h"

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

	void mechanics(const double &elapsedTime);
	void switchCollision();	// turn on/off drawing collision

	sf::IntRect& getRect();
	const sf::IntRect& getAttackRect();
	bool isAlive();
	bool isAttack();

	bool moveLeft(const double &elapsedTime);	void undoMoveLeft(const double &elapsedTime);
	bool moveRight(const double &elapsedTime);	void undoMoveRight(const double &elapsedTime);
	void idle(const double &elapsedTime);
	bool jump(const double &elapsedTime);		void undoJump(const double &elapsedTime);
	void attack();
	void rest(const double &elapsedTime);
	bool gravity();								void undoGravity();
	void read(std::string &str);
	void setVolume(float volume);

private:
	void walk(const double &elapsedTime);
	void setPosition();
	void setAlign();
	void setRect();
	void setAttackRect();
};