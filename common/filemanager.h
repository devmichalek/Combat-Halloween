#pragma once
#include <fstream>
#include <vector>
#include <string>

namespace cmm
{
	const char* const LOCALFILE_EXTENSION = ".chw";
	const char* const SERVERFILE_EXTENSION = ".chws";

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
		explicit FileManager();
		virtual ~FileManager();

		virtual bool isStatus() const;
		virtual bool isProcessing();
		virtual bool isSuccess();
		virtual bool isWarning();
		virtual bool isFailure();
		virtual const std::string& getMessage() const;

	protected:
		virtual std::string substr(std::string &buf);
		virtual void savePrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir, std::vector<std::string> &dirVec);
		virtual void uploadPrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec);
		virtual void openPrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir);
		virtual void createPrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec);
		virtual void copyPrivate(std::string &fileName, std::vector<std::string> &guts, std::string &pathToDir, std::vector<std::string> &dirVec);
		virtual void renamePrivate(std::string &oldFileName, std::string &newFileName, std::string &pathToDir, std::vector<std::string> &dirVec);
		virtual void deletePrivate(std::string &fileName, std::string &pathToDir, std::vector<std::string> &dirVec);
		virtual void refreshPrivate(std::string &pathToDir, std::vector<std::string> &dirVec);

		virtual bool saveSupport(std::string &pathToFile, std::vector<std::string> &guts);
		virtual bool openSupport(std::string &pathToFile, std::vector<std::string> &guts);
		virtual bool refreshSupport(std::string &pathToDir, std::vector<std::string> &dirVec);
	};
}