#pragma once
#include <memory>
#include <string>
#include "irrKlang.h"

using namespace irrklang;

class AudioPlayer{
public:
	~AudioPlayer() {
		soundEngine->stopAllSounds();
		delete backgroundMusic;
		delete soundEngine;
	}; //dest

	static AudioPlayer* getAudioPlayer();
	static ISound* playSound(std::string path, bool loop = false, bool track = false);
	static void stopAllSounds();
	static void playBackground();
	static void dropBackground();
	static void setBackground(std::string path);

private:
	explicit AudioPlayer();
	ISound* _playSound(std::string path, bool loop = false, bool track = false);
	void _stopAllSounds();
	void _playBackground();
	void _dropBackground();
	void _setBackground(std::string path);
	static std::shared_ptr<AudioPlayer> instance;
	ISoundEngine* soundEngine;
	ISound* backgroundMusic;
	std::string backgroundPath;
};

