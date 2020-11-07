#include "map.hpp"

/* TileMap */

TileMap::TileMap()
{}

TileMap::TileMap(const SpriteSheet& spriteSheet) : spriteSheet_(spriteSheet)
{}

TileMap::TileMap(const SpriteSheet& spriteSheet, const std::initializer_list<std::initializer_list<int>>& mapMatrix) : spriteSheet_(spriteSheet){

    numberTiles_ = Vector2u(std::size(*std::begin(mapMatrix)), std::size(mapMatrix)); // *std::begin(mapMatrix) is the first case of the Matrix (-> Rows)
    mapMatrix_.resize(numberTiles_.x,numberTiles_.y);

    /* Linearization of the 2D std::initializer_list<int>> */

    std::size_t countLine {};
    std::size_t countRow {};

    for(const auto& i : mapMatrix){ // i is a std::initialiser_list<int>, not an integer
        for(const auto& j : i){ // But j is
            mapMatrix_(countLine,countRow) = j;
            ++countRow;
        }

        ++countLine;
        countRow = 0;
    }

}

TileMap::TileMap(const std::string& path){

    std::ifstream file{ path };
    assert(file); // The file has been charged

    int currentValue{};

    Vector2u numberTilesSheet{};
    Vector2u numberTiles{};

    file >> texturePath_ >> numberTilesSheet.x >> numberTilesSheet.y >> numberTiles.x >> numberTiles.y; // The first line is the path to the texture, the two next are the number of tiles (width, height)

    spriteSheet_.setNewSheet(texturePath_, numberTilesSheet); // The SpriteSheet object is now correctly constructed (if it had'nt already done)

    mapMatrix_.resize(numberTiles.x, numberTiles.y);

    numberTiles_ = numberTiles;

    for (std::size_t i{}; i < numberTiles_.y; ++i) {

        for (std::size_t j{}; j < numberTiles_.x; ++j) {

            file >> currentValue >> std::ws;
            mapMatrix_(i, j) = currentValue;
        }
    }
}

TileMap::~TileMap(){

    spriteTiles_.clear();
}

void TileMap::tileMapping(){

    spriteTiles_.clear();

    for(std::size_t i {}; i < numberTiles_.y; ++i){ // 0 -> number of lines

        for(std::size_t j {}; j < numberTiles_.x; ++j){ // 0 -> number of rows

            std::size_t scaleX = mapMatrix_(i,j)%spriteSheet_.getSheetDim().x; // Prevent to go over the number of tiles on a single line
            std::size_t scaleY = static_cast<std::size_t>(mapMatrix_(i,j)/spriteSheet_.getSheetDim().x);

            spriteSheet_.cut(Vector2u(scaleX+1,scaleY+1)); // sf::IntRect(x,y,sizeX,sizeY)
            spriteSheet_.setPosition(Vector2f(static_cast<float>(j*spriteSheet_.getSizeOneSprite().x), static_cast<float>(i*spriteSheet_.getSizeOneSprite().y)));

            spriteTiles_.push_back(spriteSheet_); // We add to the spritesTiles vector the current sprite cut
        }
    }
}

void TileMap::changeTileWithIndex(const Vector2u& index, int newValue){

    std::size_t scaleX = newValue%spriteSheet_.getSheetDim().x; // Prevent to go over the number of tiles on a single line
    std::size_t scaleY = static_cast<std::size_t>(newValue/spriteSheet_.getSheetDim().x);

    spriteSheet_.cut(Vector2u(scaleX+1,scaleY+1));
    spriteSheet_.setPosition(Vector2f(spriteTiles_[(index.x-1)*numberTiles_.x+index.y-1].getPosition().x, // std::vector at method allow to reach an element
                                      spriteTiles_[(index.x-1)*numberTiles_.x+index.y-1].getPosition().y));

    spriteTiles_[(index.x-1)*numberTiles_.x+index.y-1] = spriteSheet_;
    mapMatrix_(index.x-1,index.y-1) = newValue; // The matrix representing the map is also modified
}

int TileMap::getTileNumber(const Vector2u& index) const{

    try {

        if (index.x-1 < numberTiles_.x && index.y-1 < numberTiles_.y && index.x-1 >= 0 && index.y-1 >= 0)
            return mapMatrix_(index.x - 1, index.y - 1);

        else
            throw std::overflow_error("");
    }

    catch (const std::overflow_error& error) {
        std::cerr << error.what();
    }

    catch (const std::exception& error) {
        std::cerr << error.what();
    }
}

void TileMap::changeTileWithPosition(const Vector2f& position, int newValue){

    changeTileWithIndex(positionToIndex(position),newValue);
}

bool const TileMap::saveMap(const std::string& path){

    std::ofstream file { path };

    bool succeed{ false };

    file << texturePath_ << "\n\n" << spriteSheet_.getSheetDim().x << ' ' << spriteSheet_.getSheetDim().y << "\n\n" << numberTiles_.x << ' ' << numberTiles_.y << "\n\n";

    if (file) {

        succeed = true;

        for (std::size_t i{}; i < numberTiles_.y; ++i) {

            for (std::size_t j{}; j < numberTiles_.x; ++j) {

                file << mapMatrix_(i, j) << ' ';
            }

            file << '\n';
        }
    }

    else
        std::cerr << "Fail opening file" << std::endl;

    return succeed;
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

    return Vector2u(static_cast<std::size_t>(std::size_t(position.y/spriteSheet_.getSizeOneSprite().y) + 1),
                    static_cast<std::size_t>(std::size_t(position.x/spriteSheet_.getSizeOneSprite().x) + 1));
}

Sprite TileMap::getTile(const Vector2u& index) const{

    return spriteTiles_[(index.x-1)*numberTiles_.x+index.y-1];
}

Sprite TileMap::getTileWithPosition(const Vector2f& position) const{

    return getTile(positionToIndex(position));
}

Vector2u const TileMap::getNumberTiles() const{

    return numberTiles_;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    // We draw the full vector of sprites that constitute the tile map

    for(const auto& k : spriteTiles_)
        target.draw(k,states);
}

void TileMap::update(){

    spriteTiles_.clear();
    tileMapping();
}
