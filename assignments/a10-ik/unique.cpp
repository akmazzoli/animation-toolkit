#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "cyclops.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;
using atkmath::Quaternion;
using atkmath::Matrix3;

class Unique : public atkui::Framework {
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   void setup() {
      Motion motion;
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, motion);
      motion.update(_skeleton, 0);

      _drawer.color = vec3(1,0,0);
      _head = _skeleton.getByName("Beta:Head");
      theta = 0;
      thetaRate = 1.6;
   }

   void reset(Joint* head) {
      head->setLocalRotation(IdentityQ);
      head->fk();
   }

   void lookAtTarget(Joint* head, const vec3& target) {

      vec3 zvec = target - head->getGlobalTranslation();
      vec3 xvec = glm::cross(vec3(0,1,0),zvec);
      vec3 yvec = glm::cross(zvec,xvec);
      zvec = glm::normalize(zvec);
      xvec = glm::normalize(xvec);
      yvec = glm::normalize(yvec);
      glm::mat3 mat = glm::mat3(xvec, yvec, zvec);

      quat q = quat(mat);
      head->setLocalRotation(inverse(head->getParent()->getGlobalRotation())*q*head->getLocalRotation());      
      head->fk();
   }

   void scene() {  
      theta += thetaRate*dt();
      float r = 100;
      float angle = elapsedTime();
      _target = vec3(300*cos(theta*(10*3.14/180)),300,300*sin(theta*(10*3.14/180)));

      reset(_head);
      lookAtTarget(_head, _target);
      _drawer.draw(_skeleton, *this);

      vec3 globalHeadPos = _head->getGlobalTranslation();
      vec3 globalForward = _head->getGlobalRotation() * vec3(0,0,1);

      setColor(vec3(0,0,1));
      drawLine(_target-vec3(50,50,50), _target+vec3(50,50,50));
      drawSphere(_target, 50);
      setColor(vec3(0,1,0));
      drawSphere(_target-vec3(30,30,30), 40);
      setColor(vec3(1,0,0));
      drawSphere(_target+vec3(30,30,30), 30);
      
   }
   Cyclops _drawer;
   Skeleton _skeleton;
   Joint* _head;
   vec3 _target;
   float theta;
   float thetaRate;
};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}

