#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include "Global_Variables.h"
#include "ScriptingArea.h"
#include "DrawPoint.h"



class Mesh
{
public:
	int sizeofline;
	Mesh();
	float pointsize = 10.0f;
	glm::vec3 ConvertToWorld(glm::vec2 LineLoc);
	void CreateMesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
	void RenderMesh(GLuint& shaderProgram,glm::mat4 & CamMatrix);
	void RenderCollisionShape(GLuint& shaderProgram, glm::mat4& CamMatrix);
	void CustomCreateMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	void UpdateVertexColor()
	{
		for (auto& Vertex : vertices)
		{
			Vertex.color = transform.color;
		}
		CreateMesh(vertices, indices);
	}
	void ClearMesh();
	void CreateLine(std::vector<glm::vec2> LineLoc);
	void CreateLine3D(std::vector<glm::vec3> LineLoc,glm::vec3 Color);
	void DrawLine(GLuint& shaderProgram, glm::mat4& CamMatrix);
	void DrawPoint(GLuint& shaderProgram, glm::mat4& CamMatrix);
	void CreatePoint();
	void CreatePoint3D();
	void CreateGrid()
	{
		vertices.clear();
		float GS = 5;
		for (int i = -GS; i < GS; i++)
		{
			vertices.push_back({ glm::vec3(i * 10.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) });
			vertices.push_back({ glm::vec3(0.0f, 0.0f,i * 10.0f), glm::vec3(1.0f, 0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) });
		}

		sizeofline = 25;
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

	glm::vec2 ConvertToScreen(glm::vec3 worldPos);

	int Meshtype = 0;

	int wid = 1080; 
	int hei = 1080;
	int chan = 1;
	
	bool texc = false;
	
	

	~Mesh();
	ModelTransform transform;

	majik::PhysicsProperties physicalProperties;
	majik::CollionProperties collisionProperties;
	void OffSet_Location(glm::vec3 displacement)
	{
		if (!physicalProperties.Is_Static)
		{
			physicalProperties.position = physicalProperties.position + displacement;
		}
	}
	
	bool PhysicsBodyCreated = false;

	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices = { { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) } };
	int rings = 6;
	int sectors = 6;
	Script_Editor Comp_Script;
	bool show_script = false;

	std::vector<glm::vec2>Line_vertices;
	std::vector<glm::vec2>Brightness_values;
	bool Brightness_read = false;

	int GroupID = -1;
	int Lonely = 0;
private:

	

	

	bool endtask = false;
	glm::vec3 scale=glm::vec3(1,1,1);

	void UpdateVertexPositions(glm::mat4 model)
	{
	
		collisionProperties.center = physicalProperties.position;	
		if (!endtask)
		{
			float raduis = 0;
			
			collisionProperties.vertices.clear();
			for (int i = 0; i < vertices.size(); ++i)
			{
				Vertex& vertex = vertices[i];
				glm::vec4 pos = model * glm::vec4(vertex.position, 0.0f);
				
				collisionProperties.vertices.push_back(glm::vec3(pos));
				
			}
			for (int i = 0; i < collisionProperties.vertices.size(); i++)
			{
				raduis = std::max(glm::distance(collisionProperties.vertices[i], collisionProperties.center), raduis);
			}
			collisionProperties.raduis = raduis;
			endtask = true;
		}
		if (collisionProperties.shape != 0)
		{
			collisionProperties.normals.clear();
			collisionProperties.vertices.clear();
			for (int i = 0; i < vertices.size(); ++i)
			{
				Vertex& vertex = vertices[i];
				glm::vec4 pos = model * glm::vec4(vertex.position, 1.0f);
				glm::vec4 norm = model * glm::vec4(vertex.normal, 0.0f);
				collisionProperties.vertices.push_back(glm::vec3(pos));
				collisionProperties.normals.push_back(glm::normalize(glm::vec3(norm)));
			}
		}

	}
	

	std::vector<unsigned int> p_indices;
	std::vector<Vertex> p_vertices;

	GLuint VAO=0, VBO=0, IBO=0, p_VAO=0, p_VBO=0 , p_IBO,texture=0;
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

	
};
#endif // !MESH_CLASS_H