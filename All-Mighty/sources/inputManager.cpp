#include "inputManager.hpp"

am::InputManager::InputManager(Window& window, Event& event) : window_(window), event_(event)
{}

void am::InputManager::setWindow(Window& window){

    window_ = window;
}
void am::InputManager::setEvent(Event& event){

    event_ = event;
}

bool am::InputManager::isEvent(Window& window) const{

    return window.isEvent(event_);
}

bool am::InputManager::click() const{

    return event_.get().type == sf::Event::MouseButtonPressed;
}

bool am::InputManager::clickReleased() const{

    return event_.get().type == sf::Event::MouseButtonReleased;
}

bool am::InputManager::mouseMoving() const{

    return event_.get().type == sf::Event::MouseMoved;
}

bool am::InputManager::clickLeft() const{

    return click() && event_.get().mouseButton.button == sf::Mouse::Left;
}
bool am::InputManager::clickRight() const{

    return click() && event_.get().mouseButton.button == sf::Mouse::Right;
}

bool am::InputManager::isKeyPressed() const{

    return event_.get().type == sf::Event::KeyPressed;
}

bool am::InputManager::isKeyReleased() const{

    return event_.get().type == sf::Event::KeyReleased;
}

bool am::InputManager::key(sf::Keyboard::Key key) const{

    return sf::Keyboard::isKeyPressed(key);
}

bool am::InputManager::isTextEntered() const{

    return event_.get().type == sf::Event::TextEntered;
}

char am::InputManager::getCurrentChar() const{

    if(event_.get().text.unicode > 128)
        return -1;

    return static_cast<char>(event_.get().text.unicode);
}

am::Vector2f am::InputManager::mousePosition(){

    return Vector2f(static_cast<float>(sf::Mouse::getPosition().x),
                    static_cast<float>(sf::Mouse::getPosition().y));
}

am::Vector2f am::InputManager::mousePosition(const Window& window){

    return Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x),
                    static_cast<float>(sf::Mouse::getPosition(window).y));
}
