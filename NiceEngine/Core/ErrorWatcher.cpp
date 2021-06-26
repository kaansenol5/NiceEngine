#include "ErrorWatcher.hpp"
#include <SDL2/SDL_error.h>
#include <iostream>

void ErrorWatcher::watch(){
    const char* error = SDL_GetError();
    if(error != ""){
        std::cout << "ErrorWatcher has detected an error on a recent SDL api call" << std::endl;
        std::cout << "This may or may not be the only error occured on this frame, I do not know what function caused it" << std::endl;
        std::cout << "Error Info is: " << std::endl;
        std::cout << SDL_GetError() << std::endl;
        std::cout << std::endl;
        if(pause_on_error){
            std::cout << "Pausing all execution until you press enter, we recommend disabling this on production builds" << std::endl;
            std::cin.get();
        }
    }
}