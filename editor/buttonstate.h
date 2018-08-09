// This class represents what happens with buttons during execution of editor.
#pragma once
#include <qabstractbutton.h>

class ButtonState
{
protected:
	static int counter;
	static int currentID;
	static bool action;
	static bool newAction;
	
public:
	static const int& getCurrentID();
	static const bool& isAction();
	static const bool& isNewAction();
};

class Button :public ButtonState
{
	int ID;
public:
	QAbstractButton* button;
	Button();
	~Button();
	void free();
	const int& getID() const;
};