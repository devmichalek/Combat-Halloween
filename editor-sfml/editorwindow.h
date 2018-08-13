#pragma once
#include "sprite.h"

class EditorWindow
{
	sf::View view;
	cmm::Sprite background;
	cmm::Sprite backgroundTile;
	cmm::Sprite framev;
	cmm::Sprite framec;
	cmm::Sprite frameh;

	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> corners;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> framesvertical;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> frameshorizontal;

public:
	EditorWindow();
	~EditorWindow();
	
	void load(float screen_w, float screen_h);
	//void handle(sf::Event& event);
	void draw(sf::RenderWindow* &window);
	//void mechanics(double elapsedTime);
};