#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED

#include <cmath>
#include "window.hpp"
#include "map.hpp"
#include "tileMapProperties.hpp"

/**************************************************************
* ~ Collision manager templates functions and namespace ~
*
* Manage simple collision between different concretes objects
*
* Sprite A {}, B {};
* if(Collision::intersect(A,B)) // Test the collision between two sprites
*   // Do something
*
***************************************************************/

namespace am {

    namespace Collision {

        template<typename T, typename U>
        static inline bool intersect(const T& A, const U& B) {

            return !(A.getBox().x + A.getBox().w < B.getBox().x ||
                A.getBox().y + A.getBox().h < B.getBox().y ||
                A.getBox().x > B.getBox().x + B.getBox().w ||
                A.getBox().y > B.getBox().y + B.getBox().h);
        }

        template<typename T>
        static inline bool intersectWindowLeft(const T& A) {

            return A.getBox().x <= 0;
        }

        template<typename T>
        static inline bool intersectWindowRight(const T& A, const Window& window) {

            return A.getBox().x + A.getBox().w >= window.getSize().x;
        }

        template<typename T>
        static inline bool intersectWindowTop(const T& A) {

            return A.getBox().y <= 0;
        }

        template<typename T>
        static inline bool intersectWindowBottom(const T& A, const Window& window) {

            return A.getBox().y + A.getBox().h >= window.getSize().y;
        }

        template<typename T>
        static inline bool intersectWindow(const T& A, const Window& window) {

            return intersectWindowRight(A, window) || intersectWindowLeft(A, window) || intersectWindowTop(A, window) || intersectWindowBottom(A, window);
        }

        /* This function prevents an object to go over the window */

        template<typename T>
        static inline void makeWindowSolid(T& A, const Window& window) {

            if (intersectWindowRight(A, window))
                A.setPosition(Vector2f(window.getSize().x - A.getBox().w, A.getBox().y));

            if (intersectWindowBottom(A, window))
                A.setPosition(Vector2f(A.getBox().x, window.getSize().y));

            if (intersectWindowTop(A))
                A.setPosition(Vector2f(A.getBox().x, 0));

            if (intersectWindowLeft(A))
                A.setPosition(Vector2f(0, A.getBox().y));
        }

        template<typename T>
        static inline bool collisionTileState(const T& A, const TileMap& tileMap, TileMapProperties& tileMapProperties, const std::string& state) {

            /* We only test the tiles that the sprite could actually intersect */

            Vector2u tilesMin{ tileMap.positionToIndex(Vector2f(A.getBox().x , A.getBox().y)) };
            Vector2u tilesMax{ tileMap.positionToIndex(Vector2f(A.getBox().x + A.getBox().w,A.getBox().y + A.getBox().h)) };

            // getNumberTiles().x -> rows number, y is the number of lines, BUT the matrix is built like (line,row)

            for (size_t i{ tilesMin.x }; i <= std::min(tileMap.getNumberTiles().y, tilesMax.x); ++i) {

                for (size_t j{ tilesMin.y }; j <= std::min(tileMap.getNumberTiles().x, tilesMax.y); ++j) {

                    if (tileMapProperties.isState(tileMap.getTileNumber(Vector2u(i, j)), state)) // The Matrix<int> object is based on (line,row)
                        return true;
                }

            }

            return false;
        }

        template<typename T>
        static inline bool intersectMouse(const T& A, const Window& window) {

            return A.getBox().x + A.getBox().w >= static_cast<std::size_t>(sf::Mouse::getPosition(window).x) &&
                A.getBox().x <= static_cast<std::size_t>(sf::Mouse::getPosition(window).x) &&
                A.getBox().y + A.getBox().h >= static_cast<std::size_t>(sf::Mouse::getPosition(window).y) &&
                A.getBox().y <= static_cast<std::size_t>(sf::Mouse::getPosition(window).y);
        }

        template<typename T>
        static inline bool intersectMouse(const T& A, const sf::RenderWindow& window) {

            return A.getBox().x + A.getBox().w >= static_cast<std::size_t>(sf::Mouse::getPosition(window).x) &&
                A.getBox().x <= static_cast<std::size_t>(sf::Mouse::getPosition(window).x) &&
                A.getBox().y + A.getBox().h >= static_cast<std::size_t>(sf::Mouse::getPosition(window).y) &&
                A.getBox().y <= static_cast<std::size_t>(sf::Mouse::getPosition(window).y);
        }
    }
}

#endif // COLLISION_HPP_INCLUDED
