#ifndef SHADERS_CLASS_H
#define SHADERS_CLASS_H
#include "Global_Variables.h"
class Shaders
{
public:
	void Create_Shaders(const char* vert, const char* frag);



	void useprogram() { glUseProgram(shaderprogram); }
	void disableprogram() { glUseProgram(0); }

	void setMat4fv(const char* uniform, glm::mat4 matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
	}// check if not working

	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(shaderprogram, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(shaderprogram, name.c_str()), 1, &value[0]);
	}


	GLuint shaderprogram;

	~Shaders();
};
#endif
