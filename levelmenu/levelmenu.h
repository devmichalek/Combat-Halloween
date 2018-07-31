#pragma once
#include "state.h"
#include "button.h"
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

	void load(float screen_w, float screen_h);
	void handle(sf::Event& event);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);
private:
	void fades(double elapsedTime);
	void fadein(float value = 1, int max = 0xFF);
	void fadeout(float value = 1, int min = 0);
};