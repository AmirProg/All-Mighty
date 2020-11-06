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
    setFont("ress/arial.ttf");
}

void Text::setTextString(const std::string& stringText){

    stringText_ = stringText;
    setString(stringText_);
}

void Text::setFont(const std::string& path){

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

inline std::string Text::getString() const{
    return stringText_;
}

Vector2f Text::getSizeOneLetter() const{

    Vector2f size {};

    Text copy { *this };

    copy.setString("o"); // We test with the o letter for the width

    size.x = copy.getBox().w;

    copy.setString("t"); // And with the t letter for the height

    size.y = copy.getBox().h;

    return size;
}

void Text::pop(){

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

Text operator+(const Text& text1, const Text& text2) noexcept{

    Text textCopy { text1 };
    textCopy += text2;

    return textCopy;
}

Text operator+(const Text& text, const std::string& s) noexcept{

    Text textCopy { text };
    textCopy += s;

    return textCopy;
}

Text Text::operator+=(Text text) noexcept{

    this->setTextString(getString() + text.getString());
    return *this;;
}

Text Text::operator+=(std::string s) noexcept{

    this->setTextString(getString() + s);

    return *this;;
}

Text Text::operator+=(char c) noexcept{

    this->setTextString(getString() + c);
    return *this;
}

void Text::update()
{}
