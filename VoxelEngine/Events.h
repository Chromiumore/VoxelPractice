#pragma once

#include "Window.h"

class Events
{
public:
	static bool* keys;
	static unsigned int* frames;
	static unsigned int current;
	static float deltaX;
	static float deltaY;
	static float x;
	static float y;
	static bool cursor_locked;
	static bool cursor_started;

	static bool isPressed(int key);
	static bool isJustPressed(int key);
	static bool isClicked(int button);
	static bool isJustClicked(int button);

	static int init();
	static void pullEvents();
};
