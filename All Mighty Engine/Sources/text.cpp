#include "text.hpp"

Text::Text() : Text("")
{}

Text::Text(const std::string& stringText) : Text(stringText, 30, Vector2f(0,0), Color::White)
{}

Text::Text(const std::string& stringText, std::size_t charSize, const Vector2f& position, const Color& color) : stringText_(stringText),
                                                                                                                charSize_(charSize),
                                                                                                                position_(position),
                                                                                                                color_(color){

    sf::Text::setPosition(sf::Vector2f(position_.x,position.y));
    setString(stringText_);
    setCharacterSize(charSize_);
    setFillColor(color_);
}

Text::Text(const Text&& text) : Text(std::move(text.stringText_), std::move(text.charSize_), std::move(text.position_), std::move(text.color_))
{ font_ = std::move(text.font_); }

Text& Text::operator=(const Text&& text){

    *this = text;
    return *this;
}

void Text::setTextString(const std::string& stringText){

    stringText_ = stringText;
    setString(stringText_);
}

void Text::setFont(const std::string& path){

    assert(font_.loadFromFile(path) && "Fail loading font");
    this->sf::Text::setFont(font_);
}

void Text::setCharSize(std::size_t charSize){

    charSize_ = charSize;
    setCharacterSize(charSize);
}

void Text::setColor(const Color& color){

    color_ = color;
    setFillColor(color);
}

void Text::setPosition(const Vector2f& position){

    position_ = position;
    sf::Text::setPosition(sf::Vector2f(position_.x,position_.y));
}

Vector4f Text::getBox() const{

    return Vector4f(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
}

std::string Text::getString() const{
    return stringText_;
}

Text Text::operator+(const Text& text){

    Text textCopy { *this };
    textCopy.setTextString(textCopy.getString() + text.getString());

    return textCopy;
}

Text Text::operator+(const std::string& s){

    Text textCopy { *this };
    textCopy.setTextString(textCopy.getString() + s);

    return textCopy;
}

Text Text::operator+=(Text text){

    this->setTextString(getString() + text.getString());
    return *this;;
}

Text Text::operator+=(std::string s){

    this->setTextString(getString() + s);

    return *this;;
}
