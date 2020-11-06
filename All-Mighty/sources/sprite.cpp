#include "sprite.hpp"

Sprite::Sprite() : Sprite("ress/claudius.png") // Default texture
{}

Sprite::Sprite(const sf::Texture& texture) : texture_(texture) {
    setTexture(texture_);
    isTextured_ = true;
}

Sprite::Sprite(const std::string& path) {

    setTextureLink(path);
}

void Sprite::setTextureLink(const std::string& path) {

    try {

        if (!texture_.loadFromFile(path))
            throw std::invalid_argument("Fail loading texture");

        this->setTexture(texture_);
        isTextured_ = true;
    }

    catch (const std::invalid_argument& error) {

        std::cerr << error.what() << std::endl;
    }

    update();
}

void Sprite::setPosition(const Vector2f& position) {

    sf::Sprite::setPosition(sf::Vector2f(position.x, position.y));
}

Vector2f Sprite::getPosition() const {

    return Vector2f(sf::Sprite::getPosition().x, sf::Sprite::getPosition().y);
}

void Sprite::move(const Vector2f& moveVector) {

    sf::Sprite::move(sf::Vector2f(moveVector.x, moveVector.y));
}

Vector2f const Sprite::getSize() const {

    return Vector2f(getGlobalBounds().width, getGlobalBounds().height);
}

Vector4f const Sprite::getBox() const {

    return Vector4f(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
}

void Sprite::update()
{}

/* SpriteSheet methods */

SpriteSheet::SpriteSheet() : SpriteSheet(Vector2u(1,1))
{}

SpriteSheet::SpriteSheet(const std::string& path, const Vector2u& numberSprites) : Sprite(path), numberSprites_(numberSprites) {

    update();
}

SpriteSheet::SpriteSheet(const Vector2u& numberSprites) : SpriteSheet("ress2/tilesMap.png", numberSprites){
    update(); 
}

void SpriteSheet::cut(const Vector2u& coord) {

    setTextureRect((sf::IntRect((coord.x - 1) * sizeOneSprite_.x, (coord.y - 1) * sizeOneSprite_.y, sizeOneSprite_.x, sizeOneSprite_.y)));
}

void SpriteSheet::setPosition(const Vector2f& position) {

    sf::Sprite::setPosition(sf::Vector2f(position.x, position.y));
}

void SpriteSheet::setNewSheet(const std::string& path, const Vector2u& numberSprites) {

    setTextureLink(path);
    numberSprites_ = numberSprites;

    update();
}

Vector2f const SpriteSheet::getSize() const {

    return sizeSheet_;
}

Vector2u const SpriteSheet::getSheetDim() const {

    return numberSprites_;
}

Vector2u const SpriteSheet::getSizeOneSprite() const {

    return sizeOneSprite_;
}

Vector4f const SpriteSheet::getBox() const {

    return Vector4f(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
}

void SpriteSheet::update() {

    try {

        if (numberSprites_.x != 0 && numberSprites_.y != 0) {

            sizeSheet_.x = static_cast<float>(getTexture()->getSize().x);
            sizeSheet_.y = static_cast<float>(getTexture()->getSize().y);
            sizeOneSprite_.x = static_cast<float>(sizeSheet_.x) / numberSprites_.x;
            sizeOneSprite_.y = static_cast<float>(sizeSheet_.y) / numberSprites_.y;
        }

        else
            throw;
    }

    catch (const std::exception& error) {

        std::cerr << error.what() << std::endl;
    }

}