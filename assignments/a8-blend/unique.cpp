#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace glm;
using namespace atk;
using namespace atkui;

class Unique : public atkui::Framework {
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _original);

      _zombieFreeze = ComputeArmFreeze(_original);
      _zombieOffset = ComputeArmOffset(_original);
      _windmill = ComputeArmWindmill(_original);
   }

   Motion ComputeArmOffset(const Motion& motion) {
      quat leftLocalRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightLocalRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowLocalRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result;
      result.setFramerate(motion.getFramerate());

      quat offsetL = leftLocalRot*inverse(leftArm->getLocalRotation());
      quat offsetR = rightLocalRot*inverse(rightArm->getLocalRotation());
      
       for(int i = motion.getNumKeys(); i > 0; i--){      
         Pose newPose = motion.getValue(i);
         newPose.jointRots[leftArm->getID()] = newPose.jointRots[leftArm->getID()]*offsetL;
         newPose.jointRots[rightArm->getID()] = newPose.jointRots[rightArm->getID()]*offsetR;
         newPose.jointRots[leftElbow->getID()] = elbowLocalRot;
         newPose.jointRots[rightElbow->getID()] = elbowLocalRot;

         result.appendKey(newPose);
      }

      return result;
   }

   Motion ComputeArmFreeze(const Motion& motion) {
      quat leftRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result;
      result.setFramerate(motion.getFramerate());

      for(int i = motion.getNumKeys(); i > 0; i--){      
         Pose newPose = motion.getValue(i);
         newPose.jointRots[leftArm->getID()] = leftRot;
         newPose.jointRots[rightArm->getID()] = rightRot;
         newPose.jointRots[leftElbow->getID()] = elbowRot;
         newPose.jointRots[rightElbow->getID()] = elbowRot;

         result.appendKey(newPose);
      }

      return result;
   }

   Motion ComputeArmWindmill(const Motion& motion) {
      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");

      Motion result;
      result.setFramerate(motion.getFramerate());
      
      for(int i = motion.getNumKeys(); i > 0; i--){

         quat leftRot = eulerAngleRO(XYZ, radians(vec3(18, 20*i, 33)));
         quat rightRot = eulerAngleRO(XYZ, radians(vec3(-18, -20*i, -33)));
         quat elbowRot = eulerAngleRO(XYZ, radians(vec3(0, 0, 0))); 

         Pose newPose = motion.getValue(i);
         newPose.jointRots[leftArm->getID()] = newPose.jointRots[leftArm->getID()]*leftRot;
         newPose.jointRots[rightArm->getID()] = newPose.jointRots[rightArm->getID()]*rightRot;
         newPose.jointRots[leftElbow->getID()] = elbowRot;
         newPose.jointRots[rightElbow->getID()] = elbowRot;

         result.appendKey(newPose);
      }

      return result;
   }

   void update() {
      double t =  elapsedTime() * 0.5;
      if (_currentMotion == 1) {
         _zombieFreeze.update(_skeleton, t);
         drawText("Joint edit type: freeze", 10, 15);

      } else if (_currentMotion == 2) {
         _zombieOffset.update(_skeleton, t);
         drawText("Joint edit type: offset", 10, 15);
      }else if(_currentMotion == 3){
         _windmill.update(_skeleton, t);
         drawText("Joint edit type: windmill", 10, 15);
      } else {
         _original.update(_skeleton, t);
         drawText("Joint edit type: none", 10, 15);
      }
   }

   void scene() {  
      update();
      _drawer.draw(_skeleton, *this);
   }

   void keyUp(int key, int mods) {
      if (key == '1') {
          _currentMotion = 1;
      } else if (key == '2') {
          _currentMotion = 2;
      } else if(key == '3') {
         _currentMotion = 3;
      }else if (key == '0') {
          _currentMotion = 0;
      }
   }

   SkeletonDrawer _drawer;
   Skeleton _skeleton;
   Motion _original;
   Motion _zombieFreeze;
   Motion _zombieOffset;
   Motion _windmill;
   int _currentMotion = 0;
};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}

