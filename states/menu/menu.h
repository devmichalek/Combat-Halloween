#pragma once
#include "state.h"
#include "knightspecs.h"
#include "linkbutton.h"
#include "squarebutton.h"
#include "circlebutton.h"
#include "volumebutton.h"
#include "settings.h"
#include "menuinformation.h"
#include "chat.h"
#include "pausesystem.h"
#include "music.h"

class Menu :public State
{
	bool loaded;
	Knightspecs knightspecs;
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
	Chat chat;
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

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event& event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
private:
	void fades(const float &elapsedTime);
	void fadein(const float &value, const int &max);
	void fadeout(const float &value, const int &min);
};