#include "messageboard.h"
#include "loading.h"

MessageBoard::MessageBoard()
{
	free();
}

MessageBoard::~MessageBoard()
{
	free();
}

void MessageBoard::free()
{
	reset();
}

void MessageBoard::reset()
{
	active = TYPES::EMPTY;
	decision = DECISION::NO_DECISION;
}



void MessageBoard::load(const float &screen_w, const float &screen_h)
{
	free();

	float scale_x = screen_w / 1920;	if (scale_x > 1.0f)	scale_x = 1;
	float scale_y = screen_h / 1080;	if (scale_y > 1.0f)	scale_y = 1;

	Loading::add(board.load("images/other/splank.png"));
	if (Loading::isError())	return;
	board.setScale(scale_x, scale_y);
	board.center(screen_w / 2, screen_h / 2);

	const char* pathToFont = cmm::JAPOKKI_FONT_PATH;
	Loading::add(infoText.setFont(pathToFont));
	Loading::add(yesText.setFont(pathToFont));
	Loading::add(noText.setFont(pathToFont));
	Loading::add(okText.setFont(pathToFont));
	if (Loading::isError())	return;

	infoText.setSize(screen_w / 50);
	yesText.setSize(screen_w / 60);
	noText.setSize(screen_w / 60);
	okText.setSize(screen_w / 60);

	infoText.setAlpha(MAX_ALPHA);
	yesText.setAlpha(MAX_ALPHA);
	noText.setAlpha(MAX_ALPHA);
	okText.setAlpha(MAX_ALPHA);

	yesText.setText("yes");
	noText.setText("no");
	okText.setText("ok");

	float off = screen_w / 200;
	yesText.setPosition(board.getRight() - yesText.getWidth() - off, board.getBot() - yesText.getHeight() * 1.25 - off);
	noText.setPosition(board.getLeft() + off, yesText.getTop());
	okText.setPosition(board.getRight() - okText.getWidth() - off, yesText.getTop());

	yesRect = sf::FloatRect(yesText.getX(), yesText.getY(), yesText.getWidth() * 2, yesText.getHeight() * 2);
	noRect = sf::FloatRect(noText.getX(), noText.getY(), noText.getWidth() * 2, noText.getHeight() * 2);
}

void MessageBoard::handle(const sf::Event &event)
{
	if (!isActive())
		return;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			float x = (float)event.mouseButton.x;
			float y = (float)event.mouseButton.y;

			if (yesRect.contains(x, y))
				decision = active == TYPES::OKACTIVE ? OK : YES;
			else if (active == TYPES::YESNOACTIVE && noRect.contains(x, y))
				decision = NO;
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			decision = active == TYPES::OKACTIVE ? OK : YES;
		}
		else if (event.key.code == sf::Keyboard::Escape)
		{
			decision = NO;
		}
	}
}

void MessageBoard::draw(sf::RenderWindow* &window)
{
	if (isActive())
	{
		window->draw(board);
		window->draw(infoText);

		if (active == OKACTIVE)
		{
			window->draw(okText);
		}
		else if (active == YESNOACTIVE)
		{
			window->draw(yesText);
			window->draw(noText);
		}
	}
}



void MessageBoard::setActive(int status)
{
	active = status;
}

void MessageBoard::setMessage(std::string msg)
{
	infoText.setText(msg);
	infoText.center(board.getX() + board.getWidth() / 2, board.getY() + board.getHeight() / 2.1);
}



const bool MessageBoard::isActive() const
{
	return active != TYPES::EMPTY;
}

bool MessageBoard::isDecision() const
{
	return decision != DECISION::NO_DECISION;
}

const bool MessageBoard::isYes()
{
	if (decision == YES)
	{
		decision = EMPTY;
		return true;
	}

	return false;
}

const bool MessageBoard::isNo()
{
	if (decision == NO)
	{
		decision = EMPTY;
		return true;
	}

	return false;
}

const bool MessageBoard::isOk()
{
	if (decision == OK)
	{
		decision = EMPTY;
		return true;
	}

	return false;
}
