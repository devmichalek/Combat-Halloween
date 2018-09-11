#include "knight.h"
#include "loading.h"

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



void Knight::set(const float &x, const float &y)
{
	xy = sf::Vector2f(x, y);
	specs.setSpecs();
	setAlign();
	setPosition();
}

void Knight::load(const float &screen_w, const float &screen_h)
{
	free();

	// Load Sprites.
	for (int i = 0; i < STATES::SIZE; ++i)
	{
		sprites.push_back(new cmm::Sprite);
		Loading::add(sprites[i]->load("images/platform/knight/" + std::to_string(i) + ".png", offset_max));
		if (Loading::isError())	return;
		sprites[i]->setScale(specs.scale, specs.scale);
	}

	// Set rects size
	rect.width = static_cast<int>(sprites[IDLE]->getWidth() * 0.9);
	rect.height = static_cast<int>(sprites[IDLE]->getHeight() * 0.9);
	attackRect.width = static_cast<int>(sprites[IDLE]->getWidth() * 0.4);
	attackRect.height = static_cast<int>(sprites[IDLE]->getHeight() * 0.4);

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
	}

	if (coxing.isMovingLeft())
	{
		align = ALIGN::LEFT;
		walk(elapsedTime);
		xy.x -= (coxing.walkTimer >= coxing.walkLine ? specs.velocity : specs.hvelocity) * static_cast<float>(elapsedTime);
	}
	else if (coxing.isMovingRight())
	{
		align = ALIGN::RIGHT;
		walk(elapsedTime);
		xy.x += (coxing.walkTimer >= coxing.walkLine ? specs.velocity : specs.hvelocity) * static_cast<float>(elapsedTime);
	}
	else
	{
		state = STATES::IDLE;
		if (coxing.walkTimer > 0)
			coxing.walkTimer -= static_cast<float>(elapsedTime);
	}

	if (coxing.isJumping())
	{

	}

	if (coxing.isAttacking())
	{
		state = STATES::ATTACK;
		if (state == STATES::JUMP && static_cast<int>(offset) < 4)
			state = STATES::JUMP_ATTACK;
	}



	setAlign();
	setPosition();
	setRect();
	setAttackRect();
}

void Knight::switchCollision()
{
	collisionMode = !collisionMode;
}

const sf::IntRect& Knight::getRect()
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
	return false;
}

void Knight::gravity()
{
	xy.y += specs.gravity;
}

void Knight::undoGravity()
{
	xy.y -= specs.gravity;
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
		case STATES::IDLE: newX -= cw / 2; break;
		case STATES::WALK: newX -= cw / 2; break;
		case STATES::RUN: newX -= cw / 2; break;
		}
	}
	else
	{
		switch (state)
		{
		case STATES::IDLE: newX += cw / 2; break;
		case STATES::WALK: newX += cw / 2; break;
		case STATES::RUN: newX += cw / 2; break;
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