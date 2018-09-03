#pragma once
#include "thread.h"
#include "econtent.h"
#include "filemanager.h"

// File Manager does saving, opening, refreshing and creating on another thread.
class EFileManager : public EContent, public FileManager
{
	std::string dirPath;
	std::vector<std::string> dirVec;
	std::string chosenFileName;
	std::string loadedFileName;
	cmm::Thread thread;

public:
	EFileManager();
	~EFileManager();
private:
	void free();
public:
	void clear();		// remove content and remove path
	void mechanics();	// used only to free thread

	void setChosenFileName(std::string newChosenFileName);
	void setLoadedFileName(std::string newLoadedFileName);
	void setDirectoryPath(std::string newPath);
	void setContent(std::vector<std::string> &newContent);
	const std::string& getLoadedFileName() const;
	const std::string& getDirectoryPath() const;
	const std::vector<std::string>& getContent() const;
	const std::vector<std::string>& getFileNames() const;
	bool loadedIsChosen();
	void push(const std::string &line);
	void pop();

	void save();
	void open();
	void create(std::string newFileName);
	void copy();
	void rename(std::string newFileName);
	void deletee();
	void refresh();
	
	bool checkIfFileExists(std::string fileName);
	void freeThread();

private:	// thread functions
	void thread_save();
	void thread_open();
	void thread_create(std::string newFileName);
	void thread_copy();
	void thread_rename(std::string newFileName);
	void thread_delete();
	void thread_refresh();
};