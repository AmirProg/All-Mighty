#include "text.hpp"

am::Text::Text() : Text("")
{}

am::Text::Text(const std::string& stringText) : Text(stringText, 30, Vector2f(0,0), Color::White)
{}

am::Text::Text(const std::string& stringText, std::size_t charSize, const Vector2f& position, const Color& color) : stringText_(stringText),
                                                                                                                charSize_(charSize),
                                                                                                                position_(position),
                                                                                                                color_(color){

    sf::Text::setPosition(sf::Vector2f(position_.x,position.y));
    setString(stringText_);
    setCharacterSize(charSize_);
    setFillColor(color_);
    setFont("ress/arial.ttf");
}

void am::Text::setTextString(const std::string& stringText){

    stringText_ = stringText;
    setString(stringText_);
}

void am::Text::setFont(const std::string& path){

    try{

        if(font_.loadFromFile(path))
            this->sf::Text::setFont(font_);
        else
            throw std::invalid_argument("Fail loading font");
    }

    catch(const std::invalid_argument& error){

        std::cerr << error.what() << std::endl;
    }
}

void am::Text::setCharSize(std::size_t charSize){

    charSize_ = charSize;
    setCharacterSize(charSize);
}

void am::Text::setColor(const Color& color){

    color_ = color;
    setFillColor(color);
}

void am::Text::setPosition(const Vector2f& position){

    position_ = position;
    sf::Text::setPosition(sf::Vector2f(position_.x,position_.y));
}

am::Vector4f am::Text::getBox() const{

    return Vector4f(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
}

inline std::string am::Text::getString() const{

    return stringText_;
}

am::Vector2f am::Text::getSizeOneLetter() const{

    Vector2f size {};

    Text copy { *this };

    copy.setString("o"); // We test with the o letter for the width

    size.x = copy.getBox().w;

    copy.setString("t"); // And with the t letter for the height

    size.y = copy.getBox().h;

    return size;
}

void am::Text::pop(){

    try{

        if(!(std::size(getString()) > 0))
            throw std::underflow_error("");

        std::string copyErased { getString() };
        copyErased.erase(std::size(copyErased) - 1 , 1);
        setTextString(copyErased);
    }

    catch(const std::underflow_error& error){
        std::cerr << error.what() << std::endl;
    }
}

am::Text operator+(const am::Text& text1, const am::Text& text2) noexcept{

    am::Text textCopy { text1 };
    textCopy += text2;

    return textCopy;
}

am::Text operator+(const am::Text& text, const std::string& s) noexcept{

    am::Text textCopy { text };
    textCopy += s;

    return textCopy;
}

am::Text am::Text::operator+=(Text text) noexcept{

    this->setTextString(getString() + text.getString());
    return *this;;
}

am::Text am::Text::operator+=(std::string s) noexcept{

    this->setTextString(getString() + s);

    return *this;;
}

am::Text am::Text::operator+=(char c) noexcept{

    this->setTextString(getString() + c);
    return *this;
}

void am::Text::update()
{}
