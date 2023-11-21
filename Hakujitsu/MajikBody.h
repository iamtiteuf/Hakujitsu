#pragma once

#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <vector>



namespace majik
{
	struct CollisionData
	{
		glm::vec3 normal = glm::vec3(0,0,0);
		float depth = 0;
		std::vector<glm::vec3> contact_points;
		

	};
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;
		glm::vec2 texUV;

	};
	class Math
	{
	public:
		static float Clamp(float value, float min, float max)
		{
			if (min > max)
			{
				float temp = min;
				min = max;
				max = temp;
			}

			if (value < min)
			{
				return min;
			}
			else if (value > max)
			{
				return max;
			}
			else
			{
				return value;
			}
		}
		static float Pi() 
		{
			return  3.141592653589793238462643383279502884197f;
		}
	
	};

	enum ShapeType
	{
		Sphere = 0,
		Box = 1,
		Polygon = 2,
		Cylinder = 3,
		Plane = 4,
		Circle = 5
	};
	class Physics_Body
	{
	public:
		

		glm::vec3 Position;
		glm::vec3 LinearVelocity;
		glm::vec3 Rotation;
		glm::vec3 Rotationalvelocity;

		float Density;
		float Mass;
		float Restitution;
		float Area;
		
		bool IsStatic;

		float Raduis;
		float Width;
		float Thickness;
		float Height;

		ShapeType Shapetype;

		void Ini_Physics_Body(glm::vec3 & Position, float Density, float Mass, float Restitution, float Area, bool IsStatic, float Raduis, float Width, float Height, float thickness, ShapeType Shapetype
		)
		{
			
			this->Position = Position;

			this->Density = Density;
			this->Mass = Mass;
			this->Restitution = Restitution;
			this->Area = Area;

			this->IsStatic = IsStatic;

			this->Raduis = Raduis;
			this->Width = Width;
			this->Height = Height;
			this->Thickness = thickness;
			this->Shapetype = Shapetype;
		}
		
		
		void CreateCircleBody(float raduis, glm::vec3 & position, float density, bool Isstatic, float restitution)
		{
			float area = 4.0f * Math::Pi() * raduis * raduis;
			restitution = Math::Clamp(restitution, 0.0f, 1.0f);
			float mass = area* density;
			Ini_Physics_Body(position, density, mass, restitution, area, Isstatic, raduis, 0.0f, 0.0f,0.0f,ShapeType::Sphere);
		}
		void CreateBoxBody(float width, float height, float thickness, glm::vec3 & position, float density, bool Isstatic, float restitution)
		{
			float area = 2.0f*(thickness * width + thickness * height + width * height);
			restitution = Math::Clamp(restitution, 0.0f, 1.0f);
			float mass = area * density;
			Ini_Physics_Body(position, density, mass, restitution, area, Isstatic, 0.0f, width, height,thickness,ShapeType::Box);
		}
			

	};

	struct PhysicsProperties
	{
		bool ApplyPhysics = false;
		bool CustomCollider = false;
		bool DisplayCollider = false;
		bool EditTransform = false;
		bool Is_Static = false;
		float inverseMass = 1.0f;
		float restitution = 1.0f;
		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		float Raduis = 1;
		float mass = 1000;

		float drift = 0;
		float InverseMass()
		{
			return 1 / mass;
		}

		glm::vec3 force = glm::vec3(0, 0, 0);
		glm::vec3 velocity = glm::vec3(0, 0, 0);
		glm::vec3 drag = glm::vec3(0, 0, 0);
	

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		

		Physics_Body PhysicsBody;

		
		

		void Move(glm::vec3  amount)
		{
			if (Is_Static == false)
			{
				if (amount.x <100000000.0f && amount.x >-100000000.0f)
				{
					position = position + amount;
				}
			}
			
		}
		void MoveTo(glm::vec3& Position)
		{
			position = Position;
		}
	};
	struct CollionProperties
	{
		glm::vec3 center;
		float raduis = 1;
		float offset;
		bool colliding = false;
		CollisionData collisionData;

		ShapeType shape;
		std::vector < glm::vec3> vertices;
		std::vector < glm::vec3> normals;
		glm::vec3 Debug_point = glm::vec3(0, 0, 0);

	};
	
}
