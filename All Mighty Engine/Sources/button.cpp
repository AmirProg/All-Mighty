#include "button.hpp"

Button::Button() : Button("")
{}

Button::Button(const std::string& textButton) : Button(textButton, Vector2f(0,0))
{}

Button::Button(const std::string& textButton, const Vector2f& positionButton) : textButton_(Text(textButton, 10, Vector2f(this->position_), Color::White))
{ this->position_ = positionButton; }

Button::Button(const Button&& button) : textButton_(std::move(button.textButton_)),
                                        spriteButton_(std::move(button.spriteButton_))
{}

Button& Button::operator=(const Button&& button){

    *this = button;
    return *this;
}

void Button::setSprite(const Sprite& sprite){

    spriteButton_ = sprite;
    spriteButton_.setPosition(position_);
    size_ = Vector2u(spriteButton_.getBox().w,spriteButton_.getBox().h);
}

void Button::setSprite(const std::string& path){

    spriteButton_.setTextureLink(path);
    spriteButton_.setPosition(position_);
    size_ = Vector2u(spriteButton_.getBox().w,spriteButton_.getBox().h);
}

void Button::setText(const Text& text){

    textButton_ = text;
    update();
}

void Button::setTextString(const std::string& text){

    textButton_.setString(text);
}

void Button::setTextStyle(size_t charSize, const std::string& font, const Color& color){

    textButton_.setCharSize(charSize);
    textButton_.setFont(font);
    textButton_.setColor(color);

    update();
}


void Button::setColor(const Color& color){

    spriteButton_.setColor(color);
}

void Button::setPosition(const Vector2f& newPosition){

    position_ = newPosition;
    spriteButton_.setPosition(newPosition);

    update();
}

void Button::setSize(const Vector2u& newSize){
    size_ = newSize;
}

void Button::adjustTextPosition(Vector2f& positionText){

    if(textButton_.getBox().w + positionText.x >= spriteButton_.getBox().x + spriteButton_.getBox().w){

        std::string textCopy {};

        for(size_t k {}; k < std::size(textButton_.getString()); ++k){

            textCopy += *(std::begin(textButton_.getString()) + k); // We add the current letter to the copy

            if(std::size(textCopy) == static_cast<size_t>(std::size(textButton_.getString())/2)){ // We will cut the sentence at the middle

                textCopy+="\n"; // We go to the next line when we reach the end of the button
                positionText.x -= textButton_.getCharacterSize()+k-10;
                positionText.y -= (textButton_.getBox().y - textButton_.getCharacterSize());
                textButton_.setCharSize(textButton_.getCharacterSize()-5);
            }
        }

        textButton_.setTextString(textCopy); // Now we can give the copy to the button's text
    }
}

void Button::update(){

    Vector2f positionText { spriteButton_.getBox().x+spriteButton_.getBox().w/4,
                            spriteButton_.getBox().y+spriteButton_.getBox().h/4 };

    adjustTextPosition(positionText); // We adjust the position of the text

    textButton_.setPosition(positionText);
}

Vector2u Button::getSize() const{

    return size_;
}

Vector2f Button::getPosition() const{

    return position_;
}

Vector4f Button::getBox() const{

    return Vector4f(spriteButton_.getBox());
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(spriteButton_, states);
    target.draw(textButton_, states);
}
