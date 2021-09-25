#include "atkui/framework.h"
using namespace glm;

#include "atkui/framework.h"
using namespace glm;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
   for(int i = 0; i < 50; i++){
      Curve noodle;
      noodle.b0 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1,0);
      noodle.b1 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1,0);
      noodle.b2 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1,0);
      noodle.b3 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1,0);
      noodle.color = vec3(1,1,0);
      curves.push_back(noodle);
      t = 0;
   }
  }

  void scene() {
   t = t + 0.000000001;
   if(t > 1){
      t = 0;
   }
    for(std::list<Curve>::iterator it=curves.begin(); it != curves.end(); ++it){
         Curve curve1;
         Curve curve2;
        curve1.b0 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1.0,0);
        curve1.b1 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1.0,0);
        curve1.b2 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1.0,0);
        curve1.b3 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1.0,0);
   
        curve2.b0 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1.0,0);
        curve2.b1 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1.0,0);
        curve2.b2 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1.0,0);
        curve2.b3 = vec3(rand() % (int)width() + 1.0,rand() % (int)height() + 1.0,0);
        
        vec3 noodleNext = it->next;
        vec3 noodleLast = it->last;
        vec3 noodleb0 = it->b0;
        vec3 noodleb1 = it->b1;
        vec3 noodleb2 = it->b2;
        vec3 noodleb3 = it->b3;
        vec3 noodleColor = it->color;
        noodleb0 = vec3(curve1.b0*(1-t) + curve2.b0*t);
        noodleb1 = vec3(curve1.b1*(1-t) + curve2.b1*t);
        noodleb2 = vec3(curve1.b2*(1-t) + curve2.b2*t);
        noodleb3 = vec3(curve1.b3*(1-t) + curve2.b3*t);
        for(float t = 0.0f; t < 1.0f; t = t+0.01f){
          float a = (std::pow((1-t),3));
          float b = (3*t*std::pow((1-t),2));
          float c = (3*std::pow(t,2)*(1-t));
          float d = (std::pow(t,3));
          noodleNext = a*noodleb0 + b*noodleb1 + c*noodleb2 + d*noodleb3;
          setColor(noodleColor);
          drawLine(noodleLast,noodleNext);
          noodleLast = noodleNext;
        }
    }
  }
  struct Curve {
    vec3 b0;
    vec3 b1;
    vec3 b2;
    vec3 b3;
    vec3 last;
    vec3 next;
    vec3 color;
  };
  std::list<Curve> curves;
  float t;
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
}
