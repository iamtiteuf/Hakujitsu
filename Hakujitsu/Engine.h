#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H
#include "Global_Variables.h"
class Engine
{
public:
	void Init(GLuint width, GLuint height, glm::vec3 position);
	~Engine();
	void EnableWriting();
	void DisableWriting();

	void Input();

	glm::vec4 Read_Pixels();
private:

	float Round_Read_Pixel(float value)
	{
		return roundf(value * 100) / 100;
	}

	GLuint width, height, m_pickingTexture, m_depthTexture, m_fbo;
	

	
};
#endif
