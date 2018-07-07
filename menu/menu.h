#pragma once
#include "state.h"
// #include "knight_specs.h"
#include "button.h"
#include "settings.h"
#include "menuinformation.h"
// #include "level/chat.h"
#include "pausesystem.h"
#include "music.h"

class Menu :public State
{
	bool loaded;
	// Knight_specs knight_specs;
	LinkButton github;
	LinkButton scores;
	LinkButton website;
	SquareButton singleplayerbutton;
	SquareButton multiplayerbutton;
	SquareButton exitbutton;
	Circlebutton soundbutton;
	Circlebutton musicbutton;
	Circlebutton updatebutton;
	Circlebutton reloadbutton;
	Circlebutton settingsbutton;
	Settings settings;
	VolumeButton sound_volumebutton;
	VolumeButton music_volumebutton;
	MenuInformation information;
	// Chat chat;
	Pausesystem pausesystem;
	cmm::Music music;

public:
	Menu();
	~Menu();
private:
	void free();
	void set();
	bool isReady() const;
public:
	void reset();

	void load(float screen_w, float screen_h);
	void handle(sf::Event& event);
	void head(sf::RenderWindow* &window, double elapsedTime);

private:
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);
	void fades(double elapsedTime);
	void fadein(float value = 1, int max = 0xFF);
	void fadeout(float value = 1, int min = 0);
};