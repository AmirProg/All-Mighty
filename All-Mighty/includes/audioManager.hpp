#ifndef AUDIOMANAGER_HPP_INCLUDED
#define AUDIOMANAGER_HPP_INCLUDED

#include "resourcesManager.hpp"
#include "audio.hpp"
#include <SFML/Audio.hpp>

/********************************
*
*
* ~ AudioManager class ~
* Stacks your Audio resources
*
********************************/

class AudioManager : public ResourcesManager<std::string, Audio>{

public:
    AudioManager() = default;
    virtual ~AudioManager();
    void playAll();
    void pauseAll();
    void stopAll();
};

#endif // AUDIOMANAGER_HPP_INCLUDED
