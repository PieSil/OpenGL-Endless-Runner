#include "FileManager.h"

std::shared_ptr<FileManager>FileManager::managerInstance(nullptr);

FileManager::FileManager() {
}

FileManager* FileManager::getInstance() {
    //singleton pattern, if timerInstance does not exist create one and return pointer to timerInstance
//otherwise only return pointer
    if (!managerInstance) {
        managerInstance.reset(new FileManager());
    }
    return managerInstance.get();
	return nullptr;
}

void FileManager::openFile(std::string directory, std::string filename, bool append) {

    struct stat sb;

    if (stat(directory.c_str(), &sb) != 0) {
        //path is invalid
        //create directory (works in windows only)
        _mkdir(directory.c_str());
    }

    std::string path = directory + "\\" + filename;
    if (append) {
        currentFile.open(path.c_str(), std::ios::in | std::ios::out | std::ios::app);
    }
    else {
        currentFile.open(path.c_str(), std::ios::in | std::ios::out);
    }

}

void FileManager::closeFile()
{
    currentFile.close();
}

void FileManager::readString()
{
}

void FileManager::writeString()
{
}
