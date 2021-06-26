#pragma once
#include "Graphics.hpp"
#include "BaseEventHandler.hpp"
#include "../SceneManagement/SceneManager.hpp"
#include "ErrorWatcher.hpp"

namespace NiceEngine::Core{
    using namespace NiceEngine::SceneManagement;
    class Engine{
    public:
        Engine(char* title, int w, int h);
        ~Engine();
        int target_FPS = 60;
        static Graphics *graphics;
        static BaseEventHandler *events;
        static SceneManager *scene_manager;
        static bool running;
        void update();
        void handle_events();
//        ErrorWatcher errorwatcher; we leave this for now
    };
}