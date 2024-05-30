#include <iostream>

#include "Window.h"
#include "glew.h"
#include "glfw3.h"

#define GLEW_STATIC

int WIDTH = 1280;
int HEIGHT = 720;
const char* TITLE = "voxels";

int main(void)
{
    Window::init(WIDTH, HEIGHT, TITLE);

    while (!Window::isShouldClose()) {
        glfwPollEvents();
        Window::swap();
    }

    return 0;
}