#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "matrix.hpp"
#include "sprite.hpp"
#include "nonCopyable.hpp"
#include <fstream>

/*
* ~ Map classes ~
*
* You can manage a Map object
*
* Give to the constructor a Sprite object if you want your map to be a single sprite
*
* The TileMap class inherit from Map class and you can manage a tile map using SpriteSheet object
*
* It uses a Matrix object, but the user of the class gives a 2D initializer_list<>.
*
* TileMap map { SpriteSheet(...), std::initializer_list<std::initializer_list<int>>() };
*
* Or directly TileMap map { SpriteSheet(...), {{0,0,...},
*                                              {0,0,...}} };
*
* map.tileMapping(); -> Set the tile map (You can also read a file insted of using a 2D Vector, and if you put a std::string in argument it will read the file
*
* The INDEX means the position of the tile on the window, for example (1,1) is the first tile that appears on the window. Index starts always by 1 not 0
* The POSITION is the relative position of the sprite that constitute the tile
* You can convert a position into an index with positionToIndex(Vector2u) method
*
* If you want to draw your map you can create a Window object then Window.draw(map) in the main loop (Map Class inherit from sf::Drawable)
*
*/

/* Base interface */

class Map : public sf::Drawable, NonCopyable{

public:
    Map() = default;
    Map(const Map&& map)
    { *this = std::move(map); }
    virtual ~Map() = default;
    Map& operator=(const Map&& map){
       *this = std::move(map);
       return *this;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0; // window.draw(map)
};

/* TileMap class */

class TileMap : public Map{

public:
    TileMap();
    TileMap(const TileMap&&);
    TileMap& operator=(const TileMap&&);
    TileMap(const SpriteSheet& spriteSheet);
    TileMap(const SpriteSheet& spriteSheet, const std::initializer_list<std::initializer_list<int>>& mapMatrix);
    TileMap(const std::string& path);
    virtual ~TileMap();
    void tileMapping(); // Proceed to the tile mapping algorithm
    void tileMapping(const std::string& path); // Tile mapping with a vector charged in a file
    int getTileNumber(const Vector2u& index) const; // Get the value of a tile according to its index in the map Matrix
    void changeTileWithIndex(const Vector2u& index, int newValue); // Remplaces and changes an element in the map vector according to the index
    void changeTileWithPosition(const Vector2f& position, int newValue); // Remplace and change an element in the map vector according to the position
    void saveMap(const std::string& path); // Saves the modifications in a file
    bool isTile(const Vector2f& position) const; // Tells if there is a tile on a position
    Vector2u const positionToIndex(const Vector2f& position) const; // Gives the index of the tile according to the position of the sprite
    SpriteSheet getTile(const Vector2u& index) const; // Returns the sprite according to its index (CUT the sprite sheet but the texture has the same size /!\)
    SpriteSheet getTileWithPosition(const Vector2f& position) const; // Returns the sprite according to the position
    Vector2u const getNumberTiles() const;

private:
    SpriteSheet spriteSheet_;
    Vector2u numberTiles_; // Dimensions of the tiles sheet (equal to spriteSheet_.getSheetDim())
    Matrix<int> mapMatrix_; // A Matrix object representing the map, we linearize the 2D container
    std::vector<SpriteSheet> spriteTiles_; // Every sprites that constitute the map
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // MAP_HPP_INCLUDED
