#pragma once

class GLFWwindow;

class Window
{
public:
	static int width;
	static int height;
	static GLFWwindow* window;

	static int init(int width, int height, const char* title);
	static void terminate();

	static bool isShouldClose();
	static void setShouldClose(bool flag);
	static void swap();
	static void setCursorMode(int mode);
};

