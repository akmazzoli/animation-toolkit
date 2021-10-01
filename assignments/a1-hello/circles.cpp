#include "atkui/framework.h"

using namespace glm;
class Circles : public atkui::Framework
{
public:
   Circles() : atkui::Framework(atkui::Orthographic) {
   }

   virtual void setup() {
      theta = 0.0;
      thetaRate = 0.2;

      vec3 pallet [11] = {
         vec3(255,100,73)/255.0f,
         vec3(25,118,101)/255.0f,
         vec3(27,88,74)/255.0f,
         vec3(58,118,141)/255.0f,
         vec3(168,197,206)/255.0f,
         vec3(255,100,73)/255.0f,
         vec3(25,118,101)/255.0f,
         vec3(27,88,74)/255.0f,
         vec3(58,118,141)/255.0f,
         vec3(168,197,206)/255.0f,
         vec3(255,100,73)/255.0f,
      };

      for(int i = 0; i < 11; i++){
         for(int j = 0; j < 36; j++){
            particles[j+(i*36)].px = 0.0;
            particles[j+(i*36)].py = 0.0;
            particles[j+(i*36)].r = i*30.0f;
            particles[j+(i*36)].color = pallet[i];
         }
      }
   }

   virtual void scene() {
      theta += thetaRate * dt();
      for(int i = 0; i < 11; i++){
         for(int j = 0; j < 36; j++){
            if(i%2 == 0){
               particles[j+(i*36)].px = particles[j+(i*36)].r * cos(theta+j*(10*3.14/180)) + 0.5 * width();
               particles[j+(i*36)].py = particles[j+(i*36)].r * sin(theta+j*(10*3.14/180)) + 0.5 * height();
            }else{
               particles[j+(i*36)].px = particles[j+(i*36)].r * cos(-theta+j*(10*3.14/180)) + 0.5 * width();
               particles[j+(i*36)].py = particles[j+(i*36)].r * sin(-theta+j*(10*3.14/180)) + 0.5 * height();
            }
         }
         for(int j = 0; j < 36; j++){
            setColor(particles[j+(i*36)].color);
            drawSphere(vec3(particles[j+(i*36)].px,particles[j+(i*36)].py,0),10);
         }
      }
   }

   struct Particle {
    float px;
    float py;
    float r;
    vec3 color;
   };
   Particle particles [396];

   private:
      float theta;
      float thetaRate;
      float r;
};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}
