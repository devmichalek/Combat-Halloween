#include "foetext.h"

FoeText::FoeText()
{
	free();
}

FoeText::~FoeText()
{
	free();
}

inline void FoeText::free()
{
	setFrequency(4);
	blend();
	resetLine();
	resetCounter();
	removeVector();
}

bool FoeText::empty()
{
	return texts.empty();
}

int FoeText::size()
{
	return texts.size();
}



inline void FoeText::blend()
{
	chosen = rand() % size();
}

void FoeText::insertText(std::string text)
{
	texts.push_back(text);
}

void FoeText::insertVector(std::vector<std::string> newTexts)
{
	for(auto &it :newTexts)
	{
		texts.push_back(it);
	}
}

void FoeText::removeBack()
{
	if (!empty())
	{
		texts.pop_back();
		texts.shrink_to_fit();
	}
}

void FoeText::removeFront()
{
	if (!empty())
	{
		texts.front() = std::move(texts.back());
		texts.pop_back();
		texts.shrink_to_fit();
	}
}

void FoeText::removeVector()
{
	if (!empty())
	{
		texts.clear();
		texts.shrink_to_fit();
	}
}

void FoeText::remove(std::string text)
{
	auto it = std::find(texts.begin(), texts.end(), text);

	if (it != texts.end())
	{
		texts.erase(it);
	}
}



inline void FoeText::resetLine()
{
	line = (rand() % static_cast<int>(frequency) + frequency);
}

inline void FoeText::resetCounter()
{
	counter = 0;
}

void FoeText::setFrequency(float seconds)
{
	frequency = seconds;
}





void FoeText::mechanics(double elapsedTime)
{
	if (!empty())
	{
		counter += elapsedTime;
		if (counter > line * 1.6)
		{
			blend();
			resetLine();
			resetCounter();
		}
	}
}

bool FoeText::isAble()
{
	return counter > line;
}

const std::string& FoeText::getCurrentText() const
{
	return texts[chosen];
}