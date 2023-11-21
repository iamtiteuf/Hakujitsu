#include "SwarmDemo.h"
#define N 10

#define minDrift 30
#define minVelocity 2
#define dt  100.0f;
#define G_const 6.67430e-11f
#include <memory>

void SwarmDemo::SpawnSatellite()
{
	for (int i = 0; i < N; i++)
	{
		Mesh* mesh = new Mesh;
		mesh->CreatePoint3D();
		mesh->physicalProperties.position = RandomPosition();
		mesh->physicalProperties.drift = rand() % 10;
		AllSatelites.push_back(mesh);

	}


}
void SwarmDemo::RenderSatellites(glm::mat4 Cam, GLuint Shaderprog)
{
	Clohessy_Wiltshire();

	for (auto Satellite : AllSatelites)
	{
		Satellite->DrawPoint(Shaderprog, Cam);
	}
	/*for (auto Lines : AllLines)
	{
		Lines->ClearMesh();
	}*/
	
	AllLines.clear();
	if (SwarmGroups())
	{
		for (int i = 0; i < AllLines.size(); i++)
		{
			AllLines[i]->DrawLine(Shaderprog, Cam);
		}
	}
	
	

		
	
}


glm::vec3 SwarmDemo::RandomPosition()
{
	float x = ((float)rand() / (float)RAND_MAX) * 20.0f - 10.0f;
	float y = ((float)rand() / (float)RAND_MAX) * 20.0f - 10.0f;
	float z = ((float)rand() / (float)RAND_MAX) * 20.0f - 10.0f;

	return glm::vec3(x, y, z);
}

bool SwarmDemo::SwarmGroups()
{
	AllLines.clear();
	
	
	for (int i = 0; i < AllSatelites.size(); i++)
	{
		AllSatelites[i]->GroupID = -1;
		AllSatelites[i]->Lonely = 0;
	}
	std::vector<std::vector<Mesh*>>Sorted_Group;

	int GroupAmt = -1;

	for (int i = 0; i < AllSatelites.size(); i++)
	{
		if (AllSatelites[i]->GroupID == -1)
		{
			++GroupAmt;
			AllSatelites[i]->GroupID = GroupAmt;
			for (int j = 0; j < AllSatelites.size(); j++)
			{
				if (i != j)
				{
					if (AllSatelites[j]->GroupID == -1)
					{	
						if (abs(AllSatelites[i]->physicalProperties.drift - AllSatelites[j]->physicalProperties.drift) < minDrift && glm::length(AllSatelites[i]->physicalProperties.velocity - AllSatelites[j]->physicalProperties.velocity) < minVelocity)
						{
							AllSatelites[j]->GroupID = GroupAmt;
						}
					}
				}
			}
		}
	
	}
	

	Sorted_Group.resize(GroupAmt + 1);
	while (GroupAmt > -1)
	{
		for (int i = 0; i < AllSatelites.size(); i++)
		{
			if (AllSatelites[i]->GroupID == GroupAmt)
			{
				Sorted_Group[GroupAmt].push_back(AllSatelites[i]);
			}
		}
		--GroupAmt;
	}
	

	int maxgrp = -1;
	int maxgrp_size =0;
	int maxAmt = 0;

	for (int i = 0; i < Sorted_Group.size(); i++)
	{
		if (Sorted_Group[i].size() == maxgrp_size)
		{
			++maxAmt;

		}
		if (Sorted_Group[i].size() > maxgrp_size)
		{
			maxgrp = i;
			maxgrp_size = Sorted_Group[i].size();
			
		}
		
	}

	for (auto obj : Sorted_Group)
	{
		if (obj.size() < 2)
		{
			obj[0]->Lonely = 1;
		}
	}

	for (int i = 0; i < Sorted_Group.size(); i++)
	{
		if (Sorted_Group[i].size() < 2 && Sorted_Group[i].size() > 0)
		{
			
			float min = FLT_MAX;
			int Index = -1;

			for (int s = 0; s < AllSatelites.size(); s++)
			{
				if (AllSatelites[s]->physicalProperties.position != Sorted_Group[i][0]->physicalProperties.position && AllSatelites[s]->Lonely == 0)
				{
					if (glm::distance(AllSatelites[s]->physicalProperties.position, Sorted_Group[i][0]->physicalProperties.position) < min)
					{
						min = glm::distance(AllSatelites[s]->physicalProperties.position, Sorted_Group[i][0]->physicalProperties.position);
						Index = s;
					}
				}
			}
			std::unique_ptr<Mesh> bline = std::make_unique<Mesh>();
			std::vector<glm::vec3> Line;

			if (Index != -1)
			{
				Line.push_back(Sorted_Group[i][0]->physicalProperties.position);
				Line.push_back(AllSatelites[Index]->physicalProperties.position);

				bline->CreateLine3D(Line, glm::vec3(1, 0, 0)); //draw red line

				// Add the unique_ptr to AllLines
				AllLines.push_back(std::move(bline));
			}

		}
		else
		{
			for (int j = 0; j < Sorted_Group[i].size()-1; j++)
			{

				std::vector<glm::vec3> Line;
				Line.push_back(Sorted_Group[i][j]->physicalProperties.position);
				float min = FLT_MAX;
				int Index = -1;  // Change here
				glm::vec3 Color;
				if (maxgrp == i)
				{
					if (maxAmt > 1)
					{
						Color = glm::vec3(0, 0, 1);
					}
					Color = glm::vec3(0, 1,0);
				}
				else
				{
					
					Color = glm::vec3(0, 0, 1);
				}
				for (int k = j + 1; k < Sorted_Group[i].size(); k++)
				{
					
					if (glm::distance(Sorted_Group[i][j]->physicalProperties.position, Sorted_Group[i][k]->physicalProperties.position) < min)
					{

						min = glm::distance(Sorted_Group[i][j]->physicalProperties.position, Sorted_Group[i][k]->physicalProperties.position);
						Index = k;  // Change here}

					}
					if (Index != -1)
					{
						Line.push_back(Sorted_Group[i][Index]->physicalProperties.position);
						if (Line.size() > 1)
						{
							std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
							mesh->CreateLine3D(Line, Color);
							AllLines.push_back(std::move(mesh));
						}
					}
				}
			}
		}
	}

	if (maxAmt == 1)
	{
		for (size_t i = 0; i < Sorted_Group.size(); i++) {
			if (Sorted_Group[i].size() <= 1) {
				continue;
			}
			Mesh* closestInI = nullptr;
			Mesh* closestInMax = nullptr;
			double minDistance = std::numeric_limits<double>::max();
			for (Mesh* meshI : Sorted_Group[i]) {
				for (Mesh* meshMax : Sorted_Group[maxgrp]) {
					double distance = glm::distance(meshI->physicalProperties.position, meshMax->physicalProperties.position);
					if (distance < minDistance) {
						minDistance = distance;
						closestInI = meshI;
						closestInMax = meshMax;
					}
				}
			}
			// Draw a line between closestInI and closestInMax
			std::unique_ptr<Mesh> bline = std::make_unique<Mesh>();
			std::vector<glm::vec3> Line;
			if (closestInI != nullptr && closestInMax != nullptr)
			{
				Line.push_back(closestInI->physicalProperties.position);
				Line.push_back(closestInMax->physicalProperties.position);
				bline->CreateLine3D(Line, glm::vec3(0.5, 0.5, 0.5)); //draw white line
				AllLines.push_back(std::move(bline)); // Add the unique_ptr to AllLines
			}
		}

	}
	else
	{
		for (size_t i = 0; i < Sorted_Group.size(); i++) {
			if (Sorted_Group[i].size() <= 1) {
				continue;
			}
			Mesh* closestInI = nullptr;
			Mesh* closestInMax = nullptr;
			double minDistance = std::numeric_limits<double>::max();
			for (Mesh* meshI : Sorted_Group[i]) {
				for (Mesh* meshMax : Sorted_Group[maxgrp]) {
					double distance = glm::distance(meshI->physicalProperties.position, meshMax->physicalProperties.position);
					if (distance < minDistance) {
						minDistance = distance;
						closestInI = meshI;
						closestInMax = meshMax;
					}
				}
			}
			// Draw a line between closestInI and closestInMax
			std::unique_ptr<Mesh> bline = std::make_unique<Mesh>();
			std::vector<glm::vec3> Line;
			if (closestInI != nullptr && closestInMax != nullptr)
			{
				Line.push_back(closestInI->physicalProperties.position);
				Line.push_back(closestInMax->physicalProperties.position);
				bline->CreateLine3D(Line, glm::vec3(0.5, 0.5, 0.5)); //draw white line
				AllLines.push_back(std::move(bline)); // Add the unique_ptr to AllLines
			}
		}

	}
	
	

}
void SwarmDemo::Drawtables()
{
	matrix.resize(AllSatelites.size());
	// Set the number of columns and initialize them
	for (int i = 0; i < matrix.size(); ++i)
	{
		matrix[i].resize(AllSatelites.size(), 0);
	}
	for (int i = 0; i < AllSatelites.size(); i++)
	{
		for (int j = 0; j < AllSatelites.size(); j++)
		{
			if (i == j)
			{
				matrix[i][j] = 0;
			}
			if (glm::distance(AllSatelites[i]->physicalProperties.position, AllSatelites[j]->physicalProperties.position) < minDrift)
			{
				matrix[i][j] = 1;
			}
			else
			{
				matrix[i][j] = 0;
			}

		}

	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	if (ImGui::Begin("Matrix Table"))
	{
		// Create a new table
		if (ImGui::BeginTable("matrix", matrix[0].size() + 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) // +1 for row numbers
		{
			// Draw new row at the top
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text("Aj mat");
			for (int j = 0; j < matrix[0].size(); ++j)
			{
				ImGui::TableNextColumn();
				ImGui::Text("%d", j + 1);
			}

			// Draw existing rows
			for (const auto& row : matrix)
			{
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("%d", &row - &matrix[0] + 1);

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

void SwarmDemo::Clohessy_Wiltshire()
{
	glm::vec3 targetPos = glm::vec3(0, 0, 0);
	glm::vec3 targetVelocity = glm::vec3(0,0, 0);
	float targetmass = 10.0f;
	for (int i= 0;i < AllSatelites.size(); i++)
	{
		glm::vec3 r = AllSatelites[i]->physicalProperties.position - targetPos;
		glm::vec3 v = AllSatelites[i]->physicalProperties.velocity - targetVelocity;

		double omega = sqrt(G_const * (AllSatelites[i]->physicalProperties.mass + targetmass) / powf(glm::length(r), 3));
		AllSatelites[i]->physicalProperties.force.x = 3 * omega * omega * r.x + 2 * omega * v.y;
		AllSatelites[i]->physicalProperties.force.y = -2 * omega * v.x;
		AllSatelites[i]->physicalProperties.force.z = -omega * omega * r.z;
		AllSatelites[i]->physicalProperties.drift = AllSatelites[i]->physicalProperties.velocity.y + 2.0f * AllSatelites[i]->physicalProperties.position.x;
	}
			
				

	Step();
}


void SwarmDemo::Step()
{
	
	for (int i = 0; i < AllSatelites.size(); i++)
	{
		AllSatelites[i]->physicalProperties.velocity += AllSatelites[i]->physicalProperties.force * dt;
		AllSatelites[i]->physicalProperties.position += AllSatelites[i]->physicalProperties.velocity * dt;
		AllSatelites[i]->physicalProperties.force = glm::vec3(0, 0, 0);
	}
}

//for (size_t i = 0; i < Sorted_Group.size() - 1; i++) {
//	if (Sorted_Group[i].size() <= 1) {
//		continue;
//	}
//	for (size_t j = i + 1; j < Sorted_Group.size(); j++) {
//		if (Sorted_Group[j].size() <= 1) {
//			continue;
//		}
//		Mesh* closestInI = nullptr;
//		Mesh* closestInJ = nullptr;
//		double minDistance = std::numeric_limits<double>::max();
//		for (Mesh* meshI : Sorted_Group[i]) {
//			for (Mesh* meshJ : Sorted_Group[j]) {
//				double distance = glm::distance(meshI->physicalProperties.position, meshJ->physicalProperties.position);
//				if (distance < minDistance) {
//					minDistance = distance;
//					closestInI = meshI;
//					closestInJ = meshJ;
//				}
//			}
//		}
//		 Draw a line between closestInI and closestInJ
//		std::unique_ptr<Mesh> bline = std::make_unique<Mesh>();
//		std::vector<glm::vec3> Line;
//		Line.push_back(closestInI->physicalProperties.position);
//		Line.push_back(closestInJ->physicalProperties.position);
//		bline->CreateLine3D(Line, glm::vec3(1, 1, 1)); //draw white line
//		AllLines.push_back(std::move(bline)); // Add the unique_ptr to AllLines
//
//		 Break out of the loop for this group after drawing the line
//		break;
//	}
//}