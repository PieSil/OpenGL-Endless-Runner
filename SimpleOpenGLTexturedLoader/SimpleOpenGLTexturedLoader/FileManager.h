#pragma once
#include <memory>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <cstdlib>

class FileManager
{
public:
	~FileManager() {
		closeFile();
	}; //destroyer

	static FileManager* getInstance();
	void openFile(std::string directory, std::string filename);
	void closeFile();
	std::vector<std::pair<std::string, int>> readScores(std::string directory, std::string filename);
	void writeScore(const std::string& playerName, int newScore, std::string directory, std::string filename);


private:
	explicit FileManager();
	static std::shared_ptr<FileManager> managerInstance;
	std::fstream file;
};

