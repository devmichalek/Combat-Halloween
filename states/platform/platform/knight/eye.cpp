#include "eye.h"
#include "loading.h"

pla::Eye::Eye()
{
	free();
}

pla::Eye::~Eye()
{
	free();
}

void pla::Eye::free()
{
	line_y = 0;
	distance_y = 0;

	scale_x = 0;

	//balloonchat.free();
	if (!texts.empty())
		texts.clear();

	textWas = -1;
	textCounter = 0;
	textLine = 6;

	viewX = viewY = 0;
}

void pla::Eye::reset(const sf::Rect<int> &rect)
{
	distance_y = 0;

	scale_x = 0;
	sprite.setPosition(rect.left, rect.top);
	viewX = static_cast<float>(rect.left);
	viewY = static_cast<float>(rect.top);
	view.setCenter(viewX, viewY);

	textWas = -1;
	textCounter = 0;
}



void pla::Eye::load(const float &screen_w, const float &screen_h)
{
	free();

	view.setSize(screen_w, screen_h);

	Loading::add(sprite.load("images/platform/knight/eye.png"));
	if (Loading::isError()) return;
	sprite.setScale(0.5, 0.5);
	line_y = sprite.getHeight() / 3 * 2;
	scale_x = 0.5;

	//balloonchat.load(screen_w, screen_h);
}

void pla::Eye::draw(sf::RenderTexture &rt)
{
	if (scale_x < 0)
	{
		float x = sprite.getX();
		sprite.setPosition(sprite.getX() + sprite.getWidth(), sprite.getY());
		rt.draw(sprite);
		sprite.setPosition(x, sprite.getY());
	}
	else
	{
		rt.draw(sprite);
	}

	if (textCounter > 0)
	{
		bool left = false;
		if (scale_x > 0)	left = false;
		else				left = true;
		//balloonchat.setPosition(sprite.getX() + sprite.getWidth() / 2, sprite.getY(), !left);
		//balloonchat.draw(window, shader);
	}
}

void pla::Eye::mechanics(const float &elapsedTime, const sf::Rect<int> &rect, const bool &align)
{
	if (textCounter > 0 && textCounter < textLine)
	{
		textCounter += elapsedTime;
		if (textCounter > textLine)
		{
			textCounter = 0;
		}
	}


	// Hovering.
	distance_y -= elapsedTime * 4;
	if (distance_y < -line_y)
		distance_y = 0;

	if (sprite.getY() < rect.top - sprite.getHeight() + distance_y)
		sprite.move(0, elapsedTime *((rect.top - sprite.getHeight() + distance_y) - sprite.getY()) * 2);
	else if (sprite.getY() > rect.top - sprite.getHeight() + distance_y)
		sprite.move(0, -elapsedTime * (sprite.getY() - (rect.top - sprite.getHeight() + distance_y)) * 2);

	// X.
	if (sprite.getX() < rect.left - rect.width)
	{
		scale_x = -0.5f;
		sprite.move(elapsedTime *((rect.left - sprite.getWidth() / 2) - sprite.getX()) * 2, 0);
	}
	else if (sprite.getX() + sprite.getWidth() > rect.left + rect.width)
	{
		scale_x = 0.5f;
		sprite.move(-elapsedTime * (sprite.getX() - (rect.left - sprite.getWidth() / 2)) * 2, 0);
	}
		

	//scale_x = align ? 0.5f : -0.5f;
	sprite.setScale(scale_x, 0.5f);


	// Set view.
	float velocity = 1280 / view.getSize().x;
	if (rect.left + rect.width / 2 > view.getSize().x / 2 || viewX > view.getSize().x / 2)
	{
		if (viewX < rect.left + rect.width / 2)
		{
			viewX += elapsedTime * (rect.left + rect.width / 2 - viewX) * velocity;
		}
		else if (viewX > rect.left + rect.width / 2)
		{
			viewX -= elapsedTime * (viewX - rect.left + rect.width / 2) * velocity;
		}
	}
	else
	{
		viewX = view.getSize().x / 2;
	}

	if (rect.top + rect.height / 2 < view.getSize().y / 2 || viewY < view.getSize().y / 2)
	{
		if (viewY < rect.top + rect.height / 2)
		{
			viewY += elapsedTime * (rect.top + rect.height / 2 - viewY) * velocity;
		}
		else if (viewY > rect.top + rect.height / 2)
		{
			viewY -= elapsedTime * (viewY - rect.top + rect.height / 2) * velocity;
		}
	}
	else
	{
		viewY = view.getSize().y / 2;
	}

	view.setCenter(sf::Vector2f(viewX, viewY));
}



const sf::View& pla::Eye::getView() const
{
	return view;
}

float pla::Eye::getViewX()
{
	float x = (view.getCenter().x - view.getSize().x / 2);
	return x < 0 ? 0 : x;
}

float pla::Eye::getViewY()
{
	float y = view.getCenter().y - view.getSize().y / 2;
	return y > 0 ? 0 : -y;
}