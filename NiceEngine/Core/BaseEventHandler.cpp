#include "BaseEventHandler.hpp"
#include "Engine.hpp"
#include <iostream>


using namespace NiceEngine::Core;
void BaseEventHandler::handle(){
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        Engine::running = false;
        std::cout << "quit signal recieved" << std::endl;
        break;
    
    default:
        break;
    }
}

SDL_Event& BaseEventHandler::get_event(){
    return event;
}