#ifndef PHYSICS_HANDLER_H
#define PHYSICS_HANDLER_H
#include "Global_Variables.h"
#include "Mesh.h"
class PhysicsHandler
{

public:
	void StartSupervision(std::vector<Mesh*>& All_Objects);
private:
	void TwoD_Handler(std::vector<Mesh*>& All_Objects);
	void ThereD_Handler(std::vector<Mesh*>& All_Objects);
	float depth;
	glm::vec3 normal;
	majik::MajikCollisions resolvers;
};
	
#endif

