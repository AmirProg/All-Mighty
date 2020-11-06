#include "animation.hpp"

Animation::Animation(SpriteSheet& spriteSheet) : spriteSheet_(spriteSheet),
                                                 frame_(0),
                                                 currentSprite_(Vector2u(1,1)),
                                                 stopWatch_(StopWatch::Accuracy::Milliseconds),
                                                 status_(Status::Disable)
{}

void Animation::setSpriteSheet(SpriteSheet& spriteSheet){

    spriteSheet_ = spriteSheet;
}

void Animation::setFrame(std::size_t frame){
    frame_ = frame;
}

void Animation::restart(){

    stopWatch_.restart();
    currentSprite_ = Vector2u(1,1);
}

void Animation::setBase(const Vector2u& base){

    spriteSheet_.get().cut(Vector2u(base.x,base.y));
    stopWatch_.restart();
}

void Animation::playAnimationLine(std::size_t lineSheet){

    status_ = Status::Active;

    if(stopWatch_.getElapsedTime() >= sf::Int32(frame_) || currentSprite_.y != lineSheet){ // Every frame or when we change the current line on the sheet

        stopWatch_.restart(); // Set the clock to 0

        spriteSheet_.get().cut(Vector2u(currentSprite_.x,(lineSheet)));

        ++currentSprite_.x; // We pass to the next sprite on the line

        currentSprite_.y = lineSheet;

        if(currentSprite_.x >= spriteSheet_.get().getSheetDim().x){
            currentSprite_.x = 1; // The current number of the sprite (on the line) on the spritesheet is reset every lines
            currentSprite_.y++;
        }
    }
}

void Animation::playAnimation(){

    status_ = Status::Active;
    playAnimationLine(currentSprite_.y);

    if(currentSprite_.y >= spriteSheet_.get().getSheetDim().y)
        restart();
}

void Animation::pauseAnimation(){

    status_ = Status::Disable;
}
