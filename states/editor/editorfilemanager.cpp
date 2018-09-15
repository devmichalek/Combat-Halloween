#include "editorfilemanager.h"
#include "loading.h"

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
}

void EditorFileManager::reset()
{
	info.reset();
	library.reset();
	buttons.reset();
	messageBoard.reset();
	textEditor.reset();
	textEditor.clear();
	refresh();
}




void EditorFileManager::load(const float &screen_w, const float &screen_h)
{
	info.load(screen_w, screen_h);
	buttons.load(screen_w, screen_h, info.getLeft(), info.getRight(), info.getTop());
	library.load(screen_w, screen_h, sf::FloatRect(info.getRect()));
	messageBoard.load(screen_w, screen_h);
	fileManager.setDirectoryPath("local");
	textEditor.load(screen_w, screen_h);
	refresh();
}

void EditorFileManager::handle(const sf::Event &event)
{
	bool status = !messageBoard.isActive() && !textEditor.isActive() ? buttons.handle(event) : false;

	if (buttons.isActive())
	{
		if (!messageBoard.isActive())
		{
			textEditor.handle(event);

			if (!textEditor.isActive())
			{
				if (library.handle(event, status))
				{
					if (library.isChosen())
						fileManager.setChosenFileName(info.setChosenText(library.getChosenStr()));
					else
						fileManager.setChosenFileName(info.setChosenText("-"));
				}
			}
		}
		
		messageBoard.handle(event);
	}
}

void EditorFileManager::draw(sf::RenderWindow* &window)
{
	buttons.drawButton(window);

	if (!buttons.isActive()) return;

	// Draw Black Layer
	if (!messageBoard.isActive() && !textEditor.isActive())
		info.drawLayer(window);

	info.drawPlank(window);
	buttons.draw(window);
	
	// Draw files only if there is no message
	if (!info.isMsgTextActive())
	{
		library.draw(window);
		info.draw(window);
	}

	// Draw Black Layer
	if (messageBoard.isActive() || textEditor.isActive())
		info.drawLayer(window);

	textEditor.draw(window);
	messageBoard.draw(window);
}

void EditorFileManager::mechanics(const double &elapsedTime)
{
	if (!buttons.isActive()) return;

	if (buttons.isNewFile())		newFile();
	else if (buttons.isOpenFile())	openFile();
	else if (buttons.isSaveFile())	saveFile();
	else if (buttons.isUploadFile())
	{
		// there is no upload available
	}
	else if (buttons.isCopyFile())		copyFile();
	else if (buttons.isRenameFile())	renameFile();
	else if (buttons.isDeleteFile())	deleteFile();
	else if (buttons.isRefresh())		refresh();
	else if (buttons.isExit())			library.reset();


	if (messageBoard.isActive())
	{
		if (messageBoard.isDecision())
		{
			int temp = action;
			action = -1;

			if (messageBoard.isYes())	// yes
			{
				if (temp == CREATING)
				{
					action = CREATING;
					fileManager.create(textEditor.get());
					textEditor.clear();
					textEditor.reset();
				}
				else if (temp == LOADING)
				{
					fileManager.open();
				}	
				else if (temp == SAVING)
				{
					action = SAVING;
					fileManager.setLoadedFileName(textEditor.get());
					fileManager.save();
					textEditor.clear();
					textEditor.reset();
				}
				else if (temp == UPLOADING)		{}
				else if (temp == COPYING)		fileManager.copy();
				else if (temp == RENAMING)
				{
					action = RENAMING;
					if (fileManager.loadedIsChosen())	info.setOpenedText(textEditor.get());
					fileManager.rename(textEditor.get());
					textEditor.clear();
					textEditor.reset();
				}
				else if (temp == DELETING)
				{
					if (fileManager.loadedIsChosen())
						info.setOpenedText("-");
					fileManager.deletee();
				}
				else if (temp == REFRESHING)	fileManager.refresh();
			}
			else if (messageBoard.isOk())	// ok
			{
				if (temp == CREATING)		action = CREATING;
				else if (temp == RENAMING)	action = RENAMING;
			}

			messageBoard.reset();
		}
	}

	if (textEditor.isActive())
	{
		if (textEditor.isDecision())
		{
			if (textEditor.isProceed())	// proceed, set active as false if user made final decision
			{
				if (textEditor.isMistake())
				{
					messageBoard.setActive(2);
					messageBoard.setMessage(textEditor.getMsg());
				}
				else if (fileManager.checkIfFileExists(textEditor.get()))
				{
					messageBoard.setActive();
					messageBoard.setMessage("There is already file with this name.\nDo you want to override this file?");
				}
				else
				{
					if (action == CREATING)			fileManager.create(textEditor.get());
					else if (action == RENAMING)
					{
						if (fileManager.loadedIsChosen())	info.setOpenedText(textEditor.get());
						fileManager.rename(textEditor.get());
					}
					else if (action == SAVING)
					{
						fileManager.setLoadedFileName(textEditor.get());
						fileManager.save();
					}

					textEditor.clear();
					textEditor.reset();
				}
			}
			else
			{
				textEditor.clear();
				textEditor.reset();
			}
		}
	}

	textEditor.mechanics(elapsedTime);


	if(fileManager.isStatus())
	{
		if (fileManager.isSuccess())
		{
			// refresh library
			if (action != UPLOADING)
			{
				if (action == SAVING || action == LOADING)
					info.setOpenedText(fileManager.getLoadedFileName());

				library.refresh(fileManager.getFileNames());
				info.setChosenText();
				action = -1;
			}
		}
		else if (fileManager.isWarning())
		{
			// refresh library
			if (action != UPLOADING)
			{
				library.refresh(fileManager.getFileNames());
				info.setChosenText();
				action = -1;
			}
		}
		else if (fileManager.isFailure())
		{
			// empty
		}
		
		info.setMsgText(fileManager.getMessage());
	}

	fileManager.mechanics();
	info.mechanics(elapsedTime);
}

void EditorFileManager::setActive()
{
	buttons.setActive();
}

const bool& EditorFileManager::isActive() const
{
	return buttons.isActive();
}




bool EditorFileManager::isFileOpen()
{
	return fileManager.getLoadedFileName() != "";
}

bool EditorFileManager::isFileUnsave()
{
	return fileManager.isNewSaveVersion();
}



void EditorFileManager::newFile()
{
	action = CREATING;
	textEditor.setActive();
	textEditor.set("New File", "File Name:", "");
}

void EditorFileManager::openFile()
{
	action = LOADING;

	if (!library.isChosen())
	{
		messageBoard.setActive(2);
		messageBoard.setMessage("There is no chosen file.\nChoose file by clicking on the icon.");
	}
	else if (isFileUnsave())
	{
		messageBoard.setActive();
		messageBoard.setMessage("There is unsaved file.\nDo you want to continue?");
	}
	else
	{
		fileManager.open();
	}
}

void EditorFileManager::saveFile()
{
	if (isFileOpen())
	{
		action = SAVING;
		fileManager.save();
	}
	else
	{
		action = SAVING;
		textEditor.setActive();
		textEditor.set("New File", "File Name:", "");
	}
}

void EditorFileManager::copyFile()
{
	action = COPYING;

	if (!library.isChosen())
	{
		messageBoard.setActive(2);
		messageBoard.setMessage("There is no chosen file.\nChoose file by clicking on the icon.");
	}
	else
	{
		fileManager.copy();
	}
}

void EditorFileManager::renameFile()
{
	action = RENAMING;
	if (!library.isChosen())
	{
		messageBoard.setActive(2);
		messageBoard.setMessage("There is no chosen file.\nChoose file by clicking on the icon.");
	}
	else
	{
		textEditor.setActive();
		textEditor.set("Rename File", "File Name:", "");
	}
}

void EditorFileManager::deleteFile()
{
	action = DELETING;
	
	if (!library.isChosen())
	{
		messageBoard.setActive(2);
		messageBoard.setMessage("There is no chosen file.\nChoose file by clicking on the icon.");
	}
	else
	{
		messageBoard.setActive();
		messageBoard.setMessage("Do you really want to delete file?\nClick yes to continue...");
	}
}

void EditorFileManager::refresh()
{
	action = REFRESHING;
	fileManager.refresh();
}