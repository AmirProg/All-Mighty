#include "inputManager.hpp"

InputManager::InputManager(Window& window, Event& event) : window_(window), event_(event)
{}

InputManager::InputManager(const InputManager&& input) : InputManager(std::move(input.window_), std::move(input.event_))
{}

InputManager& InputManager::operator=(const InputManager&& input){

    window_ = std::move(input.window_);
    event_ = std::move(input.event_);

    return *this;
}

void InputManager::setWindow(Window& window){

    window_ = window;
}
void InputManager::setEvent(Event& event){

    event_ = event;
}

bool InputManager::click() const{
    return event_.get().type == sf::Event::MouseButtonPressed;
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

Vector2f InputManager::mousePosition(){
    return Vector2f(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
}

Vector2i InputManager::mousePosition(const Window& window){
    return Vector2i(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
}
