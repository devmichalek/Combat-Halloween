#pragma once
#include "state.h"
#include "circlebutton.h"
#include "volumebutton.h"
#include "movingbg.h"
#include "knight.h"
#include "eye.h"
#include "tiles.h"
#include "landscape.h"
#include "lightsystem.h"
#include "chat.h"
#include "pausesystem.h"
#include "music.h"

class Platform final :public cmm::State
{
	bool loaded;
	CircleButton homebutton;
	CircleButton levelbutton;
	CircleButton soundbutton;
	CircleButton musicbutton;
	VolumeButton sound_volumebutton;
	VolumeButton music_volumebutton;
	// Action ---
	pla::MovingBG movingBG;
	pla::Knight knight;
	pla::Eye eye;
	pla::Tiles tiles;
	pla::Landscape landscape;
	pla::LightSystem lightsystem;
	// ----------
	Chat chat;
	PauseSystem pausesystem;
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
	void mechanics(const double &elapsedTime);
	void setState(int &state);
private:
	void fades(const float &elapsedTime);
	void fadein(const float &value, const int &max);
	void fadeout(const float &value, const int &min);
	void prepare();
};