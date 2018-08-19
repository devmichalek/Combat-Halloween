#include "filemanager.h"
#include "dirent.h"


FileManager::FileManager()
{
	free();
}

FileManager::~FileManager()
{
	free();
}

void FileManager::free()
{
	loadVersion = 0;
	saveVersion = 0;
	status = EMPTY;
	msg = "";
	
	if (file.is_open())
		file.close();

	clear();
}

void FileManager::clear()
{
	if (!content.empty())
		content.clear();

	if (!dirVec.empty())
		dirVec.clear();

	dirPath = "";
	filePath = "";

	if (thread.ready)
		thread.free();
}

void FileManager::mechanics()
{
	// Delete thread if it done its job.
	freeThread();
}



// SET/GET -----------------------------------------
void FileManager::setFilePath(std::string newPath)
{
	filePath = newPath;
}

void FileManager::setDirectoryPath(std::string newPath)
{
	dirPath = newPath;
}

void FileManager::setContent(std::vector<std::string> newContent)
{
	saveVersion = 1;
	content = newContent;
}

const std::string& FileManager::getFilePath() const
{
	return filePath;
}

const std::string& FileManager::getDirectoryPath() const
{
	return dirPath;
}

const std::vector<std::string>& FileManager::getContent() const
{
	return content;
}

const std::vector<std::string>& FileManager::getDirectories() const
{
	return dirVec;
}

void FileManager::push(const std::string &line)
{
	saveVersion = 1;
	content.push_back(line);
}

void FileManager::pop()
{
	saveVersion = 1;
	content.pop_back();
}



// ACTIONS -----------------------------------------
void FileManager::save()
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Saving file...";
		thread.thread = new std::thread(&FileManager::savePrivate, this);
		thread.thread->detach();
	}
}

void FileManager::open()
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Loading file...";
		thread.thread = new std::thread(&FileManager::openPrivate, this);
		thread.thread->detach();
	}
}

void FileManager::create(std::string newPath)
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Creating new file...";
		thread.thread = new std::thread(&FileManager::createPrivate, this, newPath);
		thread.thread->detach();
	}
}

void FileManager::copy()
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Copying selected file...";
		thread.thread = new std::thread(&FileManager::copyPrivate, this);
		thread.thread->detach();
	}
}

void FileManager::rename(std::string newPath)
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Renaming selected file...";
		thread.thread = new std::thread(&FileManager::renamePrivate, this, newPath);
		thread.thread->detach();
	}
}

void FileManager::deletee()
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Deleting selected file...";
		thread.thread = new std::thread(&FileManager::deletePrivate, this);
		thread.thread->detach();
	}
}

void FileManager::refresh()
{
	if (!thread.success && !thread.ready && !thread.thread && status == EMPTY)
	{
		status = PROCESSING;
		msg = "Refreshing library...";
		thread.thread = new std::thread(&FileManager::refreshPrivate, this);
		thread.thread->detach();
	}
}



// STATUS ------------------------------------------
bool FileManager::checkIfFileExists(std::string newPath)
{
	bool retCode = false;
	file.open(dirPath + "/" + newPath, std::ios::in);
	if (file.good())
	{
		retCode = true;
	}
	file.close();

	return retCode;
}

bool FileManager::isNewSaveVersion()
{
	return saveVersion != 0;
}

bool FileManager::isNewLoadVersion()
{
	if (loadVersion != 0)
	{
		loadVersion = 0;
		return true;
	}

	return false;
}

bool FileManager::isStatus() const
{
	return status != EMPTY;
}

bool FileManager::isProcessing()
{
	if (status == PROCESSING)
	{
		status = EMPTY;
		return true;
	}

	return false;
}

bool FileManager::isSuccess()
{
	if (status == SUCCESS)
	{
		status = EMPTY;
		return true;
	}

	return false;
}

bool FileManager::isWarning()
{
	if (status == WARNING)
	{
		status = EMPTY;
		return true;
	}

	return false;
}

bool FileManager::isFailure()
{
	if (status == FAILURE)
	{
		status = EMPTY;
		return true;
	}

	return false;
}

//void FileManager::notify_one()
//{
//	cv.notify_one();
//}

const std::string& FileManager::getMessage() const
{
	return msg;
}

std::string FileManager::substr(std::string str)
{
	if (str.size() < 10)
	{
		return str;
	}

	return str.substr(0, 7) + "...";
}

void FileManager::freeThread()
{
	if (thread.ready)
		thread.free();
}




// PRIVATE -----------------------------------------
void FileManager::savePrivate()
{
	file.open(dirPath + "/" + filePath, std::ios::in);
	if (file.bad())
	{
		msg = "Can't find file \"" + substr(filePath) + "\", creating remotely...";
		status = WARNING;
	}
	file.close();

	if (saveSupport(content, filePath))
	{
		saveVersion = 0;
		msg = "Correctly saved file \"" + substr(filePath) + "\"";
		status = SUCCESS;
		thread.success = true;
	}
	else
	{
		msg = "Cannot save file \"" + substr(filePath) + "\"!";
		status = FAILURE;
	}

	thread.ready = true;
}

void FileManager::openPrivate()
{
	if (openSupport(content))
	{
		loadVersion = 1;
		msg = "Correctly loaded file \"" + substr(filePath) + "\"";
		status = SUCCESS;
		thread.success = true;
	}
	else
	{
		msg = "Cannot open file \"" + substr(filePath) + "\"!";
		status = FAILURE;
	}

	thread.ready = true;
}

void FileManager::createPrivate(std::string newPath)
{
	file.open(dirPath + "/" + newPath, std::ios::in);
	if (file.good())
	{
		msg = "File \"" + substr(newPath) + "\" exists,\noverwriting remotely...";
		status = WARNING;
	}
	file.close();

	file.open(dirPath + "/" + newPath, std::ios::out);
	if (file.good())
	{
		msg = "Correctly created file \"" + substr(newPath) + "\"";

		if (!refreshSupport())	// Not error actually, it is caused by user
			msg = "Unexpected Error.\nDirectory \"" + dirPath + "\" is empty!";

		status = SUCCESS;
		thread.success = true;
	}
	else
	{
		msg = "Cannot create file \"" + substr(newPath) + "\"!";
		status = FAILURE;
	}
	file.close();

	thread.ready = true;
}

void FileManager::copyPrivate()
{
	// Refresh and reload library
	if (refreshSupport())
	{
		std::vector<std::string> temp;
		if (openSupport(temp))
		{
			int nr = 0;
			std::string buf = filePath;
			std::string newPath = filePath;

			for (int i = 0; i < dirVec.size(); ++i)
			{
				if (dirVec[i] == newPath)
				{
					newPath = buf.substr(0, buf.size() - 4) + std::to_string(nr) + buf.substr(buf.size() - 4, buf.size());
					++nr;
					i = -1;
				}
			}

			if (saveSupport(temp, newPath))
			{
				msg = "Correctly saved file \"" + substr(newPath) + "\"";
				status = SUCCESS;

				if (!refreshSupport())	// Not error actually, it is caused by user
					msg = "Unexpected Error.\nDirectory \"" + dirPath + "\" is empty!";

				thread.success = true;
			}
			else
			{
				msg = "Cannot save file \"" + substr(filePath) + "\"!";
				status = FAILURE;
			}

			msg = "Correctly copied file \"" + substr(filePath) + "\"";
			status = SUCCESS;
		}
		else
		{
			msg = "Cannot copy file \"" + substr(filePath) + "\"!";
			status = FAILURE;
		}
	}
	else
	{
		msg = "Directory \"" + dirPath + "\" is empty!\nThere is nothing to copy...";
		status = FAILURE;
	}

	thread.ready = true;
}

void FileManager::renamePrivate(std::string newPath)
{
	std::string oldOne = dirPath + "/" + filePath;
	std::string newOne = dirPath + "/" + newPath;
	if (std::rename(oldOne.c_str(), newOne.c_str()) == 0)
	{
		msg = "Correctly renamed file \"" + substr(newPath) + "\"";

		if (!refreshSupport())	// Not error actually, it is caused by user
			msg = "Unexpected Error.\nDirectory \"" + dirPath + "\" is empty!";

		status = SUCCESS;
		thread.success = true;
	}
	else
	{
		msg = "Cannot rename file \"" + substr(newPath) + "\"!";
		status = FAILURE;
	}

	thread.ready = true;
}

void FileManager::deletePrivate()
{
	if (remove((dirPath + "/" + filePath).c_str()) == 0)
	{
		msg = "Correctly deleted file \"" + substr(filePath) + "\"";

		if (!refreshSupport())	// Not error actually, it is caused by user
			msg = "Unexpected Error.\nDirectory \"" + dirPath + "\" is empty!";

		status = SUCCESS;
		thread.success = true;
	}
	else
	{
		msg = "Cannot delete file \"" + substr(filePath) + "\"!";
		status = FAILURE;
	}

	thread.ready = true;
}

void FileManager::refreshPrivate()
{
	if (!refreshSupport())
	{
		msg = "Directory \"" + dirPath + "\" does not exist\nCreating remotely...";
		status = WARNING;
	}
	else
	{
		msg = "Correctly loaded files, from\ndirectory \"" + dirPath + "\"";
		status = SUCCESS;
	}

	// There is no way of failure...
	thread.success = true;
	thread.ready = true;
}

bool FileManager::saveSupport(std::vector<std::string>& content, std::string &filePath)
{
	file.open(dirPath + "/" + filePath, std::ios::out | std::ios::app);
	if (file.good())
	{
		for (auto &it : content)
			file << it;
	}
	else
	{
		file.close();
		return false;
	}

	file.close();
	return true;
}

bool FileManager::openSupport(std::vector<std::string>& newContent)
{
	file.open(dirPath + "/" + filePath, std::ios::in);
	if (file.good())
	{
		if (!newContent.empty())
			newContent.clear();

		std::string line = "";

		while (getline(file, line))
			newContent.push_back(line);
	}
	else
	{
		file.close();
		return false;
	}

	file.close();
	return true;
}

bool FileManager::refreshSupport()
{
	// Wait.
	// std::unique_lock<std::mutex> lck(mtx);
	// while (cv.wait_for(lck, std::chrono::milliseconds(10)) == std::cv_status::timeout) {}

	// Clear dirs.
	if (!dirVec.empty())
		dirVec.clear();

	// Open directory
	DIR* dir = opendir(dirPath.c_str());

	if (!dir)	// Create directory if it does not exist
	{
		_mkdir(dirPath.c_str());
		file.open(dirPath + "/example.chw", std::ios::out | std::ios::app);	// Create example.chw
		file.close();
		dirVec.push_back("example.chw");
		return false;
	}
	else
	{
		// Fill.
		struct dirent* ent = nullptr;
		while (ent = readdir(dir))
			dirVec.push_back(ent->d_name);

		// Close.
		closedir(dir);
		return true;
	}
}