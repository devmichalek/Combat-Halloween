#pragma once
#include <vector>
#include <string>

class FoeText
{
	int chosen;
	float line;
	float counter;
	float frequency;
	std::vector<std::string> texts;

public:
	FoeText();
	~FoeText();
private:
	void free();
public:
	bool empty();
	int size();

	void blend();
	void insertText(std::string text);
	void insertVector(std::vector<std::string> newTexts);

	void removeBack();
	void removeFront();
	void removeVector();
	void remove(std::string text);

private:
	void resetLine();
	void resetCounter(); 
public:
	void setFrequency(float seconds = 8);

	void mechanics(double elapsedTime);
	bool isAble();
	const std::string& getCurrentText() const;
}