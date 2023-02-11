#pragma once
#include <memory>
#include <string>
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <direct.h>
class FileManager
{
public:
	~FileManager() {
		currentFile.close();
	}; //destroyer

	static FileManager* getInstance();
	void openFile(std::string directory, std::string filename, bool append = true);
	void closeFile();
	void readString();
	void writeString();


private:
	explicit FileManager();
	static std::shared_ptr<FileManager> managerInstance;
	std::fstream currentFile;
};

