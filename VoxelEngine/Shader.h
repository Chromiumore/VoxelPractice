#pragma once

#include <string>
#include <glm\glm.hpp>

class Shader
{
public:
	unsigned int id;

	Shader(unsigned int id);
	~Shader();

	void use();
	void uniformMatrix(std::string name, glm::mat4 model);
};

// �������� ������� � ������� ������
extern Shader* load_shader(std::string vertexPath, std::string fragmentPath);
