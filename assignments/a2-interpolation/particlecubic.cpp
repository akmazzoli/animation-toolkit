#include "atkui/framework.h"
using namespace glm;

class ParticleCubic : public atkui::Framework {
 public:
  ParticleCubic() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    b0 = vec3(100,  50, 0);
    b1 = vec3(150, 200, 0);
    b2 = vec3(250, 100, 0);
    b3 = vec3(300, 300, 0);
    t = 0;
  }

  void scene() {
    last = b0;
    for(float t = 0.0f; t < 1.0f; t = t+0.01f){
       float a = (std::pow((1-t),3));
       float b = (3*t*std::pow((1-t),2));
       float c = (3*std::pow(t,2)*(1-t));
       float d = (std::pow(t,3));
       next = a*b0 + b*b1 + c*b2 + d*b3;
       setColor(vec3(0,1,0));
       drawLine(last,next);
      last = next;
    }

    if(elapsedTime() < 5){
      t = elapsedTime()/5;
    }else{
      t = fmod(elapsedTime(),5)/5;
    }
    float a = (std::pow((1-t),3));
    float b = (3*t*std::pow((1-t),2));
    float c = (3*std::pow(t,2)*(1-t));
    float d = (std::pow(t,3));
    next = a*b0 + b*b1 + c*b2 + d*b3;
    setColor(vec3(1,1,0));
    drawSphere(next,10);
  }
  vec3 last;
  vec3 next;
  vec3 b0;
  vec3 b1;
  vec3 b2;
  vec3 b3;
  float t;
};

int main(int argc, char** argv) {
  ParticleCubic viewer;
  viewer.run();
}

