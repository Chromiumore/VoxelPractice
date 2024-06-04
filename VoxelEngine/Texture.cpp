#include "Texture.h"

#include <iostream>
#include <glew.h>
#include <png.h>
#include <zlib.h>

Texture::Texture(unsigned int id, int width, int height) : id(id), width(width), height(height) {}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}
