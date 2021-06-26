#include "Scene.hpp"
#include <SDL2/SDL_render.h>
#include "../Core/Engine.hpp"
#include <future>

using namespace NiceEngine::SceneManagement;

void Scene::add_system(std::function<void(entt::registry *registry)> fn){
    system_list.push_back(fn);
}


void Scene::remove_system(std::function<void(entt::registry *registry)> fn){
    for(unsigned i = 0 ; i < system_list.size() ; i++){
//        if(system_list[i] == fn){
  //          system_list.erase(system_list.begin()+i);
 //       }
    }
}

void Scene::update(){
    for(unsigned i = 0; i < system_list.size() ; i++){
        std::async(std::launch::async, system_list[i], &registry);
    //    system_list[i](&registry);
    }
}


entt::entity Scene::new_entity(){
    entt::entity entity = registry.create();
    return entity;
}