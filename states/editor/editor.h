#pragma once
#include "state.h"
#include "editornavigation.h"
#include "editorfilemanager.h"
#include "eafactory.h"
#include "eagrid.h"
#include "eainfo.h"

class Editor final :public cmm::State
{
	bool loaded;
	EditorNavigation navigation;
	EditorFileManager editorFileManager;
	EAFactory factory;
	EAGrid grid;
	EAInfo info;
	
public:
	Editor();
	~Editor();
private:
	void free();
	void set();
	bool isReady() const;
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
	void setState(int &state);
};