#include "atkui/framework.h"
#include "atk/toolkit.h"
using namespace atk;
using glm::vec3;

class Unique : public atkui::Framework {
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   virtual void setup() {
      lookAt(vec3(200), vec3(0));

      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,0,0));
      scorpion.addJoint(root);

      Joint* joint1  = new Joint("joint1");
      joint1->setLocalTranslation(vec3(25,0,0));
      scorpion.addJoint(joint1, root);

      Joint* joint2  = new Joint("joint2");
      joint2->setLocalTranslation(vec3(25,0,0));
      scorpion.addJoint(joint2, joint1);

      Joint* joint3  = new Joint("joint3");
      joint3->setLocalTranslation(vec3(25,0,0));
      scorpion.addJoint(joint3, joint2);

      Joint* joint4  = new Joint("joint4");
      joint4->setLocalTranslation(vec3(25,0,0));
      scorpion.addJoint(joint4, joint3);

      Joint* joint5  = new Joint("joint5");
      joint5->setLocalTranslation(vec3(-50,0,0));
      scorpion.addJoint(joint5,root);

      Joint* joint6  = new Joint("joint6");
      joint6->setLocalTranslation(vec3(-50,0,-20));
      scorpion.addJoint(joint6,joint5);

      Joint* joint7  = new Joint("joint7");
      joint7->setLocalTranslation(vec3(-50,0,20));
      scorpion.addJoint(joint7,joint5);

      scorpion.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
      for(int i = 0; i < 5; i++){
            glm::quat offset = glm::angleAxis(float(sin(elapsedTime())), vec3(1,1,0));
            Joint* joint = scorpion.getByID(i);
            joint->setLocalRotation(offset);
      }

      scorpion.fk(); // computes local2global transforms
      //setColor(vec3(0,1,0));

      // todo: loop over all joints and draw
      for(int i = 0; i < scorpion.getNumJoints(); i++){
          if(i == 0){
              continue;
          }
         Joint* joint = scorpion.getByID(i);
         Joint* parent = joint->getParent();
         vec3 globalParentPos = parent->getGlobalTranslation();
         vec3 globalPos = joint->getGlobalTranslation();
         if(i < 5 && i%2==0){
            setColor(vec3(65,128,0));
            drawEllipsoid(globalParentPos, globalPos, 10);
         }else if(i < 5){
            setColor(vec3(0,0,0));
            drawEllipsoid(globalParentPos, globalPos, 10);
         }else{
             globalParentPos = vec3(0,0,0);
             globalPos = joint->getGlobalTranslation();
            setColor(vec3(1,0,0));
            drawEllipsoid(globalParentPos,globalPos, 20);
         }
      }
   
   }

protected:
   Skeleton scorpion;
};

int main(int argc, char** argv)
{
   Unique viewer;
   viewer.run();
} 