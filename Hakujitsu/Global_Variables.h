#ifndef GLOBAL_CLASS_H
#define GLOBAL_CLASS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <math.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <glm/gtx/hash.hpp>
#include <GLFW/glfw3.h>

#include "PhysicsWorld.h"



extern GLFWwindow* Main_Window;
extern float Background_Color[4][4];
extern bool IsWidget;
extern float MinA;
extern float MinB;
extern float Click_Timer;
extern int g_current_object_index;

extern glm::mat4 g_Projection;
extern glm::mat4 g_View;

extern glm::vec3 Oorigin;

enum WorkSpaceTypes
{
	twoD = 0,
	threeD = 1
};

extern WorkSpaceTypes Myspace;

struct Texture
{
	unsigned int id;
	std::string type;
};
struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texUV;

};

struct ModelTransform
{
	std::string name = "Untitled";

	glm::vec3 location = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::vec3 color = glm::vec3(0.5, 0.5, 0.5);

	glm::vec4 colorID = glm::vec4(0.0f, 0.0f, 0.0f, 0.01f);
};

void Debug_TimeCheck_Start();
void Debug_TimeCheck_End();
extern clock_t start_time;
extern clock_t end_time;
extern bool Simulate_Physics;


bool Almost_Equal(glm::vec4 a, glm::vec4 b);

#endif
