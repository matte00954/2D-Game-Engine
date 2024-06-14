#ifndef __ENTITYCOMPONENTSYSTEM_H__
#define __ENTITYCOMPONENTSYSTEM_H__

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <string>

// ECS Pattern
// Entity component system allows for components similar to Unity engine
// System allows creating any type of component by creating a new class and inheriting Component class
// System cleans up after itself
// Also makes sure any entity does not have two of the same component
// Add components with addComponent() func
// Get components with getComponent() allows access to sub class functions
class Component;
class Entity;

// comp ID is unique, different components will have different IDs
using ComponentID = std::size_t;
// max components that an entity can hold, arbitrary number
constexpr std::size_t maxComponents = 32;
// component bit set
using ComponentBitSet = std::bitset<maxComponents>;
// array of component pointers
using ComponentArray = std::array<Component *, maxComponents>;

inline ComponentID getComponentTypeID()
{
    static ComponentID lastID = 0;
    // increase each time function is called, to create unique IDs
    return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
    // generate new ID
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

// Create any type of component by inheriting this
class Component
{
public:
    Entity *pEntity;

    // component is created and added to entity, just before the game begins
    virtual void start(){};
    // game loop
    virtual void update(){};
    // graphics
    virtual void draw(){};

    virtual ~Component(){};
};

/// Holds components
// entity is one object in the game
class Entity
{
private:
    std::string name;
    // If false, then remove from game
    bool active = true;
    // list of entity components
    std::vector<std::unique_ptr<Component>> entityComponents;

    ComponentArray componentArray;

    ComponentBitSet componentBitSet;

public:
    // entity will loop through for each component
    void update()
    {
        for (auto &component : entityComponents)
            component->update();
    }
    void draw()
    {
        for (auto &component : entityComponents)
            component->draw();
    }
    // checks active status during loop
    bool isActive() const { return active; }
    // to remove from game
    void destroy() { active = false; }
    // entity name (not required, but useful for debugging)
    void setName(std::string s) { name = s; };

    std::string getName() { return name; };

    template <typename T>
    bool hasComponent() const
    {
        // compare entity bitset
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    // add component to entity
    T &addComponent(TArgs &&...mArgs)
    {
        T *component(new T(std::forward<TArgs>(mArgs)...));
        component->pEntity = this;
        std::unique_ptr<Component> uniquePointer{component};
        // adds components to entity vector
        entityComponents.emplace_back(std::move(uniquePointer));

        componentArray[getComponentTypeID<T>()] = component;
        componentBitSet[getComponentTypeID<T>()] = true;

        component->start();
        return *component;
    }

    template <typename T>
    T &getComponent() const
    {
        auto pointer(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T *>(pointer);
    }
};

/// handles component updates of all entities, there should only be one of these active
class EntitySystemManager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void update()
    {
        for (auto &entity : entities)
            entity->update();
    }
    void draw()
    {
        for (auto &e : entities)
            e->draw();
    }
    void refresh()
    {
        entities.erase(std::remove_if(
                           std::begin(entities), std::end(entities),
                           [](const std::unique_ptr<Entity> &mEntity)
                           {
                               return !mEntity->isActive();
                           }),
                       std::end(entities));
        // remove entities if not active
    }

    Entity &createEntity()
    {
        // create entity
        Entity *pEntity = new Entity();
        // assign pointer to entity
        std::unique_ptr<Entity> uniqueEntity{pEntity};
        // insert at end of vector
        entities.emplace_back(std::move(uniqueEntity));

        return *pEntity;
    }
};
#endif // __ENTITYCOMPONENTSYSTEM_H__