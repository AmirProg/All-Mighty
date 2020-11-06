#include "inputManager.hpp"

InputManager::InputManager(Window& window, Event& event) : window_(window), event_(event)
{}

void InputManager::setWindow(Window& window){

    window_ = window;
}
void InputManager::setEvent(Event& event){

    event_ = event;
}

bool InputManager::isEvent(Window& window) const{

    return window.isEvent(event_);
}

bool InputManager::click() const{

    return event_.get().type == sf::Event::MouseButtonPressed;
}

bool InputManager::clickReleased() const{

    return event_.get().type == sf::Event::MouseButtonReleased;
}

bool InputManager::mouseMoving() const{

    return event_.get().type == sf::Event::MouseMoved;
}

bool InputManager::clickLeft() const{

    return click() && event_.get().mouseButton.button == sf::Mouse::Left;
}
bool InputManager::clickRight() const{

    return click() && event_.get().mouseButton.button == sf::Mouse::Right;
}

bool InputManager::isKeyPressed() const{

    return event_.get().type == sf::Event::KeyPressed;
}

bool InputManager::isKeyReleased() const{

    return event_.get().type == sf::Event::KeyReleased;
}

bool InputManager::key(sf::Keyboard::Key key) const{

    return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::isTextEntered() const{

    return event_.get().type == sf::Event::TextEntered;
}

char InputManager::getCurrentChar() const{

    if(event_.get().text.unicode > 128)
        return -1;

    return static_cast<char>(event_.get().text.unicode);
}

Vector2f InputManager::mousePosition(){

    return Vector2f(static_cast<float>(sf::Mouse::getPosition().x),
                    static_cast<float>(sf::Mouse::getPosition().y));
}

Vector2f InputManager::mousePosition(const Window& window){

    return Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x),
                    static_cast<float>(sf::Mouse::getPosition(window).y));
}
