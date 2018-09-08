#pragma once
#include "state.h"
#include "circlebutton.h"
#include "volumebutton.h"
#include "levelmenuinformation.h"
#include "chat.h"
#include "pausesystem.h"
#include "music.h"

class LevelMenu :public State
{
	bool loaded;
	Circlebutton homebutton;
	Circlebutton updatebutton;
	Circlebutton playbutton;
	Circlebutton soundbutton;
	Circlebutton musicbutton;
	VolumeButton sound_volumebutton;
	VolumeButton music_volumebutton;
	LevelMenuInformation information;
	Chat chat;
	Pausesystem pausesystem;
	cmm::Music music;

public:
	LevelMenu();
	~LevelMenu();
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
	void fades(const double &elapsedTime);
	void fadein(const float &value, const int &max);
	void fadeout(const float &value, const int &min);
};