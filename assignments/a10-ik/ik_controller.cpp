#include "ik_controller.h"
#include <cmath>
#include <iostream>

using namespace atk;
using namespace glm;
using namespace std;

bool IKController::solveIKAnalytic(Skeleton& skeleton, 
    int jointid, const vec3& goalPos, float epsilon) {
  if (jointid == -1) return true;

  Joint* ankle = skeleton.getByID(jointid);
  if (!ankle->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* knee = ankle->getParent();
  if (!knee->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* hip = knee->getParent();

  // TODO: Your code here
  return true;
}

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {

//skeleton - character to modify
//jointid - the id of the joint to pose 
//goalpos - the target position for jointid (global)
//chain - the list of joints to nudge towards the goal
//threshold - when the given joint is within threshold of the goal, stop iterating 
//maxIters - the max number of iterations to try to reach the goal 

//p - end effectors position in global 
//for each joint in the chain from end effector to root "nudge" joint towards pd - update p with ned ee position

//nudge - deltaPhi = c atan2(||rxe||,r*r+r*e)

  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;

  vec3 p = skeleton.getByID(jointid)->getGlobalTranslation();
  vec3 tc = goalPos - p; 
  float tc2 = sqrt(tc.x*tc.x + tc.y*tc.y + tc.z*tc.z);
  int iterations = 0;
  while(tc2 > threshold && iterations < maxIters){
    for(int i = 0; i < chain.size(); i++){
      Joint* joint = chain[i];
      vec3 r = joint->getGlobalTranslation() - (joint->getParent()->getGlobalTranslation()); 
      vec3 e = goalPos - joint->getGlobalTranslation();
      //end effector - chain[0]?
      vec3 rCe = glm::cross(r,e);
      float mag = sqrt(rCe.x*rCe.x + rCe.y*rCe.y + rCe.z*rCe.z);
      float deltaPhi = nudgeFactor*atan2(mag,glm::dot(r,r)+glm::dot(r,e));
      vec3 axis = glm::cross(r,e)/mag;
      quat nudge = angleAxis(deltaPhi,axis);
      joint->setLocalRotation(joint->getLocalRotation()*nudge);
      //NUDGE??? 
      //UPDATE P???
    }
  }

  // for(int i = 0; i < chain.length(); i++){
  //   vec3 r = chain[i]->getGlobalTranslation()-(chain[i]->getParent())->getGlobalTranslation();
  //   vec3 e = target - chain[i]->getGlobalTranslation();
  // }

  // TODO: Your code here
  return false;
}
