#include "sprite.hpp"

am::Sprite::Sprite() : Sprite("ress/claudius.png") // Default texture
{}

am::Sprite::Sprite(const sf::Texture& texture) : texture_(texture) {
    setTexture(texture_);
    isTextured_ = true;
}

am::Sprite::Sprite(const std::string& path) {

    setTextureLink(path);
}

void am::Sprite::setTextureLink(const std::string& path) {

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

void am::Sprite::setPosition(const Vector2f& position) {

    sf::Sprite::setPosition(sf::Vector2f(position.x, position.y));
}

am::Vector2f am::Sprite::getPosition() const {

    return Vector2f(sf::Sprite::getPosition().x, sf::Sprite::getPosition().y);
}

void am::Sprite::move(const Vector2f& moveVector) {

    sf::Sprite::move(sf::Vector2f(moveVector.x, moveVector.y));
}

am::Vector2f const am::Sprite::getSize() const {

    return Vector2f(getGlobalBounds().width, getGlobalBounds().height);
}

am::Vector4f const am::Sprite::getBox() const {

    return Vector4f(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
}

void am::Sprite::update()
{}

/* SpriteSheet methods */

am::SpriteSheet::SpriteSheet() : SpriteSheet(Vector2u(1,1))
{}

am::SpriteSheet::SpriteSheet(const std::string& path, const Vector2u& numberSprites) : Sprite(path), numberSprites_(numberSprites) {

    update();
}

am::SpriteSheet::SpriteSheet(const Vector2u& numberSprites) : SpriteSheet("ress2/tilesMap.png", numberSprites){
    update(); 
}

void am::SpriteSheet::cut(const Vector2u& coord) {

    setTextureRect((sf::IntRect((coord.x - 1) * sizeOneSprite_.x, (coord.y - 1) * sizeOneSprite_.y, sizeOneSprite_.x, sizeOneSprite_.y)));
}

void am::SpriteSheet::setPosition(const Vector2f& position) {

    sf::Sprite::setPosition(sf::Vector2f(position.x, position.y));
}

void am::SpriteSheet::setNewSheet(const std::string& path, const Vector2u& numberSprites) {

    setTextureLink(path);
    numberSprites_ = numberSprites;

    update();
}

am::Vector2f const am::SpriteSheet::getSize() const {

    return sizeSheet_;
}

am::Vector2u const am::SpriteSheet::getSheetDim() const {

    return numberSprites_;
}

am::Vector2u const am::SpriteSheet::getSizeOneSprite() const {

    return sizeOneSprite_;
}

am::Vector4f const am::SpriteSheet::getBox() const {

    return Vector4f(getGlobalBounds().left, getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
}

void am::SpriteSheet::update() {

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