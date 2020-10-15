#ifndef GRAPHICMANAGER_HPP_INCLUDED
#define GRAPHICMANAGER_HPP_INCLUDED

#include "resourcesManager.hpp"
#include <SFML/Graphics.hpp>

class GraphicManager : public ResourcesManager<std::string, sf::Drawable>, public sf::Drawable{

public:
    GraphicManager() = default;
    GraphicManager(const GraphicManager&&);
    GraphicManager& operator=(const GraphicManager&&);
    virtual ~GraphicManager();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // GRAPHICMANAGER_HPP_INCLUDED
