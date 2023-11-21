#ifndef PHYSICS_WOLRD_CLASS
#define PHYSICS_WORLD_CLASS

#include "PhysicsHeaders.h"

namespace majik
{
	class PhysicsWorld
	{
	public:
		static glm::vec3 gravity() { return glm::vec3(0, -9.82f, 0); }
		static void step(PhysicsProperties& propertiesA, float dt);

		

		static void Collision_Resolve(PhysicsProperties& propertiesA, PhysicsProperties& propertiesB, float dt);
		static void Collision_Resolve2D(PhysicsProperties& propertiesA, PhysicsProperties& propertiesB, glm::vec3 ContactNormal,float Depth, float dt);
	private:
	
	};
	class Particles
	{
	public:
	
		glm::vec3 force = glm::vec3(0.0f, 20.0f, 0.0f);
		glm::vec3 net_force = glm::vec3(0, 0, 0);
		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec3 velocity = glm::vec3(0, 0, 0);
		glm::vec3 acceleration = glm::vec3(0, 0, 0);
		glm::vec3 drag = glm::vec3(0, 4, 0);
		float mass = 1.0f;

		static glm::vec3 gravity() 
		{ return glm::vec3(0, -9.82f, 0); 
		}

		void step(glm::vec3& position, float dt);
		static void Step(PhysicsProperties& propertiesA,float dt);
	};
}
#endif // !PHYSICS_WOLRD_CLASS

