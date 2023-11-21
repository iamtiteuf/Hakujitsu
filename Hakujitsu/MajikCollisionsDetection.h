#pragma once
#include "MajikBody.h"

namespace majik
{
	class MajikCollisions
	{
		

	private:
		glm::vec3 MainNormal = glm::vec3(0,0,0);
		std::vector<glm::vec3>simplex;
		
		CollionProperties collionPropertiesA;
		CollionProperties collionPropertiesB;

		bool Circle_Polygon(CollionProperties collionPropertiesA, CollionProperties collionPropertiesB, glm::vec3& normal, float& depth);

		glm::vec3 SupportPoint();
		bool HandleSimplex();

		glm::vec3 FindSupportPoints(CollionProperties collionProperties,glm::vec3 normal)
		{
			if (collionProperties.shape == Polygon || collionProperties.shape == Plane)
			{
				glm::vec3 A = glm::vec3(0,0,0);
				float point;
				point = glm::dot(collionProperties.vertices[0], normal);
				for (int i = 0; i < collionProperties.vertices.size(); i++)
				{
					if (glm::dot(collionProperties.vertices[i], normal) >= point)
					{
						point = glm::dot(collionProperties.vertices[i], normal);
						A = collionProperties.vertices[i];
					}

				}
				return A;
			}
			if (collionProperties.shape == Sphere)
			{
				return collionProperties.center + collionProperties.raduis * glm::normalize(normal);
			}
		}

		void LineCase();
		bool PyramidCase();
		void TriangleCase();

		struct ShapeOnShape
		{
			bool IsInRange = false;
			bool SphereOnSphere = false;
		};

		ShapeOnShape CheckShapeRaduis()
		{
			float distance = glm::distance(collionPropertiesA.center, collionPropertiesB.center);
			float radii = collionPropertiesA.raduis + collionPropertiesB.raduis;
			
			if (distance >= radii)
			{
				return {false,false};
			}
			else if(collionPropertiesA.shape == Sphere && collionPropertiesB.shape == Sphere)
			{
				return { true,true };
			}
			else
			{
				return { true,false};
			}
		}

		
		void Contact_Points(CollisionData &points);
		CollisionData EPA();
		std::vector<glm::vec4> GetNormals(size_t& minFace);

		bool SupportExist(glm::vec3 support);
		
		CollisionData SAT();
		std::vector<glm::ivec3>iface;
		std::vector<glm::ivec2> edges;
		void ConvertToIndex()
		{
			facess.clear();
			for (int i = 0; i < iface.size(); i++)
			{
				facess.push_back(iface[i].x);
				facess.push_back(iface[i].y);
				facess.push_back(iface[i].z);
			}
		}

		void SphereAndSphere(CollisionData& data);
		void SphereAndPlane(CollisionData& data);

		glm::vec3 FindclosestPoint(CollionProperties collionProperties, glm::vec3 point)
		{
			glm::vec3 closest_point = glm::vec3(0, 0, 0);
			float dis = FLT_MAX;
			for (int i = 0; i < collionProperties.vertices.size(); i++)
			{
				float current = glm::distance(collionProperties.vertices[i], point);
				if (current >= dis)
				{
					closest_point = collionProperties.vertices[i];
					dis = current;
				}
			}
			return  glm::normalize(closest_point - point) ;
		}
	
	public:
		
		std::vector<glm::vec3>polytope;
		std::vector<unsigned int> facess;
		
		glm::vec3 contact;

		
		static bool Intersection(PhysicsProperties propertyA, PhysicsProperties propertyB, glm::vec3& normal, float& depth);
   
		bool GJK(const CollionProperties collionPropertiesA, const CollionProperties collionPropertiesB, glm::vec3& v_normal, float& v_depth);

		bool ToD_Particles_Collision(const CollionProperties collionPropertiesA, const CollionProperties collionPropertiesB, glm::vec3& p_normal, float& p_depth);
		void Check_Clipping(PhysicsProperties& physicsPropertiesA, glm::vec3 offset);
		
		void RepairFace(bool& isvalid);
      
		
	};
}
