#include "audio.hpp"

am::Audio::Audio()
{}

am::Audio::Audio(const std::string& path) : path_(path){}

/* Sound */

am::Sound::Sound() : Sound(""){}

am::Sound::Sound(const std::string& path) : Audio(path){

    setTrack(path);
}

void am::Sound::setTrack(const std::string& path){

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

void am::Sound::play(){
    sf::Sound::play();
}
void am::Sound::pause(){
    sf::Sound::pause();
}

void am::Sound::stop(){
    sf::Sound::stop();
}

/* Music */

am::Music::Music(){}

am::Music::Music(const std::string& path) : Audio(path){

    setTrack(path);
}

void am::Music::setTrack(const std::string& path){

    path_ = path;

    try{

        if(!openFromFile(path_))
            throw std::invalid_argument("Fail loading Music");
    }

    catch(const std::invalid_argument& error){

        std::cerr << error.what();
    }
}

void am::Music::play(){

    sf::Music::play();
}

void am::Music::pause(){

    sf::Music::pause();
}

void am::Music::stop(){

    sf::Music::stop();
}
