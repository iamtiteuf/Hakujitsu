#ifndef ALL_PHYSICS_HEADERS
#define ALL_PHYSICS_HEADERS
#include "MajikCollisionsDetection.h"
#include "glm/gtx/rotate_vector.hpp"
#endif // !ALL_PHYSICS_HEADERS


   

  

      

    

    //DoSimplex() {
    // 
    // 

    //    if (this.simplexPoints.length == 2) {
    //        minkowskiView.WriteToConsole("2 vertices currently in simplex");
    //        minkowskiView.WriteToConsole("Origin is towards AB direction");
    //        var A = this.simplexPoints[0];
    //        var B = this.simplexPoints[1];
    //        var AB = A.clone().sub(B);
    //        var BO = B.clone().negate();

    //        this.simplexDirectionObjectOrigin = A.clone().add(B).divideScalar(2);
    //        this.simplexDirection = AB.clone().cross(BO).cross(AB);
    //    }
    //    else if (this.simplexPoints.length == 3) {
    //        minkowskiView.WriteToConsole("3 vertices currently in simplex");

    //        var A = this.simplexPoints[0];
    //        var B = this.simplexPoints[1];
    //        var C = this.simplexPoints[2];

    //        var CO = C.clone().negate();

    //        var CB = B.clone().sub(C);
    //        var CA = A.clone().sub(C);
    //        var CBA = CB.clone().cross(CA);
    //        var O = new THREE.Vector3();

    //        if (CBA.clone().cross(CA).dot(CO) > 0) {
    //            if (CA.dot(CO) > 0) {
    //                this.simplexPoints = [C, A];

    //                minkowskiView.WriteToConsole("Origin is towards AC direction. Removing vertex B");
    //                minkowskiView.WriteToConsole("Reassigning vertex letters...");

    //                this.simplexDirectionObjectOrigin = A.clone().add(C).divideScalar(2);
    //                this.simplexDirection = CA.clone().cross(CO).cross(CA);
    //            }
    //            else if (CB.dot(CO) > 0) {
    //                this.simplexPoints = [B, C];

    //                minkowskiView.WriteToConsole("Origin is towards BC direction. Removing vertex A");
    //                minkowskiView.WriteToConsole("Reassigning vertex letters...");

    //                this.simplexDirectionObjectOrigin = B.clone().add(A).divideScalar(2);
    //                this.simplexDirection = CB.clone().cross(CO).cross(CB);
    //            }
    //            else {
    //                this.simplexPoints = [C];

    //                minkowskiView.WriteToConsole("Origin is towards C direction. Removing vertices A and B");
    //                minkowskiView.WriteToConsole("Reassigning vertex letters...");

    //                this.simplexDirectionObjectOrigin = C;
    //                this.simplexDirection = CO;
    //            }
    //        }
    //        else {
    //            if (CB.clone().cross(CBA).dot(CO) > 0) {
    //                if (CB.dot(CO) > 0) {
    //                    this.simplexPoints = [B, C];

    //                    minkowskiView.WriteToConsole("Origin is towards BC direction. Removing vertex A");
    //                    minkowskiView.WriteToConsole("Reassigning vertex letters...");

    //                    this.simplexDirectionObjectOrigin = B.clone().add(C).divideScalar(2);
    //                    this.simplexDirection = CB.clone().cross(CO).cross(CB);
    //                }
    //                else {
    //                    this.simplexPoints = [C];

    //                    minkowskiView.WriteToConsole("Origin is towards C direction. Removing vertices A and B");
    //                    minkowskiView.WriteToConsole("Reassigning vertex letters...");

    //                    this.simplexDirectionObjectOrigin = C;
    //                    this.simplexDirection = CO;
    //                }
    //            }
    //            else if (CBA.clone().dot(CO) > 0) {
    //                this.simplexPoints = [B, A, C];

    //                minkowskiView.WriteToConsole("Origin is towards B, A, C direction");

    //                this.simplexDirectionObjectOrigin = B.clone().add(A).add(C).divideScalar(3);
    //                this.simplexDirection = CBA;
    //            }
    //            else {
    //                this.simplexPoints = [A, B, C];

    //                minkowskiView.WriteToConsole("Origin is towards A, B, C direction");

    //                this.simplexDirectionObjectOrigin = B.clone().add(A).add(C).divideScalar(3);
    //                this.simplexDirection = CBA.clone().negate();
    //            }
    //        }
    //    }
    //    else if (this.simplexPoints.length == 4) {
    //        var A = this.simplexPoints[0];
    //        var B = this.simplexPoints[1];
    //        var C = this.simplexPoints[2];
    //        var D = this.simplexPoints[3];

    //        var DO = D.clone().negate();
    //        var DC = C.clone().sub(D);
    //        var DB = B.clone().sub(D);
    //        var DA = A.clone().sub(D);
    //        var DBC = DB.clone().cross(DC);
    //        var DAB = DA.clone().cross(DB);
    //        var DCA = DC.clone().cross(DA);

    //        var O = new THREE.Vector3();

    //        if (DBC.dot(DO) > 0) {
    //            this.simplexPoints = [D, B, C];

    //            minkowskiView.WriteToConsole("Origin is outside tetrahedron. Removing vertex A");
    //            minkowskiView.WriteToConsole("Reassigning vertex letters...");

    //            this.simplexDirectionObjectOrigin = D.clone().add(B).add(C).divideScalar(3);
    //            this.simplexDirection = DBC;
    //        }
    //        else if (DAB.dot(DO) > 0) {
    //            this.simplexPoints = [D, A, B];

    //            minkowskiView.WriteToConsole("Origin is outside tetrahedron. Removing vertex C");
    //            minkowskiView.WriteToConsole("Reassigning vertex letters...");

    //            this.simplexDirectionObjectOrigin = D.clone().add(A).add(B).divideScalar(3);
    //            this.simplexDirection = DAB;
    //        }
    //        else if (DCA.dot(DO) > 0) {
    //            this.simplexPoints = [D, C, A];

    //            minkowskiView.WriteToConsole("Origin is outside tetrahedron. Removing vertex B");
    //            minkowskiView.WriteToConsole("Reassigning vertex letters...");

    //            this.simplexDirectionObjectOrigin = D.clone().add(C).add(A).divideScalar(3);
    //            this.simplexDirection = DCA;
    //        }
    //        else {
    //            // Origin is contained
    //            this.isSimplexDone = true;
    //            minkowskiView.WriteToConsole("Origin is enclosed in tetrahedron");
    //            minkowskiView.WriteToConsole("Collision detected.");
    //        }
    //    }
    //},
    //