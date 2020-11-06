#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include "collision.hpp"
#include "widget.hpp"
#include "resourcesManager.hpp"
#include "map.hpp"

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
*    -> The container is ordored by the keys
*
* GUI inherits from sf::Drawable so call draw() will draw every widgets
* A GUI is always linked to a Window object.
*
* You can use the basics styles proposed by the class
*
*************************************************************************/

class GUI : public ResourcesManager<std::string, Widget>, public sf::Drawable {

public:
    enum class Style { Default, Center, Right, Left, Row, Line, Max }; // Default = no style, you have to move every widgets yourself

    GUI() = default;
    GUI(Style style, Window& window);
    GUI(GUI&&) noexcept = default;
    GUI& operator=(GUI&&) noexcept = default;
    virtual ~GUI();
    void add(const std::string& key, Widget& resource); // Stack system
    virtual void remove(const std::string& key);
    void setWindow(Window& window); // If you want to change the current window your GUI is associated with
    void setStyle(Style style);
    void move(const Vector2f& moveVector); // Move every widgets in the GUI
    void getMovable(InputManager& input); // Get every widgets of the GUI movable according to the inputs

private:
    std::reference_wrapper<Window> window_;
    Style style_;
    void update(); // Update the responsive GUI according to the chosen style
    static void setCenterStyle(std::map<std::string, std::reference_wrapper<Widget>>& resources, std::reference_wrapper<Window> window);
    void alignAxisX(float x); // Used for Right, Left and Row styles
    void moveWithMouse(InputManager& input);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool movable_{ false }; // Says if the widgets stacked in the GUI are movable
};

#endif // GUI_HPP_INCLUDED