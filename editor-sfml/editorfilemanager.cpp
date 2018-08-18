#include "editorfilemanager.h"
#include "dirent.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include "state.h"

EditorFileManager::EditorFileManager()
{
	free();
}

EditorFileManager::~EditorFileManager()
{
	free();
}

void EditorFileManager::free()
{
	action = -1;

	active = false;
	ableToSave = false;
	ableToNew = false;
	ableToOpen = false;
	ableToUpload = false;
	ableToGoLeft = false;
	ableToGoRight = false;
	page = 0;
	gridSquare = 9;
	chosenFile = -1;
}

void EditorFileManager::reset()
{
	ableToOpen = true;
	ableToNew = true;
	page = 0;
	chosenFile = -1;

	setButtonsAlpha(0xFF / 1.5);
	refresh();
	setPageText();
	setFileNameText();
}




void EditorFileManager::load(const float &screen_w, const float &screen_h)
{
	float scale_x = screen_w / 1920;	if (scale_x > 1.0f)	scale_x = 1;
	float scale_y = screen_h / 1080;	if (scale_y > 1.0f)	scale_y = 1;


	filebutton.load("images/buttons/save.png");
	filebutton.setScale(screen_w / 2560, screen_h / 1440);
	filebutton.setPosition(screen_w - screen_w / 128 - filebutton.getWidth() * 2, screen_h / 144);
	
	plank.load("images/other/plank.png");
	plank.setScale(scale_x, scale_y);
	plank.center(screen_w / 2, screen_h / 2);
	blackLayer.setFillColor(sf::Color(0, 0, 0, 140));
	blackLayer.setSize(sf::Vector2f(screen_w, screen_h));
	blackLayer.setPosition(0, 0);

	float factor = 0.9f;
	float off = screen_w / 200.0f;
	refreshButton.load("images/icons/refreshicon.png");
	uploadButton.load("images/icons/uploadicon.png");
	saveFileButton.load("images/icons/savefileicon.png");
	openFileButton.load("images/icons/openfileicon.png");
	newFileButton.load("images/icons/newfileicon.png");
	exitButton.load("images/icons/exiticon.png");
	leftButton.load("images/icons/lefticon.png");
	rightButton.load("images/icons/righticon.png");
	worldIcon.load("images/icons/fileicon.png");
	checkedIcon.load("images/icons/checkedicon.png");

	refreshButton.setScale(scale_x * factor, scale_y * factor);
	uploadButton.setScale(scale_x * factor, scale_y * factor);
	saveFileButton.setScale(scale_x * factor, scale_y * factor);
	openFileButton.setScale(scale_x * factor, scale_y * factor);
	newFileButton.setScale(scale_x * factor, scale_y * factor);
	exitButton.setScale(scale_x * factor, scale_y * factor);
	leftButton.setScale(scale_x * factor, scale_y * factor);
	rightButton.setScale(scale_x * factor, scale_y * factor);
	worldIcon.setScale(scale_x * factor, scale_y * factor);
	checkedIcon.setScale(scale_x * factor, scale_y * factor);

	newFileButton.setPosition(plank.getLeft() + off, plank.getTop() + off);
	openFileButton.setPosition(newFileButton.getRight() + off / 2, newFileButton.getTop());
	saveFileButton.setPosition(openFileButton.getRight() + off, newFileButton.getTop());
	uploadButton.setPosition(saveFileButton.getRight() + off, newFileButton.getTop());
	refreshButton.setPosition(uploadButton.getRight() + off, newFileButton.getTop());
	exitButton.setPosition(plank.getRight() - newFileButton.getWidth() - off, plank.getTop() + off);
	leftButton.setPosition(plank.getLeft() + off, plank.getTop() + plank.getHeight() / 2 - leftButton.getHeight() / 2);
	rightButton.setPosition(plank.getRight() - off - rightButton.getWidth(), leftButton.getTop());

	const char* pathToFont = "fonts/Jaapokki-Regular.otf";
	pageText.setFont(pathToFont);
	filenameText.setFont(pathToFont);
	filenameFormText.setFont(pathToFont);
	fileManagerMessage.setFont(pathToFont);
	pageText.setSize(plank.getWidth() / 20);
	filenameText.setSize(plank.getWidth() / 20);
	filenameFormText.setSize(plank.getWidth() / 20);
	fileManagerMessage.setSize(plank.getWidth() / 20);
	pageText.setAlpha(0xFF);
	filenameText.setAlpha(0xFF);
	filenameFormText.setAlpha(0xFF);
	filenameFormText.setText("File: ");
	filenameFormText.setPosition(plank.getLeft() + off, newFileButton.getBot() + off);
	fileManagerMessage.setOutlineThickness(1);

	messageBoard.load(screen_w, screen_h);
	fileManager.setDirectoryPath("local");

	ableToOpen = true;
	ableToNew = true;
	setButtonsAlpha(0xFF / 1.5);
	refresh();
	setPageText();
	setFileNameText();
}

void EditorFileManager::handle(const sf::Event &event)
{
	if (active)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				float x = (float)event.mouseButton.x;
				float y = (float)event.mouseButton.y;

				messageBoard.handle(event);

				if (refreshButton.checkCollision(x, y))
				{
					refresh();
				}
				else if (saveFileButton.checkCollision(x, y))
				{
					saveFile();
				}
				else if (openFileButton.checkCollision(x, y))
				{
					openFile();
				}
				else if (newFileButton.checkCollision(x, y))
				{
					newFile();
				}
				else if (exitButton.checkCollision(x, y))
				{
					page = 0;
					setPageText();
					active = false;
				}
				else if (leftButton.checkCollision(x, y))
				{
					if (page > 0)
					{
						--page;
						setPageText();
					}
				}
				else if (rightButton.checkCollision(x, y))
				{
					if (page < (int)worldIconPositions.size() / gridSquare)
					{
						++page;
						setPageText();
					}
				}
				else	// maybe icon?
				{
					chosenFile = -1;
					setFileNameText();
					int iconStart = page == 0 ? 0 : gridSquare * page;
					int iconPage = gridSquare + gridSquare * page;
					int iconEnd = (int)worldIconPositions.size() > iconPage ? iconPage : worldIconPositions.size();
					for (int i = iconStart; i < iconEnd; ++i)
					{
						worldIcon.setPosition(worldIconPositions[i].x, worldIconPositions[i].y);
						if (worldIcon.checkCollision(x, y))
						{
							checkedIcon.setPosition(worldIcon.getX(), worldIcon.getY());
							chosenFile = i;
							setFileNameText();
							break;
						}
					}
				}
			}
		}

		// hovering...
		if (event.type == sf::Event::MouseMoved)
		{
			setButtonsAlpha(0xFF / 1.5);

			float newAlpha = 0xFF;
			float x = (float)event.mouseMove.x;
			float y = (float)event.mouseMove.y;

			if (refreshButton.checkCollision(x, y))						refreshButton.setAlpha(newAlpha);
			else if (saveFileButton.checkCollision(x, y) && ableToSave)	saveFileButton.setAlpha(newAlpha);
			else if (openFileButton.checkCollision(x, y) && ableToOpen)	openFileButton.setAlpha(newAlpha);
			else if (newFileButton.checkCollision(x, y) && ableToNew)	newFileButton.setAlpha(newAlpha);
			else if (exitButton.checkCollision(x, y))					exitButton.setAlpha(newAlpha);
			else if (leftButton.checkCollision(x, y) && ableToGoLeft)	leftButton.setAlpha(newAlpha);
			else if (rightButton.checkCollision(x, y) && ableToGoRight)	rightButton.setAlpha(newAlpha);
		}
	}

	filebutton.setActive(active);
	filebutton.handle(event);
}

void EditorFileManager::draw(sf::RenderWindow* &window)
{
	filebutton.draw(window);

	if (!active) return;

	if (!messageBoard.isActive())
		window->draw(blackLayer);

	window->draw(plank.get());
	window->draw(newFileButton.get());
	window->draw(openFileButton.get());
	window->draw(saveFileButton.get());
	window->draw(uploadButton.get());
	window->draw(refreshButton.get());
	window->draw(exitButton.get());
	
	// Draw files only if there is no message
	if (fileManagerMessage.getAlpha() > 0)
	{
		window->draw(fileManagerMessage.get());
	}
	else
	{
		if (ableToGoLeft)	window->draw(leftButton.get());
		if (ableToGoRight)	window->draw(rightButton.get());

		int iconStart = page == 0 ? 0 : gridSquare * page;
		int iconPage = gridSquare + gridSquare * page;
		int iconEnd = (int)worldIconPositions.size() > iconPage ? iconPage : worldIconPositions.size();
		for (int i = iconStart; i < iconEnd; ++i)
		{
			worldIcon.setPosition(worldIconPositions[i].x, worldIconPositions[i].y);
			window->draw(worldIcon.get());
			window->draw(worldNameTexts[i]->get());
		}

		window->draw(pageText.get());
		window->draw(filenameText.get());
		window->draw(filenameFormText.get());
		if(chosenFile != -1)	window->draw(checkedIcon.get());
	}

	if (messageBoard.isActive())
		window->draw(blackLayer);

	messageBoard.draw(window);
}

void EditorFileManager::mechanics(const double &elapsedTime)
{
	if (filebutton.isActive())
	{
		setActive();
	}

	if (!active) return;

	if (messageBoard.isActive())
	{
		if (messageBoard.isDecision())
		{
			if (messageBoard.isYes())	// yes
			{
				if (action == REFRESHING)	fileManager.refresh();
				else if (action == SAVING)	fileManager.save();
				else if (action == CREATING)fileManager.create();
				else if (action == LOADING)	fileManager.open();
			}

			action = -1;
			messageBoard.free();
		}
	}


	if(fileManager.isStatus())
	{
		if (fileManager.isSuccess())
		{
			if (action == REFRESHING)
			{
				refreshText();
				setPageText();
				action = -1;
			}
			else if (action == LOADING)
			{

			}
		}
		else if (fileManager.isWarning())
		{
			if (action == REFRESHING)
			{
				refreshText();
				setPageText();
				action = -1;
			}
		}
		else if (fileManager.isFailure())
		{

		}
		
		setFileManagerMessage();
	}

	fileManager.mechanics();


	int min = 0;
	fileManagerMessage.fadeout((float)elapsedTime * 150, min);
}




bool EditorFileManager::isActive()
{
	return active;
}

void EditorFileManager::setActive()
{
	active = true;
}

bool EditorFileManager::loadedFile()
{
	return false;
}

void EditorFileManager::setFileButtonActive()
{
	filebutton.setActive(true);
}





bool EditorFileManager::isFileOpen()
{
	return fileManager.getFilePath() != "";
}

bool EditorFileManager::isFileUnsave()
{
	return fileManager.isNewSaveVersion();
}

void EditorFileManager::saveFile()
{
	if (isFileOpen())
	{
		action = SAVING;
		fileManager.save();
	}
}

void EditorFileManager::openFile()
{
	action = LOADING;

	if (chosenFile == -1)
	{
		messageBoard.setActive(2);
		messageBoard.setMessage("There is no chosen file.\nChoose file by clicking on the icon.");
	}
	else if (isFileUnsave())
	{
		if (isFileUnsave())
		{
			messageBoard.setActive();
			messageBoard.setMessage("There is unsaved file.\nDo you want to continue?");
		}
		else
		{
			fileManager.open();
		}
	}
	else
	{
		fileManager.open();
	}
}

void EditorFileManager::newFile()
{
	action = CREATING;

	if (fileManager.checkIfFileExists())
	{
		messageBoard.setActive();
		messageBoard.setMessage("There is already file with this name.\nDo you want to override this file?");
	}
	else if (isFileOpen())
	{
		if (isFileUnsave())
		{
			messageBoard.setActive();
			messageBoard.setMessage("There is unsaved file.\nDo you want to continue?");
		}
	}
	else
	{
		fileManager.create();
	}
}

void EditorFileManager::refresh()
{
	action = REFRESHING;
	fileManager.refresh();
}



void EditorFileManager::refreshText()
{
	page = 0;
	chosenFile = -1;
	setFileNameText();

	std::vector<std::string> temp;
	temp = fileManager.getDirectories();

	// Erase other files.
	for (std::vector<std::string>::iterator it = temp.begin(); it != temp.end();)
	{
		int size = it->size() - 1;

		std::string str = *it;
		if(size - 3 < 1)
			it = temp.erase(it);
		else if (str[size] != 'w' || str[size - 1] != 'h' || str[size - 2] != 'c' || str[size - 3] != '.')
			it = temp.erase(it);
		else
			++it;
	}

	// Clear world names.
	if (!worldNames.empty())
		worldNames.clear();

	// Clear world texts.
	if (!worldNameTexts.empty())
	{
		for (auto &it : worldNameTexts)
		{
			delete it;
			it = nullptr;
		}

		worldNameTexts.clear();
	}

	// Clear icon positions
	if (!worldIconPositions.empty())
		worldIconPositions.clear();

	const char* pathToFont = "fonts/Jaapokki-Regular.otf";
	for (auto &it : temp)
	{
		worldNameTexts.push_back(new cmm::Text);
		int n = worldNameTexts.size() - 1;
		worldNameTexts[n]->setFont(pathToFont);
		worldNameTexts[n]->setSize(plank.getWidth() / 30);
		worldNames.push_back(it);

		std::string outStr = it.substr(0, it.size() - 4);
		if (it.size() > 21)			outStr = it.substr(0, 11) + "\n" + it.substr(12, 8) + "...";
		else if (it.size() > 12)	outStr = it.substr(0, 8) + "..."; // 11 c
		worldNameTexts[n]->setText(outStr);

		worldNameTexts[n]->setAlpha(0xFF);
	}

	// Positioning.
	int xc = 0, yc = 0;
	int gridLength = (int)sqrt(gridSquare) - 1;
	float off = plank.getWidth() / 30;
	float w = plank.getWidth() / 5;
	int startX = (int)(plank.getX() + plank.getWidth() / 2 - (w * (gridLength + 1) + off * gridLength) / 2 + off);
	for (unsigned i = 0; i < worldNameTexts.size(); ++i)
	{
		worldIconPositions.push_back(sf::Vector2f());
		worldIconPositions[i].x = startX + off + (w + off) * xc;
		worldIconPositions[i].y = filenameFormText.getBot() + off * 2 + w * yc;

		worldNameTexts[i]->setPosition(worldIconPositions[i].x + worldIcon.getWidth() / 2 - worldNameTexts[i]->getWidth() / 2, worldIconPositions[i].y + worldIcon.getHeight());

		++xc;

		if (xc > gridLength)
		{
			xc = 0;
			++yc;
		}

		if (yc > gridLength)	yc = 0;
	}

	worldNameTexts.shrink_to_fit();
	worldIconPositions.shrink_to_fit();
}

void EditorFileManager::setPageText()
{
	pageText.setText(std::to_string(page) + "/" + std::to_string(worldIconPositions.size() / gridSquare));
	pageText.setPosition(plank.getRight() - pageText.getWidth() * 1.2, plank.getBot() - plank.getWidth() / 15);

	if (page == 0)	ableToGoLeft = false;
	else			ableToGoLeft = true;

	if (page == worldIconPositions.size() / gridSquare)	ableToGoRight = false;
	else												ableToGoRight = true;
}

void EditorFileManager::setFileNameText()
{
	std::string str = "-", oryg = "-";
	if (chosenFile != -1)
	{
		int size = worldNames[chosenFile].size();
		if (size < 25)	str = worldNames[chosenFile].substr(0, size);
		else			str = worldNames[chosenFile].substr(0, 22) + "...";
		oryg = worldNames[chosenFile];
	}

	fileManager.setFilePath(str);
	filenameText.setText(oryg);
	filenameText.setPosition(filenameFormText.getRight() + (filenameFormText.getLeft() - plank.getLeft()), filenameFormText.getTop());
}

void EditorFileManager::setFileManagerMessage()
{	
	fileManagerMessage.setText(fileManager.getMessage());

	fileManagerMessage.setPosition(plank.getX() + plank.getWidth() / 2 - fileManagerMessage.getWidth() / 2,
		plank.getY() + plank.getHeight() / 2 - fileManagerMessage.getHeight() / 2);
	fileManagerMessage.setAlpha(0xFF);

	fileManagerMessage.setFillColor(User::getLoadingColor());
	fileManagerMessage.setOutlineColor(sf::Color::Black);
}

void EditorFileManager::setButtonsAlpha(float newAlpha)
{
	refreshButton.setAlpha(newAlpha);
	uploadButton.setAlpha(newAlpha);
	saveFileButton.setAlpha(newAlpha);
	openFileButton.setAlpha(newAlpha);
	newFileButton.setAlpha(newAlpha);
	exitButton.setAlpha(newAlpha);
	leftButton.setAlpha(newAlpha);
	rightButton.setAlpha(newAlpha);
}