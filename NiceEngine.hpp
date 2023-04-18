#include <SDL2/SDL.h>
#include "include/entt.hpp"
#include <string>
#include <vector>
#include <functional>
#include <future>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace NiceEngine::SceneManagement{
    class Scene{
    public:
        inline void add_system(std::function<void(entt::registry *registry)> fn){
            system_list.push_back(fn);
        }
        inline void remove_system(std::function<void(entt::registry *registry)> fn){
            for(unsigned i = 0 ; i < system_list.size() ; i++){
        //        if(system_list[i] == fn){
        //          system_list.erase(system_list.begin()+i);
        //       }
            }
        }
        inline void update(){
            for(unsigned i = 0; i < system_list.size() ; i++){
                std::async(std::launch::async, system_list[i], &registry);
            //    system_list[i](&registry);
            }
        }
        inline entt::entity new_entity(){
            {
                entt::entity entity = registry.create();
                return entity;
            }
        }
        template<typename T, typename... Args>
        inline T& add_component(entt::entity target, Args... args){
            T& component = registry.emplace<T>(target, args...);
            return component;
        }
        template<typename T>
        inline void remove_component(entt::entity target){
            registry.remove<T>(target);
        }
        entt::registry registry;
    private:
        std::vector<std::function<void(entt::registry *regisrty)>> system_list;
    };

    class SceneManager{
    public:
        inline SceneManager(){
             //   load_scene(new Scene);
        }
        inline void load_scene(Scene *scene){
            active_scene = scene;
        }
        inline void update(){
            active_scene->update();
        }
        inline entt::registry* get_registry(){
            return &active_scene->registry;
        }
    private:
        Scene *active_scene;
    };

}






namespace NiceEngine::Core{
    class BaseEventHandler{
    public:
        inline BaseEventHandler(bool& running): running(running){}
        inline void handle()
            {
                SDL_PollEvent(&event);
                switch (event.type)
                {
                case SDL_QUIT:
                    running = false;
                    std::cout << "quit signal recieved" << std::endl;
                    break;
                
                default:
                    break;
                }
            }
            inline SDL_Event& get_event(){
                return event;
            }
            private:
                bool& running;
                SDL_Event event;
    };
    class Graphics{
    public:
        inline Graphics(char* title, int width, int height){
            window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            clear();
            swap_buffers();
        }
        inline ~Graphics(){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
        }
        inline void draw_texture(SDL_Texture* texture, const SDL_Rect* source_rect, const SDL_Rect* destination_rect){
            int error;
            error = SDL_RenderCopy(renderer, texture, source_rect, destination_rect);
            if(error == -1){
                std::cout << "[Graphics.cpp][draw_texture] Error!: " << SDL_GetError() << std::endl;
            }
        }
        inline void draw_texture_rotated(SDL_Texture* texture, const SDL_Rect* source_rect, const SDL_Rect* destination_rect, double angle, SDL_Point center, SDL_RendererFlip flip){
            int error;
            error = SDL_RenderCopyEx(renderer, texture, source_rect, destination_rect, angle, &center, flip);
            if(error == -1){
                std::cout << "[Graphics.cpp][draw_texture] Error!: " << SDL_GetError() << std::endl;
            }
        }

        inline SDL_Texture* load_image(char* filename){
            SDL_Surface* temp = IMG_Load(filename);
            if(temp == nullptr){
                std::cout << "[Graphics.cpp][load_image] Error!: " << SDL_GetError() << std::endl;
            }
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);
            SDL_FreeSurface(temp);
            return texture;
        }
        inline SDL_Texture* load_text(TTF_Font* font, char* text, SDL_Color color){
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
        inline void draw_rect(SDL_Rect* rect, SDL_Color color, bool filled = true){
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            if(filled){
                SDL_RenderFillRect(renderer, rect);
            }
            else{
                SDL_RenderDrawRect(renderer, rect);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        inline void clear(){
            SDL_RenderClear(renderer);
        }
        inline void swap_buffers(){
            SDL_RenderPresent(renderer);
        }
        inline SDL_Renderer* get_renderer(){
            return renderer;
        }
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    };
    
    class Engine{
        public:
            inline Engine(char* title, int w, int h){
            SDL_Init(SDL_INIT_EVERYTHING);
                IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
                TTF_Init();
              std::cout << "SDL initialized" << std::endl;
                graphics = new Graphics(title, w, h);
                events = new BaseEventHandler(Engine::running);
                scene_manager = new SceneManagement::SceneManager;
                std::cout << "engine systems initialized" << std::endl;
            }
            inline ~Engine(){
                delete graphics;
                std::cout << "graphics quit" << std::endl;
                delete events;
                std::cout << "events quit" << std::endl;
                delete scene_manager;
                std::cout << "scenemanager quit" << std::endl;
                TTF_Quit();
                IMG_Quit();
                SDL_Quit();
                std::cout << "SDL quit" << std::endl;
                std::cout << "engine systems deleted" << std::endl;
            }
            int target_FPS = 60;
            static Graphics *graphics;
            static BaseEventHandler *events;
            static SceneManagement::SceneManager *scene_manager;
            static bool running;
            inline void update(){
                int frameDelay = 1000 / target_FPS;
                Uint32 frameStart;
                frameStart = SDL_GetTicks();
                int frameTime;
                graphics->clear();
                scene_manager -> update();
                graphics->swap_buffers();
               frameTime = SDL_GetTicks() - frameStart;
               if(frameDelay > frameTime){
                SDL_Delay(frameDelay - frameTime); 
                }
                //errorwatcher.watch(); not to be used, for now
            }
            
            inline void handle_events(){
                events->handle();
            }
    //        ErrorWatcher errorwatcher; we leave this for now
        };
    Graphics* Engine::graphics;
    SceneManagement::SceneManager* Engine::scene_manager;
    BaseEventHandler* Engine::events;
    bool Engine::running = true;
    

    


}





namespace NiceEngine::Builtins::Components{
    struct Animation{
        unsigned frame_count;
        unsigned frame_size;
        unsigned current_frame = 0;
    };
}
namespace NiceEngine::Builtins::Components{
    struct Rotation{
        double angle;
        SDL_Point center;
        SDL_RendererFlip flip;
    };
}
namespace NiceEngine::Builtins::Components{
    struct Texture{
        SDL_Texture* texture;
        SDL_Rect source_rect;
    };
}
namespace NiceEngine::Builtins::Components{
    struct Transform{
        SDL_Rect rect;
        bool draw = false;
        bool fill_rect = false;
        SDL_Color rect_color = {255, 255, 255, 255};
    };
}

namespace NiceEngine::Builtins::Systems{
    void render_transforms(entt::registry *registry){
        auto view = registry->view<NiceEngine::Builtins::Components::Transform>();
        for(auto entity : view){
            NiceEngine::Builtins::Components::Transform& transform = view.get<NiceEngine::Builtins::Components::Transform>(entity);
            if(transform.draw){
                Core::Engine::graphics->draw_rect(&transform.rect, transform.rect_color, transform.fill_rect);
            }
        }
    }

    void render_textures(entt::registry *registry){
        auto group = registry->group<NiceEngine::Builtins::Components::Texture, NiceEngine::Builtins::Components::Transform>();
        for(auto entity : group){
            NiceEngine::Builtins::Components::Transform transform = group.get<NiceEngine::Builtins::Components::Transform>(entity);
            NiceEngine::Builtins::Components::Texture texture = group.get<NiceEngine::Builtins::Components::Texture>(entity);
            Core::Engine::graphics->draw_texture(texture.texture, &texture.source_rect, &transform.rect);
        }
    }
}


