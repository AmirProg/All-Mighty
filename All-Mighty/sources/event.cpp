#include "event.hpp"

am::Event::Event(){}

inline bool am::Event::isKeyboardEvent() const{

    return type == sf::Event::KeyPressed || type == sf::Event::KeyReleased;
}

inline bool am::Event::isMouseEvent() const{

    return type == sf::Event::MouseButtonPressed || type == sf::Event::MouseButtonReleased;
}

 bool am::Event::close() const{
    return type == sf::Event::Closed;
}
