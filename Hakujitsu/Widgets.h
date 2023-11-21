#ifndef WIDGETS_CLASS_H
#define WIDGETS_CLASS_H
#include "Global_Variables.h"
#include "implot.h"
#include "gui/imgui.h"
#include "gui/imgui_impl_glfw.h"
#include "gui/imgui_impl_opengl3.h"
#include "gui/imgui_stdlib.h"
#include "gui/imgui_internal.h"
#include "Mesh.h"
#include "Extra_Math.h"
#include "WidgetAddMesh.h"



class Widgets
{
public:
	void Window_1_Half(std::vector<Mesh*>& All_Objects);
	void Update(std::vector<Mesh*> &All_Objects, std::vector<Mesh*> &Temp_Objects);
	void ObjectDetails(std::vector<Mesh*>& All_Objects);
	void MainMenuBar();
	
	void SceneManager(std::vector<Mesh*>& All_Objects);
	void ObjectPhysics(std::vector<Mesh*>& All_Objects);
	void AddPhysicsSetting(std::vector<Mesh*>& All_Objects);
	void RightClick(std::vector<Mesh*>& All_Objects);
	void Timeline(std::vector<Mesh*>& All_Objects);
	void CustomPhysics(std::vector<Mesh*>& All_Objects);
	

private:
	WidgetAddMesh MeshControl;
	
	int c_num = 0;
	int t_num = 0;
	int display_w;
	int display_h;
	std::string force = "None";
	
	

	



};
#endif
