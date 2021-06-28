#include "../NiceEngine/Core/Engine.hpp"
#include "../NiceEngine/Builtins/Components/Transform.hpp"
#include "../NiceEngine/Builtins/Systems/render_transforms.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <random>
/* 
THIS WILL DISPLAY 1024 COLOR CHANGING MOVING RECTANGLES ON A 1000x800 WINDOW
*/

// this is more of a "how to make systems" example

using namespace NiceEngine::Core;
using namespace NiceEngine;
using namespace NiceEngine::Builtins::Components;
std::random_device rseed;
std::mt19937 rng(rseed());
std::uniform_int_distribution<int> dist(-5,5);
//creating a system
void shake_rect(entt::registry *registry){ // entt::registry* is given by the Scene, every Scene holds its own registry
    auto view = registry->view<Transform>();  // gets a list of every entity that holds Transform component
    for(auto entity : view){  // iterates over the list
        Transform& transform = view.get<Transform>(entity); // gets a reference to a Transform component held by the current entity
        int x_move = dist(rng);  // randomly move it for a "shake" effect
        int y_move = dist(rng);
        transform.rect.x += x_move; // move it
        transform.rect.y += y_move;
    }
} // this function will be called by the engine every frame once we add a pointer of it with Scene::add_system(std::function<void(entt::registry* registry)>)


void change_color(entt::registry *registry){
    auto view = registry->view<Transform>();  // gets a list of every entity that holds Transform component
    for(auto entity : view){  // iterates over the list
        Transform& transform = view.get<Transform>(entity); // gets a reference to a Transform component held by the current entity
        unsigned char r = rand()%255;
        unsigned char g = rand()%255;
        unsigned char b = rand()%255;
        transform.rect_color = {r, g, b, 255};
    }
}


// WHAT ABOUT EVENT HANDLING?
// the library will run SDL_PollEvent every frame, to get its result you will have to use Engine::events.get_event()
// other than that, you can use the good old SDL_GetKeyboardState and SDL_GetMouseState methods, which will send a const state of input devices
// lets make a system that writes Hello to stdout every time we press the SPACE key
void say_hello(entt::registry *registry){ // it still takes registry as a parameter, because scenemanager will give it to every function it executes
    SDL_Event event = Engine::events->get_event();
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_RETURN:
            std::cout << "hello" << std::endl;
            break;
        
        default:
            break;
        }
        break;
    
    default:
        break;
    }
}

int main(){
    srand(time(NULL));
    Engine engine((char*)"DEMO", 1000, 800); // initialize engine, sdl, open window, create renderer
    NiceEngine::SceneManagement::Scene *scene = new Scene; // create a new scene on the heap
    engine.target_FPS = 60;
    for(unsigned i = 0; i < 1024; i++){
        entt::entity square = scene->new_entity(); // add a new entity to the scene registry
        scene->add_component<Builtins::Components::Transform>(square, rand()%900, rand()%700, rand()%40+20, rand()%40+20, true, true, 255, 0, 0, 255); // add a Transform component to the entity we created, we write all the vars in the struct next to each other with no braces.
    }
    
    scene->add_system(&Builtins::Systems::render_transforms); // add a function (a.k.a system) that will be executed by the engine every frame
    scene->add_system(&shake_rect); // add the system we just created
    scene->add_system(&say_hello);
    engine.scene_manager->load_scene(scene); // finally, this will load the scene we just generated, and that scene will be playing, until another scene gets loaded
    scene->add_system(&change_color); // we can also add in systems *after* loading the scene, since all we do is sending a pointer to an object on the heap
    while(engine.running){ // Engine::running is set to false if the internal event handler gets a quit signal
        engine.update();   // Engine::update will do all logic updates, rendering, and event handling
        engine.handle_events(); // Engine::handle_events will **ONLY** do the internal event handling of the engine, and refresh events with PollEvent
        // you can retrieve current SDL_Event using Engine::events.get_event()
    }
    return 0;
}