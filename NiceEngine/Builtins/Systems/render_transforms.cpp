#include "render_transforms.hpp"
#include "../Components/Transform.hpp"
#include "../../Core/Engine.hpp"
#include <iostream>
using namespace NiceEngine;
using namespace NiceEngine::Builtins::Components;
void NiceEngine::Builtins::Systems::render_transforms(entt::registry *registry){
    auto view = registry->view<Transform>();
    for(auto entity : view){
        Transform& transform = view.get<Transform>(entity);
        if(transform.draw){
            Core::Engine::graphics->draw_rect(&transform.rect, transform.rect_color, transform.fill_rect);
        }
    }
}