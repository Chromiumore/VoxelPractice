#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <png.h>

#include "Shader.h"
#include "Window.h"
#include "Events.h"

#define GLEW_STATIC

int WIDTH = 1280;
int HEIGHT = 720;
const char* TITLE = "voxels";

float vertices[] = {
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

int main()
{
    Window::init(WIDTH, HEIGHT, TITLE);
    Events::init();

    Shader* shader = load_shader("main.glslv", "main.glslf");
    if (shader == nullptr) {
        std::cerr << "Unable to load shader\n";
        Window::terminate();
        return -1;
    }

    // Vertex Array Object
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    // Создание вершинного буфера
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Позиция
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0*sizeof(GLfloat)));

    glEnableVertexAttribArray(0);
    // Отвязывем объект на всякий случай
    glBindVertexArray(0);

    glClearColor(0, 0, 0, 1);

    while (!Window::isShouldClose()) {  
        Events::pullEvents();
        if (Events::isJustPressed(GLFW_KEY_ESCAPE))
            Window::setShouldClose(true);
        if (Events::isJustClicked(GLFW_MOUSE_BUTTON_1))
            glClearColor((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, 1);


        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        // Отрисовка
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        Window::swap();
    }
    Window::terminate();

    return 0;
}