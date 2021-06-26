#include "Engine.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace NiceEngine::SceneManagement;
using namespace NiceEngine::Core;
Graphics* Engine::graphics;
SceneManager* Engine::scene_manager;
BaseEventHandler* Engine::events;
bool Engine::running = true;

Engine::Engine(char* title, int w, int h){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    std::cout << "SDL initialized" << std::endl;
    graphics = new Graphics(title, w, h);
    events = new BaseEventHandler;
    scene_manager = new SceneManager;
    std::cout << "engine systems initialized" << std::endl;
}

Engine::~Engine(){
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "SDL quit" << std::endl;
    delete scene_manager;
    delete graphics;
    delete events;
    std::cout << "engine systems deleted" << std::endl;
}


void Engine::update(){
    int frameDelay = 1000 / target_FPS;
    Uint32 frameStart;
    frameStart = SDL_GetTicks();
    int frameTime;
    graphics->clear();
    scene_manager -> update();
    graphics->swap_buffers();
    frameTime = SDL_GetTicks() - frameStart;
    if(frameDelay > frameTime){
      SDL_Delay(frameDelay - frameTime); 
    }
    //errorwatcher.watch(); not to be used, for now
}


void Engine::handle_events(){
    events->handle();
}