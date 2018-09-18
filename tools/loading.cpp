#include "loading.h"
#include "logconsole.h"
#include <fstream>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>

cmm::Sprite Loading::progress_bar;
cmm::Text Loading::text;
cmm::Text Loading::info;

const sf::Uint8& LoadingState::getState()
{
	return state;
}

Loading::Loading()
{
	free();

	// Here below is the list of all files that "Loading" object need to have to initialize.
	printf("Checking files to initialize game...\n");
	isFileExist("openal32.dll");
	isFileExist("sfml-audio-2.dll");
	isFileExist("sfml-graphics-2.dll");
	isFileExist("sfml-network-2.dll");
	isFileExist("sfml-system-2.dll");
	isFileExist("sfml-window-2.dll");
	isDirExist("config");
	isDirExist("fonts");
	isDirExist("images");
	isDirExist("local");
	isDirExist("music");
	isDirExist("sounds");
	isFileExist(cmm::JAPOKKI_FONT_PATH);
	isFileExist("images/other/progress_bar.png");

	// If error occured we cannot start window app because of lack of missing files.
	if (error_occured)
	{
		// Press enter to continue...
		std::cout << "Press Enter to Continue...\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	else
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

Loading::~Loading()
{
	free();
}

void Loading::free()
{
	screen_w = 0;
	screen_h = 0;
	state = 0;
	prev = next = exit = false;
}



void Loading::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	// Set text.
	text.setFont(cmm::JAPOKKI_FONT_PATH);
	text.setSize(screen_h / 24);
	text.setAlpha(0xFF);
	setText();

	// Set info.
	info.setFont(cmm::JAPOKKI_FONT_PATH);
	info.setSize(screen_h / 48);
	info.setAlpha(0xFF);
	setInfo(" ");

	// Set progress bar.
	progress_bar.load("images/other/progress_bar.png", 7);
	progress_bar.setScale(screen_w / 1707, screen_h / 960);
	progress_bar.setAlpha(0xFF);
	progress_bar.setPosition(screen_w / 2 - progress_bar.getWidth() / 2, screen_h / 2 + screen_h / 36);
}

void Loading::draw(sf::RenderWindow* &window)
{
	window->clear(color);
	window->draw(text.get());
	window->draw(info.get());
	window->draw(progress_bar.get());
	window->display();
}

void Loading::mechanics(const double &elapsedTime)
{
	if (next)
	{
		int min = 0;
		text.fadeout((float)elapsedTime * 0xFF * 2, min);
		progress_bar.fadeout((float)elapsedTime * 0xFF * 2, min);
	}
	else if(!error_occured)
	{
		setText();
		++state;
		progress_bar.setOffset(state%7);

		if (state >= 101) // 100%
			next = true;
	}
}



void Loading::add(std::string str)
{
	if (error_occured)
		return;

	if (str[0] == 'S')		info.setFillColor(cmm::LogConsole::getGreenColor());
	else if(str[0] == 'W')	info.setFillColor(cmm::LogConsole::getWarningColor());
	else if (str[0] == 'E')
	{
		error_occured = true;
		state = 101;
		info.setFillColor(cmm::LogConsole::getErrorColor());
	}
	
	setInfo(str);
	drawPrivate();
}

const bool& Loading::isError()
{
	return error_occured;
}

void Loading::setState(int &state)
{
	if (isReady())
	{
		state = cmm::INIT;
	}
}



void Loading::isFileExist(std::string pathToFile)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::ifstream infile(pathToFile);
	bool status = infile.good();
	if (status)
	{
		SetConsoleTextAttribute(hConsole, 2);
		printf("Success: Correctly inspected file \"%s\".\n", pathToFile.c_str());
	}
	else
	{
		error_occured = true;
		SetConsoleTextAttribute(hConsole, 4);
		printf("Error: File \"%s\" does not exist.\n", pathToFile.c_str());
	}

	SetConsoleTextAttribute(hConsole, 7);
}

void Loading::isDirExist(std::string pathToDir)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	struct stat info;
	if (stat(pathToDir.c_str(), &info) != 0)
	{
		SetConsoleTextAttribute(hConsole, 6);
		printf("Warning: Cannot access directory \"%s\".\n", pathToDir.c_str());
	}
	
	SetConsoleTextAttribute(hConsole, 7);
}

bool Loading::isReady() const
{
	return next && progress_bar.getAlpha() == 0;
}

void Loading::setText()
{
	text.setText("Loading " + std::to_string(state) + "%");
	text.setPosition(screen_w / 2 - text.getWidth() / 2 + screen_w / 160, screen_h / 2 - text.getHeight() / 2 - screen_h / 72);
}

void Loading::setInfo(std::string n)
{
	 info.setText(n);
	 info.setPosition(screen_w / 256, screen_h - info.getHeight() * 1.25);
}

void Loading::drawPrivate()
{
	window->clear(color);
	window->draw(text.get());
	window->draw(info.get());
	window->draw(progress_bar.get());
	window->display();
}