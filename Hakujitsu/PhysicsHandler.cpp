#include "PhysicsHandler.h"

void PhysicsHandler::StartSupervision(std::vector<Mesh*>& All_Objects)
{
	if (Myspace == 0)
	{
		TwoD_Handler(All_Objects);
	}
	else if (Myspace == 1)
	{
		ThereD_Handler(All_Objects);
	}
}

void PhysicsHandler::TwoD_Handler(std::vector<Mesh*>& All_Objects)
{
	majik::MajikCollisions resolver;
	if (All_Objects.size() > 1)
	{
		for (int i = 0; i < All_Objects.size() - 1; i++)
		{
			for (int j = i + 1; j < All_Objects.size(); j++)
			{

				if (resolver.ToD_Particles_Collision(All_Objects[i]->collisionProperties, All_Objects[j]->collisionProperties, normal, depth))
				{
					glm::vec3 offset = normal * (depth /3.0f);
					All_Objects[i]->physicalProperties.Move(offset);
					All_Objects[j]->physicalProperties.Move(-offset);

				}

			}
		}
	}
	


}
void PhysicsHandler::ThereD_Handler(std::vector<Mesh*>& All_Objects)
{
	
	for (int i = 0; i < All_Objects.size(); i++)
	{
		for (int j = 0; j < All_Objects.size(); j++)
		{
			if (i != j)
			{
				glm::vec3 normal = glm::vec3(0, 0, 0);
				float depth = 0;
				if (Simulate_Physics)
				{
					majik::PhysicsWorld::step(All_Objects[i]->physicalProperties,  0.006f);

					if (resolvers.GJK(All_Objects[i]->collisionProperties, All_Objects[j]->collisionProperties, normal, depth))
					{

						
						majik::PhysicsWorld::Collision_Resolve(All_Objects[i]->physicalProperties, All_Objects[j]->physicalProperties, 0.006f);
						
						All_Objects[i]->OffSet_Location(-normal * depth / 2.0f);
						All_Objects[j]->OffSet_Location(normal * depth / 2.0f);

					}

				}

			
			}
		}

	}


}
