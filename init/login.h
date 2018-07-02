#pragma once
#include "rectbutton.h"
#include "own/sprite.h"
#include "own/request.h"

class Login
{
	// Basics.
	float screen_w;
	float screen_h;
	
	float counter;
	float arrow_counter;
	float arrow_line;
	
	// First scene.
	MySprite loginbg;
	MySprite signupbg;
	Rectbutton loginbutton;
	Rectbutton signupbutton;
	
	// Second scene.
	Rectbutton gobutton;
	Rectbutton backbutton;
	MyText title;
	MyText arrow;
	MyText username_form;
	MyText password_form;
	MyText username_written;
	MyText password_written;
	
	// Information
	MyText info;
	
	// Support.
	int state;	// 0 - setting login, 1 - setting password, 2 - entered.
	string username;
	string password;
	unsigned max_length_username;
	unsigned min_length_username;
	unsigned max_length_password;
	unsigned min_length_password;
	
	// Thread.
	MyThread thread;
	
	// "I forgot password" stuff below.
	int forget_counter;
	Rectbutton forgetbutton;
	
public:
	
	// Basics.
	Login();
	~Login();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	// Getters
	bool isReady();
	string getUsername();
	
private:

	// Support.
	void setArrow();
	void setThread();
	string getPassword();
	void organizeWritten();
	bool isPossibleKey( sf::Uint8 code );
	void move( float y_add, float x_add );
	void position( float x_add = 0, float y_add = 0 );
};