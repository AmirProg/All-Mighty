#ifndef EVENT_HPP_INCLUDED
#define EVENT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "nonCopyable.hpp"

/*
* ~ Event class ~
* Handling generals event
* However you have to use InputManager class in order to be specific
*
*/

class Event : public sf::Event, NonCopyable{

public:
    Event();
    virtual ~Event() = default;
    bool isKeyboardEvent() const;
    bool isMouseEvent() const;
    bool close() const; // True if the window comes to be closed
};

#endif // EVENT_HPP_INCLUDED
