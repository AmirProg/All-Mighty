#ifndef STOPWATCH_HPP_INCLUDED
#define STOPWATCH_HPP_INCLUDED

#include <SFML/System.hpp>
#include "nonCopyable.hpp"

/********************************************************************************
*
* ~ StopWatch class ~
*
* A tool handling time
* Inspired by (c) Thor
*
* You have to choose how accurate the stop watch will be in the constructor
* (count seconds, milliseconds or microseconds)
*
*********************************************************************************/

class StopWatch : private NonCopyable{

public:

    enum class Accuracy { Seconds, Milliseconds, Microseconds, MAX };

    StopWatch(Accuracy accuracy);
    virtual ~StopWatch() = default;
    void start();
    void stop();
    void reset();
    void restart();
    void saveElapsed();
    float getTotalElapsedTime() const;
    void changeAccuracy(Accuracy accuracy);
    bool isRunning() const;
    sf::Int32 getElapsedTime() const;

private:
    float timeLimit_;
    sf::Clock clock_;
    sf::Time time_;
    bool running_;
    Accuracy accuracy_;
    float previousElapsed_;
};

#endif // STOPWATCH_HPP_INCLUDED
