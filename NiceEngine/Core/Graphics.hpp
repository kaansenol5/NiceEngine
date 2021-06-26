#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

namespace NiceEngine::Core{
    class Graphics{
    public:
        Graphics(char* title, int width, int height);
        ~Graphics();
        void draw_texture(SDL_Texture* texture, const SDL_Rect* source_rect, const SDL_Rect* destination_rect);
        void draw_texture_rotated(SDL_Texture* texture, const SDL_Rect* source_rect, const SDL_Rect* destination_rect, double angle, SDL_Point center, SDL_RendererFlip flip);
        SDL_Texture* load_image(char* filename);
        SDL_Texture* load_text(TTF_Font* font, char* text, SDL_Color color);
        void draw_rect(SDL_Rect* rect, SDL_Color color, bool filled = true);
        void clear();
        void swap_buffers();
        SDL_Renderer* get_renderer();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    };
}