#include "textBox.hpp"

am::TextBox::TextBox() : TextBox(Type::Thin)
{}

am::TextBox::TextBox(Type type) : Widget(Vector2f(0,0), Vector2f(0,0)), type_(type), currentTextWidth_(text_.getBox().w), textLabel_(""){

    if(type_ == Type::Perso)
        size_ = Vector2f(0,0);
    else if(type_ == Type::Thin)
        size_ = Vector2f(140,20);
    else if(type_ == Type::Large)
        size_ = Vector2f(260,100);
    else if (type_ == Type::MiddleLarge)
        size_ = Vector2f(210, 50);
    else if(type == Type::LongThin)
        size_ = Vector2f(200, 20);

    rectBox_.setSize(size_);
    rectBox_.setColor(Color::White);

    text_.setPosition(Vector2f(rectBox_.getPosition().x, rectBox_.getPosition().y+rectBox_.getBox().h/2));
    setTextStyle(15, "ress/arial.ttf", Color::Black);
}

void am::TextBox::setTextString(const std::string& text){

    text_.setTextString(text);
    update();
}

void am::TextBox::setLabel(const std::string& labelString, std::size_t charSize, const Color& color){

    textLabel_.setTextString(labelString);
    textLabel_.setColor(color);
    textLabel_.setCharacterSize(charSize);
    textLabel_.setFont("ress/arial.ttf");
}

void am::TextBox::setTextStyle(std::size_t charSize, const std::string& font, const Color& color){

    text_.setCharSize(charSize);
    text_.setFont(font);
    text_.setColor(color);

    update();
}

void am::TextBox::setOutline(float thickness, const Color& color) {

    rectBox_.setOutlineThickness(thickness);
    rectBox_.setOutlineColor(color);
}

void am::TextBox::setSize(const Vector2f& newSize){

    rectBox_.setSize(newSize);
    update();
}

void am::TextBox::setPosition(const Vector2f& newPosition){

    rectBox_.setPosition(newPosition);
    update();
}

am::Vector2f am::TextBox::getSize() const{

    return rectBox_.getSize();
}

am::Vector2f am::TextBox::getPosition() const{

    return Vector2f(rectBox_.getPosition().x, rectBox_.getPosition().y);
}

am::Vector4f am::TextBox::getBox() const{

    return rectBox_.getBox();
}

std::string am::TextBox::getText() const{

    return text_.getString();
}

bool& am::TextBox::isClicked(InputManager& input, Window& window) noexcept{

    if(Collision::intersectMouse(*this, window) && input.clickLeft())
        clicked_ = true;

    else if(!(Collision::intersectMouse(*this, window)) && input.clickLeft())
        clicked_ = false;

    if (Collision::intersectMouse(*this, window) && input.clickRight()) { // Erase the text allready typed

        setTextString("");
        clicked_ = true; // Focus on
    }

    else if (!(Collision::intersectMouse(*this, window)) && input.clickRight())
        clicked_ = false;

    return clicked_;
}

void am::TextBox::manageTextEntered(InputManager& input, Window& window){

    if(isClicked(input, window)){

        if(input.isTextEntered()){

            if(input.key(InputManager::Key::BackSpace))
                text_.pop();

            else{
                text_ += input.getCurrentChar();
                currentTextWidth_ += text_.getSizeOneLetter().x;
                update();
            }
        }
    }
}

void am::TextBox::responsive(Text& text, Rectangle& rectBox, float& currentTextWidth){

    if(currentTextWidth >= rectBox.getBox().w){ // TODO

        text+='\n';

        if(text.getBox().h + text.getBox().y > rectBox.getBox().h + rectBox.getBox().y)
            rectBox.setSize(Vector2f(rectBox.getBox().w, rectBox.getBox().h + text.getCharacterSize()*text.getScale().y));

        currentTextWidth = 0;
    }

    text.setPosition(Vector2f(rectBox.getBox().x, rectBox.getBox().y));
}

void am::TextBox::update(){

    responsive(text_, rectBox_, currentTextWidth_);
}

void am::TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(rectBox_, states);
    target.draw(text_, states);
}
