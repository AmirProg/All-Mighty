#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED

#include <cmath>
#include "window.hpp"
#include "map.hpp"
#include "tileMapProperties.hpp"

/*
* ~ Collision manager templates functions ~
*
* Manage simple collision between different concretes objects
*
* Sprite A {}, B {};
* if(intersect(A,B)) // Test the collision between two sprites
*   // Do something
*/

template<typename T, typename U>
bool intersect(const T& A, const U& B){

    return !(A.getBox().x + A.getBox().w < B.getBox().x ||
             A.getBox().y + A.getBox().h < B.getBox().y ||
             A.getBox().x > B.getBox().x + B.getBox().w ||
             A.getBox().y > B.getBox().y + B.getBox().h);
}

template<typename T>
bool intersectWindowLeft(const T& A){

    return A.getBox().x <= 0;
}

template<typename T>
bool intersectWindowRight(const T& A, const Window& window){

    return A.getBox().x + A.getBox().w >= window.getSize().x;
}

template<typename T>
bool intersectWindowTop(const T& A){

    return A.getBox().y <= 0;
}

template<typename T>
bool intersectWindowBottom(const T& A, const Window& window){

    return A.getBox().y + A.getBox().h >= window.getSize().y;
}

template<typename T>
bool intersectWindow(const T& A, const Window& window){

    return intersectWindowRight(A,window) || intersectWindowLeft(A,window) || intersectWindowTop(A,window) || intersectWindowBottom(A,window);
}

template<typename T>
void makeWindowSolid(T& A, const Window& window, const Vector2f& moveVector){ /* This function prevents an object to go over the window */

    if(intersectWindowRight(A,window))
        A.setPosition(Vector2f(A.getBox().x - moveVector.x, A.getBox().y));

    if(intersectWindowBottom(A,window))
        A.setPosition(Vector2f(A.getBox().x, A.getBox().y - moveVector.x));

    if(intersectWindowTop(A))
        A.setPosition(Vector2f(A.getBox().x, A.getBox().y + moveVector.x));

    if(intersectWindowLeft(A))
        A.setPosition(Vector2f(A.getBox().x + moveVector.x, A.getBox().y));
}

template<typename T>
bool collisionTileState(const T& A, const TileMap& tileMap, TileMapProperties& tileMapProperties, const std::string& state){

    /* We only test the tiles that the sprite could actually intersect */

    Vector2u tilesMin { tileMap.positionToIndex(Vector2f(A.getBox().x , A.getBox().y)) };
    Vector2u tilesMax { tileMap.positionToIndex(Vector2f(A.getBox().x + A.getBox().w,A.getBox().y+A.getBox().h)) };

    // getNumberTiles().x -> rows number, y is the number of lines, BUT the matrix is built like (line,row)

    for(size_t i { tilesMin.x }; i <= std::min(tileMap.getNumberTiles().y, tilesMax.x); ++i){

        for(size_t j { tilesMin.y }; j <= std::min(tileMap.getNumberTiles().x, tilesMax.y); ++j){

            if(tileMapProperties.isState(tileMap.getTileNumber(Vector2u(i,j)), state)) // The Matrix<int> object is based on (line,row)
                return true;
        }

    }

    return false;
}

template<typename T>
bool intersectMouse(const T& A, const Window& window){

    return A.getBox().x + A.getBox().w >= static_cast<size_t>(sf::Mouse::getPosition(window).x) &&
           A.getBox().x <= static_cast<size_t>(sf::Mouse::getPosition(window).x) &&
           A.getBox().y + A.getBox().h >= static_cast<size_t>(sf::Mouse::getPosition(window).y) &&
           A.getBox().y <= static_cast<size_t>(sf::Mouse::getPosition(window).y) ;
}

#endif // COLLISION_HPP_INCLUDED
