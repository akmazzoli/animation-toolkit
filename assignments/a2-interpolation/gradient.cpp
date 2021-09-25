#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class Gradient : public atkui::Framework {
 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    n = width()/20;
    nw = vec3(1,1,0);
    ne = vec3(0,1,1);
    sw = vec3(1,0,0);
    se = vec3(1,0,1);
  }

  virtual void scene() {
    setColor(vec3(0,1,0));
    for(int i = 0; i < 20;i++){
      for(int j = 0; j < 20; j++){
        float t = i*n/width();
        t = glm::clamp(t, 0.0f, 1.0f);
        vec3 cx0 = vec3(nw*(1-t) + ne*t);
        vec3 cx1 = vec3(sw*(1-t) + se*t);
        t = j*n/height();
        t = glm::clamp(t, 0.0f, 1.0f);
        vec3 c = vec3(cx0*(1-t) + cx1*t);
        setColor(vec3(c));
        drawCube(vec3(n*i+n/2,j*n+n/2,0),vec3(n,n,0));
      }
    }
  }
  int n;
  vec3 ne;
  vec3 nw;
  vec3 se;
  vec3 sw;
};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
