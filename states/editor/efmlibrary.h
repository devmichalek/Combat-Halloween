#pragma once
#include "eventwindow.h"
#include "sprite.h"
#include "text.h"

class EFMLibrary final
{
	enum STORING
	{
		LOCAL = 0,
		SERVER = 1
	};

	enum TYPES
	{
		LEFT = 0,
		RIGHT,
		WORLD,
		SERVER_WORLD,
		CHECKED,
		SIZE
	};

	int page;
	int gridSquare;
	int chosen;
	bool ableToGoLeft;
	bool ableToGoRight;
	sf::FloatRect plank;

	cmm::Text pageText;
	std::vector<cmm::Sprite*> icons;
	std::vector<std::string> strLabels;
	std::vector<cmm::Text*> textLabels;
	std::vector<sf::Vector2f> worldPositions;
	std::vector<int> worldTypes;

public:
	EFMLibrary();
	~EFMLibrary();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h, sf::FloatRect planewPlanknk);
	bool handle(const sf::Event &event, const bool &status);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	void refresh(std::vector<std::string> copy);
	bool isChosen();
	const std::string& getChosenStr() const;

private:
	void setPageText();
	void getPositions(int &s, int &e);
};