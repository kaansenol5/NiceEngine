#include <SDL2/SDL_render.h>

namespace NiceEngine::Builtins::Components{
    struct Texture{
        SDL_Texture* texture;
        SDL_Rect source_rect;
    };
}