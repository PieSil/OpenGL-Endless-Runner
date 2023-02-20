#include "AudioPlayer.h"
#include "Const.h"

std::shared_ptr<AudioPlayer> AudioPlayer::instance(nullptr);

AudioPlayer::AudioPlayer() {
    soundEngine = createIrrKlangDevice();
    soundEngine->addSoundSourceFromFile(SUBWAY_BACK.c_str(), ESM_AUTO_DETECT, true);
    soundEngine->play2D(SUBWAY_BACK.c_str());
    soundEngine->stopAllSounds();
    soundEngine->addSoundSourceFromFile(RUPEE_SOUND.c_str(), ESM_AUTO_DETECT, true);
    soundEngine->play2D(SUBWAY_BACK.c_str());
    soundEngine->stopAllSounds();
    soundEngine->addSoundSourceFromFile(SWORD_SOUND.c_str(), ESM_AUTO_DETECT, true);
    soundEngine->play2D(SUBWAY_BACK.c_str());
    soundEngine->stopAllSounds();
    soundEngine->addSoundSourceFromFile(HEART_SOUND.c_str(), ESM_AUTO_DETECT, true);
    soundEngine->play2D(HEART_SOUND.c_str());
    soundEngine->stopAllSounds();
    soundEngine->addSoundSourceFromFile(DAMAGE_SOUND.c_str(), ESM_AUTO_DETECT, true);
    soundEngine->play2D(DAMAGE_SOUND.c_str());
    soundEngine->stopAllSounds();
    soundEngine->addSoundSourceFromFile(POP_SOUND.c_str(), ESM_AUTO_DETECT, true);
    soundEngine->play2D(POP_SOUND.c_str());
    soundEngine->stopAllSounds();
    soundEngine->addSoundSourceFromFile(SHOOT_SOUND.c_str(), ESM_AUTO_DETECT, true);
    soundEngine->play2D(SHOOT_SOUND.c_str());
    soundEngine->stopAllSounds();
    soundEngine->addSoundSourceFromFile(CLICK_SOUND.c_str(), ESM_AUTO_DETECT, true);
    soundEngine->play2D(CLICK_SOUND.c_str());
    soundEngine->stopAllSounds();
    soundEngine->addSoundSourceFromFile(FAIRY_BACKGROUND.c_str(), ESM_AUTO_DETECT, true);
    soundEngine->play2D(FAIRY_BACKGROUND.c_str());
    soundEngine->stopAllSounds();
    backgroundMusic = nullptr;
    backGroundSet = false;
    //_setBackground("");
}

ISound* AudioPlayer::_playSound(std::string path, bool loop, bool track) {
    return soundEngine->play2D(path.c_str(), loop, false, track);
}

void AudioPlayer::_stopAllSounds(){
    soundEngine->stopAllSounds();
}

ISound* AudioPlayer::_playBackground() {
    backgroundMusic = playSound(backgroundPath, true, true);
    if (backgroundPath.compare(FAIRY_BACKGROUND) == 0) {
        backgroundMusic->setVolume(.05);
    }
    else {
        backgroundMusic->setVolume(1);
    }
    backGroundSet = true;

    return backgroundMusic;
}

void AudioPlayer::_dropBackground() {
    if (backGroundSet) {
        backgroundMusic->stop();
        backgroundMusic->drop();
    }
    backGroundSet = false;
}

bool AudioPlayer::_setBackground(std::string path){
    bool result = false;
    if (!(backgroundPath.compare(path)==0)) {
        backgroundPath = path;
        result = true;
    }

    return result;

}

AudioPlayer* AudioPlayer::getAudioPlayer()
{
    //singleton pattern
    if (!instance) {
        instance.reset(new AudioPlayer());
    }
    return instance.get();
}

ISound* AudioPlayer::playSound(std::string path, bool loop, bool track){
    return AudioPlayer::getAudioPlayer()->_playSound(path, loop, track);
}

void AudioPlayer::stopAllSounds(){
    AudioPlayer::getAudioPlayer()->_stopAllSounds();
}

ISound* AudioPlayer::playBackground(){
    return AudioPlayer::getAudioPlayer()->_playBackground();
}

void AudioPlayer::dropBackground(){
    AudioPlayer::getAudioPlayer()->_dropBackground();
}

bool AudioPlayer::setBackground(std::string path) {
    return AudioPlayer::getAudioPlayer()->_setBackground(path);
}

