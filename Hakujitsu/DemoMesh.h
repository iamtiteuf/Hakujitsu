#pragma once
#include "Global_Variables.h"
class Demo_mesh
{
public:
	void Demo_int()
	{

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glBufferData(GL_ARRAY_BUFFER, cube_vert.size() * sizeof(Vertex), cube_vert.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube_ing.size() * sizeof(unsigned int), cube_ing.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));


		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind
	}
	void Draw()
	{
		Demo_int();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, cube_ing.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	~Demo_mesh()
	{

			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &IBO);
			glDeleteVertexArrays(1, &VAO);
	
	}
	std::string name = "Untitled";
	glm::vec3 location = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::vec4 colorID = glm::vec4(0, 0, 0, 0.01f);

	void Set_Model(GLuint& shaderProgram)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, location);
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, scale);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		if (glGetUniformLocation(shaderProgram, "aColor") == 1)
		{
			std::cout << "hello";
			glUniform4fv(glGetUniformLocation(shaderProgram, "aColor"), 1, glm::value_ptr(colorID));
		}
		
	}
private:
	std::vector<Vertex> cube_vert =
	{
		// positions          // colors           // normals         // texUV
	 { glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0, 1, 0), glm::vec3(-1,-1,-1), glm::vec2(0, 0) },
	 { glm::vec3(-0.5,-0.5,0.5), glm::vec3(0, 1, 0), glm::vec3(-1,-1, 1), glm::vec2(1, 0) },
	 { glm::vec3(-0.5,0.5,-0.5), glm::vec3(0, 1, 0), glm::vec3(-1, 1,-1), glm::vec2(0, 1) },
	 { glm::vec3(-0.5,0.5,0.5),  glm::vec3(0, 1, 0), glm::vec3(-1, 1, 1), glm::vec2(1, 1) },
	 { glm::vec3(0.5,-0.5,-0.5), glm::vec3(0, 1, 0), glm::vec3(1,-1,-1),  glm::vec2(1, 0) },
	 { glm::vec3(0.5,-0.5,0.5),  glm::vec3(0, 1, 0), glm::vec3(1,-1, 1),  glm::vec2(0, 0) },
	 { glm::vec3(0.5,0.5,-0.5),  glm::vec3(0, 1, 0), glm::vec3(1, 1,-1),  glm::vec2(1, 1) },
	 { glm::vec3(0.5,0.5,0.5),   glm::vec3(0, 1, 0), glm::vec3(1, 1, 1),  glm::vec2(0, 1) }
	};
	std::vector<unsigned int> cube_ing =
	{
	   0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7, // front 
	   1, 5, 3, 5, 3, 7, 0, 4, 2, 4, 2, 6, // back 
	   0, 1, 4, 1, 4, 5, 2, 3, 6, 3, 6, 7  // sides
	};
	std::vector <Vertex> tri_vert =
	{
		// positions                             // colors           // normals                     // texUV
	   { glm::vec3(0.0f,  0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) },//top 0
	   { glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },//b1 1
	   { glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) },//b11 2
	   { glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },//b2 3
	   { glm::vec3(0.5f, -0.5f, -0.5f),   glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) }//b22 4
	};
	std::vector<unsigned int> tri_ing =
	{
		0, 1, 2,
		0,1,3,
		0,2,4,
		0,3,4,
		1,2,3,
		4,2,3
	};
	GLuint VAO, VBO, IBO;
	GLuint G_VAO, G_VBO, G_IBO;

};
