#pragma once
#include "eafactory.h"
#include "eagrid.h"
#include "eainfo.h"

class EditorAction final
{
	EAFactory factory;
	EAGrid grid;
	EAInfo info;

public:
	EditorAction();
	~EditorAction();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
};