#ifndef APP_CLASS_H
#define APP_CLASS_H
#include "Window.h"
#include "Widgets.h"
#include "Shaders.h"
#include "Engine.h"
#include "Camera.h"
#include "DemoMesh.h"
#include "DrawPoint.h"
#include <stb/stb_image.h>
#include "PhysicsHandler.h"


namespace fs = std::experimental::filesystem;
class App
{
public:
	PhysicsHandler CollisionSupervisor;
	Window window;
	Widgets widget;
	Shaders shader;
	Shaders picking;
	Shaders outline;
	Shaders lighting;
	Engine engine;
	Camera camera;

	Mesh* polytope = new Mesh;

	glm::mat4 model = glm::mat4(1.0f);
	void Start_Up_App();
	void Run_App();
	App();
	~App();
	
	std::vector <Mesh*> All_Objects;
	std::vector<Mesh*> Temp_Objects;
	std::vector<points*> Particles;
	glm::vec3 contact;
	

	glm::vec3 normal = glm::vec3(1, 0, 0);
	float depth = 0.0f;
private:
	glm::mat4 CamMatrix = glm::mat4(1.0f);
	
	glm::vec3 Origin = glm::vec3(0, 0, 0);

	bool del = false;

	bool leftclicked = false;
	void Render_Scene();
	void Render_Paticles_Scene();
	void Render_Picking_Scene();
	void Initiate_Picking();
	void Check_If_Widget(ImGuiIO& io)
	{
		if (io.WantCaptureMouse || ImGui::IsAnyItemHovered())
		{
			IsWidget = true;
		}
		else
		{
			IsWidget = false;
		}
	}
	int Get_Object(glm::vec4 colorID);
	void Outline_Selected();
	void Render_Light();
	
	
	void Simplex(majik::MajikCollisions& resolver);
	
};
#endif
