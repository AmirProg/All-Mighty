#include "gui.hpp"

GUI::GUI(Style style, Window& window) : window_(window), style_(style)
{}

GUI::GUI(const GUI&& gui) : window_(std::move(gui.window_)), style_(std::move(gui.style_))
{}

GUI& GUI::operator=(const GUI&& gui){

    *this = std::move(gui);
    return *this;
}

GUI::~GUI(){

    resources_.clear();
}

void GUI::add(const std::string& key, Widget& resource){

    resources_.insert({key, resource});
    update();
}

void GUI::remove(const std::string& key){

    resources_.erase(key);
    update();
}

void GUI::setWindow(Window& window){

    window_ = window;
}

void GUI::setStyle(Style style){

    style_ = style;
    update();
}

void GUI::update(){

    if(style_ == Style::Center)
        setCenterStyle();
    else if(style_ == Style::Right)
        alignAxisX(window_.get().getSize().x-std::begin(resources_)->second.get().getSize().x);
    else if(style_ == Style::Left)
        alignAxisX(0);
    else if(style_ == Style::Row)
        alignAxisX(window_.get().getSize().x/2-std::begin(resources_)->second.get().getSize().x/2);
}

void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(auto& i : resources_)
        target.draw(i.second,states);
}

void GUI::move(const Vector2f& moveVector){

    for(auto& i : resources_)
        i.second.get().move(moveVector.x,moveVector.y);
}

void GUI::setCenterStyle(){

    auto currentWidget { std::begin(resources_)->second };
    std::size_t positionX { window_.get().getSize().x/2-currentWidget.get().getSize().x/2 };
    std::size_t positionY { window_.get().getSize().y/2-currentWidget.get().getSize().y/2 };
    bool isFirstWidget { true }; // Allow to know if the widget is the first one

    for(auto& i : resources_){

        if(isFirstWidget)
            i.second.get().setPosition(Vector2f(positionX, positionY));
        else
            i.second.get().setPosition(Vector2f(positionX, currentWidget.get().getPosition().y+currentWidget.get().getSize().y));

        // If one widget go out the window by the bottom then we put it at the top of the stack

        if(i.second.get().getPosition().y+i.second.get().getSize().y >= window_.get().getSize().y)
            i.second.get().setPosition(Vector2f(i.second.get().getPosition().x, i.second.get().getPosition().y+(-1)*std::size(resources_)*i.second.get().getSize().y));

        currentWidget = i.second;
        isFirstWidget = false;
    }
}

void GUI::alignAxisX(std::size_t x){

    auto currentWidget { std::begin(resources_)->second };
    std::size_t positionX { x };

    bool isFirstWidget { true };

    for(auto& i : resources_){

        if(isFirstWidget)
            i.second.get().setPosition(Vector2f(positionX, 0));
        else
            i.second.get().setPosition(Vector2f(positionX, currentWidget.get().getPosition().y+currentWidget.get().getSize().y));

        currentWidget = i.second.get();
        isFirstWidget = false;
    }
}
