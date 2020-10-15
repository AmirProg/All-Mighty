#include "audio.hpp"

Audio::Audio()
{}

Audio::Audio(const std::string& path) : path_(path){}

/* Sound */

Sound::Sound() : Sound(""){}

Sound::Sound(const std::string& path) : Audio(path){

    assert((buffer_.loadFromFile(path_)) && "Fail loading Buffer");
    setBuffer(buffer_); // Buffer init
}

void Sound::setTrack(const std::string& path){

    path_ = path;
    assert((buffer_.loadFromFile(path)) && "Fail loading Buffer");

    setBuffer(buffer_);
}

void Sound::play(){
    sf::Sound::play();
}
void Sound::pause(){
    sf::Sound::pause();
}

void Sound::stop(){
    sf::Sound::stop();
}

/* Music */

Music::Music(){}

Music::Music(const std::string& path) : Audio(path){

    assert((openFromFile(path_)) && "Fail loading Music");
}

void Music::setTrack(const std::string& path){

    path_ = path;

    assert((openFromFile(path_)) && "Fail loading Music");
}

void Music::play(){

    sf::Music::play();
}

void Music::pause(){

    sf::Music::pause();
}

void Music::stop(){

    sf::Music::stop();
}
