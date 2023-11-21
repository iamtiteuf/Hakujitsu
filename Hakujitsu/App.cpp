#include "App.h"
#include "SwarmDemo.h"
#define STB_IMAGE_IMPLEMENTATION




App::App()
{
	window.Create_Window();
	engine.Init(1920, 1080, glm::vec3(0, 0, 0));
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(Main_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();
	
	shader.Create_Shaders("vertexshader.glsl", "fragmentshader.glsl");
	picking.Create_Shaders("pickingvs.glsl", "pickingfs.glsl");
	outline.Create_Shaders("outlinevs.glsl", "outlinefs.glsl");
}
App::~App()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	ImPlot::DestroyContext();
	polytope->~Mesh();
	for (auto p : Temp_Objects)
	{
		delete p;
	}
	for (auto p : All_Objects)
	{
		delete p;
	}
	for (auto p : Particles)
	{
		delete p;
	}

	
}
void App::Start_Up_App()
{
	
	
}
void App::Run_App()
{
	Mesh* Grid = new Mesh;
	points* pot = new points;
	Particles.push_back(pot);
	points center;
	points particles;
 	
	glEnable(GL_DEPTH_TEST);
	ImGuiIO& io = ImGui::GetIO();
	
	//io.Fonts->AddFontDefault();
	const char * fontPath = "../ExternalLibs/freedom-font/VTCSundaykomix.ttf";
	
	ImFont* font = io.Fonts->AddFontFromFileTTF(fontPath, 18.0f);
	
	if (font)
	{
		std::cout << "Font loaded"<< "\n";
	}
	else
	{
		std::cout << "Font failed to load"<<"\n";
	}
	io.FontDefault = font;

	SwarmDemo Swarm;
	//Swarm.SpawnSatellite();
	Grid->CreateGrid();
	while (window.Window_Should_Close())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		CamMatrix = camera.Camera_Matrix();
		camera.Camera_Controls(true);
		
		
		//Grid->DrawLine(shader.shaderprogram, CamMatrix);
		Check_If_Widget(io);

		Initiate_Picking();
		
		//Swarm.RenderSatellites(CamMatrix, shader.shaderprogram);
		//Swarm.Drawtables();



		Outline_Selected();
		
		
		Render_Scene();
		//Render_Paticles_Scene();

		//center.Drawpoint(Oorigin, CamMatrix, shader.shaderprogram);

		/*for (int i = 0; i < All_Objects.size(); i++)
		{
			center.Drawpoint(All_Objects[i]->physicalProperties.position, CamMatrix, shader.shaderprogram);
			
		}
		center.Drawpoint(contact, CamMatrix, shader.shaderprogram);
		for (int i = 0; i < 1; i++)
		{
			particles.Draw(CamMatrix, shader.shaderprogram);

		}*/
	
		
		widget.Update(All_Objects, Temp_Objects);
		
		glfwPollEvents();
		glfwSwapBuffers(Main_Window);
	}
	delete Grid;
}

void App::Render_Scene()
{
	for (int i = 0; i < Temp_Objects.size(); i++)
	{
		Temp_Objects[i]->DrawPoint(shader.shaderprogram, CamMatrix);
	}
	//CollisionSupervisor.StartSupervision(All_Objects);

	for (int i = 0; i < All_Objects.size(); i++)
	{
		
		majik::MajikCollisions resolver;
		//All_Objects[i]->transform.color = glm::vec3(0, 1, 0);
		//All_Objects[i]->UpdateVertexColor();
		
		
			for (int j = i + 1; j < All_Objects.size(); j++)
			{
				if (i != j)
				{
					glm::vec3 normal = glm::vec3(0, 0, 0);
					float depth = 0;
					if (Myspace == 1)
					{
						if (Simulate_Physics)
						{
							majik::PhysicsWorld::step(All_Objects[i]->physicalProperties, 0.006f);

							if (resolver.GJK(All_Objects[i]->collisionProperties, All_Objects[j]->collisionProperties, normal, depth))
							{

								//All_Objects[j]->transform.color = glm::vec3(0.5, 0, 0.5);
								//All_Objects[j]->UpdateVertexColor();

								//Simplex(resolver);
								//majik::PhysicsWorld::Collision_Resolve(All_Objects[i]->physicalProperties, All_Objects[j]->physicalProperties, 0.006f);
								All_Objects[i]->physicalProperties.velocity = glm::vec3(0, 0, 0);
								All_Objects[j]->physicalProperties.velocity = glm::vec3(0, 0, 0);
								All_Objects[i]->OffSet_Location(-normal * depth / 2.0f);
								All_Objects[j]->OffSet_Location(normal * depth / 2.0f);

							}

						}
					}
					else if (Myspace == 0)
					{
						if (Simulate_Physics)
						{
							majik::PhysicsWorld::step(All_Objects[i]->physicalProperties, 0.006f);

							if (resolver.ToD_Particles_Collision(All_Objects[0]->collisionProperties, All_Objects[1]->collisionProperties, normal, depth))
							{
								majik::PhysicsWorld::Collision_Resolve2D(All_Objects[0]->physicalProperties, All_Objects[1]->physicalProperties, normal, depth, 0.006f);

								MinA = depth;
								MinB = normal.y;

							}

						}
					}

					//Simplex(resolver);
				}

			}
		
		
		All_Objects[i]->RenderMesh(shader.shaderprogram, CamMatrix);
		if (!del)
		{
			del = true;
			std::cout << "x : " << Extra_Math::math::ConvertToScreen(All_Objects[i]->transform.location).x << "\n";
			std::cout << "y : " << Extra_Math::math::ConvertToScreen(All_Objects[i]->transform.location).y << "\n";
		}
		//All_Objects[i]->DrawLine(shader.shaderprogram, CamMatrix);
	}	
	
}
void App::Render_Picking_Scene()
{
	for (int i = 0; i < All_Objects.size(); i++)
	{
		All_Objects[i]->RenderMesh(picking.shaderprogram, CamMatrix);
	}
}
void App::Initiate_Picking()
{
	if (glfwGetMouseButton(Main_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !IsWidget)
	{
		if (!leftclicked)
		{
			Render_Scene();
			Render_Picking_Scene();
			engine.EnableWriting();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			//Render_Scene();
			Render_Picking_Scene();
			engine.DisableWriting();
			g_current_object_index = Get_Object(engine.Read_Pixels());

			leftclicked = true;
		}

	}
	else if (glfwGetMouseButton(Main_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		if (leftclicked)
		{
			leftclicked = false;
		}

	}
}
int App::Get_Object(glm::vec4 colorID)
{
	int e = 0;
	for (int i = 0; i < All_Objects.size(); i++)
	{
		if (Almost_Equal(All_Objects[i]->transform.colorID, colorID))
		{
			e = i;
			break;
			
		}
	}
	return e;

}
void App::Outline_Selected()
{
	if (All_Objects.size() > 0)
	{
		// Enable depth testing
		//shader.useprogram();
		glEnable(GL_DEPTH_TEST);

		// Set the depth function to GL_LEQUAL
		glDepthFunc(GL_LEQUAL);

		// Enable stencil testing
		glEnable(GL_STENCIL_TEST);

		// Configure the stencil buffer
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFF);  // Make sure we can update the stencil buffer

		// Set the stencil and depth functions before drawing the object
		glStencilFunc(GL_ALWAYS, 1, 0xFF);

		// Draw the object regularly, this will populate the stencil buffer and depth buffer correctly
		
		All_Objects[g_current_object_index]->RenderMesh(shader.shaderprogram, CamMatrix);

		
		//shader.disableprogram();
		//mesh.Draw(All_Objects[g_current_object_index]);
		//outline.useprogram();
		// Now we configure the stencil test for the outline drawing
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);  // Make sure we don't update the stencil buffer while drawing the outline
		glDisable(GL_DEPTH_TEST); // Disable the depth test so the outline is drawn on top

		// Draw the outline using the outline shader, this will only affect pixels where the stencil buffer is not 1 (the object)

		
		All_Objects[g_current_object_index]->RenderMesh(outline.shaderprogram, CamMatrix);
		
		//mesh.DrawForOutline(All_Objects[g_current_object_index]);

		// Reset the stencil mask and depth function
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);  // Reset depth testing
		glClear(GL_STENCIL_BUFFER_BIT);
		glDisable(GL_STENCIL_TEST);
		//outline.disableprogram();
	}
	
}
void App::Simplex(majik::MajikCollisions& resolver)
{
	points Center;
	/*for (int j = 0; j < resolver.polytope.size(); j++)
	{
		Center.Drawpoint(resolver.polytope[j], CamMatrix, shader.shaderprogram);

	}*/
	contact = resolver.contact;
	Center.Drawpoint(resolver.contact,CamMatrix, shader.shaderprogram);
	std::cout << resolver.contact.x << "\n";
	std::cout << resolver.contact.y << "\n";
	std::cout << resolver.contact.z << "\n";
	std::vector<Vertex> vert;
	for (int i = 0; i < resolver.polytope.size(); ++i)
	{
		vert.push_back({ glm::vec3(0,0,0),glm::vec3(1,0,1),glm::vec3(0,0,0),glm::vec2(0,0) });
		vert[i].position = resolver.polytope[i];

	}
	std::vector<unsigned int> ind;
	ind = resolver.facess;
	polytope->CreateMesh(vert, ind);
	for (int i = 0; i < resolver.polytope.size(); ++i)
	{
		vert[i].color = glm::vec3(1, 1, 1);
		vert[i].position = resolver.polytope[i];

	}
	polytope->physicalProperties.DisplayCollider = true;
	polytope->CustomCreateMesh(vert, ind);
	polytope->RenderMesh(shader.shaderprogram, CamMatrix);
	
}
void App::Render_Paticles_Scene()
{
	majik::MajikCollisions resolver;
	glm::vec3 p_Normal;
	float p_Depth;

	for (int i = 0; i < Particles.size(); i++)
	{
		for (int j = 0; j < Particles.size(); j++)
		{
			if (i != j)
			{
				if (resolver.ToD_Particles_Collision(Particles[i]->collisionProperties, Particles[j]->collisionProperties, p_Normal, p_Depth))
				{

				}
			}
		}

	}
	for (auto P : Particles)
	{
		P->Draw(CamMatrix, shader.shaderprogram);
		majik::Particles::Step(P->physicsProperties, 0.006);
	}
}