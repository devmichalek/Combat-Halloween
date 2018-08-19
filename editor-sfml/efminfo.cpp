#include "efminfo.h"

EFMInfo::EFMInfo()
{
	free();
}

EFMInfo::~EFMInfo()
{
	free();
}

void EFMInfo::free()
{
	// empty?
}

void EFMInfo::reset()
{
	setChosenText();
}



void EFMInfo::load(const float &screen_w, const float &screen_h)
{
	free();

	float scale_x = screen_w / 1920;	if (scale_x > 1.0f)	scale_x = 1;
	float scale_y = screen_h / 1080;	if (scale_y > 1.0f)	scale_y = 1;

	plank.load("images/other/plank.png");
	plank.setScale(scale_x, scale_y);
	plank.center(screen_w / 2, screen_h / 2);

	blackLayer.setFillColor(sf::Color(0, 0, 0, 140));
	blackLayer.setSize(sf::Vector2f(screen_w, screen_h));
	blackLayer.setPosition(0, 0);

	const char* pathToFont = "fonts/Jaapokki-Regular.otf";
	openedText.setFont(pathToFont);
	openedFormText.setFont(pathToFont);
	chosenText.setFont(pathToFont);
	chosenFormText.setFont(pathToFont);
	msgText.setFont(pathToFont);

	openedText.setSize(plank.getWidth() / 30);
	openedFormText.setSize(plank.getWidth() / 30);
	chosenText.setSize(plank.getWidth() / 30);
	chosenFormText.setSize(plank.getWidth() / 30);
	msgText.setSize(plank.getWidth() / 20);

	openedText.setAlpha(0xFF);
	openedFormText.setAlpha(0xFF);
	chosenText.setAlpha(0xFF);
	chosenFormText.setAlpha(0xFF);
	msgText.setAlpha(0xFF);

	openedFormText.setText("Loaded File: ");
	openedFormText.setPosition(plank.getLeft() + screen_w / 75.0f, plank.getTop() + screen_w / 18);
	chosenFormText.setText("Chosen File: ");
	chosenFormText.setPosition(openedFormText.getX(), openedFormText.getBot() + chosenFormText.getHeight() / 2);

	msgText.setOutlineThickness(1);
	msgText.setFillColor(sf::Color::White);
	msgText.setOutlineColor(sf::Color::Black);

	setOpenedText();
	setChosenText();
}

void EFMInfo::drawPlank(sf::RenderWindow* &window)
{
	window->draw(plank.get());
	if(isMsgTextActive())	window->draw(msgText.get());
}

void EFMInfo::draw(sf::RenderWindow* &window)
{
	window->draw(openedText.get());
	window->draw(openedFormText.get());
	window->draw(chosenText.get());
	window->draw(chosenFormText.get());
}

void EFMInfo::drawLayer(sf::RenderWindow* &window)
{
	window->draw(blackLayer);
}

void EFMInfo::mechanics(const double &elapsedTime)
{
	int min = 0;
	msgText.fadeout((float)elapsedTime * 150, min);
}




bool EFMInfo::isMsgTextActive()
{
	return msgText.getAlpha() > 0;
}

void EFMInfo::setOpenedText(std::string msg)
{
	openedText.setText(msg);
	openedText.setPosition(openedFormText.getRight() + plank.getWidth() / 120, openedFormText.getTop());
}

std::string EFMInfo::setChosenText(std::string msg)
{
	std::string str = "-";
	int size = msg.size();
	if (size < 25)
		str = msg.substr(0, size);
	else
		str = msg.substr(0, 22) + "...";

	chosenText.setText(str);
	chosenText.setPosition(chosenFormText.getRight() + plank.getWidth() / 120, chosenFormText.getTop());

	return msg;
}

void EFMInfo::setMsgText(std::string msg)
{
	msgText.setText(msg);
	msgText.setPosition(plank.getX() + plank.getWidth() / 2 - msgText.getWidth() / 2, plank.getY() + plank.getHeight() / 2 - msgText.getHeight() / 2);
	msgText.setAlpha(0xFF);
}


float EFMInfo::getLeft()
{
	return plank.getLeft();
}

float EFMInfo::getRight()
{
	return plank.getRight();
}

float EFMInfo::getTop()
{
	return plank.getTop();
}

float EFMInfo::getBot()
{
	return plank.getBot();
}

sf::FloatRect EFMInfo::getRect()
{
	return sf::FloatRect(getLeft(), getTop(), plank.getWidth(), plank.getHeight());
}