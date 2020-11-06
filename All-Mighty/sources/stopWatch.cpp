#include "stopWatch.hpp"

StopWatch::StopWatch(Accuracy accuracy) : timeLimit_(0), clock_(), time_(sf::Time::Zero), running_(false), accuracy_(accuracy)
{}

void StopWatch::start(){

    running_ = true;
    clock_.restart();
}

void StopWatch::stop(){

    running_ = false;
    time_ += clock_.getElapsedTime();
}

void StopWatch::reset(){

    running_ = false;
    time_ = sf::Time::Zero;
}

void StopWatch::restart(){

    reset();
    start();
}

void StopWatch::saveElapsed() {

    previousElapsed_ += getElapsedTime();
}

float StopWatch::getTotalElapsedTime() const {

    return previousElapsed_;
}

void StopWatch::changeAccuracy(Accuracy accuracy){

    accuracy_ = accuracy;
}

bool StopWatch::isRunning() const{

    return running_;
}

sf::Int32 StopWatch::getElapsedTime() const{

    if(isRunning()){ // If the stop watch is working then we return the time plus the time counted by the stop watch

        if(accuracy_ == Accuracy::Milliseconds)
            return time_.asMilliseconds() + clock_.getElapsedTime().asMilliseconds();

        else if(accuracy_ == Accuracy::Seconds)
            return time_.asSeconds() + clock_.getElapsedTime().asSeconds();

        else if(accuracy_ == Accuracy::Microseconds)
            return time_.asMicroseconds() + clock_.getElapsedTime().asMicroseconds();
    }

    if(accuracy_ == Accuracy::Milliseconds)
        return time_.asMilliseconds();

    else if(accuracy_ == Accuracy::Seconds)
        return time_.asSeconds();

    else if(accuracy_ == Accuracy::Microseconds)
        return time_.asMicroseconds();

    return time_.asMilliseconds(); // Base case
}
