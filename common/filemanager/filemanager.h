#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <direct.h>

class FileManager
{
protected:
	enum STATUS
	{
		EMPTY = 0,
		PROCESSING,
		SUCCESS,
		WARNING,
		FAILURE
	};

	int status;
	std::string msg;
	std::fstream file;

public:
	FileManager();
	~FileManager();
	
	bool isStatus() const;
	bool isProcessing();
	bool isSuccess();
	bool isWarning();
	bool isFailure();
	const std::string& getMessage() const;

protected:
	std::string substr(std::string &buf);
	void savePrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir, std::vector<std::string> &dirVec);
	void openPrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir);
	void createPrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec);
	void copyPrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir, std::vector<std::string> &dirVec);
	void renamePrivate(std::string &oldFileName, std::string &newFileName, std::string &pathToDir, std::vector<std::string> &dirVec);
	void deletePrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec);
	void refreshPrivate(std::string &pathToDir, std::vector<std::string> &dirVec);

	bool saveSupport(std::string &pathToFile, std::vector<std::string> &guts);
	bool openSupport(std::string &pathToFile, std::vector<std::string> &guts);
	bool refreshSupport(std::string &pathToDir, std::vector<std::string> &dirVec);
};