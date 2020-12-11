#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

#include "vector.hpp"
#include "visualEntity.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

/************************************************************************
*
* ~ Sprite and SpriteSheet classes ~
*
* SpriteSheet class inherit from Sprite class
*
* You can load a texture from a direct link file (std::string object)
* and get the bounding box (getBox() method) useful for collisions tests
*
* SpriteSheet class is useful when you work with some sprites sheets
* and not just a single sprite
*
*************************************************************************/

namespace am {

    class Sprite : public sf::Sprite, public VisualEntity {

    public:
        Sprite();
        Sprite(const Sprite&) = default;
        Sprite& operator=(const Sprite&) = default;
        Sprite(const sf::Texture& texture);
        Sprite(const std::string& path);
        virtual ~Sprite() = default;
        void setTextureLink(const std::string& path); // Load a texture from a path
        virtual void setPosition(const Vector2f& position);
        virtual Vector2f getPosition() const;
        virtual void move(const Vector2f& moveVector);
        virtual Vector2f const getSize() const;
        virtual Vector4f const getBox() const; // Return the bounding box

    protected:
        sf::Texture texture_; // Texture associated with the sprite
        bool isTextured_;
        virtual void update();
    };

    /* SpriteSheet class */

    class SpriteSheet : public Sprite {

    public:

        SpriteSheet();
        SpriteSheet(const SpriteSheet&) = default;
        SpriteSheet& operator=(const SpriteSheet&) = default;
        SpriteSheet(const Vector2u& numberSprites, const Vector2f& sizeOneSprite);
        SpriteSheet(const std::string& path, const Vector2u& numberSprites);
        SpriteSheet(const Vector2u& numberSprites);
        void cut(const Vector2u& coord); // Cut the sheet to get the (x,y) sprite on the sheet : (1,1) is the FIRST sprite on the sheet
        virtual void setPosition(const Vector2f& position);
        void setNewSheet(const std::string& path, const Vector2u& numberSprites); // Use ONLY if you don't really know the sheet you will work with
        virtual Vector2f const getSize() const override;
        Vector2u const getSheetDim() const; // Give the dimensions of the sheet (x,y) (sprites numbers)
        Vector2u const getSizeOneSprite() const;
        virtual Vector4f const getBox() const override;
        virtual void update();

    private:
        Vector2u numberSprites_;
        Vector2f sizeSheet_;
        Vector2u sizeOneSprite_;
    };
}

#endif // SPRITE_HPP_INCLUDED
