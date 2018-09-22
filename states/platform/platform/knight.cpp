#include "knight.h"
#include "loading.h"
#include <boost/lexical_cast.hpp>

Knight::Knight()
{
	free();
}

Knight::~Knight()
{
	free();
}

void Knight::free()
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

void Knight::reset()
{
	resetState();
	coxing.reset();

	// --- TEST ---
	collisionMode = false;
	// ---      ---
}



void Knight::load(const float &screen_w, const float &screen_h)
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
	shape.setFillColor(sf::Color(0xFF, 0xFA, 0xCD, 0xFF / 3));
	shape.setSize(sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height)));
	attackShape.setFillColor(sf::Color(0xFF, 0x00, 0x00, 0xFF / 3));
	attackShape.setSize(sf::Vector2f(static_cast<float>(attackRect.width), static_cast<float>(attackRect.height)));
	// ---      ---
}

void Knight::handle(const sf::Event &event)
{

}

void Knight::draw(sf::RenderWindow* &window/*, sf::Shader &shader*/)
{
	if (state == STATES::VOID)
		return;
	
	sprites[state]->setOffset(static_cast<int>(offset));
	window->draw(sprites[state]->get());

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

void Knight::mechanics(const double &elapsedTime)
{
	offset += static_cast<float>(elapsedTime * OPS);
	if (static_cast<int>(offset) >= offset_max)
	{
		offset = 0;
		coxing.attack = false;
	}
}

void Knight::switchCollision()
{
	collisionMode = !collisionMode;
}

sf::IntRect& Knight::getRect()
{
	return rect;
}

const sf::IntRect& Knight::getAttackRect()
{
	return attackRect;
}

bool Knight::isAlive()
{
	return false;
}

bool Knight::isAttack()
{
	return coxing.attack && offset > 3 && offset < 8;
}

bool Knight::moveLeft(const double &elapsedTime)
{
	if (coxing.isMovingLeft() && !coxing.attack)
	{
		coxing.attack = false;
		align = ALIGN::LEFT;
		walk(elapsedTime);
		xy.x -= (coxing.walkTimer >= coxing.walkLine ? specs.velocity : specs.hvelocity) * static_cast<float>(elapsedTime);
		return true;
	}

	return false;
}

void Knight::undoMoveLeft(const double &elapsedTime)
{
	xy.x += (coxing.walkTimer >= coxing.walkLine ? specs.velocity : specs.hvelocity) * static_cast<float>(elapsedTime);
}

bool Knight::moveRight(const double &elapsedTime)
{
	if (coxing.isMovingRight() && !coxing.attack)
	{
		align = ALIGN::RIGHT;
		walk(elapsedTime);
		xy.x += (coxing.walkTimer >= coxing.walkLine ? specs.velocity : specs.hvelocity) * static_cast<float>(elapsedTime);
		return true;
	}

	return false;
}

void Knight::undoMoveRight(const double &elapsedTime)
{
	xy.x -= (coxing.walkTimer >= coxing.walkLine ? specs.velocity : specs.hvelocity) * static_cast<float>(elapsedTime);
}

void Knight::idle(const double &elapsedTime)
{
	if(!coxing.attack)
		state = STATES::IDLE;

	if (coxing.walkTimer > 0)
	{
		coxing.walkTimer -= static_cast<float>(elapsedTime);
		if (coxing.walkTimer < 0)
			coxing.walkTimer = 0;
	}
}

bool Knight::jump(const double &elapsedTime)
{
	if (coxing.isJumping() && coxing.jumpCounter < coxing.jumpLine - 1)
	{
		++coxing.jumpCounter;
		state = STATES::JUMP;
		offset = 0;
	}

	if ((state == STATES::JUMP || state == STATES::JUMP_ATTACK) && offset < 5) // go up
	{
		xy.y -= specs.gravity;
		return true;
	}

	return false;
}

void Knight::undoJump(const double &elapsedTime)
{
	xy.y += specs.gravity;
}

void Knight::attack()
{
	if (coxing.isAttacking())
	{
		state = STATES::ATTACK;
		if (state == STATES::JUMP && static_cast<int>(offset) < 4)
			state = STATES::JUMP_ATTACK;
		else
		{
			if (!coxing.attack)
			{
				coxing.attack = true;
				offset = 0;
			}
		}
	}
}

void Knight::rest(const double &elapsedTime)
{
	setAlign();
	setPosition();
	setRect();
	setAttackRect();
}

bool Knight::gravity()
{
	if (state == STATES::JUMP || state == STATES::JUMP_ATTACK)
		return false;

	xy.y += specs.gravity;
	return true;
}

void Knight::undoGravity()
{
	coxing.jumpCounter = 0;
	xy.y -= specs.gravity;
}

void Knight::read(std::string &str)
{
	int tempX = boost::lexical_cast<int>(str.substr(str.find("x:") + 2, str.find(" y:") - (str.find("x:") + 2)));
	int tempY = boost::lexical_cast<int>(str.substr(str.find("y:") + 2, str.find(" id:") - (str.find("y:") + 2)));
	xy.x = tempX + sprites[IDLE]->getWidth() / 2;
	xy.y = ((tempY - sprites[IDLE]->getHeight()) * -1) + screen_h;

	specs.setSpecs();
	setAlign();
	setPosition();
}






void Knight::walk(const double &elapsedTime)
{
	if (state != STATES::JUMP /*&& state != STATES::ATTACK*/ && state != STATES::JUMP_ATTACK)
	{
		if (coxing.walkTimer < coxing.walkLine)
		{
			coxing.walkTimer += static_cast<float>(elapsedTime);
			state = STATES::WALK;

		}
		else
			state = STATES::RUN;
	}
}

void Knight::setPosition()
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
		case STATES::WALK:
		case STATES::RUN: newX -= cw / 2; break;
		case STATES::ATTACK: newX -= cw / 2.18; break;
		}
	}
	else
	{
		switch (state)
		{
		case STATES::IDLE:
		case STATES::WALK:
		case STATES::RUN: newX += cw / 2; break;
		case STATES::ATTACK: newX += cw / 2.18; break;
		}
	}

	sprites[state]->setPosition(newX, newY);
}

void Knight::setAlign()
{
	if (align == ALIGN::LEFT)
		sprites[state]->setScale(-specs.scale, specs.scale);
	else
		sprites[state]->setScale(specs.scale, specs.scale);
}

void Knight::setRect()
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

void Knight::setAttackRect()
{
	if (align == ALIGN::RIGHT)
		attackRect.left = xy.x;
	else
		attackRect.left = xy.x - attackRect.width;
	attackRect.top = xy.y - rect.height / 1.8;

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