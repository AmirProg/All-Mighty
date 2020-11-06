#include "audio.hpp"

Audio::Audio()
{}

Audio::Audio(const std::string& path) : path_(path){}

/* Sound */

Sound::Sound() : Sound(""){}

Sound::Sound(const std::string& path) : Audio(path){

    setTrack(path);
}

void Sound::setTrack(const std::string& path){

    path_ = path;

    try{

        if(!buffer_.loadFromFile(path_))
            throw std::invalid_argument("Fail loading buffer");

        setBuffer(buffer_);
    }

    catch(const std::invalid_argument& error){

        std::cerr << error.what() << std::endl;
    }
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

    setTrack(path);
}

void Music::setTrack(const std::string& path){

    path_ = path;

    try{

        if(!openFromFile(path_))
            throw std::invalid_argument("Fail loading Music");
    }

    catch(const std::invalid_argument& error){

        std::cerr << error.what();
    }
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
