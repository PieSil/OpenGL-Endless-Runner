#pragma once
#include <memory>
#include <string>
#include "irrKlang.h"

using namespace irrklang;

class AudioPlayer{
public:
	~AudioPlayer() {
		soundEngine->stopAllSounds();

		/*if(backgroundMusic)
			delete backgroundMusic;*/

		if (soundEngine)
			delete soundEngine;
	}; //dest

	static AudioPlayer* getAudioPlayer();
	static ISound* playSound(std::string path, bool loop = false, bool track = false);
	static void stopAllSounds();
	static ISound* playBackground();
	static void dropBackground();
	static bool setBackground(std::string path);
	static bool isBackgroundActive() {
		return getAudioPlayer()->_isBackgroundActive();
	};

private:
	explicit AudioPlayer();
	ISound* _playSound(std::string path, bool loop = false, bool track = false);
	void _stopAllSounds();
	ISound* _playBackground();
	void _dropBackground();
	bool _setBackground(std::string path);
	bool _isBackgroundActive() {
		return backGroundSet;
	};
	static std::shared_ptr<AudioPlayer> instance;
	ISoundEngine* soundEngine;
	ISound* backgroundMusic;
	std::string backgroundPath;
	bool backGroundSet;
};

