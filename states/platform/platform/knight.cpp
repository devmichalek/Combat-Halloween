#include "knight.h"
#include "loading.h"
#include <boost/lexical_cast.hpp>

pla::Knight::Knight()
{
	free();
}

pla::Knight::~Knight()
{
	free();
}

void pla::Knight::free()
{
	screen_w = screen_h = 0;

	if (!sprites.empty())
	{
		for (auto &it : sprites)
		{
			delete it;
			it = nullptr;
		}

		sprites.clear();
	}

	reset();
}

void pla::Knight::reset()
{
	resetState();
	coxing.reset();

	// --- TEST ---
	collisionMode = false;
	// ---      ---
}



void pla::Knight::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	// Load Sprites.
	for (int i = 0; i < STATES::SIZE; ++i)
	{
		sprites.push_back(new cmm::Sprite);
		Loading::add(sprites[i]->load("images/platform/knight/" + std::to_string(i) + ".png", offset_max));
		if (Loading::isError())	return;
		sprites[i]->setScale(specs.scale, specs.scale);
	}

	// Set rects size
	rect.width = static_cast<int>(sprites[IDLE]->getWidth() * 0.75);
	rect.height = static_cast<int>(sprites[IDLE]->getHeight() * 0.9);
	attackRect.width = static_cast<int>(sprites[IDLE]->getWidth() * 0.7);
	attackRect.height = static_cast<int>(sprites[IDLE]->getHeight() * 0.6);

	// --- TEST ---
	sf::Color color = cmm::GREEN_COLOR;
	color.a = MAX_ALPHA / 3;
	shape.setFillColor(color);
	shape.setSize(sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height)));
	color = cmm::RED_COLOR;
	color.a = MAX_ALPHA / 3;
	attackShape.setFillColor(color);
	attackShape.setSize(sf::Vector2f(static_cast<float>(attackRect.width), static_cast<float>(attackRect.height)));
	// ---      ---
}

void pla::Knight::handle(const sf::Event &event)
{
	coxing.releaseJumping(event);
}

void pla::Knight::draw(sf::RenderWindow* &window/*, sf::Shader &shader*/)
{
	if (state == STATES::VOID)
		return;
	
	sprites[state]->setOffset(static_cast<int>(offset));
	window->draw(*sprites[state]);

	// --- TEST ---
	if (collisionMode)
	{
		window->draw(shape);
		if (isAttack())
		{
			window->draw(attackShape);
		}
	}
	// ---      ---
}

void pla::Knight::mechanics(const float &elapsedTime)
{
	offset += elapsedTime * OPS;
	if (static_cast<int>(offset) >= offset_max)
	{
		offset = 0;
		coxing.attack = false;
		coxing.jump = false;
	}
}

void pla::Knight::switchCollision()
{
	collisionMode = !collisionMode;
}

sf::IntRect& pla::Knight::getRect()
{
	return rect;
}

const sf::IntRect& pla::Knight::getAttackRect()
{
	return attackRect;
}

//const int& Knight::getX() const
//{
//	return rect.left;
//}
//
//const int& Knight::getY() const
//{
//	return rect.top;
//}

bool pla::Knight::isAlive()
{
	return !coxing.die && static_cast<int>(offset) == offset_max;
}

bool pla::Knight::isAttack()
{
	return coxing.attack && offset > 3 && offset < 8;
}

bool pla::Knight::isLeftAligned() const
{
	return !align;
}

const bool &pla::Knight::isRightAligned() const
{
	return align;
}

bool pla::Knight::moveLeft(const float &elapsedTime)
{
	if (coxing.isMovingLeft() && (!coxing.attack || coxing.jump))
	{
		coxing.attack = false;
		align = ALIGN::LEFT;
		walk(elapsedTime);
		xy.x -= (coxing.walkTimer > coxing.walkLine ? specs.velocity : specs.hvelocity) * elapsedTime;
		return true;
	}

	return false;
}

void pla::Knight::undoMoveLeft(const float &elapsedTime)
{
	xy.x += (coxing.walkTimer >= coxing.walkLine ? specs.velocity : specs.hvelocity) * elapsedTime;
}

bool pla::Knight::moveRight(const float &elapsedTime)
{
	if (coxing.isMovingRight() && (!coxing.attack || coxing.jump))
	{
		align = ALIGN::RIGHT;
		walk(elapsedTime);
		xy.x += (coxing.walkTimer > coxing.walkLine ? specs.velocity : specs.hvelocity) * elapsedTime;
		return true;
	}

	return false;
}

void pla::Knight::undoMoveRight(const float &elapsedTime)
{
	xy.x -= (coxing.walkTimer >= coxing.walkLine ? specs.velocity : specs.hvelocity) * elapsedTime;
}

void pla::Knight::idle(const float &elapsedTime)
{
	if (!coxing.attack && !coxing.jump)
	{
		state = coxing.falling ? STATES::FALL : STATES::IDLE;
	}

	if (coxing.walkTimer > 0)
	{
		coxing.walkTimer -= elapsedTime;
		if (coxing.walkTimer < 0)
			coxing.walkTimer = 0;
	}
}

bool pla::Knight::jump(const float &elapsedTime)
{
	if (coxing.isJumping())
	{
		++coxing.jumpCounter;
		state = STATES::JUMP;
		offset = 0;
		coxing.jump = true;
		coxing.jumpReleased = false;
	}

	if (state == STATES::JUMP_ATTACK)
	{
		xy.y -= specs.gravity; // keep the level
		return false;
	}
	else if ((state == STATES::JUMP) && offset < 5) // go up
	{
		xy.y -= specs.gravity * 2;
		return true;
	}

	return false;
}

void pla::Knight::undoJump(const float &elapsedTime)
{
	xy.y += specs.gravity * 2;
}

void pla::Knight::attack()
{
	if (coxing.isAttacking())
	{
		if (coxing.jump && static_cast<int>(offset) < 5)
		{
			state = STATES::JUMP_ATTACK;
			coxing.attack = true;
		}
		else if(state != STATES::JUMP_ATTACK && coxing.jumpCounter == 0) // able to attack only if knight is on the ground
		{
			state = STATES::ATTACK;
			if (!coxing.attack)
			{
				coxing.attack = true;
				offset = 0;
			}
		}
	}
}

void pla::Knight::rest()
{
	// die
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) // test
	{
		state = STATES::DIE;
		offset = 0;
		coxing.die = true;
	}
	// ---

	setAlign();
	setPosition();
	setRect();
	setAttackRect();
}

void pla::Knight::gravity()
{
	coxing.falling = true;
	xy.y += specs.gravity;
}

void pla::Knight::undoGravity()
{
	coxing.jumpCounter = 0;
	coxing.jumpReleased = true;
	coxing.falling = false;
	xy.y -= specs.gravity;
}

void pla::Knight::read(std::string &str)
{
	int tempX = boost::lexical_cast<int>(str.substr(str.find("x:") + 2, str.find(" y:") - (str.find("x:") + 2)));
	int tempY = boost::lexical_cast<int>(str.substr(str.find("y:") + 2, str.find(" id:") - (str.find("y:") + 2)));
	xy.x = tempX + sprites[IDLE]->getWidth() / 2;
	xy.y = ((tempY - sprites[IDLE]->getHeight()) * -1) + screen_h;

	specs.setSpecs();
	setAlign();
	setPosition();
	setRect();
	setAttackRect();
}






void pla::Knight::walk(const double &elapsedTime)
{
	if (!coxing.jump /*&& state != STATES::ATTACK*/)
	{
		coxing.walkTimer < coxing.walkLine ? state = STATES::WALK : state = STATES::RUN;
	}

	if (coxing.walkTimer < coxing.walkLine * 3)
	{
		coxing.walkTimer += static_cast<float>(elapsedTime);
	}
}

void pla::Knight::setPosition()
{
	// set y
	float newX = xy.x;
	float newY = xy.y - sprites[IDLE]->getHeight();
	float cw = sprites[state]->getWidth(); // current width

	if (align == ALIGN::RIGHT)
	{
		switch (state)
		{
		case STATES::IDLE:
		case STATES::FALL:
		case STATES::WALK:
		case STATES::RUN: newX -= cw / 2.0f; break;
		case STATES::JUMP: newX -= cw / 1.9f; break;
		case STATES::ATTACK: newX -= cw / 2.18f; break;
		case STATES::JUMP_ATTACK: newX -= cw / 2.2f; break;
		}
	}
	else
	{
		switch (state)
		{
		case STATES::IDLE:
		case STATES::FALL:
		case STATES::WALK:
		case STATES::RUN: newX += cw / 2.0f; break;
		case STATES::JUMP: newX += cw / 1.9f; break;
		case STATES::ATTACK: newX += cw / 2.18f; break;
		case STATES::JUMP_ATTACK: newX += cw / 2.2f; break;
		}
	}

	sprites[state]->setPosition(newX, newY);
}

void pla::Knight::setAlign()
{
	if (align == ALIGN::LEFT)
		sprites[state]->setScale(-specs.scale, specs.scale);
	else
		sprites[state]->setScale(specs.scale, specs.scale);
}

void pla::Knight::setRect()
{
	rect.left = static_cast<int>(xy.x - rect.width / 2);
	rect.top = static_cast<int>(xy.y - rect.height);

	// --- TEST ---
	if (collisionMode)
	{
		shape.setPosition(static_cast<float>(rect.left), static_cast<float>(rect.top));
	}
	// ---      ---
}

void pla::Knight::setAttackRect()
{
	if (align == ALIGN::RIGHT)
		attackRect.left = static_cast<int>(xy.x);
	else
		attackRect.left = static_cast<int>(xy.x) - attackRect.width;
	attackRect.top = static_cast<int>(xy.y) -static_cast<int>(rect.height / 1.8f);

	// --- TEST ---
	if (collisionMode)
	{
		if (isAttack())
		{
			attackShape.setPosition(static_cast<float>(attackRect.left), static_cast<float>(attackRect.top));
		}
	}
	// ---      ---
}