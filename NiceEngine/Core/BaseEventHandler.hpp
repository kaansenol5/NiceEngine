#pragma once
#include <SDL2/SDL_events.h>


namespace NiceEngine::Core{
    class BaseEventHandler{
    public:
        void handle();
        SDL_Event& get_event();
    private:
        SDL_Event event;
    };
}