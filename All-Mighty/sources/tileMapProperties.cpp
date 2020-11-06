#include "tileMapProperties.hpp"

TileMapProperties::TileMapProperties(const propMap& properties) : properties_(properties)
{}

TileMapProperties::~TileMapProperties()
{ properties_.clear(); }

void TileMapProperties::addState(int tileNumber, const std::string& state){

    properties_.insert( { tileNumber, state } );
}

bool TileMapProperties::isState(int tileNumber, const std::string& state){

    try {

        return properties_[tileNumber] == state; // TODO
    }

    catch(const std::underflow_error& error){
        
        std::cerr << error.what();
    }

    catch (const std::overflow_error& error) {
        
        std::cerr << error.what();
    }

    catch (const std::exception& error) {

        std::cerr << error.what();
    }
}
