#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include "Global_Variables.h"
#include "Shaders.h"

class Camera
{
public:
	glm::mat4 Camera_Matrix();
	void Camera_Controls(bool IsActive);
private:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	glm::vec3 position = glm::vec3(0,0,100.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	double mouseX2;
	double mouseY2;
	int width, height;

	bool firstClick = false;
	
	bool done = false;
	float speed = 0.1f;
	float sensitivity = 100.0f;

};
#endif
