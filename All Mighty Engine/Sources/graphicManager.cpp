#include "graphicManager.hpp"

GraphicManager::GraphicManager(const GraphicManager&& graphic) : ResourcesManager(std::move(graphic.resources_))
{}

GraphicManager& GraphicManager::operator=(const GraphicManager&& graphic){

    *this = std::move(graphic);
    return *this;
}

GraphicManager::~GraphicManager(){

    resources_.clear();
}

void GraphicManager::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(auto& i : resources_)
        target.draw(i.second, states);
}
