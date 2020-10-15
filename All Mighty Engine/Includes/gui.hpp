#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include "window.hpp"
#include "widget.hpp"
#include "resourcesManager.hpp"

/*************************************************************************
*
*
*   ~ GUI CLASS ~
*
* This class handle your GUI, you can add a Widget object
* (by calling the method add(YourWidget))
*
* Always link to a Window object
*
* It inherits from ResourcesManager<std::string, Widget*>
* => So it inherits from NonCopyable too
*  (which means you can't copy a GUI object)
*
* When you decide to add a widget you have to give it a key
*    -> This key is a std::string object
*
* GUI inherits from sf::Drawable so call draw() will draw every widgets
* A GUI is always linked to a Window object.
*
* You can use the basics styles proposed by the class
*
*************************************************************************/

class GUI : public ResourcesManager<std::string, Widget>, public sf::Drawable{

public:
    enum class Style { Default, Center, Right, Left, Row, Line, Max }; // Default = no style, you have to move every widgets yourself

    GUI() = delete;
    GUI(Style style, Window& window);
    GUI(const GUI&&);
    GUI& operator=(const GUI&&);
    virtual ~GUI();
    void add(const std::string& key, Widget& resource); // Stack system
    virtual void remove(const std::string& key);
    void setWindow(Window& window); // If you want to change the current window your GUI is associated with
    void setStyle(Style style);
    void move(const Vector2f& moveVector); // Move every widgets in the GUI

private:
    std::reference_wrapper<Window> window_;
    Style style_;
    void update(); // Update the responsive GUI according to the chosen style
    void setCenterStyle();
    void alignAxisX(std::size_t x); // Used for Right, Left and Row styles
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // GUI_HPP_INCLUDED
