#ifndef RESOURCESMANAGER_HPP_INCLUDED
#define RESOURCESMANAGER_HPP_INCLUDED

#include "nonCopyable.hpp"
#include <map>
#include <functional>

/****************************************************************************************************
*
* ~ ResourcesManager<> template class ~
*
* Every resources that you could use (graphics, audio...)
*
* You have to create an instance of an object before being able to add it to the std::map
*
* Ex : ResourcesManager<int, Sprite> spriteManager;
*
* Sprite ennemy { ... };
*
* spriteManager.add(0,ennemy);
* spriteManager.add(1,ennemy); // An other instance of the Sprite ennemy
*
* In order to get an access to an element according to its key, you can do : spriteManager[key]
*
* Make sure to load every Sprites, Sounds and Musics only once
*
*****************************************************************************************************/

/* MAIN CLASS RESOURCES MANAGER <> */

namespace am {

    template<typename Key, typename T>
    class ResourcesManager : private NonCopyable {

    public:
        ResourcesManager()
        {}

        ResourcesManager(const std::map<Key, std::reference_wrapper<T>>& resources) : resources_(resources)
        {}

        ResourcesManager(const ResourcesManager&& resources) : ResourcesManager(std::move(resources.resources_))
        {}

        ResourcesManager& operator=(const ResourcesManager&& resources) {

            resources_ = std::move(resources.resources_);
            return *this;
        }

        virtual ~ResourcesManager()
        {
            this->clear();
        }

        virtual void add(const Key& key, T& resource) {

            resources_.insert({ key, resource });
        }

        virtual void add(const Key& key, const T& resource) {

            add(key, resource);
        }

        void remove(const Key& key) {

            resources_.erase(key);
        }

        void clear() {

            resources_.clear();
        }

        /*void doToElements(auto action){ // action is a function that is applied to every elements of the std::unordered_map
            for(auto& i : resources_)
                action(i.second);
        }*/

        T& operator[](const Key& key) {

            auto it{ resources_.find(key) }; // Iterator on the element
            assert((it != resources_.end()) && "Fail seeking resource"); // If the iterator has reached the end then there is no element associated to that key

            return it->second.get();
        }

    protected:
        std::map<Key, std::reference_wrapper<T>> resources_;

    };
}

#endif // RESOURCESMANAGER_HPP_INCLUDED