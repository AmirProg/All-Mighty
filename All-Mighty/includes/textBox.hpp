#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "widget.hpp"
#include "shape.hpp"
#include "text.hpp"
#include "inputManager.hpp"

/*******************************
*
* ~ TextBox class ~
*
* Handling text boxes widgets
*
*******************************/

namespace am {

    class TextBox : public Widget {

    public:

        enum class Type { Perso, Thin, LongThin, Large, MiddleLarge, Max };

        TextBox();
        TextBox(Type type); // Pre-defined types
        TextBox(const TextBox&) = default;
        virtual ~TextBox() = default;
        TextBox& operator=(const TextBox&) = default;
        TextBox(TextBox&&) noexcept = default;
        TextBox& operator=(TextBox&&) noexcept = default;
        void setTextString(const std::string& textString);
        void setLabel(const std::string& label, std::size_t charSize, const Color& color);
        void setTextStyle(std::size_t charSize, const std::string& font, const Color& color);
        void setOutline(float thickness, const Color& color);
        virtual void setSize(const Vector2f& newSize) override;
        virtual void setPosition(const Vector2f& newPosition) override;
        virtual Vector2f getSize() const override;
        virtual Vector2f getPosition() const override;
        virtual Vector4f getBox() const override;
        std::string getText() const;
        virtual bool& isClicked(InputManager& input, Window& window) noexcept override;
        void manageTextEntered(InputManager& input, Window& window);

    private:
        Rectangle rectBox_;
        Type type_;
        Text text_;
        Text textLabel_;
        float currentTextWidth_; // The actual width of the text block

        virtual void update() override;
        static void responsive(Text& text, Rectangle& rectBox, float& linesText);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif // TEXTBOX_HPP_INCLUDED
