#pragma once
#include "Scene.hpp"

namespace NiceEngine::SceneManagement{
    class SceneManager{
    public:
        SceneManager();
        void load_scene(Scene *scene);
        void update();
        entt::registry* get_registry();
    private:
        Scene *active_scene;
    };
}
