#pragma once

#include <GLFW/glfw3.h>

class Keyboard {
public:
    static void keyCallback(GLFWwindow* window, const int32_t key, const int32_t scancode, const int32_t action, const int32_t mods);
    static bool key(const int32_t key);
    static bool keyChanged(const int32_t key);
    static bool keyWentUp(const int32_t key);
    static bool keyWentDown(const int32_t key);
private:
    Keyboard();

    static bool keys[];
    static bool keysChanged[];
};