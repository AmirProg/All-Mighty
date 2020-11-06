#ifndef AUDIO_HPP_INCLUDED
#define AUDIO_HPP_INCLUDED

#include <iostream>
#include <SFML/Audio.hpp>
#include <cassert>
#include "nonCopyable.hpp"

/****************************************************************
*
* ~ Audio (abstract), Sound, Music classes ~
*
* Allow you to handle Sounds and Musics.
* Prefer Sound class for short sounds (like a quick explosion)
* and Music class for the others (main game music for instance)
*
* You will not need to mind about buffers
*
* For instance, Sound explosion { "explosion.wav" };
*
* if(...) // A touch pressed or whatever
*    explosion.play(); // Bruit d'explosion...
*
*****************************************************************/

class Audio : private NonCopyable{

public:
    Audio();
    Audio(const std::string& path);
    ~Audio() = default;
    virtual void setTrack(const std::string& path) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;

protected:
    std::string path_; // The path leading to the audio file
};

/* Sound class */

class Sound : public Audio, sf::Sound{

public:
    Sound();
    Sound(const std::string& path);
    virtual ~Sound() = default;
    virtual void setTrack(const std::string& path) override;
    virtual void play() override;
    virtual void pause() override;
    virtual void stop() override;

private:
    sf::SoundBuffer buffer_; // Buffer
};

/* Music class */

class Music : public Audio, sf::Music{

public:
    Music();
    Music(const std::string& path);
    virtual ~Music() = default;
    virtual void setTrack(const std::string& path) override;
    virtual void play() override;
    virtual void pause() override;
    virtual void stop() override;
};

#endif // AUDIO_HPP_INCLUDED
