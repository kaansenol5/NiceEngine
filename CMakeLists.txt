cmake_minimum_required(VERSION 3.19)
INCLUDE(FindPkgConfig)
project(NiceEngine)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-lSDL2 -lSDL2_image -lSDL2_ttf -std=c++17 -pthread -O3")
set(CMAKE_CXX_STANDARD 17)

add_library(
  NiceEngine
  NiceEngine/Core/Engine.cpp
  NiceEngine/SceneManagement/Scene.cpp
  NiceEngine/SceneManagement/SceneManager.cpp
  NiceEngine/Core/BaseEventHandler.cpp
  NiceEngine/Core/Graphics.cpp
  NiceEngine/Builtins/Systems/render_textures.cpp
  NiceEngine/Builtins/Systems/render_transforms.cpp
  NiceEngine/Core/ErrorWatcher.cpp
)

add_executable(
  Example1
  Examples/Example1.cpp
)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

TARGET_LINK_LIBRARIES(Example1 LINK_PUBLIC /home/kaan/programming/cpp/NiceEngine/build/libNiceEngine.a)