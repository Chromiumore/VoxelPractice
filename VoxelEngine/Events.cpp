#include "Events.h"
#include <glfw3.h>

#include <iostream>

bool* Events::keys;
unsigned int* Events::frames;
unsigned int Events::current = 0;
bool Events::cursor_locked = false;
bool Events::cursor_started = false;
float Events::deltaX = 0.0f;
float Events::deltaY= 0.0f;
float Events::x = 0.0f;
float Events::y = 0.0f;

#define KEYS 1024

void key_callback(GLFWwindow* window, int key, int code, int action, int mode) {
	if (action == GLFW_PRESS) {
		Events::keys[key] = true;
		Events::frames[key] = Events::current;
	}
	else if (action == GLFW_RELEASE) {
		Events::keys[key] = false;
		Events::frames[key] = Events::current;
	}
}

void mouse_callback(GLFWwindow* window, int key, int action, int mode) {
	if (action == GLFW_PRESS) {
		Events::keys[KEYS + key] = true;
		Events::frames[KEYS + key] = Events::current;
	}
	else if (action == GLFW_RELEASE) {
		Events::keys[KEYS + key] = false;
		Events::frames[KEYS + key] = Events::current;
	}
}

void cursor_pos_callback(GLFWwindow* window, double x, double y) {
	if (Events::cursor_locked) {
		Events::deltaX = x - Events::x;
		Events::deltaY = y - Events::y;
	}
	else {
		Events::cursor_started = true;
	}
	Events::x = x;
	Events::y = y;
}

int Events::init() {
	GLFWwindow* window = Window::window;
	keys = new bool[1032];
	frames = new unsigned int[1032];

	memset(keys, false, 1032 * sizeof(bool));
	memset(frames, 0, 1032 * sizeof(unsigned int));

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);

	return 0;
}

void Events::pullEvents() {
	current++;
	glfwPollEvents();
}

bool Events::isPressed(int key) {
	return keys[key];
}

bool Events::isJustPressed(int key) {
	return keys[key] && frames[key] == current;
}

bool Events::isClicked(int button) {
	return keys[KEYS + button];
}

bool Events::isJustClicked(int button) {
	return keys[KEYS+button] && frames[KEYS + button] == current;
}
