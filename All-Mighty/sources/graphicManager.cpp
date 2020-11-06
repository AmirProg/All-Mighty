#include "graphicManager.hpp"

GraphicManager::~GraphicManager(){

    resources_.clear();
}

void GraphicManager::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(const auto& i : resources_)
        target.draw(i.second, states);
}
