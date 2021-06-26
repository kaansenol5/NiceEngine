#include <SDL2/SDL_render.h>

namespace NiceEngine::Builtins::Components{
    struct Rotation{
        double angle;
        SDL_Point center;
        SDL_RendererFlip flip;
    };
}