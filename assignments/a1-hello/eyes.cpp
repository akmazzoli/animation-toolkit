#include "atkui/framework.h"

using namespace glm;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
    }

    virtual void scene() {

    //drawing the whites of the eyes
    setColor(vec3(255,255,255));
    double r1 = 120;

    double x1 = width() * 0.70;
    double y1 = height() * 0.5;
    drawSphere(vec3(x1,y1,0), r1);

    double x2 = width() * 0.30;
    double y2 = height() * 0.5;
    drawSphere(vec3(x2,y2,0), r1);

    float px1 = 40.0f * sin(elapsedTime()) + width()*0.70;
    float px2 = 40.0f * sin(elapsedTime()) + width()*0.30;

    //drawing and animating the pupils
    setColor(vec3(0,0,0));
    double r2 = 40;
    drawSphere(vec3(px1,y1,200), r2);
    drawSphere(vec3(px2,y2,200), r2);

    }
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
