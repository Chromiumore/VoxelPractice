#include <iostream>

#include <glew.h>
#include <glfw3.h>

#include <png.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "png_loading.h"
#include "Shader.h"
#include "Window.h"
#include "Events.h"
#include "Camera.h"
#include "Chunk.h"
#include "VoxelRenderer.h"

#define GLEW_STATIC

int WIDTH = 1280;
int HEIGHT = 720;
const char* TITLE = "voxels";

float vertices[] = {
   -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
    1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int attrs[] = {
    3, 2, 0
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

    Texture* texture = load_texture("block.png");
    if (texture == nullptr) {
        std::cerr << "Unable to load test png\n";
        delete shader;
        Window::terminate();
        return -1;
    }

    VoxelRenderer* renderer = new VoxelRenderer(1024 * 1024 * 8);
    Chunk* chunk = new Chunk();
    Mesh* mesh = renderer->render(chunk);;

    glClearColor(0, 0, 0, 1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    Camera* camera = new Camera ( glm::vec3(0, 0, 1), glm::radians(40.0f));

    glm::mat4 model(1.0f);
    //model = glm::scale(model, glm::vec3(2, 2, 2));
    model = glm::translate(model, glm::vec3(0.5f, 0, 0));

    float last_time = glfwGetTime();
    float delta = 0.0f;

    float camX = 0.0f;
    float camY = 0.0f;

    float speed = 5;
    while (!Window::isShouldClose()) {
        float cur_time = glfwGetTime();
        delta = cur_time - last_time;
        last_time = cur_time;
        if (Events::isJustPressed(GLFW_KEY_ESCAPE))
            Window::setShouldClose(true);
        if (Events::isJustClicked(GLFW_MOUSE_BUTTON_1))
            glClearColor((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, 1);
        if (Events::isJustPressed(GLFW_KEY_TAB)) {
            Events::toggleCursor();
        }
        if (Events::isPressed(GLFW_KEY_S))
            camera->position -= camera->front * delta * speed;
        if (Events::isPressed(GLFW_KEY_W))
            camera->position += camera->front * delta * speed;
        if (Events::isPressed(GLFW_KEY_A))
            camera->position -= camera->right * delta * speed;
        if (Events::isPressed(GLFW_KEY_D))
            camera->position += camera->right * delta * speed;
        if (Events::isPressed(GLFW_KEY_SPACE))
            camera->position += camera->up * delta * speed;
        if (Events::isPressed(GLFW_KEY_LEFT_SHIFT))
            camera->position -= camera->up * delta * speed;


        if (Events::cursor_locked) {
            camY += -Events::deltaY / Window::height * 2;
            camX += -Events::deltaX / Window::height * 2;

            if (camY < -glm::radians(89.0f)) {
                camY = -glm::radians(89.0f);
            }
            if (camY > glm::radians(89.0f)) {
                camY = glm::radians(89.0f);
            }

            camera->rotation = glm::mat4(1.0f);
            camera->rotate(camY, camX, 0);

        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader->use();
        shader->uniformMatrix("model", model);
        shader->uniformMatrix("projview", camera->getProjection() * camera->getView());
        texture->bind();
        // Отрисовка
        mesh->draw(GL_TRIANGLES);

        Events::pullEvents();
        Window::swap();
    }
    delete shader;
    delete texture;
    delete mesh;
    delete chunk;

    Window::terminate();

    return 0;
}