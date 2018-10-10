#include "efminfo.h"
#include "loading.h"

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

	Loading::add(plank.load("images/other/plank.png"));
	if (Loading::isError())	return;
	plank.setScale(scale_x, scale_y);
	plank.center(screen_w / 2, screen_h / 2);

	blackLayer.setFillColor(sf::Color(0, 0, 0, 140));
	blackLayer.setSize(sf::Vector2f(screen_w, screen_h));
	blackLayer.setPosition(0, 0);

	const char* pathToFont = cmm::JAPOKKI_FONT_PATH;
	Loading::add(openedText.setFont(pathToFont));
	Loading::add(openedFormText.setFont(pathToFont));
	Loading::add(chosenText.setFont(pathToFont));
	Loading::add(chosenFormText.setFont(pathToFont));
	Loading::add(msgText.setFont(pathToFont));
	if (Loading::isError())	return;

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
	msgText.setFillColor(cmm::LOADING_COLOR);
	msgText.setOutlineColor(cmm::BACKGROUND_COLOR);

	setOpenedText();
	setChosenText();
}

void EFMInfo::drawPlank(sf::RenderWindow* &window)
{
	window->draw(plank);
	if(isMsgTextActive())	window->draw(msgText);
}

void EFMInfo::draw(sf::RenderWindow* &window)
{
	window->draw(openedText);
	window->draw(openedFormText);
	window->draw(chosenText);
	window->draw(chosenFormText);
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

void EFMInfo::setMsgTextActive(bool active)
{
	active ? msgText.setAlpha(0xFF) : msgText.setAlpha(0.0f);
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