#pragma once
#include "text.h"
#include "sprite.h"
#include "thread.h"
#include "request.h"
#include "eventwindow.h"
#include "colors.h"

class MenuInformation final
{
	float screen_w;
	float screen_h;

	cmm::Text money;
	cmm::Text money_form;
	cmm::Text username;
	cmm::Text username_form;

	cmm::Sprite plank;
	cmm::Sprite scene;
	cmm::Sprite background;
	cmm::Thread thread;

public:
	MenuInformation();
	~MenuInformation();
	void free();

	void load(float screen_w, float screen_h);
	void draw(sf::RenderWindow* &window);
	void mechanics();
	void fadein(float v = 1, int max = (int)MAX_ALPHA);
	void fadeout(float v = 1, int min = (int)MIN_ALPHA);

	void setThread();
	void reloadThread();
	private: void setMoney(); public:
	bool isReady() const;		// money is loaded correctly from database
	int getBackgroundAlpha() const;
};