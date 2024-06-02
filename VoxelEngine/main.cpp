#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include "Shader.h"
#include "Window.h"
#include "Events.h"

#define GLEW_STATIC

int WIDTH = 1280;
int HEIGHT = 720;
const char* TITLE = "voxels";

int main()
{
    Window::init(WIDTH, HEIGHT, TITLE);
    Events::init();

    glClearColor(0, 0, 0, 1);

    Shader* shader = load_shader("main.glslv", "main.glslf");
    if (shader == nullptr) {
        std::cerr << "Unable to load shader\n";
        Window::terminate();
        return -1;
    }

    while (!Window::isShouldClose()) {  
        Events::pullEvents();
        if (Events::isJustPressed(GLFW_KEY_ESCAPE))
            Window::setShouldClose(true);
        if (Events::isJustClicked(GLFW_MOUSE_BUTTON_1))
            glClearColor((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, 1);


        glClear(GL_COLOR_BUFFER_BIT);

        Window::swap();
    }
    Window::terminate();

    return 0;
}