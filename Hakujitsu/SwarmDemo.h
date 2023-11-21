#ifndef SWARM_CLASS_H
#define SWARM_CLASS_H
#include "Global_Variables.h"
#include "Mesh.h"

class SwarmDemo
{
public:
	void SpawnSatellite();
	void RenderSatellites(glm::mat4 Cam, GLuint Shaderprog);
	~SwarmDemo()
	{
		for (auto point : AllSatelites)
		{
			delete point;
		}
	}
	std::vector<std::vector<int>> matrix;

	void Drawtables();
	void MainGroups(std::vector<std::vector<Mesh*>>Sorted_Group)
	{
		std::vector<std::vector<int>> grp;
		grp.resize(Sorted_Group.size());
		// Set the number of columns and initialize them
		for (int i = 0; i < Sorted_Group.size(); ++i)
		{
			grp[i].resize(Sorted_Group[i].size(), 0);
		}
		for (int i = 0; i < Sorted_Group.size(); i++)
		{
			for (int j = 0; j < Sorted_Group[i].size(); j++)
			{
				grp[i][j] = Sorted_Group[i][j]->GroupID;

			}

		}
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (ImGui::Begin("Group Table"))
		{
			// Create a new table
			if (ImGui::BeginTable("Group", grp[0].size() + 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) // +1 for row numbers
			{
				// Draw new row at the top
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Aj Group");
				for (int j = 0; j < grp[0].size(); ++j)
				{
					ImGui::TableNextColumn();
					ImGui::Text("%d", j + 1);
				}

				// Draw existing rows
				for (const auto& row : grp)
				{
					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					ImGui::Text("%d", &row - &grp[0] + 1);

					// Draw row cells
					for (const auto& cell : row)
					{
						ImGui::TableNextColumn();
						ImGui::Text("%d", cell);
					}
				}
				ImGui::EndTable();
			}
			ImGui::End();
		}


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void Clohessy_Wiltshire();
	void Step();
    bool SwarmGroups();
	
private:
	std::vector<Mesh*>AllSatelites;
	std::vector<std::unique_ptr<Mesh>> AllLines;
	
	
	glm::vec3 RandomPosition();
};
#endif

