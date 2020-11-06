#include "gui.hpp"

GUI::GUI(Style style, Window& window) : window_(window), style_(style)
{}

GUI::~GUI() {

    resources_.clear();
}

void GUI::add(const std::string& key, Widget& resource) {

    resources_.insert({ key, resource });
    update();
}

void GUI::remove(const std::string& key) {

    resources_.erase(key);
    update();
}

void GUI::setWindow(Window& window) {

    window_ = window;
    update();
}

void GUI::setStyle(Style style) {

    style_ = style;
    update();
}

void GUI::update() {

    if (style_ == Style::Center)
        setCenterStyle(resources_, window_);
    else if (style_ == Style::Right)
        alignAxisX(window_.get().getSize().x - std::begin(resources_)->second.get().getSize().x);
    else if (style_ == Style::Left)
        alignAxisX(0);
    else if (style_ == Style::Row)
        alignAxisX(window_.get().getSize().x / 2 - std::begin(resources_)->second.get().getSize().x / 2);
}

void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    for (const auto& i : resources_)
        target.draw(i.second, states);
}

void GUI::move(const Vector2f& moveVector) {

    for (auto& i : resources_)
        i.second.get().move(moveVector.x, moveVector.y);
}

void GUI::setCenterStyle(std::map<std::string, std::reference_wrapper<Widget>>& resources, std::reference_wrapper<Window> window) {

    auto currentWidget{ std::begin(resources)->second };

    float positionX{ window.get().getSize().x / 2 - currentWidget.get().getBox().w / 2 };
    float positionY{ window.get().getSize().y / 2 - currentWidget.get().getBox().h / 2 };

    bool isFirstWidget{ true }; // Allow to know if the widget is the first one

    for (auto& i : resources) {

        if (isFirstWidget)
            i.second.get().setPosition(Vector2f(positionX, positionY));

        else
            i.second.get().setPosition(Vector2f(positionX, currentWidget.get().getPosition().y + currentWidget.get().getBox().h));

        // If one widget go out the window by the bottom then we put it at the top of the stack

        if (i.second.get().getPosition().y + i.second.get().getBox().h >= window.get().getSize().y)
            i.second.get().setPosition(Vector2f(i.second.get().getPosition().x, i.second.get().getPosition().y + (-1) * std::size(resources) * i.second.get().getBox().h));

        currentWidget = i.second;
        isFirstWidget = false;
    }
}

void GUI::getMovable(InputManager& input) {

    movable_ = true;
    moveWithMouse(input);
}

void GUI::moveWithMouse(InputManager& input) {

    Vector2f posMouse{ InputManager::mousePosition(window_) };

    for (auto& i : resources_) {

        if (Collision::intersectMouse(i.second.get(), window_.get())) {

            if (input.click())
                i.second.get().isMoved() = true;

            if (input.clickReleased())
                i.second.get().isMoved() = false;

            if (input.mouseMoving() && i.second.get().isMoved())
                i.second.get().setPosition(Vector2f(posMouse.x - i.second.get().getBox().w / 2, posMouse.y - i.second.get().getBox().h / 2));
        }
    }
}

void GUI::alignAxisX(float x) {

    auto currentWidget{ std::begin(resources_)->second };
    auto positionX{ x };

    bool isFirstWidget{ true };

    for (auto& i : resources_) {

        if (isFirstWidget)
            i.second.get().setPosition(Vector2f(positionX, 0));
        else
            i.second.get().setPosition(Vector2f(positionX, currentWidget.get().getPosition().y + currentWidget.get().getBox().h));

        currentWidget = i.second.get();
        isFirstWidget = false;
    }
}