#include "event.hpp"

Event::Event(){}

inline bool Event::isKeyboardEvent() const{

    return type == sf::Event::KeyPressed || type == sf::Event::KeyReleased;
}

inline bool Event::isMouseEvent() const{

    return type == sf::Event::MouseButtonPressed || type == sf::Event::MouseButtonReleased;
}

 bool Event::close() const{
    return type == sf::Event::Closed;
}
