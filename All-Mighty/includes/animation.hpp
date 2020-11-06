#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

#include "sprite.hpp"
#include "window.hpp"
#include "stopWatch.hpp"
#include <functional>

/******************************************************************************************************************************************
*
* ~ Animation class ~
*
* You can animate a SpriteSheet object easily
*
*   Animation animation(spriteSheet); -> Give a SpriteSheet object to the animation object
*   animation.setFrame(frame); -> Set the frame (fps)
*   animation.setBase(Vector2u(x,y)); -> This is the first sprite that will appears on the screen (the (x,y) one on the 2D sheet)
*
*   Then, you can test the keyboard events with SFML or something else
*
*   if(Input...)
*        animation.playAnimationLine(1); -> Play the animation by considering only the first line on the sprite sheet (0 => no sprite)
*
*
*    animation.restart(); -> Reload the StopWatch object and the animation
*
******************************************************************************************************************************************/

class Animation : private NonCopyable{

public:
    enum class Status { None, Disable, Active, MAX };
    Animation() = delete;
    Animation& operator=(Animation&&) noexcept;
    Animation(SpriteSheet& spriteSheet);
    virtual ~Animation() = default;
    void setSpriteSheet(SpriteSheet& spriteSheet);
    void setFrame(std::size_t frame); // Set the frame of the animation
    void restart(); // Reload the clock and the number of sprite animated
    void setBase(const Vector2u& base); // The first sprite on the screen (row,line) (x,y), set (-1,-1) allow to have not any sprite in the screen
    void playAnimationLine(std::size_t lineSheet); // Play the animation according to the clock and the line on sheet
    void playAnimation(); // Play the entire sprite sheet
    void pauseAnimation();

private:
    std::reference_wrapper<SpriteSheet> spriteSheet_; // Reference on the current spriteSheet_ animated
    std::size_t frame_;
    Vector2u currentSprite_; // The current sprite animated : (1,1) si the first one
    StopWatch stopWatch_; // Time measure
    Status status_;
};

#endif // ANIMATION_HPP_INCLUDED
