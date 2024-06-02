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

	static int init();
	static void pullEvents();
};
