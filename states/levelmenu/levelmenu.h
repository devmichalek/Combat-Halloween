#pragma once
#include "state.h"
#include "circlebutton.h"
#include "volumebutton.h"
#include "levelmenuinformation.h"
#include "chat.h"
#include "pausesystem.h"
#include "music.h"

class LevelMenu final :public cmm::State
{
	bool loaded;
	CircleButton homebutton;
	CircleButton updatebutton;
	CircleButton playbutton;
	CircleButton soundbutton;
	CircleButton musicbutton;
	VolumeButton sound_volumebutton;
	VolumeButton music_volumebutton;
	LevelMenuInformation information;
	Chat chat;
	PauseSystem pausesystem;
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
	void setState(int &state);
private:
	void fades(const double &elapsedTime);
	void fadein(const float &value, const int &max);
	void fadeout(const float &value, const int &min);
};