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

class Menu :public cmm::State
{
	bool loaded;
	Knightspecs knightspecs;
	LinkButton github;
	LinkButton scores;
	LinkButton website;
	SquareButton singleplayerbutton;
	SquareButton multiplayerbutton;
	SquareButton exitbutton;
	CircleButton soundbutton;
	CircleButton musicbutton;
	CircleButton updatebutton;
	CircleButton reloadbutton;
	CircleButton settingsbutton;
	Settings settings;
	VolumeButton sound_volumebutton;
	VolumeButton music_volumebutton;
	MenuInformation information;
	Chat chat;
	PauseSystem pausesystem;
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
	void setState(int &state);
private:
	void fades(const float &elapsedTime);
	void fadein(const float &value, const int &max);
	void fadeout(const float &value, const int &min);
};