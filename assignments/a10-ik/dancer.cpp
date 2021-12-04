#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "cyclops.h"
#include "ik_controller.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class ADancer : public atkui::Framework
{
public:
   ADancer() : atkui::Framework(atkui::Perspective) {}
   virtual ~ADancer() {}

   void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, _motion);
      _drawer.color = vec3(1,0,0);
      // _lhandTarget = _skeleton.getByName("Beta:LeftHand")->getGlobalTranslation();
      // _rhandTarget = _skeleton.getByName("Beta:RightHand")->getGlobalTranslation();
      thetaRate = 2.0;
   }

   void update()
   {
      theta += thetaRate*dt();
      _motion.update(_skeleton, elapsedTime());

      _lhandTarget = vec3(50,35.0*sin(theta) +110.0,0);
      _rhandTarget = vec3(-50,35.0*sin(theta) +110.0,0);

       IKController ik;
       int jointIDR = _skeleton.getByName("Beta:RightHand")->getID();
       int jointIDL = _skeleton.getByName("Beta:LeftHand")->getID();

       std::vector<Joint*> rchain;
      rchain.push_back(_skeleton.getByName("Beta:RightHand"));
      rchain.push_back(_skeleton.getByName("Beta:RightElbow"));
      rchain.push_back(_skeleton.getByName("Beta:RightShoulder"));
      std::vector<Joint*> lchain;
      lchain.push_back(_skeleton.getByName("Beta:LeftHand"));
      lchain.push_back(_skeleton.getByName("Beta:LeftElbow"));
      lchain.push_back(_skeleton.getByName("Beta:LeftShoulder"));


       //ik.solveIKCCD(_skeleton, jointIDR, _rhandTarget, rchain, 0.2, 10, 1);
       //ik.solveIKCCD(_skeleton, jointIDL, _lhandTarget, lchain, 0.01, 300, 1);

   }

   void scene()
   {  
      update();
      _drawer.draw(_skeleton, *this);
      setColor(vec3(0,0,1));
      drawSphere(_lhandTarget, 20);
      drawSphere(_rhandTarget, 20);
   }

protected:
   Cyclops _drawer;
   Skeleton _skeleton;
   Motion _motion;

   // Hand target positions
   vec3 _lhandTarget;
   vec3 _rhandTarget;
   float theta;
   float thetaRate;
};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.run();
   return 0;
}

