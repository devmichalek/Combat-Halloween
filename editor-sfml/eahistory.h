#pragma once
#include <vector>

class EAHistory
{
	bool change;
	std::vector<std::pair<int, int>> xy;	// x y pos
	std::vector<std::pair<char, char>> tc;	// type chosen
	std::vector<std::string> ai;			// additional info
	std::vector<std::string> history;

public:
	EAHistory();
	~EAHistory();
private:
	void free();
public:
	void reset();

	const std::vector<std::string>& get();
	void set(const std::vector<std::string> &newHistory);

	void add(const int &x, const int &y, const int &t, const int &c, const std::string &ai);
	void undo();
	void remove(const int &t, const int &c, const int &x, const int &y);
	void modify(const int &t, const int &c, const int &x, const int &y, const std::string &ai);
};