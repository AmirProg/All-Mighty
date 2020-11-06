#ifndef TILEMAPPROPERTIES_HPP_INCLUDED
#define TILEMAPPROPERTIES_HPP_INCLUDED

#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include "nonCopyable.hpp"

/*************************************************************
*                                                            *
* ~ TileMapProperties class ~                                *
*                                                            *
* This class allow you to declare if a tile                  *
* is specific in your app                                    *
*                                                            *
* Declare a TileMap object which handle the graphic view     *
* Then, if you want to add a certain logic to it, declare    *
* a TileMapProperties object then make the tiles specific    *
*                                                            *
*************************************************************/

class TileMapProperties : NonCopyable{

public:

    using propMap = std::unordered_map<int, std::string>;

    TileMapProperties() = default;
    TileMapProperties(const propMap&);
    virtual ~TileMapProperties();
    void addState(int tileNumber, const std::string& state); // The integer representing the tile is now considered as under the state
    bool isState(int tileNumber, const std::string& state); // Look if a tile number is a certain type of tile (state)

private:

    propMap properties_; // The int is the number of the tile in the TileMap's Matrix, the std::string is the state of this tile
};

#endif // TILEMAPPROPERTIES_HPP_INCLUDED
