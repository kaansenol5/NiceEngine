#include "../NiceEngine.hpp"

#include <string>
#include <iostream>

// THIS WILL WRITE BUNCH OF MESSAGES TO STDOUT, AND SHOW AN EMPTY WINDOW




// THIS IS METHOD A, BETTER WHEN YOUR COMPONENT MAY INTERACT WITH OTHER COMPONENTS, (like Transform and Texture, you need both to render something)
struct CharacterDescription{
    std::string name;
    std::string type;
};

struct SpecialAbility{
    std::string ability;
};

void speak(entt::registry* registry){
    auto view = registry->view<CharacterDescription, SpecialAbility>();
    for(auto entity : view){
        CharacterDescription& desc = view.get<CharacterDescription>(entity);
        SpecialAbility& ability = view.get<SpecialAbility>(entity);
        std::cout << "My name is " << desc.name << " and i am an " << desc.type << " i can " << ability.ability << std::endl;
    }
} // as shown, we needed two components in this function
// however, if we merged the two components, we could have a class with 3 variables and a function called speak.
// in a class like this, the speak() would do the cout line and we'd make another function to iterate over these classes and execute all the speak()'s

using namespace NiceEngine::Core;
using namespace NiceEngine::SceneManagement;
int main(){
    Engine engine((char*)"DEMO", 100, 100);
    Scene* scene = new Scene;
    entt::entity monkey = scene->new_entity();
    scene->add_component<CharacterDescription>(monkey, "Jeff", "monkey");
    scene->add_component<SpecialAbility>(monkey, "eat bananas");
    entt::entity robot = scene->new_entity();
    scene->add_component<CharacterDescription>(robot, "Joe", "robot");
    scene->add_component<SpecialAbility>(robot, "beat the shit out of Jeff");
    scene->add_system(&speak);
    engine.scene_manager->load_scene(scene);
    while(engine.running){
        engine.update();
        engine.handle_events();
    }
}