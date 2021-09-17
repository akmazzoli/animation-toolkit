#include "atkui/framework.h"

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;

    x1 = width() * 0.70;
    y1 = height() * 0.5;
    px1 = x1;
    py1 = y1;
    x2 = width() * 0.30;
    y2 = height() * 0.5;
    px2 = x2;
    py2 = y2;
  }

  virtual void scene() {
    //drawing the whites of the eyes
    setColor(vec3(255,255,255));
    double r1 = 120;
    drawSphere(vec3(x1,y1,0), r1);
    drawSphere(vec3(x2,y2,0), r1);

    float px2 = 40.0f * sin(elapsedTime()) + width()*0.30;

    mouseMove(mousePosition().x,mousePosition().y);

    //right eye
    vec3 mouse = vec3(_mouseX,_mouseY,0);
    vec3 eyer = vec3(x1,y2,0);
    vec3 eyel = vec3(x2,y2,0);
    vec3 vectr = mouse - eyer; 
    vec3 vectl = mouse - eyel;

    float thetar = atan2(vectr.y,vectr.x);
    px1 = 30 * cos(thetar) + 0.7 * width();
    py1 = 30 * sin(thetar) + 0.5 * width();

    float thetal = atan2(vectl.y,vectl.x);
    px2 = 30 * cos(thetal) + 0.3 * width();
    py2 = 30 * sin(thetal) + 0.5 * width();

    //draw pupils
    setColor(vec3(0,0,0));
    double r2 = 40;
    drawSphere(vec3(px1,py1,200), r2);
    drawSphere(vec3(px2,py2,200), r2);

    //draw red dot
    vec3 target = vec3(_mouseX, _mouseY, 0);
    setColor(vec3(1,0,0));
    drawSphere(target, 10);
  }

  float px1;
  float py1;
  float px2;
  float py2;
  double x2;
  double y2;
  double x1;
  double y1;

  void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;
  }

 private:
  int _mouseX;
  int _mouseY;
};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}
