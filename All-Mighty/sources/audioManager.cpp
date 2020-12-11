#include "audioManager.hpp"

am::AudioManager::~AudioManager(){

    resources_.clear();
}

void am::AudioManager::playAll(){

    for(auto& i : resources_)
        i.second.get().play();
}

void am::AudioManager::pauseAll(){

    for(auto& i : resources_)
        i.second.get().pause();
}

void am::AudioManager::stopAll(){

    for(auto& i : resources_)
        i.second.get().stop();
}
