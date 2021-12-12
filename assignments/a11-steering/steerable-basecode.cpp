#include "steerable.h"
#include "behaviors.h"

using namespace glm;
using namespace atk;

float ASteerable::kVelKv = 150.0; 
float ASteerable::kOriKv = 150.0;  
float ASteerable::kOriKp = 150.0;

// Given a desired velocity, veld, and dt, compute a transform holding 
// the new orientation and change in position
//
// rotation control: tau = I * (-Kv1 * thetaDot + Kp1 * (thetaD - theta))
// translation control: f = m * Kv0 * (vd - v)
void ASteerable::senseControlAct(const vec3& veld, float dt)
{
   //Z IS FORWARD ROTATE AROUND Y 
   // Compute _vd and _thetad
   _vd = length(veld);
   _thetad = atan2(veld.x,veld.z);

   // compute _force and _torque - torque to spin it, linear forces to push and pull it 
   _force = _mass*kVelKv*(_vd-_state[2]);
   float a = _thetad-_state[1];
   if(a < -180.0f){
      a = a + 360.0f;
   }
   if(a > 180.0f){
      a = a - 360.0f;
   }
   _torque = _inertia*(kOriKp*(a) - kVelKv*_state[3]);

   // find derivative - [v, f/ma] - f is all forces - ma 
   _derivative[0] = _state[2];
   _derivative[1] = _state[3];
   _derivative[2] = (float)_force/_mass;
   _derivative[3] = (float)_torque/_inertia;

   _state[0] = _derivative[0]*dt;
   _state[1] = _derivative[1]*dt;
   _state[2] = _derivative[2]*dt;
   _state[3] = _derivative[3]*dt;

   // update state

   // compute global position and orientation and update _characterRoot
   quat rot = glm::angleAxis(_state[ORI], vec3(0,1,0));
   vec3 localPos(0,0,_state[POS]);

   _characterRoot.setT(rot * localPos + _characterRoot.t());
   _characterRoot.setR(rot); 
}

// randomize the colors, characters, and animation times here
void ASteerable::randomizeAppearance()
{
   // to randomize the walking animations, compute different initial values 
   // for _time

   // to randomize color, call _drawer.setColor

   // to randomize shape, compute random values for _drawer.setJointRadius
   // or randomly assign different drawers to have a mix of characters
}

