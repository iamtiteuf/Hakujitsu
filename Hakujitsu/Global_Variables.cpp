#include "Global_Variables.h"

float Background_Color[4][4] = { {0.1f,0.1f,0.1f,1.0f}, {0.4f,0.4f,0.4f,1.0f} ,{0.1f,0.1f,0.2f,1.0f},{0.1f,0.2f,0.2f,1.0f} };
GLFWwindow* Main_Window = nullptr;
bool IsWidget = false;
float Click_Timer = 0;
float MinA = 0;
float MinB = 0;
int g_current_object_index = 0;
bool Almost_Equal(glm::vec4 a, glm::vec4 b)
{
    double epsilon = 0.0001;
    bool check_diff = true;
    for (int i = 0; i < 4; i++)
    {
        if (std::abs(a[i] - b[i]) > epsilon)
        {
            check_diff = false;
        }
    }
    return check_diff;
}
bool Simulate_Physics = false;

glm::mat4 g_Projection = glm::mat4(1.0f);
glm::mat4 g_View = glm::mat4(1.0f);

glm::vec3 Oorigin = glm::vec3(0.0f,0.0f,0.0f);

WorkSpaceTypes Myspace = twoD;

void Debug_TimeCheck_Start()
{
		start_time = clock();	
}
void Debug_TimeCheck_End()
{
	end_time = clock();
	double time_taken = double(end_time - start_time) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by operation is : " << time_taken << "\n";
}
clock_t start_time;
clock_t end_time;