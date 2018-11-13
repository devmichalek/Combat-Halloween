#include "efilemanager.h"


EFileManager::EFileManager()
{
	free();
}

EFileManager::~EFileManager()
{
	free();
}

void EFileManager::free()
{
	status = EMPTY;
	msg = "";
	
	if (file.is_open())
		file.close();

	clear();
}

void EFileManager::clear()
{
	if (!content.empty())
		content.clear();

	if (!dirVec.empty())
		dirVec.clear();

	dirPath = "";
	chosenFileName = "";
	loadedFileName = "";

	if (thread.ready)
		thread.free();

	saveVersion = 0;
	loadVersion = 0;
}

void EFileManager::mechanics()
{
	// Delete thread if the job is done.
	freeThread();
}



// SET/GET -----------------------------------------
void EFileManager::setChosenFileName(std::string newChosenFileName)
{
	chosenFileName = newChosenFileName;
}

void EFileManager::setLoadedFileName(std::string newLoadedFileName)
{
	loadedFileName = newLoadedFileName;
}

void EFileManager::setDirectoryPath(std::string newPath)
{
	dirPath = newPath;
}

void EFileManager::setContent(std::vector<std::string> &newContent)
{
	saveVersion = 1;
	content = newContent;
}

const std::string& EFileManager::getLoadedFileName() const
{
	return loadedFileName;
}

const std::string& EFileManager::getDirectoryPath() const
{
	return dirPath;
}

const std::vector<std::string>& EFileManager::getContent() const
{
	return content;
}

const std::vector<std::string>& EFileManager::getFileNames() const
{
	return dirVec;
}

bool EFileManager::loadedIsChosen()
{
	return loadedFileName == chosenFileName;
}

void EFileManager::push(const std::string &line)
{
	saveVersion = 1;
	content.push_back(line);
}

void EFileManager::pop()
{
	saveVersion = 1;
	content.pop_back();
}



// ACTIONS -----------------------------------------
void EFileManager::save()
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Saving file...";
		thread.thread = new std::thread(&EFileManager::thread_save, this);
		thread.thread->detach();
	}
}

void EFileManager::open()
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Loading file...";
		thread.thread = new std::thread(&EFileManager::thread_open, this);
		thread.thread->detach();
	}
}

void EFileManager::create(std::string newFileName)
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Creating new file...";
		thread.thread = new std::thread(&EFileManager::thread_create, this, newFileName);
		thread.thread->detach();
	}
}

void EFileManager::copy()
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Copying selected file...";
		thread.thread = new std::thread(&EFileManager::thread_copy, this);
		thread.thread->detach();
	}
}

void EFileManager::rename(std::string newFileName)
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Renaming selected file...";
		thread.thread = new std::thread(&EFileManager::thread_rename, this, newFileName);
		thread.thread->detach();
	}
}

void EFileManager::deletee()
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Deleting selected file...";
		thread.thread = new std::thread(&EFileManager::thread_delete, this);
		thread.thread->detach();
	}
}

void EFileManager::refresh()
{
	if (!thread.success && !thread.ready && !thread.thread && status == EMPTY)
	{
		status = PROCESSING;
		msg = "Refreshing library...";
		thread.thread = new std::thread(&EFileManager::thread_refresh, this);
		thread.thread->detach();
	}
}



bool EFileManager::checkIfFileExists(std::string fileName)
{
	bool retCode = false;
	file.open(dirPath + "/" + fileName, std::ios::in);
	if (file.is_open())
	{
		retCode = true;
	}
	file.close();

	return retCode;
}



void EFileManager::freeThread()
{
	if (thread.ready)
		thread.free();
}



void EFileManager::thread_save()
{
	if (saveVersion == 0)
	{
		msg = "There is nothing new to save!";
		if (content.empty())
			loadedFileName = "";
		status = WARNING;
		thread.success = true;
	}
	else
	{
		savePrivate(loadedFileName, content, dirPath, dirVec);

		if (status == SUCCESS)
		{
			saveVersion = 0;
			thread.success = true;
		}

		if (dirVec.empty())	// library is empty...
		{
			if (!loadedFileName.empty())	// if file was loaded, now it does not exist
				saveVersion = 1;
			chosenFileName = "";
			loadedFileName = "";
		}
	}

	thread.ready = true;
}

void EFileManager::thread_open()
{
	if (loadedFileName == chosenFileName)
	{
		msg = "File \"" + chosenFileName + "\" is already loaded.";
		status = WARNING;
		thread.success = true;
	}
	else
	{
		openPrivate(chosenFileName, content, dirPath);

		if (status == SUCCESS)
		{
			loadVersion = 1;
			loadedFileName = chosenFileName;
			thread.success = true;
		}
	}

	thread.ready = true;
}

void EFileManager::thread_create(std::string newFileName)
{
	createPrivate(newFileName, dirPath, dirVec);

	if (status == SUCCESS)
	{
		thread.success = true;
	}
	else if (status == WARNING)	// library is empty...
	{
		if (loadedFileName == newFileName)	// if file was loaded, now it is overwritten
		{
			saveVersion = 1;
		}
	}

	if (dirVec.empty())	// library is empty...
	{
		if (!loadedFileName.empty())	// if file was loaded, now it does not exist
			saveVersion = 1;
		chosenFileName = "";
		loadedFileName = "";
	}

	thread.ready = true;
}

void EFileManager::thread_copy()
{
	copyPrivate(chosenFileName, content, dirPath, dirVec);

	if (status == SUCCESS)
	{
		thread.success = true;
	}

	if (dirVec.empty())	// library is empty...
	{
		if (!loadedFileName.empty())	// if file was loaded, now it does not exist
			saveVersion = 1;
		chosenFileName = "";
		loadedFileName = "";
	}

	thread.ready = true;
}

void EFileManager::thread_rename(std::string newFileName)
{
	// if file already exists, delete it
	for (auto &it : dirVec)
	{
		if (it == newFileName)
		{
			deletePrivate(newFileName, dirPath, dirVec);
			break;
		}
	}

	renamePrivate(chosenFileName, newFileName, dirPath, dirVec);

	if (status == SUCCESS)
	{
		if (loadedFileName == chosenFileName)
		{
			loadedFileName = newFileName;
		}

		thread.success = true;
	}

	if (dirVec.empty())	// library is empty...
	{
		if (!loadedFileName.empty())	// if file was loaded, now it does not exist
			saveVersion = 1;
		chosenFileName = "";
		loadedFileName = "";
	}
	
	thread.ready = true;
}

void EFileManager::thread_delete()
{
	deletePrivate(chosenFileName, dirPath, dirVec);

	if(status == SUCCESS)
	{
		if (loadedFileName == chosenFileName)
		{
			saveVersion = 1;
			loadedFileName = "";
		}

		thread.success = true;
	}

	if (dirVec.empty())	// library is empty...
	{
		if(!loadedFileName.empty())	// if file was loaded, now it does not exist
			saveVersion = 1;
		chosenFileName = "";
		loadedFileName = "";
	}
	
	thread.ready = true;
}

void EFileManager::thread_refresh()
{
	refreshPrivate(dirPath, dirVec);

	if (status == SUCCESS)
	{
		thread.success = true;
	}

	if (dirVec.empty())	// library is empty...
	{
		if (!loadedFileName.empty())	// if file was loaded, now it does not exist
			saveVersion = 1;
		chosenFileName = "";
		loadedFileName = "";
	}
	
	thread.ready = true;
}