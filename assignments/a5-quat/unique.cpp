#include "atkui/framework.h"
#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"
using namespace glm;
using atkmath::Deg2Rad;
using atkmath::Rad2Deg;


class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    n = width()/20;
    nw = vec3(1,1,0);
    ne = vec3(0,1,1);
    sw = vec3(1,0,0);
    se = vec3(1,0,1);

    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
  }

  void pushEulerRotation(const atkmath::Vector3& euler) {
    atkmath::Vector3 anglesRad = euler * Deg2Rad;
    rotate(anglesRad[0], vec3(1, 0, 0));
    rotate(anglesRad[1], vec3(0, 1, 0));
    rotate(anglesRad[2], vec3(0, 0, 1));
  }

  virtual void scene() {
    setColor(vec3(0,1,0));
    mouseMove(mousePosition().x,mousePosition().y);
    vec3 target = vec3(_mouseX, _mouseY, 100);
    setColor(vec3(1,0,0));
    drawSphere(target, 10);
    for(int i = 0; i < 20;i++){
      for(int j = 0; j < 20; j++){
        float t = i*n/width();
        t = glm::clamp(t, 0.0f, 1.0f);
        vec3 cx0 = vec3(nw*(1-t) + ne*t);
        vec3 cx1 = vec3(sw*(1-t) + se*t);
        t = j*n/height();
        t = glm::clamp(t, 0.0f, 1.0f);
        vec3 c = vec3(cx0*(1-t) + cx1*t);

      //get angle 
        float xpos = n*i+n/2;
        float ypos = j*n+n/2;
        vec3 cube = vec3(xpos,ypos,0);
        vec3 vect = target - cube;
        float theta = atan2(vect.y,vect.x);

        //use euler angle (0,0,theta)
        //rotation matrix z = cos -sin 0 sin cos 0 0 0 1


      // atkmath::Matrix3 mat;
      // mat.fromEulerAnglesXYZ(atkmath::Vector3(0,0,theta));
    
      // atkmath::Quaternion quat;
      // quat.fromMatrix(mat);
      // atkmath::Vector3 axis(0,0,1); double angle = theta;
      // quat.toAxisAngle(axis, angle);

      // atkmath::Matrix3 qmat = quat.toMatrix();
      //glm::mat4 qglm = qmat.writeToMat4();

      //theta = theta * Rad2Deg;
      atkmath::Vector3 rotvec = atkmath::Vector3(0,0,theta);
      rotvec = rotvec*Rad2Deg;

        setColor(vec3(c));
         push();
         pushEulerRotation(rotvec);
         // transform(qglm);
         drawCube(vec3(xpos,ypos,0),vec3(20,20,50));
         pop();
      }
    }
  }
    void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;

  }

 private:
  int _mouseX;
  int _mouseY;
  int n;
  vec3 ne;
  vec3 nw;
  vec3 se;
  vec3 sw;
};

int main(int argc, char **argv) {
  Unique viewer;
  viewer.run();
}