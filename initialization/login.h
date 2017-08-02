#pragma once

#include "own/text.h"
#include "own/sprite.h"
#include "rectbutton.h"
#include <thread>

class Login
{
	bool ready;
	int screen_w;
	int screen_h;
	
	float counter;
	float velocity;
	
	float arrow_counter;
	float arrow_line;
	
	// First scene.
	Rectbutton login;
	Rectbutton signup;
	MySprite login_bg;
	MySprite signup_bg;
	
	// Second scene.
	Rectbutton back;
	MyText label;
	MyText username_form;
	MyText password_form;
	MyText username_written;
	MyText password_written;
	MyText arrow;
	Rectbutton go;
	MyText error;
	
	// Support.
	int status;
	string username;
	string password;
	unsigned max_length_username;
	unsigned min_length_username;
	unsigned max_length_password;
	unsigned min_length_password;
	bool error_status;
	
	std::thread* myThread;
	
public:

	Login();
	~Login();
	void free();
	
	void load( int screen_w, int screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window, double elapsedTime );
	
	bool isReady();
	
	// Support.
	bool isPossibleKey( sf::Event &event );
	string getName( int n );
	void organizeWritten();
	string getPassword();
	void setArrow();
	void position( float x_add = 0, float y_add = 0 );
	void sendRequest();
};