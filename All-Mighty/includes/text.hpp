#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

#include "vector.hpp"
#include "visualEntity.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <string>

/*****************************************
*
* ~ Text Class ~
*
*  Exemple :
*
*  Text text("Hello World");
*  text.setFont("font.ttf");
*  text.setCharSize(10); -> IN PIXEL
*  text.setColor(Color::Red);
*  text.setPosition(100,100);
*  window.draw(text);
*
*****************************************/

namespace am {

    typedef sf::Color Color;

    class Text : public sf::Text, public VisualEntity {

    public:
        // enum class TextStyle { None = -1, Default, Perso, MAX };
        Text();
        Text(const std::string& stringText);
        Text(const std::string& stringText, std::size_t charSize, const Vector2f& position, const Color& color);
        Text(const Text&) = default;
        Text(Text&&) noexcept = default;
        Text& operator=(Text&&) noexcept = default;
        virtual ~Text() = default;
        Text& operator=(const Text&) = default;
        void setTextString(const std::string& stringText);
        void setFont(const std::string& path);
        void setColor(const Color& color);
        void setCharSize(std::size_t charSize);
        void setPosition(const Vector2f& position);
        Vector4f getBox() const;
        inline std::string getString() const;
        Vector2f getSizeOneLetter() const;
        void pop(); // Erase the last char of the text
        Text operator+=(Text text) noexcept;
        Text operator+=(std::string s) noexcept;
        Text operator+=(char c) noexcept;

        friend std::ostream& operator<<(std::ostream& os, const Text& text) {

            os << text.getString();
            return os;
        }

    private:
        std::string stringText_;
        std::size_t charSize_;
        sf::Font font_;
        Vector2f position_;
        Color color_;

        virtual void update() override;
    };
}

am::Text operator+(const am::Text& text1, const am::Text& text2) noexcept;
am::Text operator+(const am::Text& text, const std::string& s) noexcept;

#endif // TEXT_HPP_INCLUDED
