#ifndef _interpolator_linear_H_
#define _interpolator_linear_H_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Linear 
//--------------------------------

class InterpolatorLinear : public Interpolator
{
public:
    InterpolatorLinear() : Interpolator("Linear") {}
    virtual glm::vec3 interpolate(int segment, double u) const {
       float t = 1.0-u;
       glm::vec3 line = mCtrlPoints[segment-1]*t + mCtrlPoints[segment]*float(u);
       return line;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       for(int i = 0; i < keys.size(); i++){
          mCtrlPoints.push_back(keys[i]);
       }
    }
};

#endif
