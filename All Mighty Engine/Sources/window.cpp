#include "window.hpp"

Window::Window(const Vector2u& sizeWindow, const std::string& nameWindow, Camera& camera) : sizeWindow_(sizeWindow),nameWindow_(nameWindow), camera_(camera) {

    setTitle(nameWindow_);
}

void Window::create(){

    sf::RenderWindow::create(sf::VideoMode(sizeWindow_.x, sizeWindow_.y), nameWindow_);
    currentView_.first = -1; // At the beginning there is no view
}


void Window::setSize(const Vector2u& newSize){

    sizeWindow_ = newSize;
    sf::RenderWindow::setSize(sf::Vector2u(newSize.x,newSize.y));
}

void Window::setCamera(Camera& camera){

    camera_ = camera;
}

void Window::setFPSLimit(std::size_t fps){
    setFramerateLimit(fps);
}

void Window::nextView(){

    ++currentView_.first;

    if(currentView_.first >= camera_.get().getNumberView()) // We go to the beginning every time we reach the end of views
        currentView_.first = 0;

    auto it { camera_.get().operator[](currentView_.first) };
    currentView_.second = std::make_unique<sf::View>(it);


    setView(*(currentView_.second)); // Set the new view
}

void Window::previousView(){

    --currentView_.first;

    if(currentView_.first < 0)
        currentView_.first = 0;

    auto it { camera_.get().operator[](currentView_.first) };
    currentView_.second = std::make_unique<sf::View>(it);


    setView(*(currentView_.second));
}

Vector2f Window::viewPosition(const Vector2i& position, int id){

    Vector2f viewPosition { mapPixelToCoords(sf::Vector2i(position.x,position.y), camera_.get().operator[](id)).x,
                            mapPixelToCoords(sf::Vector2i(position.x,position.y), camera_.get().operator[](id)).y };
    return viewPosition;
}

bool Window::isEvent(Event& event){

    return pollEvent(event);
}
