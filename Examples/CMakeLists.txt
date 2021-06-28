add_executable(
    Example1
    Example1.cpp
)

add_executable(
    Example2
    Example2.cpp
)


TARGET_LINK_LIBRARIES(Example1 LINK_PUBLIC /home/kaan/programming/cpp/NiceEngine/build/libNiceEngine.a)
TARGET_LINK_LIBRARIES(Example2 LINK_PUBLIC /home/kaan/programming/cpp/NiceEngine/build/libNiceEngine.a)