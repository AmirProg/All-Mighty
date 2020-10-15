#ifndef TILEMAPPROPERTIES_HPP_INCLUDED
#define TILEMAPPROPERTIES_HPP_INCLUDED

#include "map.hpp"
#include <unordered_map>

/*************************************************************
*                                                            *
*                                                            *
* ~ TileMapProperties class ~                                *
*                                                            *
* This class allow you to declare if a tile                  *
* is specific in your app                                    *
*                                                            *
* Declare a TileMap object which handle the graphic view     *
* Then, if you want to add a certain logic to it, declare    *
* a TileMapProperties object then make the tiles             *
* you want to be special... Special.                         *
*                                                            *
*************************************************************/

class TileMapProperties : NonCopyable{

public:

    typedef std::unordered_map<int, std::string> propMap;

    TileMapProperties() = default;
    TileMapProperties(const propMap&);
    virtual ~TileMapProperties();
    void addState(int tileNumber, const std::string& state); // The integer representing the tile is now considered as under the state
    bool isState(int tileNumber, const std::string& state); // Look if a tile number is a certain type of tile (state)

private:
    propMap properties_; // The int is the number of the tile in the TileMap's Matrix, the std::string is the state of this tile
};

#endif // TILEMAPPROPERTIES_HPP_INCLUDED
