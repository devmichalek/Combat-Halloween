#pragma once
#include "state.h"
#include "circlebutton.h"
#include "volumebutton.h"
#include "background/moving_bg.h"
#include "chat.h"
#include "pausesystem.h"
#include "music.h"

class Platform :public State
{
	bool loaded;
	Circlebutton homebutton;
	Circlebutton levelbutton;
	Circlebutton soundbutton;
	Circlebutton musicbutton;
	VolumeButton sound_volumebutton;
	VolumeButton music_volumebutton;
	MovingBG movingBG;
	Chat chat;
	Pausesystem pausesystem;
	cmm::Music music;
	
	void free();
	void set();
	bool isReady() const;
public:
	Platform();
	~Platform();
	void reset();

	void load(const float& screen_w, const float& screen_h);
	void handle(const sf::Event& event);
	void draw(sf::RenderWindow* &window);
	void mechanics(double elapsedTime);
private:
	void fades(const float &elapsedTime);
	void fadein(const float &value, const int &max);
	void fadeout(const float &value, const int &min);
};