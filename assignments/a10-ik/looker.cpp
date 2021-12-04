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

class ALooker : public atkui::Framework {
public:
   ALooker() : atkui::Framework(atkui::Perspective) {}
   virtual ~ALooker() {}

   void setup() {
      Motion motion;
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, motion);
      motion.update(_skeleton, 0);

      _drawer.color = vec3(1,0,0);
      _head = _skeleton.getByName("Beta:Head");
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
      float r = 100;
      float angle = elapsedTime();
      _target = vec3(r * cos(angle), r * sin(angle) + r, 150);

      reset(_head);
      lookAtTarget(_head, _target);
      _drawer.draw(_skeleton, *this);

      vec3 globalHeadPos = _head->getGlobalTranslation();
      vec3 globalForward = _head->getGlobalRotation() * vec3(0,0,1);

      setColor(vec3(0,0,1));
      drawLine(globalHeadPos, globalHeadPos + 200.0f*globalForward);
      drawSphere(_target, 5);
   }
   

   Cyclops _drawer;
   Skeleton _skeleton;
   Joint* _head;
   vec3 _target;
};

int main(int argc, char** argv) {
   ALooker viewer;
   viewer.run();
   return 0;
}

