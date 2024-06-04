#pragma once

#include <stdlib.h>

class Mesh
{
private:
	unsigned int vao;
	unsigned int vbo;
	size_t vertices;
public:
	Mesh(const float* buffer, size_t, const int* attrs);
	~Mesh();

	void draw(unsigned int primitive);

};

