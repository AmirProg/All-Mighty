#ifndef INPUTMANAGER_HPP_INCLUDED
#define INPUTMANAGER_HPP_INCLUDED

#include "window.hpp"

/*
* ~ InputManager class ~
*
* Handling keyboard and mouse input
*
* An InputManager is always linked to a Window object and an Event object
*
* For instance : InputManager input { Event(), Window() };
*
*       if(input.isKeyPressed()){ // If a key is pressed (no matter which key)

*          if(input.key(sf::Keyboard::Escape)) // If it is the escape key
*             window.close(); // Then we close the window
*       }
*/

class InputManager : public NonCopyable{

public:

    typedef sf::Keyboard Key; // Alias sf::Keyboard::Left <=> InputManager::Key::Left

    InputManager() = delete;
    InputManager(const InputManager&&);
    InputManager& operator=(const InputManager&&);
    InputManager(Window& window, Event& event);
    virtual ~InputManager() = default;
    void setWindow(Window& window);
    void setEvent(Event& event);
    bool click() const;
    bool clickLeft() const;
    bool clickRight() const;
    bool isKeyPressed() const;
    bool isKeyReleased() const;
    bool key(sf::Keyboard::Key key) const;
    static Vector2f mousePosition(); // Get the absolute mouse position
    static Vector2i mousePosition(const Window& window); // Get the relative mouse position in the window

private:
    std::reference_wrapper<Window> window_;
    std::reference_wrapper<Event> event_;
};

#endif // INPUTMANAGER_HPP_INCLUDED
