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
	if (thread.ready)
		thread.free();
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

void FileManager::push(std::string line)
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

void FileManager::create()
{
	if (!thread.success && !thread.ready && !thread.thread)
	{
		status = PROCESSING;
		msg = "Creating new file...";
		thread.thread = new std::thread(&FileManager::createPrivate, this);
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
bool FileManager::checkIfFileExists()
{
	bool retCode = false;
	file.open(filePath, std::ios::in);
	if (file.good())
	{
		retCode = true;
	}
	file.close();

	return retCode;
}

bool FileManager::isNewSaveVersion() const
{
	return saveVersion != 0;
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



// PRIVATE -----------------------------------------
void FileManager::savePrivate()
{
	file.open(filePath, std::ios::in);
	if (file.bad())
	{
		msg = "Can't find file \"" + substr(filePath) + "\", creating remotely...";
		status = WARNING;
	}
	file.close();

	file.open(filePath, std::ios::out | std::ios::app);
	if (file.good())
	{
		for (auto &it : dirVec)
			file << it;

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
	file.close();

	thread.ready = true;
}

void FileManager::openPrivate()
{
	file.open(dirPath + "/" + filePath, std::ios::in);
	if (file.good())
	{
		if (!dirVec.empty())
			dirVec.clear();

		std::string line = "";

		while (getline(file, line))
			dirVec.push_back(line);

		msg = "Correctly loaded file \"" + substr(filePath) + "\"";
		status = SUCCESS;
		thread.success = true;
	}
	else
	{
		msg = "Cannot find file \"" + substr(filePath) + "\"!";
		status = FAILURE;
	}
	file.close();

	thread.ready = true;
}

void FileManager::createPrivate()
{
	file.open(filePath, std::ios::in);
	if (file.bad())
	{
		msg = "File \"" + substr(filePath) + "\" exists,\noverwriting remotely...";
		status = WARNING;
	}
	file.close();

	file.open(filePath, std::ios::out);
	if (file.good())
	{
		for (auto &it : dirVec)
			file << it;

		msg = "Correctly created file \"" + substr(filePath) + "\"";
		status = SUCCESS;
		thread.success = true;
	}
	else
	{
		msg = "Cannot create file \"" + substr(filePath) + "\"!";
		status = FAILURE;
	}
	file.close();

	thread.ready = true;
}

void FileManager::refreshPrivate()
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
		msg = "Directory \"" + dirPath + "\" does not exist\nCreating remotely...";
		status = WARNING;
	}
	else
	{
		// Fill.
		struct dirent* ent = nullptr;
		while (ent = readdir(dir))
			dirVec.push_back(ent->d_name);

		// Close.
		closedir(dir);

		msg = "Correctly loaded files, from\ndirectory \"" + dirPath + "\"";
		status = SUCCESS;
	}

	// There is no way of failure...
	thread.success = true;
	thread.ready = true;
}