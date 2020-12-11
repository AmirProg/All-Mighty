#include "graphicManager.hpp"

am::GraphicManager::~GraphicManager(){

    resources_.clear();
}

void am::GraphicManager::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(const auto& i : resources_)
        target.draw(i.second, states);
}
