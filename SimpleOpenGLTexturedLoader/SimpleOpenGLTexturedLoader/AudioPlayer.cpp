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
    _setBackground(SUBWAY_BACK);
}

ISound* AudioPlayer::_playSound(std::string path, bool loop, bool track) {
    return soundEngine->play2D(path.c_str(), loop, false, track);
}

void AudioPlayer::_stopAllSounds(){
    soundEngine->stopAllSounds();
}

void AudioPlayer::_playBackground() {
    backgroundMusic = playSound(backgroundPath, true, true);
}

void AudioPlayer::_dropBackground() {
    backgroundMusic->stop();
    backgroundMusic->drop();
}

void AudioPlayer::_setBackground(std::string path){
    backgroundPath = path;
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

void AudioPlayer::playBackground(){
    AudioPlayer::getAudioPlayer()->_playBackground();
}

void AudioPlayer::dropBackground(){
    AudioPlayer::getAudioPlayer()->_dropBackground();
}

void AudioPlayer::setBackground(std::string path) {
    AudioPlayer::getAudioPlayer()->_setBackground(path);
}

