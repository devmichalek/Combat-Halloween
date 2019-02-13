#pragma once
#include "eeitem.h"
#include "econtent.h"
#include <SFML/Window/Event.hpp>

class EAHistory final : public EContent
{
	int index;
	int counterID;
	std::vector<ee::Item> items;

public:
	EAHistory();
	~EAHistory();
private:
	void free();
public:
	void clear();
	void clear_local();
	void fill_local();

	bool next();
	const ee::Item &getItem();

	void add(const ee::Item &item);
	bool force(const ee::Item &item);
	bool tryUndo(int &t, int &x, int &y);
	std::vector<ee::Item>::iterator getIteratorByID(const int &ID);
	void remove(const ee::Item &item);
	void modify(const ee::Item &item);
	const int getNewID();
};