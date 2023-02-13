#include "FileManager.h"
#ifdef _WIN32
#include <direct.h>
#define mkdir _mkdir
#endif

std::shared_ptr<FileManager>FileManager::managerInstance(nullptr);

FileManager::FileManager() {
}

FileManager* FileManager::getInstance() {
    //singleton pattern
    if (!managerInstance) {
        managerInstance.reset(new FileManager());
    }
    return managerInstance.get();
	return nullptr;
}

void FileManager::openFile(std::string directory, std::string filename) {

    struct stat sb;

    if (stat(directory.c_str(), &sb) != 0) {
        //path is invalid
        //create directory
        mkdir(directory.c_str());
    }

    std::string path = directory + "\\" + filename;
    file.open(path.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    if (!file.good()) {
        std::ofstream newFile(path.c_str(), std::ios::binary);
        newFile.close();
        file.open(path.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    }
    if (!file) {
        std::cerr << "Error: Unable to write score to file." << std::endl;
    }

}

void FileManager::closeFile() {
    file.close();
}

std::vector<std::pair<std::string, int>> FileManager::readScores(std::string directory, std::string filename) {
    std::vector<std::pair<std::string, int>> scores;
    struct stat sb;

    if (stat(directory.c_str(), &sb) != 0) {
        //path is invalid
        //create directory
        mkdir(directory.c_str());
    }

    std::string path = directory + "\\" + filename;
    file.open(path.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    if (!file.good()) {
        return scores;
    }

    file.seekg(0, std::ios::beg); //move to the beginning of file

    while (file.good()) { //keep reading until end of file
        std::string player;
        int score;
        file.read(reinterpret_cast<char*>(&score), sizeof score);
        std::getline(file, player, '\0');
        if (file.good()) {
            scores.emplace_back(player, score);
        }
    }
    file.close();
    return scores;
}

void FileManager::writeScore(const std::string& playerName, int newScore, std::string directory, std::string filename){
    // Read the existing high scores from the file into a vector.
    std::vector<std::pair<std::string, int>> scores = readScores(directory, filename);

    struct stat sb;

    if (stat(directory.c_str(), &sb) != 0) {
        //path is invalid
        //create directory
        mkdir(directory.c_str());
    }

    std::string path = directory + "\\" + filename;
    file.open(path.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    if (!file.good()) {
        std::ofstream newFile(path.c_str(), std::ios::binary);
        newFile.close();
        file.open(path.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    }
    if (!file) {
        std::cerr << "Error: Unable to write score to file." << std::endl;
    }
    

    // Find the correct position to insert the new player name and score.
    auto it = std::lower_bound(scores.begin(), scores.end(), std::make_pair(playerName, newScore),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    scores.insert(it, { playerName, newScore });

    // Write the updated high scores back to the file.
    file.seekp(0, std::ios::beg); //move to the beggining of file
    const std::string p;
    int max = 5;
    if (max > scores.size())
        max = scores.size();
    for (int i = 0; i<max; i++) {
        int score = scores[i].second;
        std::string name = scores[i].first;
        file.write(reinterpret_cast<const char*>(&score), sizeof score);
        if (!file) {
            std::cerr << "Error: Unable to write score to file." << std::endl;
        }
        file.write(name.c_str(), name.size() + 1);
        if (!file) {
            std::cerr << "Error: Unable to write score to file." << std::endl;
        }
    }
    file.close();

}
