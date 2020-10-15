#include "audioManager.hpp"

AudioManager::~AudioManager(){

    resources_.clear();
}

void AudioManager::playAll(){

    for(auto& i : resources_)
        i.second.get().play();
}

void AudioManager::pauseAll(){

    for(auto& i : resources_)
        i.second.get().pause();
}

void AudioManager::stopAll(){

    for(auto& i : resources_)
        i.second.get().stop();
}
