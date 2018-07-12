#pragma once
#include "state.h"
#include "button.h"
// #include "level/chat.h"
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
	// Chat chat;
	Pausesystem pausesystem;
	cmm::Music music;
	
	void free();
	void set();
	bool isReady() const;
public:
	Platform();
	~Platform();
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