#pragma once
#include "state.h"
#include "sprite.h"
#include "text.h"
#include "thread.h"
#include "eventwindow.h"
#include "wcontent.h"
#include "rectbutton.h"

class WSim : public cmm::State// World Simulator
{
	enum STATUS
	{
		NONE = -1,
		PROCESSING = 0,
		SUCCESS,
		WARNING,
		FAILURE,
		EXIT
	};

	int status;

	// Diplay info data.
	cmm::Text text;
	cmm::Text info;
	cmm::Sprite progress_bar;

	// Navigation.
	RectButton errorButton;

	// Processing entities
	cmm::Thread thread;
	

public:
	WSim();
	~WSim();
private:
	void free();
public:

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
	void setState(int &state);

private:
	bool isReady() const;
	void disunite();
	bool prepare();		// load from file / download from server
	bool sort();
	bool simulate();
};