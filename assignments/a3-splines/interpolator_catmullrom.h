#ifndef _interpolator_catmullrom_
#define _interpolator_catmullrom_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Catmull-Rom 
//--------------------------------

class InterpolatorCatmullRom : public Interpolator
{
public:
    InterpolatorCatmullRom() : Interpolator("Catmull-Rom") {}

    virtual glm::vec3 interpolate(int segment, double u) const {
       int i = segment*4;
       glm::vec3 b0 = mCtrlPoints[i];
       glm::vec3 b1 = mCtrlPoints[i+1];
       glm::vec3 b2 = mCtrlPoints[i+2];
       glm::vec3 b3 = mCtrlPoints[i+3];

       float a = (std::pow((1-u),3));
       float b = (3*u*std::pow((1-u),2));
       float c = (3*std::pow(u,2)*(1-u));
       float d = (std::pow(u,3));
       glm::vec3 next = a*b0 + b*b1 + c*b2 + d*b3;

       return next;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       for(int i = 0; i < keys.size()-1; i++){
          int size = keys.size();
          glm::vec3 b0;
          glm::vec3 b1;
          glm::vec3 b2;
          glm::vec3 b3;

          b0 = keys[i];
          b3 = keys[i+1];

          if(i == 0){
             glm::vec3 term0 = (keys[1] - keys[0])/float(6.0);
             b1 = b0 + term0;
          }else{
             glm::vec3 term1 = (keys[i+1]-keys[i-1])/float(6.0);
             b1 = keys[i] + term1;
          }
          if(i == keys.size()-2){
             glm::vec3 term2 = (keys[size-1] - keys[size-2])/float(6.0);
             b2 = b3 - term2;
          }else{
             b2 = keys[i+1] - (keys[i+2] - keys[i])/float(6.0);
          }

          mCtrlPoints.push_back(b0);
          mCtrlPoints.push_back(b1);
          mCtrlPoints.push_back(b2);
          mCtrlPoints.push_back(b3);
       }

    }
};

//use formulation from class 
//

#endif
