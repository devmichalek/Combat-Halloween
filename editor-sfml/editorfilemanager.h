#pragma once
#include "filemanager.h"
#include "messageboard.h"
#include "circlebutton.h"

class EditorFileManager
{
	int action;
	enum ACTIONS
	{
		REFRESHING = 0,
		SAVING,
		CREATING,
		LOADING,
	};

	bool active;
	bool ableToSave;
	bool ableToNew;
	bool ableToOpen;
	bool ableToUpload;
	bool ableToGoLeft;
	bool ableToGoRight;

	int page;
	int gridSquare;
	int chosenFile;

	Circlebutton filebutton;
	cmm::Sprite plank;
	sf::RectangleShape blackLayer;

	cmm::Sprite refreshButton;
	cmm::Sprite uploadButton;
	cmm::Sprite saveFileButton;
	cmm::Sprite openFileButton;
	cmm::Sprite newFileButton;
	cmm::Sprite exitButton;
	cmm::Sprite leftButton;
	cmm::Sprite rightButton;
	cmm::Sprite worldIcon;
	cmm::Sprite checkedIcon;

	cmm::Text pageText;
	cmm::Text filenameText;
	cmm::Text filenameFormText;
	cmm::Text fileManagerMessage;

	std::vector<std::string> worldNames;
	std::vector<cmm::Text*> worldNameTexts;
	std::vector<sf::Vector2f> worldIconPositions;

	FileManager fileManager;
	MessageBoard messageBoard;

public:
	EditorFileManager();
	~EditorFileManager();
	void free();
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	bool isActive();
	void setActive();
	bool loadedFile();	// file was loaded
	void setFileButtonActive();

private:
	bool isFileOpen();
	bool isFileUnsave();
	void saveFile();
	void openFile();
	void newFile();
	void refresh();

	void refreshText();
	void setPageText();
	void setFileNameText();
	void setFileManagerMessage();
	void setButtonsAlpha(float newAlpha);
};