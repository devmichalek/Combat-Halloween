#include "filemanager.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

cmm::FileManager::FileManager()
{
	status = EMPTY;
	msg = "";
}

cmm::FileManager::~FileManager()
{
	status = EMPTY;
	msg = "";

	if (file.is_open())
		file.close();
}



bool cmm::FileManager::isStatus() const
{
	return status != EMPTY;
}

bool cmm::FileManager::isProcessing()
{
	if (status == PROCESSING)
	{
		status = EMPTY;
		return true;
	}

	return false;
}

bool cmm::FileManager::isSuccess()
{
	if (status == SUCCESS)
	{
		status = EMPTY;
		return true;
	}

	return false;
}

bool cmm::FileManager::isWarning()
{
	if (status == WARNING)
	{
		status = EMPTY;
		return true;
	}

	return false;
}

bool cmm::FileManager::isFailure()
{
	if (status == FAILURE)
	{
		status = EMPTY;
		return true;
	}

	return false;
}

const std::string& cmm::FileManager::getMessage() const
{
	return msg;
}


std::string cmm::FileManager::substr(std::string &buf)
{
	if (buf.size() < 10)
	{
		return buf;
	}

	std::string temp = buf;
	temp = temp.substr(0, 7) + "...";
	if (temp[temp.size() - 4] == '.')
		temp.erase(temp.size() - 1);

	return temp;
}

void cmm::FileManager::savePrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir, std::vector<std::string> &dirVec)
{
	std::string pathToFile = pathToDir + "/" + fileName;

	file.open(pathToFile, std::ios::in);
	if (file.bad())
	{
		msg = "Cannot find file \"" + substr(fileName) + "\", creating remotely...";
		status = WARNING;
	}
	file.close();

	if (saveSupport(pathToFile, guts))
	{
		if (!refreshSupport(pathToDir, dirVec))
		{
			msg = "Unexpected Error.\nDirectory \"" + substr(pathToDir) + "\" is empty!";
			status = WARNING;
		}
		else
		{
			msg = "Correctly saved file \"" + substr(fileName) + "\".";
			status = SUCCESS;
		}
	}
	else
	{
		msg = "Cannot save file \"" + substr(fileName) + "\"!";
		status = FAILURE;
	}
}

void cmm::FileManager::openPrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir)
{
	std::string pathToFile = pathToDir + "/" + fileName;
	if (openSupport(pathToFile, guts))
	{
		msg = "Correctly loaded file \"" + substr(fileName) + "\".";
		status = SUCCESS;
	}
	else
	{
		msg = "Cannot open file \"" + substr(fileName) + "\"!";
		status = FAILURE;
	}
}

void cmm::FileManager::createPrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec)
{
	std::string pathToFile = pathToDir + "/" + fileName;

	file.open(pathToFile, std::ios::in);
	if (file.is_open())
	{
		msg = "File \"" + substr(fileName) + "\" exists,\noverwriting remotely...";
		status = WARNING;
	}
	file.close();

	file.open(pathToFile, std::ios::out);
	if (file.is_open())
	{
		if (!refreshSupport(pathToDir, dirVec))
		{
			msg = "Unexpected Error.\nDirectory \"" + substr(pathToDir) + "\" is empty!";
			status = WARNING;
		}
		else
		{
			msg = "Correctly created file \"" + substr(fileName) + "\".";
			status = SUCCESS;
		}
	}
	else
	{
		msg = "Cannot create file \"" + substr(fileName) + "\"!";
		status = FAILURE;
	}
	file.close();
}

void cmm::FileManager::copyPrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir, std::vector<std::string> &dirVec)
{
	// Refresh and reload library
	if (refreshSupport(pathToDir, dirVec))
	{
		std::string pathToFile = pathToDir + "/" + fileName;
		std::vector<std::string> temp;

		if (openSupport(pathToFile, temp))
		{
			int nr = 0;
			std::string buf = fileName;
			std::string newFileName = fileName;

			for (unsigned i = 0; i < dirVec.size(); ++i)
			{
				if (dirVec[i] == newFileName)
				{
					newFileName = buf.substr(0, buf.size() - 4) + std::to_string(nr) + buf.substr(buf.size() - 4, buf.size());
					++nr;
					i = -1;
				}
			}

			std::string pathToNewFileName = pathToDir + "/" + newFileName;
			if (saveSupport(pathToNewFileName, temp))
			{
				if (!refreshSupport(pathToDir, dirVec))
				{
					msg = "Unexpected Error.\nDirectory \"" + substr(pathToDir) + "\" is empty!";
					status = WARNING;
				}
				else
				{
					msg = "Correctly copied file \"" + substr(fileName) + "\"\nto \"" + substr(newFileName) + "\".";
					status = SUCCESS;
				}
			}
			else
			{
				msg = "Cannot copy file \"" + substr(fileName) + "\"\nto \"" + substr(newFileName) + "\"!";
				status = FAILURE;
			}
		}
		else
		{
			msg = "Cannot copy file \"" + substr(fileName) + "\"!";
			status = FAILURE;
		}
	}
	else
	{
		msg = "Directory \"" + pathToDir + "\" is empty!\nThere is nothing to copy!";
		status = FAILURE;
	}
}

void cmm::FileManager::renamePrivate(std::string &oldFileName, std::string &newFileName, std::string &pathToDir, std::vector<std::string> &dirVec)
{
	std::string oldOne = pathToDir + "/" + oldFileName;
	std::string newOne = pathToDir + "/" + newFileName;

	if (std::rename(oldOne.c_str(), newOne.c_str()) == 0)
	{
		if (!refreshSupport(pathToDir, dirVec))
		{
			msg = "Unexpected Error.\nDirectory \"" + substr(pathToDir) + "\" is empty!";
			status = WARNING;
		}
		else
		{
			msg = "Correctly renamed file \"" + substr(oldFileName) + "\"\ninto \"" + substr(newFileName) + "\".";
			status = SUCCESS;
		}
	}
	else
	{
		msg = "Cannot rename file \"" + substr(oldFileName) + "\"\ninto \"" + substr(newFileName) + "\"!";
		status = FAILURE;
	}
}

void cmm::FileManager::deletePrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec)
{
	if (remove((pathToDir + "/" + fileName).c_str()) == 0)
	{
		if (!refreshSupport(pathToDir, dirVec))
		{
			msg = "Unexpected Error.\nDirectory \"" + substr(pathToDir) + "\" is empty!";
			status = WARNING;
		}
		else
		{
			msg = "Correctly deleted file \"" + substr(fileName) + "\".";
			status = SUCCESS;
		}
	}
	else
	{
		msg = "Cannot delete file \"" + substr(fileName) + "\"!";
		status = FAILURE;
	}
}

void cmm::FileManager::refreshPrivate(std::string &pathToDir, std::vector<std::string> &dirVec)
{
	if (!refreshSupport(pathToDir, dirVec))
	{
		msg = "Directory \"" + substr(pathToDir) + "\" does not exist\nCreating remotely...";
		status = WARNING;
	}
	else
	{
		msg = "Correctly loaded files from\ndirectory \"" + substr(pathToDir) + "\".";
		status = SUCCESS;
	}
}

bool cmm::FileManager::saveSupport(std::string &pathToFile, std::vector<std::string> &guts)
{
	file.open(pathToFile, std::ios::out);
	if (file.is_open())
	{
		for (auto &it : guts)
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

bool cmm::FileManager::openSupport(std::string &pathToFile, std::vector<std::string> &guts)
{
	file.open(pathToFile, std::ios::in);
	if (file.is_open())
	{
		if (!guts.empty())
			guts.clear();

		std::string line = "";

		while (std::getline(file, line))
			guts.push_back(line + "\n");
	}
	else
	{
		file.close();
		return false;
	}

	file.close();
	return true;
}

bool cmm::FileManager::refreshSupport(std::string &pathToDir, std::vector<std::string> &dirVec)
{
	// Clear vector of file names.
	if (!dirVec.empty())
		dirVec.clear();

	// Open directory
	if (!boost::filesystem::is_directory(pathToDir))	// Create directory if it does not exist
	{
		boost::filesystem::create_directories("local");
		return false;
	}
	else
	{
		// Fill.
		for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(pathToDir), {}))
			dirVec.push_back(entry.path().string());
		return true;
	}
}