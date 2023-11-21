#include "PhysicsWorld.h"
namespace majik 
{

	void PhysicsWorld::step(PhysicsProperties& propertiesA, float dt)
	{
		if (!propertiesA.Is_Static)
		{
			propertiesA.force = gravity() * propertiesA.mass;

			propertiesA.velocity += propertiesA.force / propertiesA.mass * dt;
			propertiesA.position += propertiesA.velocity * dt;
			propertiesA.force = glm::vec3(0, 0, 0);
		}
	}
	void  PhysicsWorld::Collision_Resolve(PhysicsProperties& propertiesA, PhysicsProperties& propertiesB, float dt)
	{
		glm::vec3 Normal = glm::normalize(propertiesB.position - propertiesA.position);
		glm::vec3 relative_velocity = propertiesA.velocity - propertiesB.velocity;
		float e = std::min(propertiesA.restitution, propertiesB.restitution);
		float Impulse = -(1 + e) * (glm::dot(relative_velocity, Normal)) / ((1 / propertiesA.mass) + (1 / propertiesB.mass));
		glm::vec3 Impulse_vector = Impulse * Normal*100.0f;

		if (!propertiesA.Is_Static)
		{
			
			propertiesA.velocity += Impulse_vector / propertiesA.mass * dt;
			propertiesA.position += propertiesA.velocity * dt;
			
		}if (!propertiesB.Is_Static)
		{
			propertiesB.velocity += -Impulse_vector / propertiesB.mass * dt;
			propertiesB.position += propertiesB.velocity * dt;
		}
	}
	void  PhysicsWorld::Collision_Resolve2D(PhysicsProperties& propertiesA, PhysicsProperties& propertiesB,glm::vec3 ContactNormal, float Depth, float dt)
	{
		//calculate seperating vector
		float SeparatingVector = glm::dot((propertiesA.velocity - propertiesB.velocity), ContactNormal);
		if (SeparatingVector > 0)
		{

		}
		else
		{
			float NewSeparatingVector = -SeparatingVector *std::min(propertiesA.restitution, propertiesB.restitution);
			float DeltaVelocity = NewSeparatingVector - SeparatingVector;
			float TotalInverseMass = propertiesA.InverseMass() + propertiesB.InverseMass();
			
			float Impulse = DeltaVelocity / TotalInverseMass;
			glm::vec3 ImpulsePerMass = ContactNormal * Impulse;
			propertiesA.velocity = propertiesA.velocity + ImpulsePerMass * propertiesA.InverseMass();
			propertiesB.velocity = propertiesB.velocity - ImpulsePerMass * propertiesB.InverseMass();

			if (!propertiesA.Is_Static)
			{
				propertiesA.position = propertiesA.position - ContactNormal * Depth;
			}
			if (!propertiesB.Is_Static)
			{
				propertiesB.position = propertiesB.position - ContactNormal * Depth/2.0f;
			}
		}
		
	}
	void Particles::step(glm::vec3& position, float dt)
	{
		
		net_force = mass * gravity() + force - drag;

		velocity += net_force / mass * dt;
		this->position += velocity * dt;
		
		position = this->position;
		
		net_force = glm::vec3(0, 0, 0);
	}
	void Particles::Step(PhysicsProperties& propertiesA, float dt)
	{
		propertiesA.force = propertiesA.mass * gravity() + propertiesA.force - propertiesA.drag;
		

		propertiesA.velocity += propertiesA.force / propertiesA.mass * dt;
		propertiesA.position += propertiesA.velocity * dt;


		propertiesA.force = glm::vec3(0, 0, 0);
	}
	
}
