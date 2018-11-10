#pragma once
#include "state.h"
#include "thread.h"
#include "sprite.h"
#include "request.h"
#include "rectbutton.h"

class Login final : public cmm::State
{
	// Basics.
	float screen_w;
	float screen_h;

	float counter;
	float arrow_counter;
	float arrow_line;

	// First scene.
	cmm::Sprite loginbg;
	cmm::Sprite signupbg;
	RectButton loginbutton;
	RectButton signupbutton;

	// Second scene.
	RectButton gobutton;
	RectButton backbutton;
	sf::Rect<float> usernameCollision;
	sf::Rect<float> passwordCollision;
	cmm::Text title;
	cmm::Text arrow;
	cmm::Text username_form;
	cmm::Text password_form;
	cmm::Text username_written;
	cmm::Text password_written;

	// Information
	cmm::Text info;
	std::string info_str;

	// Support.
	int state;	// 0 - setting login, 1 - setting password, 2 - entered.
	std::string username;
	std::string password;
	unsigned max_length_username;
	unsigned min_length_username;
	unsigned max_length_password;
	unsigned min_length_password;

	// Thread.
	cmm::Thread thread;

	// "I forgot password" stuff below.
	int forget_counter;
	RectButton forgetbutton;

public:
	Login();
	~Login();
	void free();
	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

private:	// Support.
	void setArrow();
	void setThread();
	std::string getPassword();
	void organizeWritten();
	bool isPossibleKey(const sf::Uint8 &code) const;
	void move(float y_add, float x_add);
	void position(float x_add = 0, float y_add = 0);

	bool isReady() const; public:
	void setState(int &state);
};