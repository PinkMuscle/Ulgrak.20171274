#ifndef ECS_h
#define ECS_h
#include <vector>
#include <bitset>
#include <array>
#include <memory>
#include <algorithm>
#include <utility>

class Component;
class Entity;
class ECSManager;

constexpr std::size_t maxComponents = 24;
constexpr std::size_t maxGroups = 24;

using ComponentID = std::size_t;
using Group = std::size_t;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

inline ComponentID GetNewCompoentID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID GetComponentID() noexcept
{
    static_assert (std::is_base_of<Component, T>::value, "");
    static ComponentID typeID = GetNewCompoentID();
    return typeID;
}

class Component
{
public:
    Entity* entity;

    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}
    virtual ~Component() {}
};

class Entity
{
private:
    ECSManager& manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitset;
    GroupBitset groupBitset;

public:
    Entity(ECSManager& manager_) : manager(manager_) {}

    void Update()
    {
        for (auto& c : components) c->Update();
    }

    void Render()
    {
        for (auto& c : components) c->Render();
    }

    bool IsActive() const { return active; }
    void Destroy() { active = false; }

    bool HasGroup(Group group) const
    {
        return groupBitset[group];
    }

    void AddGroup(Group group)
    {
        groupBitset[group] = true;
        manager.AddToGroup(this, group);
    }

    void DeleteGroup(Group group)
    {
        groupBitset[group] = false;
    }

    template <typename T> bool HasComponent() const
    {
        return componentBitset[GetComponentID<T>()];
    }

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args)
    {
        T* c = new T(std::forward<TArgs>(args)...);
        c->entity = this;
        std::unique_ptr<Component>uPtr{ c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitset[getComponentTypeID<T>()] = true;

        c->Init();
        return *c;
    }

    template<typename T> T& GetComponent() const
    {
        auto ptr = componentArray[GetComponentID<T>()];
        return *static_cast<T*>(ptr);
    }
};

class ECSManager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
    void Update()
    {
        for (auto& e : entities) e->Update();
    }
    void Render()
    {
        for (auto& e : entities) e->Render();
    }

    void Refresh()
    {
        for (auto i = 0u; i < maxGroups; i++)
        {
            auto& v = groupedEntities[i];
            v.erase
            (
                std::remove_if(std::begin(v), std::end(v), [i](Entity* entity) { return !entity->IsActive() || !entity->HasGroup(i); }),
                std::end(v)
            );
        }

        entities.erase
        (
            std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &entity) {return !entity->IsActive(); }),
            std::end(entities)
        );
    }

    void AddToGroup(Entity* entity, Group group)
    {
        groupedEntities[group].emplace_back(entity);
    }

    std::vector<Entity*>& GetGroup(Group group)
    {
        return groupedEntities[group];
    }

    Entity& AddEntity()
    {
        Entity *e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};
#endif