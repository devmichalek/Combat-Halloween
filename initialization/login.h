#pragma once
#include "own/sprite.h"
#include "rectbutton.h"
#include <thread>

class Login
{
	// Basics.
	bool ready;
	float screen_w;
	float screen_h;
	float counter;
	float velocity;
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
	bool info_status;
	
	// Support.
	int state;
	string username;
	string password;
	unsigned max_length_username;
	unsigned min_length_username;
	unsigned max_length_password;
	unsigned min_length_password;
	
	// Thread.
	std::thread* myThread;
	bool thread_ready;
	
	// I forgot password.
	int forget_counter;
	Rectbutton forgetbutton;
	
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
	string getUsername();
	void setArrow();
	void position( float x_add = 0, float y_add = 0 );
	void sendRequest();
};