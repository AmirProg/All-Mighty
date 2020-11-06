#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include "nonCopyable.hpp"
#include "vector.hpp"
#include <functional>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <map>

/*******************************************************************
*
*
* ~ Camera class (NonCopyable) ~
*
*
* You can stack the views then give the Camera to a Window object
*
*
*******************************************************************/

class Camera : private NonCopyable{

public:

    enum class Type { None, Minimap, SplitVerticalLeft, SplitVerticalRight, Up, Max };

    Camera() = default;
    Camera(Camera&&) noexcept = default;
    Camera& operator=(Camera&&) noexcept = default;
    virtual ~Camera() noexcept;
    void setCenter(const Vector2f& center); // Set the center of every views
    void setCenter(const sf::Transformable& object); // Same but with a sf::Transformable object focus
    void setCenter(int key, const Vector2f& center);
    void setCenter(int key, const sf::Transformable& object);
    void move(const Vector2f& moveVector); // Move every views
    void move(int key, const Vector2f& moveVector); // Move only one view accoridng to it's key
    void zoom(float factor); // Zoom every views by a given factor
    void zoom(int key, float factor);
    void addView(int key, const Vector2f& center, const Vector2f& rectDim); // (width,height)
    void addView(int key, const sf::View& view);
    void setViewPosition(int key, const Vector4f& position);
    void setViewType(int key, Type type);
    std::size_t getNumberView() const;
    sf::View& operator[](int key);

private:

    Vector2f commonCenterPosition_;
    std::map<int, sf::View> views_;
};

#endif // CAMERA_HPP_INCLUDED
