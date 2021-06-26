#include "render_textures.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Texture.hpp"
#include "../Components/Rotation.hpp"
using namespace NiceEngine;
using namespace NiceEngine::Builtins::Components;
using namespace NiceEngine::Builtins::Systems;

void NiceEngine::Builtins::Systems::render_textures(entt::registry *registry){
    auto group = registry->group<Texture, Transform>();
    for(auto entity : group){
        Transform transform = group.get<Transform>(entity);
        Texture texture = group.get<Texture>(entity);
        Core::Engine::graphics->draw_texture(texture.texture, &texture.source_rect, &transform.rect);
    }
}