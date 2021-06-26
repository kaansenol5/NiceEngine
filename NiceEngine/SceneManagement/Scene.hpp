#pragma once
#include <functional>
#include <vector>
#include "../include/entt.hpp"

namespace NiceEngine::SceneManagement{
    class Scene{
    public:
        void add_system(std::function<void(entt::registry *registry)> fn);
        void remove_system(std::function<void(entt::registry *registry)> fn);
        void update();
        entt::entity new_entity();
        template<typename T, typename... Args>
        inline T& add_component(entt::entity target, Args... args){
            T& component = registry.emplace<T>(target, args...);
            return component;
        }
        template<typename T>
        inline void remove_component(entt::entity target){
            registry.remove<T>(target);
        }
        entt::registry registry;
    private:
        std::vector<std::function<void(entt::registry *regisrty)>> system_list;
    };
}