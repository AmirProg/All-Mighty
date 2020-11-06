#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "camera.hpp"
#include "event.hpp"
#include <algorithm>

/***********************************************************************************
*
* ~ Window class ~
*
*  Manage windows objects
*
*  In order to use Camera :
*
*  You have to give a Camera object to the window
*
*  Just create a Camera object then give it to the window
*  Even if you will not use it : Window(Vector2u(), std::string(), camera)
*
*  Then, in the main drawing loop:
*
*  // DRAWING LOOP //
*  window.nextView(); // Put the pointer to 0 the first view
*  window.draw(world); // Draw the world on the first view
*  window.nextView();
*  window.draw(map); // Draw the map object on the second view
*
*
***********************************************************************************/

class Window : public sf::RenderWindow, NonCopyable{

public:
    Window() = delete;
    Window(const Vector2u& sizeWindow, const std::string& nameWindow, Camera& camera);
    virtual ~Window() = default;
    virtual void create(); // Create the window or recreate it
    void setSize(const Vector2u& newSize);
    void setCamera(Camera& camera); // Set the new camera you want your window to be associated with
    void setFPSLimit(std::size_t fps);
    bool isEvent(Event& event);
    void nextView(); // Go to the next view on the camera
    void previousView(); // Go to the previous view on the camera
    Vector2f viewPosition(const Vector2f& position, int id); // Convert window coordinate into view coordinate

private:
    Vector2u sizeWindow_;
    std::string nameWindow_;
    std::reference_wrapper<Camera> camera_;
    std::pair<int, std::unique_ptr<sf::View>> currentView_; // A key and a pointer on the current view
};

#endif // WINDOW_HPP_INCLUDED
