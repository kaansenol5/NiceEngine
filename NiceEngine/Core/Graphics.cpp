#include "Graphics.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace NiceEngine::Core;
Graphics::Graphics(char* title, int width, int height){
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    clear();
    swap_buffers();
}

Graphics::~Graphics(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_Texture* Graphics::load_image(char* filename){
    SDL_Surface* temp = IMG_Load(filename);
    if(temp == nullptr){
        std::cout << "[Graphics.cpp][load_image] Error!: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
    return texture;
}

SDL_Texture* Graphics::load_text(TTF_Font* font, char* text, SDL_Color color){
    SDL_Surface* temp = TTF_RenderText_Blended(font, text, color);
    if(temp == NULL){
        std::cout << "[Graphics.cpp][load_text] Error!: " << SDL_GetError() << std::endl;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);
    if(texture == NULL){
        std::cout << "[Graphics.cpp][load_text] Error!: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(temp);
    return texture;
}

void Graphics::draw_rect(SDL_Rect* rect, SDL_Color color, bool filled){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if(filled){
        SDL_RenderFillRect(renderer, rect);
    }
    else{
        SDL_RenderDrawRect(renderer, rect);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Graphics::draw_texture(SDL_Texture* texture, const SDL_Rect* source_rect, const SDL_Rect* destination_rect){
    int error;
    error = SDL_RenderCopy(renderer, texture, source_rect, destination_rect);
    if(error == -1){
        std::cout << "[Graphics.cpp][draw_texture] Error!: " << SDL_GetError() << std::endl;
    }
}

void Graphics::draw_texture_rotated(SDL_Texture* texture, const SDL_Rect* source_rect, const SDL_Rect* destination_rect, double angle, SDL_Point center, SDL_RendererFlip flip){
    int error;
    error = SDL_RenderCopyEx(renderer, texture, source_rect, destination_rect, angle, &center, flip);
    if(error == -1){
        std::cout << "[Graphics.cpp][draw_texture] Error!: " << SDL_GetError() << std::endl;
    }
}

void Graphics::clear(){
    SDL_RenderClear(renderer);
}

void Graphics::swap_buffers(){
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Graphics::get_renderer(){
    return renderer;
}