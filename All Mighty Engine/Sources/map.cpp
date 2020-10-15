#include "map.hpp"

/* TileMap */

TileMap::TileMap(){}

TileMap::TileMap(const TileMap&& map) : spriteSheet_(std::move(map.spriteSheet_)),
                                        numberTiles_(std::move(map.numberTiles_)),
                                        mapMatrix_(std::move(map.mapMatrix_)),
                                        spriteTiles_(std::move(map.spriteTiles_))
{}

TileMap::TileMap(const SpriteSheet& spriteSheet) : spriteSheet_(spriteSheet){}

TileMap::TileMap(const SpriteSheet& spriteSheet, const std::initializer_list<std::initializer_list<int>>& mapMatrix) : spriteSheet_(spriteSheet){

    numberTiles_ = Vector2u(std::size(*std::begin(mapMatrix)), std::size(mapMatrix)); // *std::begin(mapMatrix) is the first case of the Matrix (-> Rows)
    mapMatrix_.resize(numberTiles_.x,numberTiles_.y);

    /* Linearization of the 2D std::initializer_list<int>> */

    std::size_t countLine {};
    std::size_t countRow {};

    for(auto& i : mapMatrix){ // i is a std::initialiser_list<int>, not an integer
        for(auto& j : i){ // But j is
            mapMatrix_(countLine,countRow) = j;
            ++countRow;
        }

        ++countLine;
        countRow = 0;
    }

}

TileMap::TileMap(const std::string& path){

    spriteSheet_.setTextureLink(path);
}

TileMap::~TileMap(){

    spriteTiles_.clear();
}

TileMap& TileMap::operator=(const TileMap&& map){

    *this = std::move(map);
    return *this;
}

void TileMap::tileMapping(){

    spriteTiles_.clear();

    for(std::size_t i {}; i < numberTiles_.y; ++i){ // 0 -> number of lines

        for(std::size_t j {}; j < numberTiles_.x; ++j){ // 0 -> number of rows

            std::size_t scaleX = mapMatrix_(i,j)%spriteSheet_.getSheetDim().x; // Prevent to go over the number of tiles on a single line
            std::size_t scaleY = static_cast<std::size_t>(mapMatrix_(i,j)/spriteSheet_.getSheetDim().x);

            spriteSheet_.cut(Vector2u(scaleX+1,scaleY+1)); // sf::IntRect(x,y,sizeX,sizeY)
            spriteSheet_.setPosition(Vector2f(j*spriteSheet_.getSizeOneSprite().x, i*spriteSheet_.getSizeOneSprite().y));
            spriteTiles_.push_back(spriteSheet_); // We add to the spritesTiles vector the current sprite cut
        }
    }
}

void TileMap::tileMapping(const std::string& link){

    std::ifstream file { link };
    assert(file); // The file has been charged

    std::size_t currentValue {};

    std::size_t width {}, height {};
    file >> width >> height; // The two first number in the file (width,height)

    mapMatrix_.resize(height, width);
    numberTiles_.x = width;
    numberTiles_.y = height;

    for(std::size_t i {}; i < height; ++i){

        for(std::size_t j {}; j < width; ++j){

            file >> currentValue >> std::ws;
            mapMatrix_(i,j) = currentValue;
        }
    }

    tileMapping();
}

void TileMap::changeTileWithIndex(const Vector2u& index, int newValue){

    std::size_t scaleX = newValue%spriteSheet_.getSheetDim().x; // Prevent to go over the number of tiles on a single line
    std::size_t scaleY = static_cast<std::size_t>(newValue/spriteSheet_.getSheetDim().x);

    spriteSheet_.cut(Vector2u(scaleX+1,scaleY+1));
    spriteSheet_.setPosition(Vector2f(spriteTiles_.at((index.x-1)*numberTiles_.x+index.y-1).getPosition().x, // std::vector at method allow to reach an element
                             spriteTiles_.at((index.x-1)*numberTiles_.x+index.y-1).getPosition().y));

    spriteTiles_.at((index.x-1)*numberTiles_.x+index.y-1) = spriteSheet_;
    mapMatrix_(index.x-1,index.y-1) = newValue; // The matrix representing the map is also modified
}

int TileMap::getTileNumber(const Vector2u& index) const{

    return mapMatrix_(index.x-1, index.y-1);
}

void TileMap::changeTileWithPosition(const Vector2f& position, int newValue){

    changeTileWithIndex(positionToIndex(position),newValue);
}

void TileMap::saveMap(const std::string& path){

    std::ofstream file { path };

    file << numberTiles_.x << ' ' << numberTiles_.y << '\n' << '\n';

    for(std::size_t i {}; i < numberTiles_.x; ++i){

       for(std::size_t j {}; j < numberTiles_.y; ++j){

            file << mapMatrix_(i,j) << ' ';
       }

       file << '\n';
    }
}

bool TileMap::isTile(const Vector2f& position) const{

    for(auto& i : spriteTiles_){

        if(i.getBox().x + i.getBox().w >= position.x &&
           i.getBox().x <= position.x &&
           i.getBox().y + i.getBox().h >= position.y &&
           i.getBox().y <= position.y)

           return true;
    }

    return false;
}

Vector2u const TileMap::positionToIndex(const Vector2f& position) const{

    return Vector2u(position.y/spriteSheet_.getSizeOneSprite().y+1, position.x/spriteSheet_.getSizeOneSprite().x+1);
}

SpriteSheet TileMap::getTile(const Vector2u& index) const{

    return spriteTiles_.at((index.x-1)*numberTiles_.x+index.y-1);
}

SpriteSheet TileMap::getTileWithPosition(const Vector2f& position) const{

    return getTile(positionToIndex(position));
}

Vector2u const TileMap::getNumberTiles() const{

    return numberTiles_;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    // We draw the full vector of sprites that constitute the tile map

    for(auto& k : spriteTiles_)
        target.draw(k,states);
}
