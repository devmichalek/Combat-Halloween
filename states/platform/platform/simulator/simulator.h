#pragma once
#include "state.h"
#include "sprite.h"
#include "text.h"
#include "thread.h"
#include "eventwindow.h"
#include "scontent.h"
#include "rectbutton.h"
//#include <mutex>


class Simulator final : public cmm::State
{
	enum STATUS
	{
		NONE = 0,
		PROCESSING,
		SUCCESS,
		WARNING,
		FAILURE
	};

	int status;
	float screen_w;
	float screen_h;

	// Info data.
	cmm::Text info;
	cmm::Sprite progress_bar;
	float offset; int max;

	// Navigation.
	RectButton backbutton;
	RectButton reloadbutton;

	// Processing.
	cmm::Thread thread;
	std::string msg;
	//std::mutex mtx;
	//std::condition_variable cv;

public:
	Simulator();
	~Simulator();
private:
	void free();
public:
	void reset();

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
	void setInfo();
	bool checkContent(std::string str);	// it checks whether content is empty or not, also, set msg

	// Set message.
	void condition();
	void setProcessingMsg(std::string str);
	void setSuccessMsg(std::string str);
	void setWarningMsg(std::string str);
	void setErrorMsg(std::string str);
};