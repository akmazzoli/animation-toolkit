#include "atkui/framework.h"
using namespace glm;

class Screensaver : public atkui::Framework {
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    curve1.b0 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
    curve1.b1 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
    curve1.b2 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
    curve1.b3 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
    curve1.color = agl::randomUnitVector();
  
    curve2.b0 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
    curve2.b1 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
    curve2.b2 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
    curve2.b3 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
    curve2.color = agl::randomUnitVector();
    current = curve1;
    t = 0;
    m = 0;

    //curves.push_back(curve1);
  }

  void scene() {

    curve1.last = curve1.b0;
    for(float t = 0.0f; t < 1.0f; t = t+0.01f){
       float a = (std::pow((1-t),3));
       float b = (3*t*std::pow((1-t),2));
       float c = (3*std::pow(t,2)*(1-t));
       float d = (std::pow(t,3));
       curve1.next = a*curve1.b0 + b*curve1.b1 + c*curve1.b2 + d*curve1.b3;
       setColor(curve1.color);
       drawLine(curve1.last,curve1.next);
      curve1.last = curve1.next;
    }

    curve2.last = curve2.b0;
    for(float t = 0.0f; t < 1.0f; t = t+0.01f){
       float a = (std::pow((1-t),3));
       float b = (3*t*std::pow((1-t),2));
       float c = (3*std::pow(t,2)*(1-t));
       float d = (std::pow(t,3));
       curve2.next = a*curve2.b0 + b*curve2.b1 + c*curve2.b2 + d*curve2.b3;
       setColor(curve2.color);
       drawLine(curve2.last,curve2.next);
      curve2.last = curve2.next;
    }

    t = t + 0.001;
    m++;
    if(m > 120){
      m = 0;
    }
    if(t > 1){
      t = 0;
      //current.color = agl::randomUnitVector();
      curve1 = current;
      curve2.b0 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
      curve2.b1 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
      curve2.b2 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
      curve2.b3 = vec3(rand() % (int)width() + 1,rand() % (int)height() + 1,0);
      curve2.color = agl::randomUnitVector();
    }
    //interpolate control points
    current.b0 = vec3(curve1.b0*(1-t) + curve2.b0*t);
    current.b1 = vec3(curve1.b1*(1-t) + curve2.b1*t);
    current.b2 = vec3(curve1.b2*(1-t) + curve2.b2*t);
    current.b3 = vec3(curve1.b3*(1-t) + curve2.b3*t);
    current.color = vec3(curve1.color*(1-t) + curve2.color*t);

    if (m == 4){
      Curve trailer;
      trailer.b0 = current.b0;
      trailer.b1 = current.b1;
      trailer.b2 = current.b2;
      trailer.b3 = current.b3;
      trailer.color = current.color;
      curves.push_back(trailer);
      if(curves.size() > 10){
        curves.pop_front();
      }
    }

    current.last = current.b0;
    for(float t = 0.0f; t < 1.0f; t = t+0.01f){
       float a = (std::pow((1-t),3));
       float b = (3*t*std::pow((1-t),2));
       float c = (3*std::pow(t,2)*(1-t));
       float d = (std::pow(t,3));
       current.next = a*current.b0 + b*current.b1 + c*current.b2 + d*current.b3;
       setColor(current.color);
       drawLine(current.last,current.next);
      current.last = current.next;
    }

    for(std::list<Curve>::iterator it=curves.begin(); it != curves.end(); ++it){
        vec3 trailerNext = it->next;
        vec3 trailerLast = it->last;
        vec3 trailerb0 = it->b0;
        vec3 trailerb1 = it->b1;
        vec3 trailerb2 = it->b2;
        vec3 trailerb3 = it->b3;
        vec3 trailerColor = it->color;
        for(float t = 0.0f; t < 1.0f; t = t+0.01f){
          float a = (std::pow((1-t),3));
          float b = (3*t*std::pow((1-t),2));
          float c = (3*std::pow(t,2)*(1-t));
          float d = (std::pow(t,3));
          trailerNext = a*trailerb0 + b*trailerb1 + c*trailerb2 + d*trailerb3;
          setColor(trailerColor);
          drawLine(trailerLast,trailerNext);
          trailerLast = trailerNext;
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
  Curve curve1;
  Curve curve2;
  Curve current;
  float t;
  std::list<Curve> curves;
  int m;
};

int main(int argc, char** argv) {
  Screensaver viewer;
  viewer.run();
}

