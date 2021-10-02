#ifndef _interpolator_hermite_
#define _interpolator_hermite_

#include <string>
#include <vector>
#include <Eigen/Dense>
#include "interpolator.h"

//--------------------------------
// Hermite 
//--------------------------------

class InterpolatorHermite : public Interpolator
{
public:
    InterpolatorHermite() : Interpolator("Hermite"), mClampDir(glm::vec3(1,0,0)) {}

    virtual glm::vec3 interpolate(int segment, double u) const {
       //2 points and 2 slopes
       //b0,b3 slopes, p10,p11 points?
       vec3 b0;
       vec3 b3;
       glm::vec3 next = b0*(1-3(u*u)+2(u*u*u)) + mCtrlPoints[segment]*(u*(1-u)*(1-u)) + mCtrlPoints[segment+1]((u*u)+(u*u*u)) + b3(3(u*u)-2(u*u*u));
       return next;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       for(int i = 2; i < keys.size(); i = i++){
           mCtrlPoints.push_back(3(keys[i]-keys[i-2]));
       }
    }

    void setClamped(bool c) { mIsClamped = c; }
    //clamp end cases
    bool isClamped() const { return mIsClamped; }

    void setClampedDirection(const glm::vec3& v) { mClampDir = v; }
    glm::vec3 getClampDirection() const { return mClampDir; }

private:
    bool mIsClamped = true;
    glm::vec3 mClampDir;
};

#endif
