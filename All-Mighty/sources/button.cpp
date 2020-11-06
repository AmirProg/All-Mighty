#include "button.hpp"

Button::Button(const Text& text) : Button(text, Vector2f(0,0))
{}

Button::Button(const std::string& text, const Vector2f& size) : Button(Text(text, 10, Vector2f(this->position_), Color::White), size)
{ textButton_.setTextString(text); }

Button::Button(const Text& text, const Vector2f& size) : Widget(size, Vector2f(0,0)), textButton_(text){

    setTextStyle(20, "ress/arial.ttf", Color::White);
    update();
}

Button::~Button()
{}

void Button::setText(const Text& text){

    textButton_ = text;
    update();
}

void Button::setTextString(const std::string& text){

    textButton_.setTextString(text);
    update();
}

void Button::setTextStyle(std::size_t charSize, const std::string& font, const Color& color){

    textButton_.setCharSize(charSize);
    textButton_.setFont(font);
    textButton_.setColor(color);

    update();
}

bool& Button::isClicked(InputManager& input, Window& window) noexcept{

    if(Collision::intersectMouse(*this, window) && input.click())
        clicked_ = true;

    if(input.clickReleased())
        clicked_ = false;

    return clicked_;
}

void Button::setSlot(const std::function<void()>& slot){

    funcSlot_ = slot;
}

void Button::active(){

    funcSlot_();
}

template<typename Container>
void Button::adjustTextPosition(Text& textButton, const Container& container){

    Vector2f positionText { container.getBox().x+container.getBox().w/4,
                            container.getBox().y+container.getBox().h/4 };

    textButton.setPosition(positionText);

    if(textButton.getBox().w + positionText.x >= container.getPosition().x + container.getBox().w){

        std::string textCopy {};

        for(size_t k {}; k < std::size(textButton.getString()); ++k){

            textCopy += *(std::begin(textButton.getString()) + k); // We add the current letter to the copy

            if(std::size(textCopy) == static_cast<size_t>(std::size(textButton.getString())/2)){ // We will cut the sentence at the middle

                textCopy+="\n"; // We go to the next line when we reach the end of the button
                positionText.x -= textButton.getCharacterSize()+k-10;
                positionText.y -= (textButton.getCharacterSize() - k);
                textButton.setCharSize(textButton.getCharacterSize()-2);
            }
        }

        textButton.setTextString(textCopy); // Now we can give the copy to the button's text
        textButton.setPosition(positionText);
    }
}

void Button::update()
{}

/***** SpriteButton *****/

SpriteButton::SpriteButton() : SpriteButton("")
{}

SpriteButton::SpriteButton(const std::string& textButton) : SpriteButton(textButton, "")
{}

SpriteButton::SpriteButton(const std::string& textButton, const std::string& path) : Button(Text(textButton, 10, Vector2f(0,0), Color::White), Vector2f(spriteButton_.getSize().x, spriteButton_.getSize().y)),
                                                                                            spriteButton_(path)
{}

void SpriteButton::setSprite(const Sprite& sprite){

    spriteButton_ = sprite;
    spriteButton_.setPosition(position_);
    size_ = Vector2f(spriteButton_.getBox().w,spriteButton_.getBox().h);
}

void SpriteButton::setSprite(const std::string& path){

    spriteButton_.setTextureLink(path);
    spriteButton_.setPosition(position_);
    size_ = Vector2f(spriteButton_.getBox().w,spriteButton_.getBox().h);
}

void SpriteButton::setColor(const Color& color){

    spriteButton_.setColor(color);
}

void SpriteButton::setPosition(const Vector2f& newPosition){

    this->position_ = newPosition;
    spriteButton_.setPosition(position_);

    update();
}

void SpriteButton::setSize(const Vector2f& newSize){
    size_ = newSize;
    update();
}

void SpriteButton::update(){

    Button::adjustTextPosition(textButton_, spriteButton_); // We adjust the position of the text
}

Vector2f SpriteButton::getSize() const{

    return size_;
}

Vector2f SpriteButton::getPosition() const{

    return position_;
}

Vector4f SpriteButton::getBox() const{

    return Vector4f(spriteButton_.getBox());
}

void SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(spriteButton_, states);
    target.draw(textButton_, states);
}

/***** RectButton *****/

RectButton::RectButton() : RectButton(std::string(""))
{}

RectButton::RectButton(const std::string& text) : RectButton(text, Vector2f(0,0), Color::White)
{}

RectButton::RectButton(const std::string& text, const Vector2f& size, const Color& color) : Button(text, size), color_(color){

    rectButton_.setSize(size_);
    rectButton_.setColor(color_);

    update();
}

void RectButton::setSize(const Vector2f& newSize){

    size_ = newSize;
    rectButton_.setSize(size_);

    update();
}

void RectButton::setRectColor(const Color& color){

    color_ = color;
    rectButton_.setColor(color_);
}

void RectButton::setPosition(const Vector2f& position){

    rectButton_.setPosition(position);
    update();
}

void RectButton::setOutline(float thickness = 5.0f, const Color& color = Color::White){

    rectButton_.setOutlineThickness(thickness);
    rectButton_.setOutlineColor(color);
}

Vector2f RectButton::getSize() const{

    return size_;
}

Vector2f RectButton::getPosition() const{
    return Vector2f(rectButton_.getPosition().x, rectButton_.getPosition().y);
}

Vector4f RectButton::getBox() const{

    return rectButton_.getBox();
}

void RectButton::update(){

    Button::adjustTextPosition(textButton_, rectButton_);
}

void RectButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(rectButton_, states);
    target.draw(textButton_, states);
}
