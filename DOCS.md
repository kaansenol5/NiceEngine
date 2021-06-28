# What it does

All this "library" does is:

1. Initializing SDL, creating a window and renderer

2. Executing a bunch of functions that you define in the order you add them

3. Using a class called Scene to organise which function is executed when.

# What do i need to know before using this

C++, SDL2, and EnTT.

# What happens if i need to interact with EnTT or SDL directly

The entt::registry is a public member of the Scene class, SDL_Renderer is a public member of Graphics class which is public member of Engine class.

Shortly, you can.

# How to do all these

See examples in Examples/

