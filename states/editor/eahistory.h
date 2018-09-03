#pragma once
#include "econtent.h"
#include <SFML/Window/Event.hpp>

class EAHistory : public EContent
{
	int index;
	std::vector<int> ids;					// id
	std::vector<std::pair<int, int>> xy;	// x y pos
	std::vector<std::pair<char, char>> tc;	// type chosen
	std::vector<std::string> ai;			// additional info

	bool ctrl_key;
	bool z_key;
	bool undoState;
	int counterID;

public:
	EAHistory();
	~EAHistory();
private:
	void free();
public:
	void reset();
	void clear();
	void clear_local();
	void fill_local();

	void handle(const sf::Event &event);
	bool next();
	void getXY(int &x, int &y);
	void getTC(char &t, char &c);
	void getID(int &id);
	void getAI(std::string &ai);

	void add(const int &t, const int &c, const int &x, const int &y, const std::string &ai, int ID = -1);
	bool undo(int &t, int &x, int &y);
	void remove(int t, const int &c, const int &x, const int &y);
	void removeByID(const int &ID);
	void modify(const int &t, const int &c, const int &x, const int &y, const std::string &ai);
	void modifyByID(const int &ID, const std::string &ai);
	const int getNewID();
};