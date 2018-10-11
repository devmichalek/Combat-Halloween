#pragma once
#include "state.h"
#include "editornavigation.h"
#include "editorfilemanager.h"
#include "editoraction.h"
// #include "editor_flare/editor_information.h"
// #include "editor_flare/editor_details.h"
// #include "editor_flare/editor_options.h"
// #include "tiles_editor.h"

class Editor :public cmm::State
{
	bool loaded;
	
	EditorNavigation navigation;
	EditorFileManager editorFileManager;
	EditorAction editorAction;
	// Editor_information editor_information;
	// Editor_details editor_details;
	// Editor_options editor_options;
	// Tiles_editor tiles_editor;
	
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
private:
	// void fades(double elapsedTime);
	// void fadein(float value = 1, int max = MAX_ALPHA);
	// void fadeout(float value = 1, int min = 0);
};