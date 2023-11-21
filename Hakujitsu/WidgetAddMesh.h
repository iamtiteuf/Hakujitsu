#ifndef WIDGET_ADDMESH_CLASS_H
#define WIDGET_ADDMESH_CLASS_H
#include "Global_Variables.h"
#include "implot.h"
#include "gui/imgui.h"
#include "gui/imgui_impl_glfw.h"
#include "gui/imgui_impl_opengl3.h"
#include "gui/imgui_stdlib.h"
#include "gui/imgui_internal.h"
#include "Mesh.h"
#include "Extra_Math.h"

class WidgetAddMesh
{
private:
	int brightness_points_amt = 5;
	int display_w = 0;
	int display_h = 0;

	bool leftclic = false;
	bool line_in_use = false;
	std::vector<glm::vec2> LineLoc;

	void DrawLine(std::vector<Mesh*>& All_Objects, std::vector<Mesh*>& Temp_Objects)
	{

		if (line_in_use)
		{
			float size = Temp_Objects.size();
			ImGui::Begin("Line Settings");

			ImGui::InputFloat("Number of points", &size);

			if (ImGui::Button("Draw Line"))
			{
				if (size > 1)
				{
					Mesh* mesh = new Mesh;
					mesh->Meshtype = 1;
					t_num = t_num + 1;
					SetVertices(mesh->transform.color);
					std::string t_num_s = std::to_string(t_num);
					mesh->transform.name = "Line ";
					mesh->transform.name = mesh->transform.name + t_num_s;
					mesh->CreateLine(LineLoc);
					SetVertices(glm::vec3(1, 0, 0));
					//mesh->CustomCreateMesh(tri_3vert, tri_3ing);
					mesh->physicalProperties.DisplayCollider = true;
					mesh->transform.colorID = nextColorID;
					mesh->collisionProperties.shape = majik::Polygon;
					All_Objects.push_back(mesh);
					Temp_Objects.clear();
					line_in_use = false;
				}

			}

			if (glfwGetMouseButton(Main_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !IsWidget)
			{
				if (!leftclic)
				{
					double mouseX, mouseY;
					glfwGetCursorPos(Main_Window, &mouseX, &mouseY);
					std::cout << "mousex: " << mouseX << "\n";
					std::cout << "mousey: " << mouseY << "\n";
					LineLoc.push_back(glm::vec2(mouseX, mouseY));
					Mesh* mesh = new Mesh;
					SetVertices(mesh->transform.color);

					mesh->CreatePoint();
					SetVertices(glm::vec3(1, 0, 0));
					Temp_Objects.push_back(mesh);

					leftclic = true;
				}

			}
			if (glfwGetMouseButton(Main_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
			{
				if (leftclic)
				{

					leftclic = false;

				}

			}
			ImGui::End();
		}
	}

	void SetVertices(glm::vec3 VertColor = glm::vec3(0., 0, 0))
	{
		cube_3vert =
		{
			// positions          // colors           // normals         // texUV
		 { glm::vec3(-0.5,-0.5,-0.5), VertColor , glm::vec3(-1,-1,-1), glm::vec2(0, 0) },
		 { glm::vec3(-0.5,-0.5,0.5), VertColor , glm::vec3(-1,-1, 1), glm::vec2(1, 0) },
		 { glm::vec3(-0.5,0.5,-0.5),  VertColor , glm::vec3(-1, 1,-1), glm::vec2(0, 1) },
		 { glm::vec3(-0.5,0.5,0.5),  VertColor , glm::vec3(-1, 1, 1), glm::vec2(1, 1) },
		 { glm::vec3(0.5,-0.5,-0.5),  VertColor , glm::vec3(1,-1,-1),  glm::vec2(1, 0) },
		 { glm::vec3(0.5,-0.5,0.5),   VertColor , glm::vec3(1,-1, 1),  glm::vec2(0, 0) },
		 { glm::vec3(0.5,0.5,-0.5),   VertColor , glm::vec3(1, 1,-1),  glm::vec2(1, 1) },
		 { glm::vec3(0.5,0.5,0.5),    VertColor , glm::vec3(1, 1, 1),  glm::vec2(0, 1) }
		};
		cube_3ing =
		{
		   0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7, // front 
		   1, 5, 3, 5, 3, 7, 0, 4, 2, 4, 2, 6, // back 
		   0, 1, 4, 1, 4, 5, 2, 3, 6, 3, 6, 7  // sides
		};
		tri_3vert =
		{
			// positions                    // colors           // normals                     // texUV
		   { glm::vec3(0.000f,  0.500f, 0.000f),   VertColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) },//top 0
		   { glm::vec3(-0.500f, -0.500f, 0.500f),  VertColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },//b1 1
		   { glm::vec3(0.500f, -0.500f, 0.500f),   VertColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) },//b11 2
		   { glm::vec3(-0.500f, -0.500f, -0.500f), VertColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },//b2 3
		   { glm::vec3(0.500f, -0.500f, -0.500f),   VertColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) }//b22 4
		};
		tri_3ing =
		{
			0, 1, 2,
			0,1,3,
			0,2,4,
			0,3,4,
			1,2,3,
			4,2,3
		};
		pla_3vert =
		{
			{ glm::vec3(0.500f,  0.000f, 0.500f), VertColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1, 1) },//0
			{ glm::vec3(0.500f,  0.000f, -0.500f), VertColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0, 1) },//1
			{ glm::vec3(-0.500f,  0.000f, 0.500f), VertColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1, 0) },//2
			{ glm::vec3(-0.500f,  0.000f, -0.500f), VertColor, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0, 0) }//3
		};
		pla_3ing =
		{
			0,2,1,
			2,3,1
		};

		cube_2vert =
		{
			// positions          // colors           // normals         // texUV
			{ glm::vec3(-0.5, -0.5, 0), VertColor, glm::vec3(0,-1, 0), glm::vec2(1, 0) },//0
			{ glm::vec3(-0.5, 0.5, 0), VertColor, glm::vec3(1, 0, 0), glm::vec2(1, 1) },//1
			{ glm::vec3(0.5, -0.5, 0), VertColor, glm::vec3(-1, 0, 0), glm::vec2(0, 0) },//2
			{ glm::vec3(0.5, 0.5, 0), VertColor, glm::vec3(0, 1, 0), glm::vec2(0, 1) },//3
		};
		cube_2ing =
		{
			0,2,1,
			2,3,1
		};
		tri_2vert =
		{
			// positions          // colors           // normals         // texUV
			{ glm::vec3(0, 0.5, 0), VertColor, glm::vec3(0.6,0.8, 0), glm::vec2(1, 0) },//0
			{ glm::vec3(-0.5, -0.5, 0), VertColor, glm::vec3(0, -1, 0), glm::vec2(1, 1) },//1
			{ glm::vec3(0.5, -0.5, 0), VertColor, glm::vec3(-0.6, 0.8, 0), glm::vec2(0, 0) }//2

		};
		tri_2ing =
		{
			0,1,2
		};

		line_2vert =
		{
		 { glm::vec3(1,1,0), VertColor , glm::vec3(-1,-1,-1), glm::vec2(0, 0)},
		 { glm::vec3(0,0,0), VertColor , glm::vec3(-1,-1, 1), glm::vec2(1, 0) }
		};
	}

	std::vector<Vertex> sphere_3vert;
	std::vector<unsigned int> sphere_3ing;

	std::vector<Vertex> cube_3vert;
	std::vector<unsigned int> cube_3ing;

	std::vector <Vertex> tri_3vert;
	std::vector<unsigned int> tri_3ing;

	std::vector <Vertex> pla_3vert;
	std::vector<unsigned int> pla_3ing;

	std::vector <Vertex> cir_2vert;
	std::vector<unsigned int> cir_2ing;

	std::vector<Vertex> cube_2vert;
	std::vector<unsigned int> cube_2ing;

	std::vector<Vertex> tri_2vert;
	std::vector<unsigned int> tri_2ing;

	std::vector<Vertex> line_2vert;

	void generateCircle(float radius, unsigned int sectors, glm::vec3 color, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
		float const S = 1.0f / (float)(sectors - 1);


		vertices.resize(sectors);
		std::vector<Vertex>::iterator v = vertices.begin();

		for (unsigned int s = 0; s < sectors; ++s) {
			float const angle = 2 * glm::pi<float>() * s * S;
			float const x = cos(angle);
			float const y = sin(angle);

			v->position = glm::vec3(x, y, 0) * radius;
			v->color = color;
			v->texUV = glm::vec2(x, y);
			v++;
		}

		indices.resize((sectors - 1) * 3);
		std::vector<unsigned int>::iterator i = indices.begin();
		for (unsigned int s = 0; s < sectors - 1; ++s) {
			*i++ = 0;
			*i++ = s + 1;
			*i++ = s + 2;
		}
	}
	void generateSphere(float radius, unsigned int rings, unsigned int sectors, glm::vec3 color, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
		float const R = 1.0f / (float)(rings - 1);
		float const S = 1.0f / (float)(sectors - 1);

		vertices.resize(rings * sectors);
		std::vector<Vertex>::iterator v = vertices.begin();

		for (unsigned int r = 0; r < rings; ++r) {
			for (unsigned int s = 0; s < sectors; ++s) {
				float const y = sin(-glm::pi<float>() / 2 + glm::pi<float>() * r * R);
				float const x = cos(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);
				float const z = sin(2 * glm::pi<float>() * s * S) * sin(glm::pi<float>() * r * R);

				v->position = glm::vec3(x, y, z) * radius;
				v->color = color;
				v->texUV = glm::vec2(s * S, r * R);
				v++;
			}
		}

		indices.resize(rings * sectors * 6);
		std::vector<unsigned int>::iterator i = indices.begin();
		for (unsigned int r = 0; r < rings - 1; ++r) {
			for (unsigned int s = 0; s < sectors - 1; ++s) {
				*i++ = r * sectors + s;
				*i++ = r * sectors + (s + 1);
				*i++ = (r + 1) * sectors + (s + 1);
				*i++ = (r + 1) * sectors + s;
				*i++ = r * sectors + s;
				*i++ = (r + 1) * sectors + (s + 1);
			}
		}
	}

	bool fatfps = true;
	double previousTime;
	int frameCount;
	float FPS;
	void CalFps()
	{
		if (fatfps)
		{
			previousTime = glfwGetTime();
			frameCount = 0;
			fatfps = false;
		}

		frameCount++;
		double currentTime = glfwGetTime();
		if (currentTime - previousTime >= 1.0)
		{
			FPS = (float)frameCount;

			frameCount = 0;
			previousTime = currentTime;
		}

		std::string fps = std::to_string(FPS);

		ImGui::Text(fps.c_str());
		ImGui::InputFloat("MinA", &MinA);
		ImGui::InputFloat("MinB", &MinB);

	}

	bool AddUniqueColor()
	{
		if (freeColorID.size() > 0)
		{
			nextColorID = freeColorID.back();
			freeColorID.pop_back();
			return true;
		}
		else
		{
			if (intermediateID[3] < 1)
			{
				intermediateID[3] = intermediateID[3] + 0.1f;
				nextColorID = intermediateID;
				return true;
			}
			else if (nextColorID[2] < 1)
			{
				intermediateID[2] = intermediateID[2] + 0.1f;
				nextColorID = intermediateID;
				return true;
			}
			else if (intermediateID[1] < 1)
			{
				intermediateID[1] = intermediateID[1] + 0.1f;
				nextColorID = intermediateID;
				return true;
			}
			else if (intermediateID[0] < 1)
			{
				intermediateID[0] = intermediateID[0] + 0.1f;
				nextColorID = intermediateID;
				return true;
			}
			else
			{
				std::cout << "Out of picking color";
				return false;
			}
		}

	}
	glm::vec4 nextColorID = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	glm::vec4 intermediateID = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	std::vector<glm::vec4> freeColorID;
	int c_num = 0;
	int t_num = 0;


public:
	void DrawAll(std::vector<Mesh*>& All_Objects, std::vector<Mesh*>& Temp_Objects);
	void AddCube(std::vector<Mesh*>& All_Objects)
	{
		if (ImGui::Button("Cube"))
		{
			if (AddUniqueColor())
			{
				Mesh* mesh = new Mesh;
				c_num = c_num + 1;
				std::string c_num_s = std::to_string(c_num);
				mesh->transform.name = "cube ";

				mesh->transform.name = mesh->transform.name + c_num_s;

				SetVertices(mesh->transform.color);
				mesh->CreateMesh(cube_3vert, cube_3ing);
				SetVertices(glm::vec3(1, 0, 0));
				mesh->CustomCreateMesh(cube_3vert, cube_3ing);
				mesh->physicalProperties.DisplayCollider = true;
				mesh->transform.colorID = nextColorID;
				mesh->collisionProperties.shape = majik::Polygon;

				All_Objects.push_back(mesh);
			}
		}
	}
	void AddTriangle(std::vector<Mesh*>& All_Objects)
	{
		if (ImGui::Button("Triangle"))
		{
			if (AddUniqueColor())
			{
				Mesh* mesh = new Mesh;
				c_num = c_num + 1;
				std::string c_num_s = std::to_string(c_num);
				mesh->transform.name = "triangle ";

				mesh->transform.name = mesh->transform.name + c_num_s;

				SetVertices(mesh->transform.color);
				mesh->CreateMesh(tri_2vert, tri_2ing);
				SetVertices(glm::vec3(1, 0, 0));
				mesh->CustomCreateMesh(tri_2vert, tri_2ing);
				mesh->physicalProperties.DisplayCollider = true;
				mesh->transform.colorID = nextColorID;
				mesh->collisionProperties.shape = majik::Polygon;

				All_Objects.push_back(mesh);

			}
		}
	}
	void AddBox(std::vector<Mesh*>& All_Objects)
	{

		if (ImGui::Button("Box"))
		{
			if (AddUniqueColor())
			{
				Mesh* mesh = new Mesh;
				c_num = c_num + 1;
				std::string c_num_s = std::to_string(c_num);
				mesh->transform.name = "box ";

				mesh->transform.name = mesh->transform.name + c_num_s;

				SetVertices(mesh->transform.color);
				mesh->CreateMesh(cube_2vert, cube_2ing);
				SetVertices(glm::vec3(1, 0, 0));
				mesh->CustomCreateMesh(cube_2vert, cube_2ing);
				mesh->physicalProperties.DisplayCollider = true;
				mesh->transform.colorID = nextColorID;
				mesh->collisionProperties.shape = majik::Polygon;
				All_Objects.push_back(mesh);
			}
		}
	}
	void AddPlane(std::vector<Mesh*>& All_Objects)
	{
		if (ImGui::Button("plane"))
		{
			if (AddUniqueColor())
			{
				Mesh* mesh = new Mesh;
				t_num = t_num + 1;
				SetVertices(mesh->transform.color);
				std::string t_num_s = std::to_string(t_num);
				mesh->transform.name = "Plane ";
				mesh->transform.name = mesh->transform.name + t_num_s;
				mesh->CreateMesh(pla_3vert, pla_3ing);
				SetVertices(glm::vec3(1, 0, 0));
				mesh->CustomCreateMesh(pla_3vert, pla_3ing);
				mesh->physicalProperties.DisplayCollider = true;
				mesh->transform.colorID = nextColorID;
				mesh->collisionProperties.shape = majik::Plane;
				All_Objects.push_back(mesh);

			}
		}

	}
	void AddPyramide(std::vector<Mesh*>& All_Objects)
	{
		if (ImGui::Button("pyramid"))
		{
			if (AddUniqueColor())
			{
				Mesh* mesh = new Mesh;
				t_num = t_num + 1;
				SetVertices(mesh->transform.color);
				std::string t_num_s = std::to_string(t_num);
				mesh->transform.name = "Pyramid ";
				mesh->transform.name = mesh->transform.name + t_num_s;
				mesh->CreateMesh(tri_3vert, tri_3ing);
				SetVertices(glm::vec3(1, 0, 0));
				mesh->CustomCreateMesh(tri_3vert, tri_3ing);
				mesh->physicalProperties.DisplayCollider = true;
				mesh->transform.colorID = nextColorID;
				mesh->collisionProperties.shape = majik::Polygon;
				All_Objects.push_back(mesh);
			}
		}
	}
	void AddSphere(std::vector<Mesh*>& All_Objects)
	{
		if (ImGui::Button("Sphere"))
		{
			if (AddUniqueColor())
			{
				Mesh* mesh = new Mesh;
				t_num = t_num + 1;
				std::string t_num_s = std::to_string(t_num);
				mesh->transform.name = "sphere ";
				mesh->transform.name = mesh->transform.name + t_num_s;
				generateSphere(mesh->collisionProperties.raduis, mesh->rings, mesh->sectors, mesh->transform.color, sphere_3vert, sphere_3ing);
				mesh->CreateMesh(sphere_3vert, sphere_3ing);
				mesh->collisionProperties.shape = majik::Sphere;
				mesh->transform.colorID = nextColorID;

				generateSphere(mesh->collisionProperties.raduis, mesh->rings, mesh->sectors, glm::vec3(1, 0, 0), sphere_3vert, sphere_3ing);
				mesh->CustomCreateMesh(sphere_3vert, sphere_3ing);
				mesh->physicalProperties.DisplayCollider = true;
				All_Objects.push_back(mesh);



			}
		}
	}
	void AddCircle(std::vector<Mesh*>& All_Objects)
	{

		if (ImGui::Button("Circle"))
		{
			if (AddUniqueColor())
			{
				Mesh* mesh = new Mesh;
				t_num = t_num + 1;
				std::string t_num_s = std::to_string(t_num);
				mesh->transform.name = "cirlce";
				mesh->transform.name = mesh->transform.name + t_num_s;
				generateCircle(mesh->collisionProperties.raduis, mesh->rings, mesh->transform.color, cir_2vert, cir_2ing);
				mesh->CreateMesh(cir_2vert, cir_2ing);
				mesh->collisionProperties.shape = majik::Circle;
				mesh->transform.colorID = nextColorID;

				generateCircle(mesh->collisionProperties.raduis, mesh->rings, glm::vec3(1, 0, 0), cir_2vert, cir_2ing);
				mesh->CustomCreateMesh(cir_2vert, cir_2ing);
				mesh->physicalProperties.DisplayCollider = true;
				All_Objects.push_back(mesh);

			}
		}
	}
	void AddLine(std::vector<Mesh*>& All_Objects)
	{

		if (ImGui::Button("Line"))
		{
			if (AddUniqueColor())
			{
				line_in_use = true;
			}
		}
	}
	void Remove(std::vector<Mesh*>& All_Objects)
	{

		if (ImGui::Button("Remove"))
		{
			if (All_Objects.size() > 0)
			{
				freeColorID.push_back(All_Objects[g_current_object_index]->transform.colorID);
				delete All_Objects[g_current_object_index];
				All_Objects.erase(All_Objects.begin() + g_current_object_index);
				g_current_object_index = 0;
			}
		}
	}
           
	void EditTransform(std::vector<Mesh*>& All_Objects);
 

};
#endif
