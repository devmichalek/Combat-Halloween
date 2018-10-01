#include "eatools.h"
#include "loading.h"

EATools::EATools()
{
	free();
}

EATools::~EATools()
{
	free();
}

void EATools::free()
{
	screen_w = 0;
	screen_h = 0;
}

void EATools::reset()
{
	deleteMode = false;
	keyPressed = false;
}



void EATools::load(const float& screen_w, const float& screen_h)
{
	free();

	this->screen_w = static_cast<int>(screen_w);
	this->screen_h = static_cast<int>(screen_h);

	Loading::add(checkedIcon.load("images/icons/checkedicon.png"));
	if (Loading::isError()) return;
	checkedIcon.setScale(0.3, 0.3);
	checkedIcon.setAlpha(0xFF / 1.5);

	deleteButton.load("images/buttons/rubbish.png");
	if (Loading::isError()) return;
	deleteButton.setVolume(0.0f); // muted
	deleteButton.setScale(screen_w / 2560, screen_h / 1440);
	deleteButton.setPosition(screen_w - screen_w / 85 - deleteButton.getWidth() * 3, screen_h / 144);

	Loading::add(deleteText.setFont(cmm::JCANDLE_FONT_PATH));
	if (Loading::isError()) return;
	deleteText.setSize(screen_w / 60);
	deleteText.setAlpha(0xFF);
	deleteText.setFillColor(sf::Color::White);
	deleteText.setText("Delete Mode");
	deleteText.setPosition(deleteButton.getLeft() + deleteButton.getWidth() / 2 - deleteText.getWidth() / 2, deleteButton.getBot() + screen_w / 300.0f);
}

bool EATools::handle(const sf::Event &event)
{
	deleteButton.handle(event);
	if (deleteButton.hasChanged())
	{
		if (deleteButton.isActive())
			deleteMode = 2;
		else if (deleteMode == 2)
			deleteMode = 0;
		return true;
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::LControl)	// temporary delete mode
		{
			keyPressed = true;
			if (deleteMode != 2)
				deleteMode = 1;
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::LControl)
		{
			keyPressed = false;
			if (deleteMode != 2)
				deleteMode = 0;
		}
	}

	return false;
}

void EATools::drawTools(sf::RenderWindow* &window)
{
	deleteButton.draw(window);
	window->draw(deleteText);
}

void EATools::draw(sf::RenderWindow* &window, std::vector<cmm::Sprite*> &factory, const int& chosen)	// Draws thumbnails
{
	// Save current position.
	float tempX, tempY;
	tempX = factory[chosen]->getX();
	tempY = factory[chosen]->getY();

	// Draw
	int space = screen_h / 288;
	int startX = space * 3;
	int largestWidth = 0;
	float scaleX = factory[0]->getScaleX(), scaleY = factory[0]->getScaleY();

	for (unsigned i = 0; i < factory.size(); ++i)
	{
		if (i != chosen)	factory[i]->setAlpha(0xFF / 1.5);
		
		factory[i]->setScale(0.3, 0.3); // 30% of oryginal
		if (i != 0)
		{
			factory[i]->setPosition(startX, factory[i - 1]->getBot() + space);
			factory[i - 1]->setScale(scaleX, scaleY);
			scaleX = factory[i - 1]->getScaleX();
			scaleY = factory[i - 1]->getScaleY();
		}
		else
			factory[i]->setPosition(startX, screen_h / 6);

		if (factory[i]->getWidth() > largestWidth)
			largestWidth = static_cast<int>(factory[i]->getWidth());

		if (factory[i]->getBot() > screen_h / 8 * 7)
		{
			startX += largestWidth + space * 3;
			factory[i]->setPosition(startX, screen_h / 6);
			largestWidth = 0;
		}

		window->draw(*factory[i]);
		factory[i]->setAlpha(0xFF); // set back
	}

	factory[factory.size() - 1]->setScale(scaleX, scaleY); // set back 50% of oryginal for the first one

	// Set chosen icon
	scaleX = factory[chosen]->getScaleX();
	scaleY = factory[chosen]->getScaleY();
	factory[chosen]->setScale(0.3, 0.3);
	float x = factory[chosen]->getX() + factory[chosen]->getWidth() / 2 - checkedIcon.getWidth() / 2;
	float y = factory[chosen]->getY() + factory[chosen]->getHeight() / 2 - checkedIcon.getHeight() / 2;
	checkedIcon.setPosition(x, y);
	factory[chosen]->setScale(scaleX, scaleY);
	window->draw(checkedIcon);
	factory[chosen]->setPosition(tempX, tempY);	// Set back current position.
}



const bool& EATools::isKeyPressed() const
{
	return keyPressed;
}

bool EATools::isDeleteMode() const
{
	return deleteMode != 0;
}

void EATools::resetDeleteMode()
{
	deleteButton.setActive(false);
	deleteMode = 0;
}