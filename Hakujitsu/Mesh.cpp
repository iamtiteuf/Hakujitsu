#include "Mesh.h"
#include <stb/stb_image.h>


glm::vec3 Mesh::ConvertToWorld(glm::vec2 LineLoc)
{
	double mouseX, mouseY;
	glfwGetCursorPos(Main_Window, &mouseX, &mouseY);
	mouseX = LineLoc.x;
	mouseY = LineLoc.y;

	// Convert mouse coordinates to normalized device coordinates (NDC)
	int windowWidth, windowHeight;
	glfwGetFramebufferSize(Main_Window, &windowWidth, &windowHeight);
	float ndcX = (2.0f * mouseX) / windowWidth - 1.0f;
	float ndcY = 1.0f - (2.0f * mouseY) / windowHeight;

	// Create a ray in clip space
	glm::vec4 ndcPosition(ndcX, ndcY, 0.0f, 1.0f); // Set z to -1.0f instead of 0.0f

	// Transform the ray from clip space to eye space
	glm::mat4 inverseCameraMatrix = glm::inverse(g_Projection);
	glm::vec4 eyePosition = inverseCameraMatrix * ndcPosition;

	// Transform the ray from eye space to world space
	glm::mat4 inverseViewMatrix = glm::inverse(g_View); // Assuming g_View is the view matrix
	glm::vec4 worldPosition = inverseViewMatrix * eyePosition;

	// Extract the position from the worldPosition vector
	glm::vec3 normalizedWorldPosition = glm::vec3(worldPosition) / worldPosition.w;

	return normalizedWorldPosition;
}
glm::vec2 Mesh::ConvertToScreen(glm::vec3 worldPos)
{
	// Transform the world position to clip space
	glm::vec4 clipPos = g_Projection * g_View * glm::vec4(worldPos, 1.0f);

	// Perform perspective divide
	glm::vec3 ndcPos = glm::vec3(clipPos) / clipPos.w;

	// Perform viewport transformation
	int windowWidth, windowHeight;
	glfwGetFramebufferSize(Main_Window, &windowWidth, &windowHeight);
	glm::vec2 screenPos;
	screenPos.x = (ndcPos.x + 1.0f) / 2.0f * windowWidth;
	screenPos.y = (1.0f - ndcPos.y) / 2.0f * windowHeight;

	return screenPos;
}
Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	p_VAO = 0;
	p_VBO = 0;
	p_IBO = 0;
}

void Mesh::CreatePoint()
{
	double mouseX, mouseY;
	glfwGetCursorPos(Main_Window, &mouseX, &mouseY);
	vertices = { { ConvertToWorld(glm::vec2(mouseX, mouseY)), glm::vec3(1.0f, 0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) } };
	
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

void Mesh::CreatePoint3D()
{
	

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

void Mesh::CreateLine(std::vector<glm::vec2> LineLoc)
{
	
	sizeofline = LineLoc.size();
	//vertices.clear();
	if (endtask == false)
	{
		glm::vec3 pos = glm::vec3(0,0,0);
		vertices.clear();
		for (int i = 0; i < LineLoc.size(); i++)
		{
			vertices.push_back({ ConvertToWorld(LineLoc[i]), glm::vec3(1.0f, 0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) });
			Line_vertices.push_back(ConvertToWorld(LineLoc[i]));
			pos = pos + ConvertToWorld(LineLoc[i]);
		}
		pos = glm::vec3(pos.x/sizeofline, pos.y / sizeofline, pos.z / sizeofline);


		//physicalProperties.position = pos;
		endtask = true;
	}
	
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
void Mesh::CreateLine3D(std::vector<glm::vec3> LineLoc,glm::vec3 Color)
{

	sizeofline = LineLoc.size();
	
	
		
		vertices.clear();
		for (int i = 0; i < LineLoc.size(); i++)
		{
			vertices.push_back({LineLoc[i], Color, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) });
			Line_vertices.push_back(LineLoc[i]);
			
		}


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
void Mesh::DrawLine(GLuint& shaderProgram, glm::mat4& CamMatrix)
{
	
	
	if (VAO != 0)
	{
		glUseProgram(shaderProgram);
		glDisable(GL_DEPTH_TEST);
		glBindVertexArray(VAO);



		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, position);

		model = glm::translate(model, physicalProperties.position);


		glPointSize(10.0f);



		// Perform the operation here
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "CamMatrix"), 1, GL_FALSE, glm::value_ptr(CamMatrix));


		glDrawArrays(GL_LINE_STRIP, 0, sizeofline);


		glBindVertexArray(0);


		glUseProgram(0);
		glEnable(GL_DEPTH_TEST);
	}
}
void Mesh::DrawPoint(GLuint& shaderProgram, glm::mat4& CamMatrix)
{

	glUseProgram(shaderProgram);
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(VAO);



	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, physicalProperties.position);

	//model = glm::translate(model, position);

	glPointSize(pointsize);

	// Perform the operation here
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "CamMatrix"), 1, GL_FALSE, glm::value_ptr(CamMatrix));


	glDrawArrays(GL_POINTS, 0, 1);


	glBindVertexArray(0);


	glUseProgram(0);
	glEnable(GL_DEPTH_TEST);
}
void Mesh::CreateMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	this->indices = indices;
	this->vertices = vertices;
	
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);	

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load("11.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Load texture" << "\n";
	}
	else
	{
		std::cout << "Failed to load texture" << "\n";
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}
void Mesh::CustomCreateMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	this->p_indices = indices;
	this->p_vertices = vertices;
	

	glGenVertexArrays(1, &p_VAO);
	glBindVertexArray(p_VAO);

	glGenBuffers(1, &p_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indices.size() * sizeof(unsigned int), p_indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &p_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
	glBufferData(GL_ARRAY_BUFFER, p_vertices.size() * sizeof(Vertex), p_vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::RenderMesh(GLuint & shaderProgram, glm::mat4& CamMatrix)
{
	
	

	if (!physicalProperties.EditTransform)
	{
		transform.location = physicalProperties.position ;
		transform.rotation = physicalProperties.rotation ;
		transform.scale.x = physicalProperties.scale.x ;
		transform.scale.y = physicalProperties.scale.y ;
	    transform.scale.z = physicalProperties.scale.z ;
		
	}
	

	glUseProgram(shaderProgram);
	
	
	if (texc == false)
	{
		glUniform1i(glGetUniformLocation(shaderProgram, "tex0"), 0);
		texc == true;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, transform.location);
	model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, transform.scale);
	
	
	if(transform.scale != scale)
	{
		/*float s = std::max(transform.scale.x, transform.scale.y);
		s = std::max(transform.scale.z, s);
		s = s + 0.03f;
		MinA = s;
		collisionProperties.raduis = collisionProperties.raduis * s;*/

		endtask = false;
	}

	UpdateVertexPositions(model);
	


	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "CamMatrix"), 1, GL_FALSE, glm::value_ptr(CamMatrix));
	if (glGetUniformLocation(shaderProgram, "aColor") == 1)
	{
		glUniform4fv(glGetUniformLocation(shaderProgram, "aColor"), 1, glm::value_ptr(transform.colorID));
	}

	switch (Meshtype)
	{
	case 0:
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		break;
	case 1:
		glDrawArrays(GL_LINE_STRIP, 0, sizeofline);
		break;
	}
	


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	if (physicalProperties.DisplayCollider)
	{
		RenderCollisionShape(shaderProgram, CamMatrix);
	}
	if (collisionProperties.shape != 0)
	{
		points pot;
		pot.physicsProperties.position = collisionProperties.center + collisionProperties.normals[0] * 1.0f;
		pot.Draw(CamMatrix, shaderProgram);
	}

}
void Mesh::RenderCollisionShape(GLuint& shaderProgram, glm::mat4& CamMatrix)
{
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderProgram);

	glBindVertexArray(p_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_IBO);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, physicalProperties.position);
	model = glm::rotate(model, glm::radians(physicalProperties.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(physicalProperties.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(physicalProperties.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, physicalProperties.scale);
	if (glGetUniformLocation(shaderProgram, "scale") == -1)
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "CamMatrix"), 1, GL_FALSE, glm::value_ptr(CamMatrix));
		if (glGetUniformLocation(shaderProgram, "aColor") == 1)
		{
			glUniform4fv(glGetUniformLocation(shaderProgram, "aColor"), 1, glm::value_ptr(transform.colorID));
		}
	}

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUseProgram(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Mesh::ClearMesh()
{
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	if (p_VBO != 0)
	{
		glDeleteBuffers(1, &p_VBO);
		p_VBO = 0;
	}

	if (p_IBO != 0)
	{
		glDeleteBuffers(1, &p_IBO);
		p_IBO = 0;
	}

	if (p_VAO != 0)
	{
		glDeleteVertexArrays(1, &p_VAO);
		p_VAO = 0;
	}
	if (texture != 0)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}

}

Mesh::~Mesh()
{
	ClearMesh();
}
