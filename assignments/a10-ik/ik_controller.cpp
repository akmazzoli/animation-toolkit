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

  // joint given by jointid needs to have global at goal 
  //rotations for parent and grandparent of jointid 
  //skeleton - character to modify
  //jointid - id of end effector 
  //goalpos - target position for jointid
  
  //use angle/axis ccd computation to solve for grandparent joint rotation
  vec3 d1 = knee->getGlobalTranslation() - hip->getGlobalTranslation();
  float l1 = length(d1);
  vec3 d2 = ankle->getGlobalTranslation() - knee->getGlobalTranslation();
  float l2 = length(d2);
  vec3 rVec = goalPos - hip->getGlobalTranslation();;
  float r = length(rVec);
  float cosPhi = (r*r - l1*l1 - l2*l2)/(-2*l1*l2);
  float phi = acos(cosPhi);
  float theta2z = phi - 180.0;

  vec3 limbDir = normalize(knee->getLocalTranslation());
  vec3 axis = cross(limbDir, vec3(0,0,-1));
  if(limbDir[1] < 0){
    axis = cross(limbDir, vec3(0,0,1));
  }

  quat rot = angleAxis(theta2z,inverse(knee->getGlobalRotation())*axis);
  knee->setLocalRotation(knee->getLocalRotation()*rot);

  float sinTheta1z = (-l2*sin(theta2z))/r;
  float theta1z = asin(sinTheta1z);

  quat rot2 = angleAxis(theta1z,inverse(hip->getGlobalRotation())*vec3(0,0,1));
  hip->setLocalRotation(hip->getLocalRotation()*rot2);

  //use the law of cosines to solve for the parent joint rotation

  ankle->fk();
  knee->fk();
  hip->fk();

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

  vec3 p = chain[0]->getGlobalTranslation();
  vec3 tc = goalPos - p; 
  float tc2 = glm::length(tc);
  int iterations = 0;
  while((tc2 > threshold) && (iterations < maxIters)){
    for(int i = 1; i < chain.size(); i++){
      Joint* joint = chain[i];
      Joint* end = chain[0];
      vec3 r = end->getGlobalTranslation() - joint->getGlobalTranslation();
      //goal minus end effector global 
      vec3 e = goalPos - end->getGlobalTranslation();
      //if e is less than 0.001, skip joint - continue 
      if(length(e) < 0.0001){
        continue;
      }
      vec3 rCe = glm::cross(r,e);
      float mag = length(rCe);
      if(mag < 0.0001){
        continue;
      }
      //if rce is close to 0, skip 
      float deltaPhi = nudgeFactor*atan2(mag,(glm::dot(r,r)+glm::dot(r,e)));
      vec3 axis = glm::cross(r,e)/mag;
      quat nudge = angleAxis(deltaPhi,inverse(joint->getParent()->getGlobalRotation())*axis);
      //same as looker on slack
      joint->setLocalRotation(joint->getLocalRotation()*nudge);
      joint->fk();
    }
    p = skeleton.getByID(jointid)->getGlobalTranslation();
    iterations++;
  }
  return false;
}
