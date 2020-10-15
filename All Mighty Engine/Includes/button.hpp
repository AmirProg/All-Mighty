#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "widget.hpp"
#include "text.hpp"
#include "sprite.hpp"

/**************************************************************************
*
*
*  ~ BUTTON CLASS ~
*
*  Create a Button object then you can give it a text or not
*
*  Button button("My button");
*
*  button.setSprite("sprite path");
*  button.setTextStyle(characterSize, "font path", color);
*
*  Then draw it : window.draw(button)
*
*
* Bug detected : when using copy constructor the button created by copy
*                 get every previous updates which means it
*                 will be update (then probably cut) twice
**************************************************************************/

class Button : public Widget{

public:
    Button();
    Button(const std::string& textButton);
    Button(const std::string& textButton, const Vector2f& positionButton);
    Button(const Button&) = default;
    Button(const Button&&);
    Button& operator=(const Button&&);
    Button& operator=(const Button&) = default;
    virtual ~Button() = default;
    void setSprite(const std::string& path);
    void setSprite(const Sprite& sprite);
    void setText(const Text& text);
    void setTextString(const std::string& text);
    void setTextStyle(size_t charSize, const std::string& font, const Color& color);
    virtual void setPosition(const Vector2f& newPosition) override;
    void setColor(const Color& color);
    virtual Vector2u getSize() const override;
    virtual Vector2f getPosition() const override;
    virtual Vector4f getBox() const override;

private:
    Text textButton_;
    Sprite spriteButton_;

    inline void adjustTextPosition(Vector2f& positionText);
    virtual void update() override; // Update the text position according to the modifications to the button
    virtual void setSize(const Vector2u& newSize) override; // You can't just modify the size of the button sprite, the size is automatically calculated from spriteButton_
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // BUTTON_HPP_INCLUDED
