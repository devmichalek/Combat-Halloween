#pragma once

#include "templates/text.h"
#include "templates/sprite.h"
#include "menu/doublekey.h"
#include "menu/parentchunk.h"
#include <vector>



class Setkeyboard :public Parentchunk
{
	int nr;
	MyText* text;
	
	vector <DoubleKey> keys; // basic keys
	vector <DoubleKey> actual_keys;	// used keys
	
	int which;	// -1 = nothing was clicked;
	
	sf::Uint8 add;	// by which key you can add info?
	sf::Uint8 remove;	// by which key you can insert info?
	sf::Uint8 addMode; // state
	
	int banNr;
	int* bannedKeys;
	
	MySprite save;
	
public:

	int strToInt( string s );

	Setkeyboard();
    ~Setkeyboard();
	DoubleKey addKey( int a, int b );
	string getName( int n );
	
	void loadButton( int screen_w, int screen_h );
    void load( int left, int right, int bot );
    void draw( sf::RenderWindow &window );
	void handle( sf::Event &event );

	void fadein( int j, int max );
	void fadeout( int j, int min );
	
	vector <DoubleKey> getHeroKeys();
};

/*
enum  	Key { 
  Unknown = -1, 
  A = 0, 
  B, 
  C, 
  D, // 3
  E, 
  F, 
  G, 
  H, 
  I, 
  J, 
  K, // 10
  L, 
  M, 
  N, 
  O, 
  P, // 15
  Q, 
  R, 
  S, 
  T, 
  U, // 20
  V, 
  W, 
  X, 
  Y, 
  Z, // 25
  Num0, 
  Num1, 
  Num2, 
  Num3, 
  Num4, // 30
  Num5, 
  Num6, 
  Num7, 
  Num8, 
  Num9, // 35
  Escape, 
  LControl, 
  LShift, 
  LAlt, 
  LSystem, // 40
  RControl, 
  RShift, 
  RAlt, 
  RSystem, 
  Menu, // 45
  LBracket, 
  RBracket, 
  SemiColon, 
  Comma, 
  Period,  // 50
  Quote, 
  Slash, 
  BackSlash, 
  Tilde, 
  Equal, // 55
  Dash, 
  Space, 
  Return, 
  BackSpace, 
  Tab, // 60
  PageUp, 
  PageDown, 
  End, 
  Home, 
  Insert, // 65
  Delete, 
  Add, 
  Subtract, 
  Multiply, 
  Divide, // 70
  Left, // 71
  Right, // 72
  Up, // 73
  Down, // 74 
  Numpad0, // 75
  Numpad1, 
  Numpad2, 
  Numpad3, 
  Numpad4, 
  Numpad5, 
  Numpad6, 
  Numpad7, 
  Numpad8, 
  Numpad9, // 84
  F1, 
  F2, 
  F3, 
  F4, 
  F5, 
  F6, 
  F7, 
  F8, 
  F9, 
  F10, 
  F11, 
  F12, 
  F13, 
  F14, 
  F15, 
  Pause, 
  KeyCount 
}
*/