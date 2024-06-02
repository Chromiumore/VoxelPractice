#pragma once

#include <string>

class Shader
{
public:
	unsigned int id;

	Shader(unsigned int id);
	~Shader();

	void use();
};

// Загрузка шейдера с помощью файлов
extern Shader* load_shader(std::string vertexPath, std::string fragmentPath);
