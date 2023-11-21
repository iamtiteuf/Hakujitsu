#ifndef POINTS_CLASS_H
#define POINTS_CLASS_H
#include "Global_Variables.h"

class points
{
public:
	

	points()
	{
		collisionProperties.shape = majik::Sphere;
		collisionProperties.raduis = 0.1f;
		
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void Drawpoint(glm::vec3& position,glm::mat4 CamMatrix,GLuint shaderProgram)
	{
		glUseProgram(shaderProgram);
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(VAO);
		

		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, position);
		
		model = glm::translate(model, position);
		
		glPointSize(10.0f);
		
		

		// Perform the operation here
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "CamMatrix"), 1, GL_FALSE, glm::value_ptr(CamMatrix));
		

		glDrawArrays(GL_POINTS, 0, 1);


		glBindVertexArray(0);
		
		glUseProgram(0);
		glEnable(GL_DEPTH_TEST);
	}
	void Draw(glm::mat4 CamMatrix, GLuint shaderProgram)
	{
		glUseProgram(shaderProgram);
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(VAO);
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, position);
		model = glm::translate(model, physicsProperties.position);
		glPointSize(10.0f);
		// Perform the operation here
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "CamMatrix"), 1, GL_FALSE, glm::value_ptr(CamMatrix));

		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);
		glUseProgram(0);
		glEnable(GL_DEPTH_TEST);
	}
	~points()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

	}
	glm::vec3 position = glm::vec3(1, 0, 0);
	majik::CollionProperties collisionProperties;
	majik::PhysicsProperties physicsProperties;
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	

	std::vector<Vertex> vertices =
	{
		// positions                    // colors           // normals                     // texUV
	   { glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(0.2f,  0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) }
	};
	
};
#endif // !POINTS_CLASS_H