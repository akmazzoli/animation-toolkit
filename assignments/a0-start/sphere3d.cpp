#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:

  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }

  virtual void setup(){
    position = vec3(0,0,0);
    velocity = vec3(0,0,0);
  }
  
  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    position = position + velocity*dt();
    setColor(vec3(0,1,0));

    // draw a sphere at center of the world
    float radius = 50.0;
    drawSphere(position,radius);
  }
  vec3 position;
  vec3 velocity;

  void keyUp(int key, int mods){
    if(key == GLFW_KEY_SPACE){
      velocity = 50.0f * agl::randomUnitVector();
    }
    if(key == GLFW_KEY_R){
      position = vec3(0,0,0);
      velocity = vec3(0,0,0);
    }
  }
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
