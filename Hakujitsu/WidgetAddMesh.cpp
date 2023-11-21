#include "WidgetAddMesh.h"
void WidgetAddMesh::DrawAll(std::vector<Mesh*>& All_Objects, std::vector<Mesh*>& Temp_Objects)
{
	ImGui::Begin("Add");
	CalFps();
	DrawLine(All_Objects, Temp_Objects);
	if (Myspace == 0)
	{
		ImGui::Text("2D Scene");
	}
	else
	{
		ImGui::Text("3D Scene");
	}
	if (Myspace != 0)
	{

		AddCube(All_Objects);
		AddPyramide(All_Objects);
		AddSphere(All_Objects);
        AddPlane(All_Objects);
		AddLine(All_Objects);
	}
	else
	{
		AddBox(All_Objects);
		AddCircle(All_Objects);
		AddTriangle(All_Objects);
		AddLine(All_Objects);

	}
	Remove(All_Objects);
	ImGui::Checkbox("Simulate P...", &Simulate_Physics);

	ImGui::End();

}
void WidgetAddMesh::EditTransform(std::vector<Mesh*>& All_Objects)
{

    if (All_Objects.size() > 0)
    {
        float g_step = 0.1f;
        float g_step_fast = 0.1f;
        float g_Ui_boxWidth = 120.0f;

        glfwGetFramebufferSize(Main_Window, &display_w, &display_h);
        const ImVec2 OD_winSize = { 0,0 };
        const ImVec2 OD_winPos = { (float)display_w - 430,20 };

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.25f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));


        //ImGui::Begin("Object Properties", 0, ImGuiWindowFlags_NoMove);
        ImGui::InputText("name", &All_Objects[g_current_object_index]->transform.name, ImGuiInputTextFlags_EnterReturnsTrue);
        ImGui::Text("Location");
        //ImGui::SetWindowSize(OD_winSize,0);
        //ImGui::SetWindowPos(OD_winPos, 0);

        if (ImGui::CollapsingHeader("Transform"))
        {
            ImGui::Text("Location");
            ImGui::SetNextItemWidth(120.0f);
            ImGui::InputFloat("x", &All_Objects[g_current_object_index]->physicalProperties.position.x, g_step, g_step_fast, "%.5f", ImGuiInputTextFlags_EnterReturnsTrue);

            ImGui::SameLine();
            ImGui::SetNextItemWidth(g_Ui_boxWidth);
            ImGui::InputFloat("y", &All_Objects[g_current_object_index]->physicalProperties.position.y, g_step, g_step_fast, "%.5f", ImGuiInputTextFlags_EnterReturnsTrue);

            if (Myspace != 0)
            {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(g_Ui_boxWidth);
                ImGui::InputFloat("z", &All_Objects[g_current_object_index]->physicalProperties.position.z, g_step, g_step_fast, "%.5f", ImGuiInputTextFlags_EnterReturnsTrue);

            }
             ImGui::Text("rotation");
             if (Myspace != 0)
             {

                ImGui::SetNextItemWidth(g_Ui_boxWidth);
                ImGui::InputFloat("rx", &All_Objects[g_current_object_index]->physicalProperties.rotation.x, g_step * 2.5f, g_step_fast, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
                ImGui::SameLine();
            }

           
            ImGui::SetNextItemWidth(g_Ui_boxWidth);
            ImGui::InputFloat("ry", &All_Objects[g_current_object_index]->physicalProperties.rotation.z, g_step * 2.5f, g_step_fast, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);

            if (Myspace != 0)
            {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(g_Ui_boxWidth);
                ImGui::InputFloat("rz", &All_Objects[g_current_object_index]->physicalProperties.rotation.y, g_step * 2.5f, g_step_fast, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
            }

            ImGui::Text("Scale");

            ImGui::SetNextItemWidth(g_Ui_boxWidth);
            ImGui::InputFloat("sx", &All_Objects[g_current_object_index]->physicalProperties.scale.x, g_step, g_step_fast, "%.4f", ImGuiInputTextFlags_EnterReturnsTrue);

            ImGui::SameLine();
            ImGui::SetNextItemWidth(g_Ui_boxWidth);
            ImGui::InputFloat("sy", &All_Objects[g_current_object_index]->physicalProperties.scale.y, g_step, g_step_fast, "%.4f", ImGuiInputTextFlags_EnterReturnsTrue);

            if (Myspace != 0)
            {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(g_Ui_boxWidth);
                ImGui::InputFloat("sz", &All_Objects[g_current_object_index]->physicalProperties.scale.z, g_step, 0.1f, "%.4f", ImGuiInputTextFlags_EnterReturnsTrue);
            }


        }
        if (ImGui::CollapsingHeader("Properties"))
        {
            if (ImGui::ColorEdit3("Color", glm::value_ptr(All_Objects[g_current_object_index]->transform.color)))
            {
                All_Objects[g_current_object_index]->UpdateVertexColor();
            }
            ImGui::Checkbox("Display Collider", &All_Objects[g_current_object_index]->physicalProperties.DisplayCollider);

            if (All_Objects[g_current_object_index]->collisionProperties.shape == majik::Sphere)
            {
                if (ImGui::InputFloat("raduis", &All_Objects[g_current_object_index]->collisionProperties.raduis, g_step, 0.1f, "%.4f", ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    generateSphere(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, All_Objects[g_current_object_index]->sectors, All_Objects[g_current_object_index]->transform.color, sphere_3vert, sphere_3ing);
                    All_Objects[g_current_object_index]->CreateMesh(sphere_3vert, sphere_3ing);
                    generateSphere(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, All_Objects[g_current_object_index]->sectors, glm::vec3(1, 0, 0), sphere_3vert, sphere_3ing);
                    All_Objects[g_current_object_index]->CustomCreateMesh(sphere_3vert, sphere_3ing);

                }

                if (ImGui::InputInt("rings", &All_Objects[g_current_object_index]->rings, g_step, 0.1f, ImGuiInputTextFlags_EnterReturnsTrue))

                {
                    if (All_Objects[g_current_object_index]->rings < 3)
                    {
                        All_Objects[g_current_object_index]->rings = 3;
                    }

                    generateSphere(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, All_Objects[g_current_object_index]->sectors, All_Objects[g_current_object_index]->transform.color, sphere_3vert, sphere_3ing);
                    All_Objects[g_current_object_index]->CreateMesh(sphere_3vert, sphere_3ing);
                    generateSphere(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, All_Objects[g_current_object_index]->sectors, glm::vec3(1, 0, 0), sphere_3vert, sphere_3ing);
                    All_Objects[g_current_object_index]->CustomCreateMesh(sphere_3vert, sphere_3ing);
                }

                if (ImGui::InputInt("sectors", &All_Objects[g_current_object_index]->sectors, g_step, 0.1f, ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    if (All_Objects[g_current_object_index]->sectors < 4)
                    {
                        All_Objects[g_current_object_index]->sectors = 4;
                    }
                    generateSphere(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, All_Objects[g_current_object_index]->sectors, All_Objects[g_current_object_index]->transform.color, sphere_3vert, sphere_3ing);
                    All_Objects[g_current_object_index]->CreateMesh(sphere_3vert, sphere_3ing);
                    generateSphere(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, All_Objects[g_current_object_index]->sectors, glm::vec3(1, 0, 0), sphere_3vert, sphere_3ing);
                    All_Objects[g_current_object_index]->CustomCreateMesh(sphere_3vert, sphere_3ing);
                }
            }
            if (All_Objects[g_current_object_index]->collisionProperties.shape == majik::Circle)
            {
                if (ImGui::InputFloat("raduis", &All_Objects[g_current_object_index]->collisionProperties.raduis, g_step, 0.1f, "%.4f", ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    generateCircle(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, All_Objects[g_current_object_index]->transform.color, cir_2vert, cir_2ing);
                    All_Objects[g_current_object_index]->CreateMesh(cir_2vert, cir_2ing);
                    generateCircle(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, glm::vec3(1, 0, 0), cir_2vert, cir_2ing);
                    All_Objects[g_current_object_index]->CustomCreateMesh(cir_2vert, cir_2ing);

                }

                if (ImGui::InputInt("rings", &All_Objects[g_current_object_index]->rings, g_step, 0.1f, ImGuiInputTextFlags_EnterReturnsTrue))

                {
                    if (All_Objects[g_current_object_index]->rings < 3)
                    {
                        All_Objects[g_current_object_index]->rings = 3;
                    }

                    generateCircle(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, All_Objects[g_current_object_index]->transform.color, cir_2vert, cir_2ing);
                    All_Objects[g_current_object_index]->CreateMesh(cir_2vert, cir_2ing);
                    generateCircle(All_Objects[g_current_object_index]->collisionProperties.raduis, All_Objects[g_current_object_index]->rings, glm::vec3(1, 0, 0), cir_2vert, cir_2ing);
                    All_Objects[g_current_object_index]->CustomCreateMesh(cir_2vert, cir_2ing);
                }


            }

        }

        if (All_Objects[g_current_object_index]->Meshtype == 1)
        {
            if (ImGui::CollapsingHeader("Line Readable"))
            {
                ImGui::InputInt("Points amt", &brightness_points_amt);
                if (ImGui::Button("Read brightness Allong line"))
                {
                    All_Objects[g_current_object_index]->Brightness_values = Extra_Math::math::ReadPixelsAlongLine(All_Objects[g_current_object_index]->Line_vertices, brightness_points_amt);
                    All_Objects[g_current_object_index]->Brightness_read = true;
                }
                if (All_Objects[g_current_object_index]->Brightness_read)
                {
                    float x_data[1000];
                    float y_data[1000];
                    if (ImGui::BeginTable("Brighness values", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
                    {
                        // Setup the first column as "X"
                        ImGui::TableSetupColumn("X");
                        // Setup the second column as "Y"
                        ImGui::TableSetupColumn("Y");
                        // Create the headers row
                        ImGui::TableHeadersRow();

                        for (int i = 0; i < brightness_points_amt; i++)
                        {
                            // Start a new row
                            ImGui::TableNextRow();
                            // Go to the next column (X column)
                            ImGui::TableNextColumn();
                            // Add a value to the X column
                            ImGui::Text("% .4f", All_Objects[g_current_object_index]->Brightness_values[i].x);
                            x_data[i] = All_Objects[g_current_object_index]->Brightness_values[i].x;
                            // Go to the next column (Y column)
                            ImGui::TableNextColumn();
                            // Add a value to the Y column
                            ImGui::Text("% .4f", All_Objects[g_current_object_index]->Brightness_values[i].y);
                            y_data[i] = All_Objects[g_current_object_index]->Brightness_values[i].y;
                        }
                        // End the table
                        ImGui::EndTable();
                    }


                    ImGui::Begin("graph");
                    if (ImPlot::BeginPlot("My Plot")) {

                        ImPlot::PlotLine("My Line Plot", x_data, y_data, brightness_points_amt);
                        //...
                        ImPlot::EndPlot();
                    }
                    ImGui::End();



                }
            }

        }
        // ImGui::End();
        ImGui::PopStyleColor(4);

    }



}