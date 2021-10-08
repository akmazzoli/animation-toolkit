#include "atkui/framework.h"
using namespace glm;
//using atkmath::Rad2Deg;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

virtual void setup() {

  }

virtual void scene(){

   // Matrix3 rot;
   // Vector3 euler(mXAngle, mYAngle, mZAngle);
   // Vector3 anglesRad = euler * Deg2Rad;
   // rotate(anglesRad[0], vec3(1, 0, 0));
   // rotate(anglesRad[1], vec3(0, 1, 0));
   // rotate(anglesRad[2], vec3(0, 0, 1));

   // testXYZ = rot.toEulerAnglesXYZ();
   // testXYZ = testXYZ * Rad2Deg;

   // setColor(vec3(0,1,0));
   // push();
   // translate(vec3(-1.75, -1.75, 0));
   // pushEulerRotation(XYZ, testXZY);
   // drawCube(vec3(250,250,0),vec3(100,100,100));  
}


};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
}

