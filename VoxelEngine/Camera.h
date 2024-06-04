#pragma once

#include <glm/glm.hpp>
class Camera
{
private:
	void updateVectors();
public:
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 rotation;

	float fov;
	glm::vec3 position;
	Camera(glm::vec3 position, float fov);

	glm::mat4 Projection;
	glm::mat4 getView();

	void rotate(float x, float y, float z);
	glm::mat4 getProjection();
};

