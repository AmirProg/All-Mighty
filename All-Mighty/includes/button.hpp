#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "widget.hpp"
#include "text.hpp"
#include "sprite.hpp"
#include "shape.hpp"

/**************************************************************************
*
*
*  ~ BUTTON (abstract) CLASS ~
*  ~ SPRITEBUTTON CLASS ~
*  ~  RECTBUTTON CLASS ~

*  Create a Button object then you can give it a text or not
*
*  SpriteButton button("My button");
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
*
**************************************************************************/

class Button : public Widget{

public:
    Button() = default;
    Button(const Text&);
    Button(const std::string& text, const Vector2f& size);
    Button(const Text& text, const Vector2f& size);
    Button(const Button&) = default;
    virtual ~Button();
    virtual void setText(const Text& text);
    virtual void setTextString(const std::string& text);
    virtual void setTextStyle(std::size_t charSize, const std::string& font, const Color& color);
    virtual void setPosition(const Vector2f&) override = 0;
    virtual Vector2f getSize() const override = 0;
    virtual Vector2f getPosition() const override = 0;
    virtual Vector4f getBox() const override = 0;
    virtual bool& isClicked(InputManager& input, Window& window) noexcept override;
    virtual void setSlot(const std::function<void()>& slot);
    virtual void active();

protected:
    Text textButton_;
    std::function<void()> funcSlot_;
    virtual void update() override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    template<typename Container>
    static void adjustTextPosition(Text& textButton, const Container& container);
};

class SpriteButton : public Button{

public:
    SpriteButton();
    SpriteButton(const std::string& textButton);
    SpriteButton(const std::string& textButton, const std::string& path);
    SpriteButton(const SpriteButton&) = default;
    SpriteButton(SpriteButton&&) noexcept = default;
    SpriteButton& operator=(SpriteButton&&) noexcept = default;
    SpriteButton& operator=(const SpriteButton&) = default;
    virtual ~SpriteButton() = default;
    void setSprite(const std::string& path);
    void setSprite(const Sprite& sprite);
    virtual void setPosition(const Vector2f& newPosition) override;
    void setColor(const Color& color);
    virtual Vector2f getSize() const override;
    virtual Vector2f getPosition() const override;
    virtual Vector4f getBox() const override;

private:
    Sprite spriteButton_;

    inline void adjustTextPosition(Vector2f& positionText);
    virtual void update() override; // Update the text position according to the modifications to the button
    virtual void setSize(const Vector2f& newSize) override; // You can't just modify the size of the button sprite, the size is automatically calculated from spriteButton_
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class RectButton : public Button{

public:
    RectButton();
    RectButton(const std::string& text);
    RectButton(const std::string& text, const Vector2f& size, const Color& color);
    RectButton(const RectButton&) = default;
    RectButton(RectButton&&) noexcept = default;
    RectButton& operator=(const RectButton&) = default;
    RectButton& operator=(RectButton&&) noexcept = default;
    virtual void setSize(const Vector2f& newSize);
    virtual void setPosition(const Vector2f&) override;
    void setRectColor(const Color& color);
    void setOutline(float thickness, const Color& color);
    virtual Vector2f getSize() const override;
    virtual Vector2f getPosition() const override;
    virtual Vector4f getBox() const override;

private:
    Rectangle rectButton_;
    Color color_;

    virtual void update() override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // BUTTON_HPP_INCLUDED
