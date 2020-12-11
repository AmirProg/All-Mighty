#include "button.hpp"

am::Button::Button(const Text& text) : Button(text, Vector2f(0,0))
{}

am::Button::Button(const std::string& text, const Vector2f& size) : Button(Text(text, 10, Vector2f(this->position_), Color::White), size)
{ textButton_.setTextString(text); }

am::Button::Button(const Text& text, const Vector2f& size) : Widget(size, Vector2f(0,0)), textButton_(text){

    setTextStyle(20, "ress/arial.ttf", Color::White);
    update();
}

am::Button::~Button()
{}

void am::Button::setText(const Text& text){

    textButton_ = text;
    update();
}

void am::Button::setTextString(const std::string& text){

    textButton_.setTextString(text);
    update();
}

void am::Button::setTextStyle(std::size_t charSize, const std::string& font, const Color& color){

    textButton_.setCharSize(charSize);
    textButton_.setFont(font);
    textButton_.setColor(color);

    update();
}

bool& am::Button::isClicked(InputManager& input, Window& window) noexcept{

    if(Collision::intersectMouse(*this, window) && input.click())
        clicked_ = true;

    if(input.clickReleased())
        clicked_ = false;

    return clicked_;
}

void am::Button::setSlot(const std::function<void()>& slot){

    funcSlot_ = slot;
}

void am::Button::active(){

    funcSlot_();
}

template<typename Container>
void am::Button::adjustTextPosition(Text& textButton, const Container& container){

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

void am::Button::update()
{}

/***** SpriteButton *****/

am::SpriteButton::SpriteButton() : SpriteButton("")
{}

am::SpriteButton::SpriteButton(const std::string& textButton) : SpriteButton(textButton, "")
{}

am::SpriteButton::SpriteButton(const std::string& textButton, const std::string& path) : Button(Text(textButton, 10, Vector2f(0,0), Color::White), Vector2f(spriteButton_.getSize().x, spriteButton_.getSize().y)),
                                                                                            spriteButton_(path)
{}

void am::SpriteButton::setSprite(const Sprite& sprite){

    spriteButton_ = sprite;
    spriteButton_.setPosition(position_);
    size_ = Vector2f(spriteButton_.getBox().w,spriteButton_.getBox().h);
}

void am::SpriteButton::setSprite(const std::string& path){

    spriteButton_.setTextureLink(path);
    spriteButton_.setPosition(position_);
    size_ = Vector2f(spriteButton_.getBox().w,spriteButton_.getBox().h);
}

void am::SpriteButton::setColor(const Color& color){

    spriteButton_.setColor(color);
}

void am::SpriteButton::setPosition(const Vector2f& newPosition){

    this->position_ = newPosition;
    spriteButton_.setPosition(position_);

    update();
}

void am::SpriteButton::setSize(const Vector2f& newSize){
    size_ = newSize;
    update();
}

void am::SpriteButton::update(){

    Button::adjustTextPosition(textButton_, spriteButton_); // We adjust the position of the text
}

am::Vector2f am::SpriteButton::getSize() const{

    return size_;
}

am::Vector2f am::SpriteButton::getPosition() const{

    return position_;
}

am::Vector4f am::SpriteButton::getBox() const{

    return Vector4f(spriteButton_.getBox());
}

void am::SpriteButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(spriteButton_, states);
    target.draw(textButton_, states);
}

/***** RectButton *****/

am::RectButton::RectButton() : am::RectButton(std::string(""))
{}

am::RectButton::RectButton(const std::string& text) : RectButton(text, Vector2f(0,0), Color::White)
{}

am::RectButton::RectButton(const std::string& text, const am::Vector2f& size, const Color& color) : Button(text, size), color_(color){

    rectButton_.setSize(size_);
    rectButton_.setColor(color_);

    update();
}

void am::RectButton::setSize(const am::Vector2f& newSize){

    size_ = newSize;
    rectButton_.setSize(size_);

    update();
}

void am::RectButton::setRectColor(const am::Color& color){

    color_ = color;
    rectButton_.setColor(color_);
}

void am::RectButton::setPosition(const am::Vector2f& position){

    rectButton_.setPosition(position);
    update();
}

void am::RectButton::setOutline(float thickness = 5.0f, const am::Color& color = Color::White){

    rectButton_.setOutlineThickness(thickness);
    rectButton_.setOutlineColor(color);
}

am::Vector2f am::RectButton::getSize() const{

    return size_;
}

am::Vector2f am::RectButton::getPosition() const{
    return am::Vector2f(rectButton_.getPosition().x, rectButton_.getPosition().y);
}

am::Vector4f am::RectButton::getBox() const{

    return rectButton_.getBox();
}

void am::RectButton::update(){

    am::Button::adjustTextPosition(textButton_, rectButton_);
}

void am::RectButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(rectButton_, states);
    target.draw(textButton_, states);
}
