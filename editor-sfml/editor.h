#pragma once
#include "state.h"
#include "button.h"
#include "chat.h"
#include "editorwindow.h"
// #include "editor_flare/editor_buttons.h"
// #include "editor_flare/editor_information.h"
// #include "editor_flare/editor_details.h"
// #include "editor_flare/editor_options.h"
// #include "tiles_editor.h"

class Editor :public State
{
	bool loaded;
	
	Circlebutton homebutton;
	Circlebutton levelmenubutton;
	Circlebutton playbutton;
	EditorWindow editorWindow;
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

	void load(float screen_w, float screen_h);
	void handle(sf::Event& event);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);
private:
	// void fades(double elapsedTime);
	// void fadein(float value = 1, int max = 0xFF);
	// void fadeout(float value = 1, int min = 0);
};