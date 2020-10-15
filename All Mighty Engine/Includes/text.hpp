#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

#include "vector.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <string>

/*
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
*/

typedef sf::Color Color;

class Text : public sf::Text{

public:
    // enum class TextStyle { None = -1, Default, Perso, MAX };
    Text();
    Text(const std::string& stringText);
    Text(const std::string& stringText, std::size_t charSize, const Vector2f& position, const Color& color);
    Text(const Text&) = default;
    Text(const Text&&);
    Text& operator=(const Text&&);
    ~Text() = default;
    Text& operator=(const Text&) = default;
    void setTextString(const std::string& stringText);
    void setFont(const std::string& path);
    void setColor(const Color& color);
    void setCharSize(std::size_t charSize);
    void setPosition(const Vector2f& position);
    Vector4f getBox() const;
    std::string getString() const;
    Text operator+(const Text& text);
    Text operator+(const std::string& s);
    Text operator+=(Text text);
    Text operator+=(std::string s);
    friend std::ostream& operator<<(std::ostream& os, const Text& text){
        os << text.getString();
        return os;
    }

private:
    std::string stringText_;
    std::size_t charSize_;
    sf::Font font_;
    Vector2f position_;
    Color color_;
};
#endif // TEXT_HPP_INCLUDED
