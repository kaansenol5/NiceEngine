#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_pixels.h>

namespace NiceEngine::Builtins::Components{
    struct Transform{
        SDL_Rect rect;
        bool draw = false;
        bool fill_rect = false;
        SDL_Color rect_color = {255, 255, 255, 255};
    };
}
