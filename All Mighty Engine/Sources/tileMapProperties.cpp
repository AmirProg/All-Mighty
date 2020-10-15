#include "tileMapProperties.hpp"

TileMapProperties::TileMapProperties(const propMap& properties) : properties_(properties)
{}

TileMapProperties::~TileMapProperties()
{ properties_.clear(); }

void TileMapProperties::addState(int tileNumber, const std::string& state){

    properties_.insert( { tileNumber, state } );
}

bool TileMapProperties::isState(int tileNumber, const std::string& state){

    return properties_[tileNumber] == state;
}
