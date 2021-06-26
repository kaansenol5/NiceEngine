#include "SceneManager.hpp"


using namespace NiceEngine::SceneManagement;

SceneManager::SceneManager(){
 //   load_scene(new Scene);
}

void SceneManager::update(){
    active_scene->update();
}

void SceneManager::load_scene(Scene* scene){
    active_scene = scene;
}

entt::registry* SceneManager::get_registry(){
    return &active_scene->registry;
}