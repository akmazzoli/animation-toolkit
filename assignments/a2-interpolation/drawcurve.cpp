#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class DrawCubic : public atkui::Framework
{
 public:
  DrawCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  virtual void setup(){
    b0 = vec3(100,  50, 0);
    b1 = vec3(150, 200, 0);
    b2 = vec3(250, 100, 0);
    b3 = vec3(300, 300, 0);
    bernstein = false;
    casteljau = false;
  }

  virtual void scene()
  {
    setColor(vec3(0,0,1));
    drawSphere(b0, 10);
    drawSphere(b3, 10);

    setColor(vec3(1,1,0));
    drawSphere(b1, 10);
    drawSphere(b2, 10);

    if(bernstein){
      last = b0;
      for(float t = 0.0f; t < 1.0f; t = t+0.01f){
        float a = (std::pow((1-t),3));
        float b = (3*t*std::pow((1-t),2));
        float c = (3*std::pow(t,2)*(1-t));
        float d = (std::pow(t,3));
        next = a*b0 + b*b1 + c*b2 + d*b3;
        setColor(vec3(1,1,0));
        drawLine(last,next);
        last = next;
      }
    }else if(casteljau){
      last = b0;
      for(float t = 0.0f; t < 1.0f; t = t+0.01f){
        vec3 b10 = b0*(1-t)+b1*t;
        vec3 b11 = b1*(1-t)+b2*t;
        vec3 b12 = b2*(1-t)+b3*t;

        vec3 b20 = b10*(1-t)+b11*t;
        vec3 b21 = b11*(1-t)+b12*t;

        vec3 b30 = b20*(1-t)+b21*t;
        next = b30;
        setColor(vec3(1,0,0));
        drawLine(last,next);
        last = next;
      }
    }

  }

  void keyUp(int key, int mod) {
    if (key == GLFW_KEY_1) {
      bernstein = true;
      casteljau = false;
    }
    else if (key == GLFW_KEY_2) {
      casteljau = true;
      bernstein = false;
    }
  }
  vec3 last;
  vec3 next;
  vec3 b0;
  vec3 b1;
  vec3 b2;
  vec3 b3;
  bool bernstein;
  bool casteljau;
};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}
