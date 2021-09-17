#include "atkui/framework.h"

using namespace glm;

class Particles : public atkui::Framework
{
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {

/*
    vec3 pallet [10] = {
         vec3(255,100,73)/255.0f,
         vec3(25,118,101)/255.0f,
         vec3(27,88,74)/255.0f,
         vec3(58,118,141)/255.0f,
         vec3(168,197,206)/255.0f,
         vec3(255,100,73)/255.0f,
         vec3(25,118,101)/255.0f,
         vec3(27,88,74)/255.0f,
         vec3(58,118,141)/255.0f,
         vec3(168,197,206)/255.0f
      };
      */
    //initialize 100 random particles
    for(int i = 0; i < 300; i++){
      particles[i].position = 400.0f * agl::randomUnitVector();
      particles[i].position.z = 0;
      if(particles[i].position.x < 0){
        particles[i].position.x = particles[i].position.x * -1;
      }
      if(particles[i].position.y < 0){
        particles[i].position.y = particles[i].position.y * -1;
      }
      particles[i].velocity = (i/2.5f + 1) * vec3(3,3,0);
      particles[i].color = agl::randomUnitVector();
    }

  }

  virtual void scene() {
    double radius = 10;
    for(int i = 0; i < 300 ; i++){
      particles[i].position = particles[i].position + particles[i].velocity * dt();
      if(particles[i].position.x > width() || particles[i].position.x < 0){
        particles[i].position.x = 0;
      }
      if(particles[i].position.y > height() || particles[i].position.y < 0){
        particles[i].position.y = 0;
      }
    }
    for(int i = 0; i < 300; i++){
      setColor(particles[i].color);
      drawSphere(particles[i].position,radius);
    }
  }
  struct Particle {
    vec3 velocity;
    vec3 color;
    vec3 position;
  };
  Particle particles [300];
  vec3 pallet;
};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}
