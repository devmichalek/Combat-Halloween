#pragma once
#include "efminfo.h"
#include "efmlibrary.h"
#include "efmbuttons.h"
#include "filemanager.h"
#include "messageboard.h"
#include "efmtexteditor.h"

class EditorFileManager
{
	int action;
	enum ACTIONS
	{
		CREATING = 0,
		LOADING,
		SAVING,
		UPLOADING,
		COPYING,
		RENAMING,
		DELETING,
		REFRESHING,
	};
	
	EFMInfo info;
	EFMLibrary library;
	EFMButtons buttons;
	FileManager fileManager;
	MessageBoard messageBoard;
	EFMTextEditor textEditor;

public:
	EditorFileManager();
	~EditorFileManager();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	void push(std::string line);
	void pop();
	bool isNewContent();
	void setActive();	// for chat to open file manager directly

private:
	bool isFileOpen();
	bool isFileUnsave();
	
	void newFile();
	void openFile();
	void saveFile();
	// void uploadFile();
	void copyFile();	// works
	void renameFile();
	void deleteFile();	// works
	void refresh();		// works
};