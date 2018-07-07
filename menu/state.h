#pragma once

class State
{
protected:
	bool prev;
	bool next;
	bool exit;
	virtual bool isReady() const = 0;
public:
	State();
	~State();
	void free();
	bool isPrev() const;
	bool isNext() const;
	bool isExit() const;
	bool isState() const;
};

class Username
{
public:
	static char* username;
	static char* getUsername();
};