#include "eadetails.h"
#include "loading.h"
#include "colors.h"
#include "definitions.h"

EADetails::EADetails()
{
	free();
}

EADetails::~EADetails()
{
	free();
}

void EADetails::free()
{

	arrow_line = 0.5;	// 0.5 sec.
	reset();
}

void EADetails::reset()
{
	chosen = -1;
	arrow_counter = 0;
	active = false;
}

void EADetails::load(const float& screen_w, const float& screen_h)
{
	free();

	float scale_x = screen_w / 1920;	if (scale_x > 1.0f)	scale_x = 1;
	float scale_y = screen_h / 1080;	if (scale_y > 1.0f)	scale_y = 1;

	// Set button.
	button.load("images/buttons/info.png");
	if (Loading::isError())	return;
	button.setVolume(MIN_SOUND_VOLUME); // muted
	button.setScale(screen_w / 2560, screen_h / 1440);
	button.setPosition(screen_w - (screen_w / 256 + button.getWidth()) * 3, screen_h / 144);

	// Set button label.
	Loading::add(label.setFont(cmm::JCANDLE_FONT_PATH));
	if (Loading::isError())	return;
	label.setText("details");
	label.setAlpha(MAX_ALPHA);
	label.setPosition(button.getLeft() + button.getWidth() / 2 - label.getWidth() / 2.5, button.getBot() + screen_w / 300.0f);
	label.setSize(screen_w / 60);

	// Set board.
	Loading::add(plank.load("images/other/plank.png"));
	if (Loading::isError())	return;
	plank.setScale(scale_x, scale_y);
	plank.center(screen_w / 2, screen_h / 2);

	// Set black layer.
	blackLayer.setFillColor(sf::Color(0, 0, 0, 140));
	blackLayer.setSize(sf::Vector2f(screen_w, screen_h));
	blackLayer.setPosition(0, 0);

	// Set left/right buttons.
	Loading::add(leftbutton.load("images/icons/lefticon.png"));
	Loading::add(rightbutton.load("images/icons/righticon.png"));
	if (Loading::isError())	return;
	float factor = 0.9f;
	leftbutton.setScale(scale_x * factor, scale_y * factor);
	rightbutton.setScale(scale_x * factor, scale_y * factor);
	leftbutton.setPosition(plank.getLeft() + screen_w / 128, plank.getTop() + plank.getHeight() / 2 - leftbutton.getHeight() / 2);
	rightbutton.setPosition((plank.getRight() - screen_w / 128) - rightbutton.getWidth(), leftbutton.getY());
	leftbutton.setAlpha(MAX_ALPHA / 1.5);
	rightbutton.setAlpha(MAX_ALPHA / 1.5);

	// Set forms and writtens.
	Loading::add(info.			setFont(cmm::JAPOKKI_FONT_PATH));
	Loading::add(titleform.		setFont(cmm::JAPOKKI_FONT_PATH));
	Loading::add(titlewritten.	setFont(cmm::JAPOKKI_FONT_PATH));
	Loading::add(specsform.		setFont(cmm::JAPOKKI_FONT_PATH));
	Loading::add(specswritten.	setFont(cmm::JAPOKKI_FONT_PATH));
	if (Loading::isError())	return;
	info.			setSize(plank.getWidth() / 20);
	titleform.		setSize(plank.getWidth() / 20);
	titlewritten.	setSize(titleform.getSize());
	specsform.		setSize(titleform.getSize());
	specswritten.	setSize(titleform.getSize());
	info.			setFillColor(cmm::DULL_IRON_COLOR);
	titleform.		setFillColor(cmm::DULL_IRON_COLOR);
	titlewritten.	setFillColor(cmm::WHITISH_COLOR);
	specsform.		setFillColor(cmm::DULL_IRON_COLOR);
	specswritten.	setFillColor(cmm::WHITISH_COLOR);
	info.			setAlpha(MAX_ALPHA);
	titleform.		setAlpha(MAX_ALPHA);
	titlewritten.	setAlpha(MAX_ALPHA);
	specsform.		setAlpha(MAX_ALPHA);
	specswritten.	setAlpha(MAX_ALPHA);
	info.			setText("Welcome to the world's details. Here you\ncan easily change the world's title and the\ndescription of the world. Click on the text\nto change it.");
	titleform.		setText("Title: ");
	titlewritten.	setText("Yellowstone");
	specsform.		setText("Description: ");
	specswritten.	setText("Stone is yellow.");
	info.setPosition(plank.getX() + screen_w / 128, plank.getY() + screen_h / 144);
	titleform.setPosition(info.getX(), info.getBot() + plank.getHeight() / 20);
	specsform.setPosition(titleform.getX(), titleform.getY() + plank.getHeight() / 5);

	// Set arrow.
	Loading::add(arrow.setFont(cmm::JAPOKKI_FONT_PATH));
	if (Loading::isError())	return;
	arrow.setSize(plank.getWidth() / 20);
	arrow.setFillColor(cmm::WHITISH_COLOR);
	arrow.setAlpha(MAX_ALPHA);
	arrow.setText("|");

	setText();
}

void EADetails::handle(const sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			float x = (float)event.mouseButton.x;
			float y = (float)event.mouseButton.y;

			if (!active && button.handle(event))
			{
				active = button.isActive();
				if (active)
					setText();
				return;
			}

			if (titlerect.contains(x, y))
			{
				chosen = 0;
				setTextPosition();
			}
			else if (specsrect.contains(x, y))
			{
				chosen = 1;
				setTextPosition();
			}
			else if (!plank.checkCollision(x, y))
			{
				button.setActive(false);
				reset();
			}
		}
	}

	if (!active)
		return;

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			active = false;
			button.setActive(false);
			reset();
			return;
		}
	}
}

void EADetails::drawButton(sf::RenderWindow* &window)
{
	// Draw button and label always.
	button.draw(window);
	window->draw(label);
}

void EADetails::draw(sf::RenderWindow* &window)
{
	if (!active)
		return;

	window->draw(blackLayer);
	window->draw(plank);

	// Draw texts.
	window->draw(info);
	window->draw(titleform);
	window->draw(titlewritten);
	window->draw(specsform);
	window->draw(specswritten);

	// Draw arrow.
	if (arrow_counter < arrow_line && chosen != -1)
		window->draw(arrow);
}

void EADetails::mechanics(const double &elapsedTime)
{
	arrow_counter += static_cast<float>(elapsedTime);
	if (arrow_counter > arrow_line * 2)
	{
		arrow_counter = 0;
	}
}

void EADetails::setText()
{
	
	setTextPosition();
}

void EADetails::setTextPosition()
{
	titlewritten.setPosition(titleform.getX(), titleform.getBot() + plank.getHeight() / 30);
	specswritten.setPosition(specsform.getX(), specsform.getBot() + plank.getHeight() / 30);
	titlerect = sf::IntRect(plank.getX(), titlewritten.getY(), titlewritten.getWidth(), titlewritten.getHeight());
	specsrect = sf::IntRect(plank.getX(), specswritten.getY(), specswritten.getWidth(), specswritten.getHeight());

	if (chosen == 0)
		arrow.setPosition(titlewritten.getX() + titlewritten.getWidth(), titlewritten.getY());
	else if (chosen == 1)
		arrow.setPosition(specswritten.getX() + specswritten.getWidth(), specswritten.getY());
}