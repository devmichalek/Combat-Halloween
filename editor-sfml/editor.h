#pragma once
#include "state.h"
#include "chat.h"
#include "editorfilemanager.h"
// #include "editor_flare/editor_buttons.h"
// #include "editor_flare/editor_information.h"
// #include "editor_flare/editor_details.h"
// #include "editor_flare/editor_options.h"
// #include "tiles_editor.h"

class Editor :public State
{
	bool loaded;
	
	cmm::Sprite background;
	Circlebutton homebutton;
	Circlebutton levelmenubutton;
	Circlebutton playbutton;
	EditorFileManager editorFileManager;
	// Editor_buttons editor_buttons;
	// Editor_information editor_information;
	// Editor_details editor_details;
	// Editor_options editor_options;
	// Tiles_editor tiles_editor;
	Chat chat;
	
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
private:
	// void fades(double elapsedTime);
	// void fadein(float value = 1, int max = 0xFF);
	// void fadeout(float value = 1, int min = 0);
};