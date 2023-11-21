#include "Widgets.h"



void Widgets::Update(std::vector<Mesh*> &All_Objects, std::vector<Mesh*> &Temp_Objects)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
   
   //static bool show_demo_window = true;
   //ImGui::ShowDemoWindow(&show_demo_window);

    MeshControl.DrawAll(All_Objects, Temp_Objects);
    
  

  
   

 
  


    MainMenuBar();
    
    Window_1_Half(All_Objects);
    
   
    

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void Widgets::MainMenuBar()
{

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Handle open file */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Handle save file */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("settings"))
        {
            if (ImGui::MenuItem("dark", "Ctrl+O")) { /* Handle open file */ }
            if (ImGui::MenuItem("light", "Ctrl+S")) { /* Handle save file */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("work space"))
        {
            if (ImGui::MenuItem("2D", "Ctrl+O")) 
            { 
                Myspace = twoD;
            }
            if (ImGui::MenuItem("3D", "Ctrl+S")) 
            {
                Myspace = threeD; 
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}



void Widgets::SceneManager(std::vector<Mesh*>& All_Objects)
{
   
    int source_index = -1;
    int target_index = -1;
    const ImVec2 OD_winPos = { (float)display_w - 430,267 };
    //ImGui::SetWindowPos(OD_winPos, 0);
    if (All_Objects.size() > 0)
    {
        for (int i = 0; i < All_Objects.size(); i++) {

            if (ImGui::TreeNode(All_Objects[i]->transform.name.c_str()))
            {
                // Display or edit properties of the object here
                // ...
                g_current_object_index = i;

                if (ImGui::BeginDragDropSource()) {
                    ImGui::SetDragDropPayload("DRAG_AND_DROP", &i, sizeof(int));
                    ImGui::Text("Drag %s", All_Objects[i]->transform.name.c_str());
                    ImGui::EndDragDropSource();
                }

                if (ImGui::BeginDragDropTarget()) {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_AND_DROP")) {
                        source_index = *(const int*)payload->Data;
                        target_index = i;
                    }
                    ImGui::EndDragDropTarget();
                }

                ImGui::TreePop();
            }
        }

        if (source_index != -1 && target_index != -1) {
            std::swap(All_Objects[source_index], All_Objects[target_index]);
        }
    }
    else
    {
        
        ImGui::Text("....Empty....");
        
    }
 
}
void Widgets::Window_1_Half(std::vector<Mesh*>& All_Objects)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDrawCursor = true;
    int display_h;
    int display_w;
    glfwGetFramebufferSize(Main_Window, &display_w, &display_h);
    ImVec2 w_pos = ImVec2(display_w-700,24);
    float Wsize = 0.2f;
    ImGui::SetNextWindowPos(w_pos, 0);

    
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoScrollbar);
    

    ImGui::BeginChild("top pane", ImVec2(0, ImGui::GetWindowHeight() * Wsize), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
   
    ImGui::Text("SceneManager");
    SceneManager(All_Objects);
    ImGui::EndChild();

    ImGui::Separator();
    if (ImGui::Button("##", ImVec2(-1, 10)))
    {  
        // Do nothing, this is a dummy button
    }
    if (ImGui::IsItemActive()) 
    {
        //Drag funtionality 

        std::cout << ImGui::GetMousePos().y << "\n";
        std::cout << ImGui::GetWindowHeight() << "\n";
    }if (ImGui::IsItemHovered())
    {
        
        //ImGui::Curso
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
        ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    }
    else
    {
       ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::BeginChild("bottom pane", ImVec2(0, ImGui::GetWindowHeight() * 1-Wsize), true);

    // Begin Tab Bar
    if (ImGui::BeginTabBar("MyTabBar", ImGuiTabBarFlags_None))
    {
        // Create the first tab
        if (ImGui::BeginTabItem("Transform"))
        {
            MeshControl.EditTransform(All_Objects);
            ImGui::EndTabItem();
        }
        // Create the second tab
        if (ImGui::BeginTabItem("Physics Properties"))
        {
            ObjectPhysics(All_Objects);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Custom Physics"))
        {
            CustomPhysics(All_Objects);
            ImGui::EndTabItem();
        }
        // More tabs can go here...
        ImGui::EndTabBar();

    }

    ImGui::EndChild();
    //ImGui::EndTabBar();
    ImGui::End();
}

void Widgets::ObjectPhysics(std::vector<Mesh*>& All_Objects)
{
    if (ImGui::Checkbox("Is static", &All_Objects[g_current_object_index]->physicalProperties.Is_Static))
    {
        ImGui::Text("is now static");
    }
    ImGui::Text("Nothing Implemented");
    ImGui::Text("Add Colliders");
    if (ImGui::Checkbox("Custom", &All_Objects[g_current_object_index]->physicalProperties.CustomCollider))
    {
        ImGui::Text("Custom  Added");
    }
    ImGui::SameLine();
   
    if (All_Objects[g_current_object_index]->physicalProperties.ApplyPhysics)
    {
        
        if (All_Objects[g_current_object_index]->physicalProperties.CustomCollider)
        {
            if (ImGui::CollapsingHeader("Add Collider"))
            {
                
            }
        }
        else
        {
            if (ImGui::Button("Automatic"))
            {


            }
        }
    }
    if (ImGui::Checkbox("Show collider", &All_Objects[g_current_object_index]->physicalProperties.DisplayCollider))
    {
        ImGui::Text("display Added");
    }

}

void Widgets::CustomPhysics(std::vector<Mesh*>& All_Objects)
{
    ImGui::Checkbox("Show Script", &All_Objects[g_current_object_index]->show_script);
    if (All_Objects[g_current_object_index]->show_script == true)
    {
        All_Objects[g_current_object_index]->Comp_Script.OpenWindow();
    }
        
    

    //ImGui::InputTextMultiline("hello", &force, ImVec2(0, 0), 0, NULL, NULL);

    //std::vector<std::string> words = split(force, ' '); // Assuming split is a function that splits a string into a vector of words

    //for (auto& word : words) {
    //    if (word == "Force") {
    //        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255)); // Change text color to red
    //    }
    //    ImGui::TextUnformatted(word.c_str());
    //    ImGui::SameLine();
    //    if (word == "Force") {
    //        ImGui::PopStyleColor();
    //    }
    //}
}

