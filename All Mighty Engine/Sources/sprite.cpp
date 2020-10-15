#include "sprite.hpp"

Sprite::Sprite(){}

Sprite::Sprite(const sf::Texture& texture) : texture_(texture){
    setTexture(texture_);
    isTextured_ = true;
}

Sprite::Sprite(const std::string& path){

    assert((texture_.loadFromFile(path) && "Fail loading texture"));
    this->setTexture(texture_);
    isTextured_ = true;
}

void Sprite::setTextureLink(const std::string& path){

    assert((texture_.loadFromFile(path)) && "Fail loading texture");
    this->setTexture(texture_);
    isTextured_ = true;
}

void Sprite::setPosition(const Vector2f& position){

    sf::Sprite::setPosition(sf::Vector2f(position.x, position.y));
}

void Sprite::move(const Vector2f& moveVector){

    sf::Sprite::move(sf::Vector2f(moveVector.x,moveVector.y));
}

Vector2f const Sprite::getSize() const{

    return Vector2f(getTexture()->getSize().x,getTexture()->getSize().y);
}

Vector4f const Sprite::getBox() const{

    return Vector4f(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
}

/* SpriteSheet methods */

SpriteSheet::SpriteSheet(){}

SpriteSheet::SpriteSheet(const std::string& path, const Vector2u& numberSprites) : Sprite(path), numberSprites_(numberSprites){

    assert((numberSprites_.x != 0 && numberSprites_.y != 0) && "Sheet Empty");
    assert((this->isTextured_) && "Sheet not textured");

    sizeSheet_.x = getTexture()->getSize().x;
    sizeSheet_.y = getTexture()->getSize().y;
    sizeOneSprite_.x = sizeSheet_.x/numberSprites_.x;
    sizeOneSprite_.y = sizeSheet_.y/numberSprites_.y;
}

SpriteSheet::SpriteSheet(const Vector2u& numberSprites) : SpriteSheet("",numberSprites) {}

void SpriteSheet::cut(const Vector2u& coord){

    setTextureRect((sf::IntRect((coord.x-1)*sizeOneSprite_.x, (coord.y-1)*sizeOneSprite_.y,sizeOneSprite_.x,sizeOneSprite_.y)));
}

void SpriteSheet::setPosition(const Vector2f& position){

    sf::Sprite::setPosition(sf::Vector2f(position.x,position.y));
}

Vector2f const SpriteSheet::getSize() const{

    return sizeSheet_;
}

Vector2u const SpriteSheet::getSheetDim() const{

    return numberSprites_;
}

Vector2f const SpriteSheet::getSizeOneSprite() const{

    return sizeOneSprite_;
}

Vector4f const SpriteSheet::getBox() const{

    return Vector4f(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width,getGlobalBounds().height);
}
