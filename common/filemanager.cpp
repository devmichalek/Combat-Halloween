#include "filemanager.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include "request.h"
#include "user.h"
#include "converter.h"

cmm::FileManager::FileManager()
{
	status = EMPTY;
	msg = cmm::SEMPTY;
}

cmm::FileManager::~FileManager()
{
	status = EMPTY;
	msg = cmm::SEMPTY;

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
		msg = "Cannot find file '" + substr(fileName) + "', creating remotely...";
		status = WARNING;
	}
	file.close();

	if (saveSupport(pathToFile, guts))
	{
		if (refreshSupport(pathToDir, dirVec))
		{
			msg = "Correctly saved file '" + substr(fileName) + "'.";
			status = SUCCESS;
		}
	}
	else
	{
		msg = "Cannot save file '" + substr(fileName) + "'!";
		status = FAILURE;
	}
}

void cmm::FileManager::uploadPrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec)
{
	if (compareExtension(fileName, SERVERFILE_EXTENSION))
	{
		msg = "Cannot upload file '" + substr(fileName) + "'." + cmm::SNEWLINE;
		msg += "File need to be local to be uploaded.";
		status = FAILURE;
	}
	else
	{
		if (refreshSupport(pathToDir, dirVec))
		{
			// Check if there is a file with the same name.
			bool failure = true; // Is connection is ok?
			for (auto &it : dirVec)
			{
				if (cmm::compareExtension(it, SERVERFILE_EXTENSION))
				{
					failure = false;
					std::string a = fileName, b = it;
					cmm::removeExtension(a);
					cmm::removeExtension(b);
					if (a == b)
					{
						msg = "Cannot upload file '" + substr(fileName) + "'." + cmm::SNEWLINE;
						msg += "File already exists on the server site.";
						status = FAILURE;
						return;
					}
				}
			}

			if (failure)
			{
				msg = "Cannot upload file '" + substr(fileName) + "'." + cmm::SNEWLINE;
				msg += "Couldn't find files with server extension.";
				status = FAILURE;
				return;
			}

			// File name is not occupied. Continue.
			std::string pathToFile = pathToDir + "/" + fileName;
			std::vector<std::string> guts = {};
			if (openSupport(pathToFile, guts))
			{
				std::string oneStr = cmm::SEMPTY;
				for (auto &it : guts)
					oneStr += it;

				// Upload it to server.
				{
					std::string fileNameNoExt = fileName;
					removeExtension(fileNameNoExt);
					cmm::Request request;
					request.setMessage("username=" + cmm::User::getUsername() + "&password=" + cmm::User::getPassword() + "&title=" + fileNameNoExt + "&data=" + oneStr);
					request.setHttp(cmm::WEBSITE_PATH);
					request.setRequest(cmm::WEBSITE_SUBPATH + "getters/world/uploadworld.php", sf::Http::Request::Post);

					std::string info_str = cmm::SEMPTY;
					if (request.sendRequest())
					{
						std::string result = request.getResult();
						if (result != "0")
						{
							msg = "Unexpected error." + cmm::SNEWLINE + "Cannot upload file to server!";
							status = FAILURE;
						}
						else
						{
							//if (refreshSupport(pathToDir, dirVec))
							{
								msg = "Correctly uploaded file to database!";
								status = SUCCESS;
							}
						}
					}
					else
					{
						msg = "Cannot connect with database!";
						status = FAILURE;
					}
				}
			}
		}
	}
}

void cmm::FileManager::openPrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir)
{
	if (compareExtension(fileName, SERVERFILE_EXTENSION))
	{
		msg = "Cannot open server file '" + substr(fileName) + "'." + cmm::SNEWLINE;
		msg += "File need to be copied first to be opened" + cmm::SNEWLINE + "locally.";
		status = FAILURE;
	}
	else
	{
		std::string pathToFile = pathToDir + "/" + fileName;
		if (openSupport(pathToFile, guts))
		{
			msg = "Correctly loaded file '" + substr(fileName) + "'.";
			status = SUCCESS;
		}
		else
		{
			msg = "Cannot open file '" + substr(fileName) + "'!";
			status = FAILURE;
		}
	}
}

void cmm::FileManager::createPrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec)
{
	std::string pathToFile = pathToDir + "/" + fileName;

	file.open(pathToFile, std::ios::in);
	if (file.is_open())
	{
		msg = "File '" + substr(fileName) + "' exists," + cmm::SNEWLINE + "overwriting remotely...";
		status = WARNING;
	}
	file.close();

	file.open(pathToFile, std::ios::out);
	if (file.is_open())
	{
		if (refreshSupport(pathToDir, dirVec))
		{
			msg = "Correctly created file '" + substr(fileName) + "'.";
			status = SUCCESS;
		}
	}
	else
	{
		msg = "Cannot create file '" + substr(fileName) + "'!";
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

		bool success = false;
		bool local = true;
		if (compareExtension(fileName, SERVERFILE_EXTENSION))
		{
			local = false;
			std::string fileNameNoExt = fileName;
			removeExtension(fileNameNoExt);
			cmm::Request request;
			request.setMessage("username=" + cmm::User::getUsername() + "&password=" + cmm::User::getPassword() + "&title=" + fileNameNoExt);
			request.setHttp(cmm::WEBSITE_PATH);
			request.setRequest(cmm::WEBSITE_SUBPATH + "getters/world/copyworld.php", sf::Http::Request::Post);

			std::string info_str = cmm::SEMPTY;
			if (request.sendRequest())
			{
				std::string result = request.getResult();
				if (result.size() < 2 && !result.empty()) // decimal means error e. g. -1, 1, 2 ...
				{
					msg = "Unexpected error." + cmm::SNEWLINE + "Cannot copy file from server!";
					status = FAILURE;
				}
				else
				{
					// Extract data.
					std::string line = cmm::SEMPTY;
					for (auto it : result)
					{
						if (it == cmm::CNEWLINE)
						{
							temp.push_back(line);
							line = cmm::SEMPTY;
							continue;
						}
						line += it;
					}

					success = true;
				}
			}
			else
			{
				msg = "Cannot connect with database!";
				status = FAILURE;
			}
		}
		else
		{
			if (openSupport(pathToFile, temp))
				success = true;
			else
			{
				msg = "Cannot copy file '" + substr(fileName) + "'!";
				status = FAILURE;
			}
		}

		if (success)
		{
			// Prepare new file name.
			std::string newFileName = local ? fileName : fileName.substr(0, fileName.size() - 1);
			{
				int nr = 0;
				std::string buf = newFileName;
				for (unsigned i = 0; i < dirVec.size(); ++i)
				{
					if (dirVec[i] == newFileName)
					{
						newFileName = buf.substr(0, buf.size() - 4) + std::to_string(nr) + buf.substr(buf.size() - 4, buf.size());
						++nr;
						i = -1; // Start loop again...
					}
				}
			}

			// Create and save new file.
			std::string pathToNewFileName = pathToDir + "/" + newFileName;
			if (saveSupport(pathToNewFileName, temp))
			{
				if (refreshSupport(pathToDir, dirVec))
				{
					msg = "Correctly copied file '" + substr(fileName) + "'" + cmm::SNEWLINE + "to '" + substr(newFileName) + "'.";
					status = SUCCESS;
				}
			}
			else
			{
				msg = "Cannot copy file '" + substr(fileName) + "'" + cmm::SNEWLINE + "to '" + substr(newFileName) + "'!";
				status = FAILURE;
			}
		}
	}
}

void cmm::FileManager::renamePrivate(std::string &oldFileName, std::string &newFileName, std::string &pathToDir, std::vector<std::string> &dirVec)
{
	bool retcode = false;

	if (compareExtension(oldFileName, SERVERFILE_EXTENSION))
	{
		// Rename file from server
		{
			std::string oldFileNameNoExt = oldFileName; removeExtension(oldFileNameNoExt);
			std::string newFileNameNoExt = newFileName; removeExtension(newFileNameNoExt);

			cmm::Request request;
			request.setMessage("username=" + cmm::User::getUsername() + "&password=" + cmm::User::getPassword() + "&oldtitle=" + oldFileNameNoExt + "&newtitle=" + newFileNameNoExt);
			request.setHttp(cmm::WEBSITE_PATH);
			request.setRequest(cmm::WEBSITE_SUBPATH + "getters/world/renameworld.php", sf::Http::Request::Post);

			std::string info_str = cmm::SEMPTY;
			if (request.sendRequest())
			{
				std::string result = request.getResult();
				if (result != "0")
				{
					msg = "Unexpected error." + cmm::SNEWLINE + "Cannot rename file from server!";
					status = FAILURE;
					return;
				}
				else
					retcode = true;
			}
			else
			{
				msg = "Cannot connect with database!";
				status = FAILURE;
				return;
			}
		}
	}
	else // File is local.
	{
		std::string oldOne = pathToDir + "/" + oldFileName;
		std::string newOne = pathToDir + "/" + newFileName;
		retcode = std::rename(oldOne.c_str(), newOne.c_str()) == 0;
	}

	if (retcode)
	{
		if (refreshSupport(pathToDir, dirVec))
		{
			msg = "Correctly renamed file '" + substr(oldFileName) + "'" + cmm::SNEWLINE + "into '" + substr(newFileName) + "'.";
			status = SUCCESS;
		}
	}
	else
	{
		msg = "Cannot rename file '" + substr(oldFileName) + "'" + cmm::SNEWLINE + "into '" + substr(newFileName) + "'!";
		status = FAILURE;
	}
}

void cmm::FileManager::deletePrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec)
{
	bool retcode = false;

	if (compareExtension(fileName, SERVERFILE_EXTENSION))
	{
		// Remove file from server
		{
			std::string fileNameNoExt = fileName;
			removeExtension(fileNameNoExt);
			cmm::Request request;
			request.setMessage("username=" + cmm::User::getUsername() + "&password=" + cmm::User::getPassword() + "&title=" + fileNameNoExt);
			request.setHttp(cmm::WEBSITE_PATH);
			request.setRequest(cmm::WEBSITE_SUBPATH + "getters/world/deleteworld.php", sf::Http::Request::Post);

			std::string info_str = cmm::SEMPTY;
			if (request.sendRequest())
			{
				std::string result = request.getResult();
				if (result != "0")
				{
					msg = "Unexpected error." + cmm::SNEWLINE + "Cannot delete file from server!";
					status = FAILURE;
					return;
				}
				else
					retcode = true;
			}
			else
			{
				msg = "Cannot connect with database!";
				status = FAILURE;
				return;
			}
		}
	}
	else // File is local.
		retcode = remove((pathToDir + "/" + fileName).c_str()) == 0;

	if (retcode)
	{
		refreshSupport(pathToDir, dirVec);
		msg = "Correctly deleted file '" + substr(fileName) + "'.";
		status = SUCCESS;
	}
	else
	{
		msg = "Cannot delete file '" + substr(fileName) + "'!";
		status = FAILURE;
	}
}

void cmm::FileManager::refreshPrivate(std::string &pathToDir, std::vector<std::string> &dirVec)
{
	if (!refreshSupport(pathToDir, dirVec))
	{
		msg += cmm::SNEWLINE + "Creating remotely...";
		status = WARNING;
	}

	// Force success.
	status = SUCCESS;
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

		std::string line = cmm::SEMPTY;

		while (std::getline(file, line))
			guts.push_back(line + cmm::SNEWLINE);
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
	
	// Get server files.
	{
		cmm::Request request;
		request.setMessage("username=" + cmm::User::getUsername());
		request.setHttp(cmm::WEBSITE_PATH);
		request.setRequest(cmm::WEBSITE_SUBPATH + "getters/world/refreshworld.php", sf::Http::Request::Post);

		std::string info_str = cmm::SEMPTY;
		if (request.sendRequest())
		{
			std::string result = request.getResult();
			if (result.find(cmm::SNEWLINE) != std::string::npos)
			{
				// Extract.
				std::string line = cmm::SEMPTY;
				for (auto it : result)
				{
					if (it == cmm::CNEWLINE)
					{
						// Remove doublequotes.
						//cmm::removeDoubleQuotes(line);

						dirVec.push_back(line + SERVERFILE_EXTENSION);
						line = cmm::SEMPTY;
						continue;
					}
					line += it;
				}

				msg = "Correctly loaded files from server." + cmm::SNEWLINE;
				status = SUCCESS;
			}
			else if (!result.empty())
			{
				msg = "Received Server Warning." + cmm::SNEWLINE + "Couldn't find server files!" + cmm::SNEWLINE;
				status = WARNING;
			}
		}
		else
		{
			msg = "Unexpected Error." + cmm::SNEWLINE + "Couldn't connect with database!" + cmm::SNEWLINE;
			status = WARNING;
		}
	}

	// Open directory
	if (!boost::filesystem::is_directory(pathToDir))	// Create directory if it does not exist
	{
		boost::filesystem::create_directories("local");
		msg = "Unexpected Error." + cmm::SNEWLINE + "Directory '" + substr(pathToDir) + "' is empty!";
		status = WARNING;
		return false;
	}

	// Fill.
	int length = std::string("local/").size();
	for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(pathToDir), {}))
	{
		std::string buf = entry.path().string().substr(length, entry.path().string().size() - length);
		if (compareExtension(buf, LOCALFILE_EXTENSION))
			dirVec.push_back(buf);
	}

	msg += "Correctly loaded files from" + cmm::SNEWLINE + "directory '" + substr(pathToDir) + "'.";
	status = SUCCESS;
	return true;
}