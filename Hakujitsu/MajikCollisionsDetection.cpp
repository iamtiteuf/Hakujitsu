#include "MajikCollisionsDetection.h"
#include "Global_Variables.h"
#include <quickhull/QuickHull.hpp>

namespace majik
{
	bool MajikCollisions::Intersection(PhysicsProperties propertyA, PhysicsProperties propertyB, glm::vec3& normal, float& depth)
	{
		float distance = glm::distance(propertyA.position, propertyB.position);
		float radii = propertyA.Raduis + propertyB.Raduis;
		if (distance >= radii)
		{
			return false;
		}
		else
		{
			normal = glm::normalize(propertyB.position - propertyA.position);
			depth = radii - distance;

			return true;

		}

	}
	glm::vec3 MajikCollisions::SupportPoint()
	{
		glm::vec3 A = FindSupportPoints(collionPropertiesA, MainNormal);
		glm::vec3 B = FindSupportPoints(collionPropertiesB, -MainNormal);
		return A - B;
	}

	bool MajikCollisions::GJK(const CollionProperties collionPropertiesA, const CollionProperties collionPropertiesB, glm::vec3& v_normal, float& v_depth)
	{
		this->collionPropertiesA = collionPropertiesA;
		this->collionPropertiesB = collionPropertiesB;
		ShapeOnShape checkshape = CheckShapeRaduis();
		if (checkshape.IsInRange == false && checkshape.SphereOnSphere == false)
		{

			return false;

		}
		else if (checkshape.IsInRange == true && checkshape.SphereOnSphere == true)
		{
			CollisionData data;
			v_normal = glm::normalize(collionPropertiesB.center - collionPropertiesA.center);
			v_depth = (collionPropertiesB.raduis + collionPropertiesA.raduis) - glm::distance(collionPropertiesB.center, collionPropertiesA.center);
			Contact_Points(data);
			v_normal = data.normal;
			v_depth = data.depth;
			return true;
		}


		if (collionPropertiesB.vertices.size() > 0)
		{

			MainNormal = collionPropertiesB.center - collionPropertiesA.center;
			if (MainNormal == glm::vec3(0, 0, 0))
			{
				MainNormal = glm::vec3(1, 0, 0);
			}
			simplex.push_back(SupportPoint());//C
			MainNormal = glm::vec3(0, 0, 0) - simplex[0];
			int i = 0;
			while (i < 50)
			{
				glm::vec3 A = SupportPoint();

				if (glm::dot(A, MainNormal) < 0)//no intersection
				{
					return false;
				}
				else
				{
					simplex.push_back(A);
					if (HandleSimplex())
					{
						CollisionData out_data = EPA();
						v_normal = out_data.normal;
						v_depth = out_data.depth + 0.001;
						MinA = v_depth;
						i = 0;

						return true;//intersection

					}
					else
					{
						i++;
					}
				}
			}

		}
		else
		{
			return false;
		}
	}

	bool MajikCollisions::HandleSimplex()
	{
		

		if (simplex.size() == 2)
		{
			LineCase();
			return false;

		}
		if (simplex.size() == 3)
		{
			TriangleCase();

			return false;
		}
		else if (simplex.size() == 4)
		{
			return PyramidCase();
		}

	}
	void MajikCollisions::LineCase()
	{
		glm::vec3 B = simplex[0];
		glm::vec3 A = simplex[1];
		glm::vec3 AB = B - A;
		glm::vec3 AO = -A;
		if (glm::dot(AB, AO) > 0)
		{
			MainNormal = glm::cross(glm::cross(AB, AO), AB);
		}
		else
		{
			MainNormal = AO;
			simplex.erase(simplex.begin() + 0);
			simplex[0] = A;
		}
	}
	void MajikCollisions::TriangleCase()
	{
		glm::vec3 A = simplex[2];
		glm::vec3 B = simplex[1];
		glm::vec3 C = simplex[0];

		glm::vec3 AB = B - A;
		glm::vec3 AC = C - A;
		glm::vec3 AO = glm::vec3(0, 0, 0) - A;
		glm::vec3 ABC = glm::cross(AB, AC);
		if (glm::dot(glm::cross(ABC, AC), AO) > 0)
		{
			if (glm::dot(AC, AO) > 0)
			{
				MainNormal = glm::cross(glm::cross(AC, AO), AC);
				simplex.pop_back();//remove B
				simplex[1] = A;
				simplex[0] = C;
			}
			else
			{
				if (glm::dot(AB, AO) > 0)
				{
					MainNormal = glm::cross(glm::cross(AB, AO), AB);
					simplex.pop_back();//remove C
					simplex[1] = A;
					simplex[0] = B;

				}
				else
				{
					simplex.pop_back();//remove C
					simplex.pop_back();//remove B
					MainNormal = AO;
					simplex[0] = A;
				}
			}
		}
		else
		{
			if (glm::dot(glm::cross(AB, ABC), AO) > 0)
			{
				if (glm::dot(AB, AO) > 0)
				{
					MainNormal = glm::cross(glm::cross(AB, AO), AB);
					simplex.pop_back();//remove C
					simplex[1] = A;
					simplex[0] = B;

				}
				else
				{
					simplex.pop_back();//remove C
					simplex.pop_back();//remove B
					MainNormal = AO;
					simplex[0] = A;
				}

			}
			else
			{
				if (glm::dot(ABC, AO) > 0)
				{
					MainNormal = ABC;
				}
				else
				{
					simplex[2] = A;
					simplex[1] = C;
					simplex[0] = B;
					MainNormal = -ABC;
				}
			}
		}

	}
	bool MajikCollisions::PyramidCase()
	{
		glm::vec3 A = simplex[0];
		glm::vec3 B = simplex[1];
		glm::vec3 C = simplex[2];
		glm::vec3 D = simplex[3];

		glm::vec3 DO = -D;
		glm::vec3 DC = C - D;
		glm::vec3 DB = B - D;
		glm::vec3 DA = A - D;
		glm::vec3 DBC = glm::cross((B - D), (C - D));
		glm::vec3 DAB = glm::cross((A - D), (B - D));
		glm::vec3 DCA = glm::cross((C - D), (A - D));

		if (glm::dot(DBC, DO) > 0) {

			simplex.erase(simplex.begin() + 0);// [D, B, C] 
			simplex[0] = D;
			simplex[1] = B;
			simplex[2] = C;
			MainNormal = DBC;
			return false;

		}
		else if (glm::dot(DAB, DO) > 0) {
			simplex.erase(simplex.begin() + 2);// [D, A, B];
			simplex[0] = D;
			simplex[1] = A;
			simplex[2] = B;

			MainNormal = DAB;
			return false;
		}
		else if (glm::dot(DCA, DO) > 0) {

			simplex.erase(simplex.begin() + 0);// [D, C, A]
			simplex[0] = D;
			simplex[1] = C;
			simplex[2] = A;
			MainNormal = DCA;
			return false;
		}
		else
		{
			return true;

		}
	}

	CollisionData MajikCollisions::SAT()
	{
		polytope = simplex;
		facess = {
			0,1,2,
			0,1,3,
			1,2,3,
			2,0,3
		};
		std::vector<std::vector<glm::vec3>> faces(64, std::vector<glm::vec3>(4));
		//Init with final simplex from GJK
		glm::vec3 a = polytope[0];
		glm::vec3 b = polytope[1];
		glm::vec3 c = polytope[2];
		glm::vec3 d = polytope[3];

		faces[0][0] = a;
		faces[0][1] = b;
		faces[0][2] = c;
		faces[0][3] = glm::normalize(glm::cross((b - a), (c - a))); //ABC
		if (glm::dot(faces[0][3], glm::vec3(0, 0, 0)) > 0)
		{
			faces[0][3] = -glm::normalize(glm::cross((b - a), (c - a)));
		}
		faces[1][0] = a;
		faces[1][1] = c;
		faces[1][2] = d;
		faces[1][3] = glm::normalize(glm::cross((c - a), (d - a))); //ACD
		if (glm::dot(faces[1][3], glm::vec3(0, 0, 0)) > 0)
		{
			faces[1][3] = -glm::normalize(glm::cross((c - a), (d - a)));
		}
		faces[2][0] = a;
		faces[2][1] = d;
		faces[2][2] = b;
		faces[2][3] = glm::normalize(glm::cross((d - a), (b - a))); //ADB
		if (glm::dot(faces[2][3], glm::vec3(0, 0, 0)) > 0)
		{
			faces[2][3] = -glm::normalize(glm::cross((d - a), (b - a)));
		}
		faces[3][0] = b;
		faces[3][1] = d;
		faces[3][2] = c;
		faces[3][3] = glm::normalize(glm::cross((d - b), (c - b))); //BDC
		if (glm::dot(faces[3][3], glm::vec3(0, 0, 0)) > 0)
		{
			faces[3][3] = -glm::normalize(glm::cross((d - b), (c - b)));
		}
		
		


		int num_faces = 4;
		int closest_face;

		for (int iterations = 0; iterations < 64; iterations++) {
			//Find face that's closest to origin
			float min_dist = glm::dot(faces[0][0], faces[0][3]);
			closest_face = 0;
			for (int i = 1; i < num_faces; i++) {
				float dist = glm::dot(faces[i][0], faces[i][3]);
				if (dist < min_dist) {
					min_dist = dist;
					closest_face = i;
				}
			}

			//search normal to face that's closest to origin
			glm::vec3 search_dir = faces[closest_face][3];
			MainNormal = search_dir;
			glm::vec3 p = SupportPoint();

			if (glm::dot(p, search_dir) - min_dist < 0.0001f) {
				//Convergence (new point is not significantly further from origin)
				CollisionData points;
				points.normal = faces[closest_face][3]; 
				points.depth = glm::dot(p, search_dir);
				return points; //dot vertex with normal to resolve collision along normal!
			}

			std::vector<std::vector<glm::vec3>> loose_edges(32, std::vector<glm::vec3>(2)); //keep track of edges we need to fix after removing faces
			int num_loose_edges = 0;

			//Find all triangles that are facing p
			for (int i = 0; i < num_faces; i++)
			{
				if (glm::dot(faces[i][3], p - faces[i][0]) > 0) //triangle i faces p, remove it
				{
					//Add removed triangle's edges to loose edge list.
					//If it's already there, remove it (both triangles it belonged to are gone)
					for (int j = 0; j < 3; j++) //Three edges per face
					{
						
						std::vector<glm::vec3> current_edge = { faces[i][j], faces[i][(j + 1) % 3] };
						bool found_edge = false;
						for (int k = 0; k < num_loose_edges; k++) //Check if current edge is already in list
						{
							if (loose_edges[k][1] == current_edge[0] && loose_edges[k][0] == current_edge[1]) {
								//Edge is already in the list, remove it
								//THIS ASSUMES EDGE CAN ONLY BE SHARED BY 2 TRIANGLES (which should be true)
								//THIS ALSO ASSUMES SHARED EDGE WILL BE REVERSED IN THE TRIANGLES (which 
								//should be true provided every triangle is wound CCW)
								loose_edges[k][0] = loose_edges[num_loose_edges - 1][0]; //Overwrite current edge
								loose_edges[k][1] = loose_edges[num_loose_edges - 1][1]; //with last edge in list
								num_loose_edges--;
								found_edge = true;
								k = num_loose_edges; //exit loop because edge can only be shared once
							}
						}//endfor loose_edges

						if (!found_edge) { //add current edge to list
							// assert(num_loose_edges<EPA_MAX_NUM_LOOSE_EDGES);
							if (num_loose_edges >= 32) break;
							loose_edges[num_loose_edges][0] = current_edge[0];
							loose_edges[num_loose_edges][1] = current_edge[1];
							num_loose_edges++;
						}
					}

					//Remove triangle i from list
					faces[i][0] = faces[num_faces - 1][0];
					faces[i][1] = faces[num_faces - 1][1];
					faces[i][2] = faces[num_faces - 1][2];
					faces[i][3] = faces[num_faces - 1][3];
					num_faces--;
					i--;
				}//endif p can see triangle i
			}//endfor num_faces

			//Reconstruct polytope with p added
			for (int i = 0; i < num_loose_edges; i++)
			{
				// assert(num_faces<EPA_MAX_NUM_FACES);
				if (num_faces >= 64)
				{
					break;
				}
				faces[num_faces][0] = loose_edges[i][0];
				faces[num_faces][1] = loose_edges[i][1];
				faces[num_faces][2] = p;
				faces[num_faces][3] = glm::normalize(glm::cross(loose_edges[i][0] - loose_edges[i][1], loose_edges[i][0] - p));

				//Check for wrong normal to maintain CCW winding
				float bias = 0.000001; //in case dot result is only slightly < 0 (because origin is on face)
				if (dot(faces[num_faces][0], faces[num_faces][3]) + bias < 0) {
					glm::vec3 temp = faces[num_faces][0];
					faces[num_faces][0] = faces[num_faces][1];
					faces[num_faces][1] = temp;
					faces[num_faces][3] = -faces[num_faces][3];
				}
				num_faces++;
			}
		} //End for iterations
		printf("EPA did not converge\n");
		//Return most recent closest point
		CollisionData points;
		points.normal = faces[closest_face][3]; 
		points.depth = glm::dot(faces[closest_face][0], faces[closest_face][3]);
		return points;
	}


	std::vector<glm::vec4> MajikCollisions::GetNormals(size_t& minFace)
	{
	
		std::vector<glm::vec4> normals;

		float minDistance = FLT_MAX;
		
		for (size_t i = 0; i < iface.size(); i++) {
			glm::vec3 a = polytope[iface[i].x];
			glm::vec3 b = polytope[iface[i].y];
			glm::vec3 c = polytope[iface[i].z];
			
			glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
			float distance = glm::dot(normal, a);

			if (distance < 0) {
				normal *= -1;
				distance *= -1;
			}
			glm::vec4 temp = glm::vec4(normal.x, normal.y, normal.z, distance);
			normals.push_back(temp);
			

			if (distance < minDistance) {
				minFace = i;
				minDistance = distance;
				
			}
		}

		return normals;
	}

	bool MajikCollisions::SupportExist(glm::vec3 support)
	{
		for (int i = 0; i < polytope.size(); i++)
		{
			if (polytope[i] == support)
			{
				return true;
				break;
			}
		}
		return false;
	}

	CollisionData MajikCollisions::EPA()
	{
		polytope = simplex;
		iface =
		{   glm::ivec3(0,1,2),
			glm::ivec3(0,1,3),
			glm::ivec3(1,2,3),
			glm::ivec3(2,0,3)
		};
		std::vector<glm::vec4> normals;
		size_t minFace = 0;
		bool isvalid;
		//if(collionPropertiesA.)

		for (int i = 0; i < 20; i++)
		{
			isvalid = true;

			normals = GetNormals(minFace);
			MainNormal = glm::vec3(normals[minFace]);
			glm::vec3 support = SupportPoint();
			if (SupportExist(support))
			{
				ConvertToIndex();
				CollisionData data;
				data.normal = glm::vec3(normals[minFace]);
				data.depth = normals[minFace].w;
				Contact_Points(data);
				return data;
				break;
			}
			polytope.push_back(support);
			RepairFace(isvalid);
			if (isvalid = false)
			{
				CollisionData data;
				data.normal = glm::normalize(collionPropertiesA.center - collionPropertiesB.center);
				data.depth = std::abs(glm::distance(collionPropertiesA.center, collionPropertiesB.center) - 0.5);
				Contact_Points(data);
				return data;
			}
			ConvertToIndex();
			
		}

		CollisionData data;
		data.normal = glm::vec3(normals[minFace]);
		data.depth = normals[minFace].w;
		Contact_Points(data);
		return data;
	}

	void MajikCollisions::RepairFace(bool &isvalid)
	{
		//std::vector<int> looseFace = {};
		//std::vector<glm::ivec3> looseFaces = {};
		//for (int i = 0; i < iface.size(); i++)
		//{
		//	glm::vec3 a = polytope[iface[i].x];
		//	glm::vec3 b = polytope[iface[i].y];
		//	glm::vec3 c = polytope[iface[i].z];

		//	glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
		//	glm::vec3 pointTovertex = polytope.back() - a;
		//	float distance = glm::dot(normal, a);
		//	if (distance < 0) {
		//		normal *= -1;
		//		distance *= -1;
		//	}
		//	if (glm::dot(pointTovertex, normal) > 0)
		//	{
		//		looseFace.push_back(i);
		//		
		//	}
		//}
		//MinB = looseFace.size();
		//
		////iface.push_back(glm::ivec3(iface[minFace].x, iface[minFace].y, polytope.size() - 1));
		////iface.push_back(glm::ivec3(iface[minFace].x, iface[minFace].z, polytope.size() - 1));
		////iface.push_back(glm::ivec3(iface[minFace].y, iface[minFace].z, polytope.size() - 1));
		//std::reverse(looseFace.begin(), looseFace.end());
		//for (int i = 0; i < looseFace.size(); i++)
		//{
		//	
		//	glm::ivec2 a = glm::ivec2(iface[looseFace[i]].x, iface[looseFace[i]].y);
		//	glm::ivec2 b = glm::ivec2(iface[looseFace[i]].x, iface[looseFace[i]].z);
		//	glm::ivec2 c = glm::ivec2(iface[looseFace[i]].y, iface[looseFace[i]].z);

		//	
		//	edges.push_back(a);
		//	edges.push_back(b);
		//	edges.push_back(c);
		//	looseFaces.push_back(iface[looseFace[i]]);
		//}
		//std::vector<glm::ivec3> tempFaces = {};
		//for (int k = 0; k < looseFaces.size(); k++)
		//{
		//	tempFaces.clear();

		//	for (int i = 0; i < iface.size(); i++)
		//	{
		//		if (iface[i] != looseFaces[k])
		//		{
		//			tempFaces.push_back(iface[i]);
		//		}
		//	
		//	}
		//	iface.clear();
		//	iface = tempFaces;
		//}

		//
		//for (int i = 0; i < edges.size(); i++)
		//{
		//	glm::ivec3 temp = glm::ivec3(edges[i].x, edges[i].y, polytope.size() - 1);
		//	iface.push_back(temp);
		//	
		//	//std::cout << "hello";
		//}
		
		quickhull::QuickHull<float> qh; // Could be double as well
		std::vector<quickhull::Vector3<float>> pointCloud;
		// Add points to point cloud
		for (int i = 0; i < polytope.size(); i++)
		{
			pointCloud.push_back(quickhull::Vector3<float>(polytope[i].x, polytope[i].y, polytope[i].z));

		}
		auto hull = qh.getConvexHull(pointCloud, true, false);
		quickhull::DiagnosticsData sd = qh.getDiagnostics();
		
		isvalid = sd.failed_to_create;

		const auto& indexBuffer = hull.getIndexBuffer();
		const auto& vertexBuffer = hull.getVertexBuffer();
		MinB = indexBuffer.size();
		polytope.clear();
		for (int i = 0; i < vertexBuffer.size(); i++)
		{
			polytope.push_back(glm::vec3(vertexBuffer[i].x, vertexBuffer[i].y, vertexBuffer[i].z));
		}
		iface.clear();
		for (int i = 0; i < indexBuffer.size(); i+=3)
		{
			iface.push_back(glm::ivec3(indexBuffer[i], indexBuffer[i+1], indexBuffer[i+2]));
		}

		

	}
	void MajikCollisions::Contact_Points(CollisionData& points)
	{
		//collionPropertiesA.collisionData = points;
		//collionPropertiesB.collisionData = points;
	/*	SphereAndSphere(points);
		SphereAndPlane(points);
		if (collionPropertiesA.collisionData.contact_points.size() > 0)
		{
			contact = collionPropertiesA.collisionData.contact_points[0];
		}*/
	}
	void MajikCollisions::SphereAndSphere(CollisionData& data)
	{
		if (collionPropertiesA.shape == Sphere && collionPropertiesB.shape == Sphere)
		{
			glm::vec3 midline = collionPropertiesB.center - collionPropertiesA.center;
			float size = glm::length(midline);
			if (size <= 0 || size >= collionPropertiesA.raduis + collionPropertiesB.raduis)
			{
				
			}
			else
			{
				glm::vec3 normal = midline * 1.0f / size;
				
				data.normal = normal;
				data.contact_points.clear();
				data.contact_points.push_back(collionPropertiesA.center + midline * 0.5f);
				data.depth = (collionPropertiesA.raduis + collionPropertiesB.raduis - size);

				collionPropertiesA.collisionData = data;
				contact = collionPropertiesA.collisionData.contact_points[0];
				//contact->body[0] = one.body;
				//contact->body[1] = two.body;
			}
		}
		
	}
	void MajikCollisions::SphereAndPlane(CollisionData& data)
	{
		if (collionPropertiesA.shape == Sphere && collionPropertiesB.shape == Plane)
		{
			
			data.contact_points.clear();
			data.contact_points.push_back((data.normal* collionPropertiesA.raduis)+ collionPropertiesA.center);
			collionPropertiesA.collisionData = data;
			contact = collionPropertiesA.collisionData.contact_points[0];
		}
		
	}



	bool MajikCollisions::ToD_Particles_Collision(const CollionProperties collionPropertiesA, const CollionProperties collionPropertiesB, glm::vec3& p_normal, float& p_depth)
	{
		
		if (collionPropertiesA.shape == Circle && collionPropertiesB.shape == Circle)
		{
			float distance = glm::distance(collionPropertiesA.center, collionPropertiesB.center);
			float radii = collionPropertiesA.raduis + collionPropertiesB.raduis;
			if (distance >= radii)
			{
				return false;
			}
			else
			{
				p_normal = glm::normalize(collionPropertiesB.center - collionPropertiesA.center);
				p_depth = radii - distance;

				return true;

			}

		} // sphere on sphere

		if (collionPropertiesA.shape == Polygon && collionPropertiesB.shape == Polygon)
		{
			float overlap = FLT_MAX;
			glm::vec3 overlapNormal = glm::vec3(0,0,0);

			for (auto Norm_a : collionPropertiesA.normals)
			{
				float minA = FLT_MAX;
				float maxA = FLT_MIN;
				for (auto va : collionPropertiesA.vertices)
				{
					float proja = glm::dot(va, Norm_a);
					if (proja < minA)
					{
						minA = proja;
					}
					if (proja > maxA)
					{
						maxA = proja;
					}
				}

				float minB = FLT_MAX;
				float maxB = FLT_MIN;
				for (auto vb : collionPropertiesB.vertices)
				{
					float projb = glm::dot(vb, Norm_a);
					if (projb < minB)
					{
						minB = projb;
					}
					if (projb > maxB)
					{
						maxB = projb;
					}
				}

				if (minA > maxB || minB > maxA)
				{
					return false; // found a gap
				}
				float depth = std::min(maxB - minA, maxA - minB);
				if (depth < overlap)
				{
					overlap = depth;
					overlapNormal = Norm_a;
				}
				
			}

			for (auto Norm_b : collionPropertiesB.normals)
			{
				float minA = FLT_MAX;
				float maxA = FLT_MIN;
				for (auto va : collionPropertiesA.vertices)
				{
					float proja = glm::dot(va, Norm_b);
					if (proja < minA)
					{
						minA = proja;
					}
					if (proja > maxA)
					{
						maxA = proja;
					}
				}

				float minB = FLT_MAX;
				float maxB = FLT_MIN;
				for (auto vb : collionPropertiesB.vertices)
				{
					float projb = glm::dot(vb, Norm_b);
					if (projb < minB)
					{
						minB = projb;
					}
					if (projb > maxB)
					{
						maxB = projb;
					}
				}

				if (minA > maxB || minB > maxA)
				{
					return false; // found a gap
				}
				float depth = std::min(maxB - minA, maxA - minB);
				if (depth < overlap)
				{
					overlap = depth;
					overlapNormal = Norm_b;
				}

			}

			p_normal = overlapNormal;
			
			p_depth = overlap;
			
			return true; // no gap found, the polygons are colliding
		}



		if (collionPropertiesA.shape == Polygon && collionPropertiesB.shape == Circle || collionPropertiesA.shape == Circle && collionPropertiesB.shape == Polygon)
		{
			if (collionPropertiesA.shape == Polygon)
			{
				return  Circle_Polygon(collionPropertiesA, collionPropertiesB, p_normal, p_depth);
			}
			else
			{
				return  Circle_Polygon(collionPropertiesB, collionPropertiesA, p_normal, p_depth);
			}

		
		}

	

		return false;

		
	}
		
	void MajikCollisions::Check_Clipping(PhysicsProperties& physicsPropertiesA, glm::vec3 offset)
	{
		physicsPropertiesA.position = physicsPropertiesA.position + offset;
	}
	bool MajikCollisions::Circle_Polygon(CollionProperties collionPropertiesA, CollionProperties collionPropertiesB, glm::vec3& normal, float& depth)
	{
		float overlap = FLT_MAX;
		glm::vec3 overlapNormal;
		for (auto Norm_a : collionPropertiesA.normals)
		{
			float minA = FLT_MAX;
			float maxA = FLT_MIN;
			for (auto va : collionPropertiesA.vertices)
			{
				float proja = glm::dot(va, Norm_a);
				if (proja < minA)
				{
					minA = proja;
				}
				if (proja > maxA)
				{
					maxA = proja;
				}
			}
			float minB = FLT_MAX;
			float maxB = FLT_MIN;
			glm::vec3 projb_1 = collionPropertiesB.center + Norm_a * collionPropertiesB.raduis;
			glm::vec3 projb_2 = collionPropertiesB.center - Norm_a * collionPropertiesB.raduis;

			float p1 = glm::dot(projb_1, Norm_a);
			float p2 = glm::dot(projb_2, Norm_a);

			minB = std::min(p1, p2);
			maxB = std::max(p1, p2);
			if (minA > maxB || minB > maxA)
			{
				return false; // found a gap
			}
			float depth = std::min(maxB - minA, maxA - minB);
			if (depth < overlap)
			{
				overlap = depth;
				overlapNormal = Norm_a;
			}
		}

		glm::vec3 Norm_a = FindclosestPoint(collionPropertiesA, collionPropertiesB.center);
		float minA = FLT_MAX;
		float maxA = FLT_MIN;
		for (auto va : collionPropertiesA.vertices)
		{
			float proja = glm::dot(va, Norm_a);
			if (proja < minA)
			{
				minA = proja;
			}
			if (proja > maxA)
			{
				maxA = proja;
			}
		}
		float minB = FLT_MAX;
		float maxB = FLT_MIN;
		glm::vec3 projb_1 = collionPropertiesB.center + Norm_a * collionPropertiesB.raduis;
		glm::vec3 projb_2 = collionPropertiesB.center - Norm_a * collionPropertiesB.raduis;

		float p1 = glm::dot(projb_1, Norm_a);
		float p2 = glm::dot(projb_2, Norm_a);

		minB = std::min(p1, p2);
		maxB = std::max(p1, p2);
		if (minA > maxB || minB > maxA)
		{
			return false; // found a gap
		}
		float sdepth = std::min(maxB - minA, maxA - minB);
		if (sdepth < overlap)
		{
			overlap = sdepth;
			overlapNormal = Norm_a;
		}

		normal = overlapNormal;
		depth = overlap;
		return true;
	}
}
	

	

