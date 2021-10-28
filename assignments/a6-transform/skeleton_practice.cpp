#include "atk/toolkit.h"
#include <iostream>
using namespace atk;
using glm::vec3;

int main(int argc, char** argv)
{
   Skeleton skeleton;
   Motion motion;

   BVHReader reader;
   reader.load("../motions/Beta/idle.bvh", skeleton, motion);

   int numJoints = skeleton.getNumJoints(); 
   std::cout << "The number of joints is " << numJoints << std::endl;

   // todo: loop through and print all joint names - DONE
   for (int i = 0; i < numJoints; i++)
   {
      Joint* joint = skeleton.getByID(i);
      std::string jointName = "";
      jointName = (*joint).getName();
      std::cout << i << " " << jointName << std::endl;
   }

   // todo get root of the skeleton - DONE
   Joint* root = skeleton.getRoot();
   std::string rootName = (*root).getName();
   std::cout << "The root joint name is: " << rootName << std::endl;
   int rootID = (*root).getID();
   std::cout << "The root joint ID is: " << rootID << std::endl;
   int numChildren = (*root).getNumChildren();
   std::cout << "The root joint's number of children is: " << numChildren << std::endl;

   // todo print the names of the children of the root - DONE
   int rootNumChildren = numChildren;
   for (int i = 0; i < rootNumChildren; i++)
   {
      Joint* child = (*root).getChildAt(i);
      std::string childName = (*child).getName();
      std::cout << childName << std::endl; 
   } 

   // Get the joint for the hand by looking up by name ("Beta:LeftHand") - DONE
   Joint* hand = skeleton.getByName("Beta:LeftHand");

   // vec3 offset; // todo get the local offset from the hand to its parent - HOW??
   // offset = (*hand).getLocal2Parent();
   // std::cout << "The offset between the left hand and its parent is " << glm::to_string(offset) << std::endl;

   //todo: get the hand's parent joint's name - ???
   Joint* parent = (*hand).getParent();
   //std::cout << (*hand).getID();
   // std::string handParentName = (*parent).getName();
   // std::cout << "The parent of the hand is " << handParentName << std::endl;
}
