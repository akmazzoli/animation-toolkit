#include "atkui/framework.h"

using namespace glm;

class Unique : public atkui::Framework {
  public:
    Unique() : atkui::Framework(atkui::Orthographic) {
    }

    virtual void setup(){

      //RING 1 PALLET
      vec3 pallet1 [5] = {
         vec3(255,203,153)/255.0f,
         vec3(255,188,121)/255.0f,
         vec3(255,170,87)/255.0f,
         vec3(255,153,54)/255.0f,
         vec3(255,127,0)/255.0f,
      };

      //ACCENT RING 1 PALLET
      vec3 apallet1 [5] = {
         vec3(201,91,0)/255.0f,
         vec3(214,112,7)/255.0f,
         vec3(225,125,0)/255.0f,
         vec3(255,195,102)/255.0f,
         vec3(255,226,181)/255.0f,
      };

      //ACCENT RING 2 PALLET
      vec3 apallet2 [5] = {
         vec3(255,247,205)/255.0f,
         vec3(245,235,154)/255.0f,
         vec3(245,235,179)/255.0f,
         vec3(238,218,109)/255.0f,
         vec3(253,253,172)/255.0f,
      };

      vec3 stormPallet [3] = {
         vec3(147,65,71)/255.0f,
         vec3(255,247,205)/255.0f,
         vec3(51,22,18)/255.0f,
      };

      thetaRate = 0.8;
      theta = 0.0;
      int colorCycler = 0;
      int apc1 = 0;
      int apc2 = 0;

      //initialize RING 1
      for(int i = 0; i < 360; i++){
        ring1[i].px = 0.0;
        ring1[i].py = 0.0;
        ring1[i].pz = 0.0;
        ring1[i].color = pallet1[colorCycler];
        if(i%36 == 0){
          if(colorCycler == 4){
            colorCycler = 0;
          }else{
            colorCycler++;
          }
        }
      }
      //INITIALIZE ACCENT RING 1
      for(int i = 0; i < 360; i++){
        aring1[i].px = 0.0;
        aring1[i].py = 0.0;
        aring1[i].pz = 0.0;
        aring1[i].color = apallet1[apc1];
        if(i%36 == 0){
          if(apc1 == 4){
            apc1 = 0;
          }else{
            apc1++;
          }
        }
      }

      //INITIALIZE ACCENT RING 2
      for(int i = 0; i < 360; i++){
        aring2[i].px = 0.0;
        aring2[i].py = 0.0;
        aring2[i].pz = 0.0;
        aring2[i].color = apallet2[apc2];
        if(i%36 == 0){
          if(apc2 == 4){
            apc2 = 0;
          }else{
            apc2++;
          }
        }
      }

      storm[0].px = 0.0;
      storm[0].py = height()*0.6;
      storm[0].pz = 100;
      storm[0].color = stormPallet[0];

      storm[1].px = 0.0;
      storm[1].py = 0.0;
      storm[1].pz = 120;
      storm[1].color = stormPallet[1];

      storm[2].px = 0.0;
      storm[2].py = 0.0;
      storm[2].pz = 120;
      storm[2].color = stormPallet[2];
    }

    virtual void scene(){
      theta = theta + thetaRate * elapsedTime();
      for(int i = 0; i < 360; i++){
        //UPDATE RING 1
        ring1[i].px = 200 * cos(theta+200 + i*(3.14/180)) + 0.5 * width();
        ring1[i].py = 100 * sin(theta-200 + i*(3.14/180)) + 0.5 * width();
        ring1[i].pz = 550 * -sin(theta-300 + i*(3.14/180)) + 0.5 * width();

        //UPDATE ACCENT RING 1
        aring1[i].px = 200 * cos(theta+200 + i*(3.14/180)) + 0.5 * width();
        aring1[i].py = 100 * sin(theta-200 + i*(3.14/180)) + 0.5 * width();
        aring1[i].pz = 475 * -sin(theta-300 + i*(3.14/180)) + 0.5 * width();

        //UPDATE ACCENT RING 1
        aring2[i].px = 200 * cos(theta+200 + i*(3.14/180)) + 0.5 * width();
        aring2[i].py = 100 * sin(theta-200 + i*(3.14/180)) + 0.5 * width();
        aring2[i].pz = 570 * -sin(theta-300 + i*(3.14/180)) + 0.5 * width();
      
         //UPDATE STORM
        storm[0].px = 5.0f * cos(elapsedTime()) + width()*0.55;

        storm[1].px = 5.0f * cos(elapsedTime()) + width()*0.55;
        storm[1].py = 3.0f * cos(elapsedTime()) + height()*0.59;

        storm[2].px = 4.0f * cos(theta+200 + i*(3.14/180)) + 0.55 * width();
        storm[2].py = 6.0f * sin(theta-200 + i*(3.14/180)) + 0.61 * width();
      }

      for(int i = 0; i < 360; i++){
        //DRAW RING1
        setColor(ring1[i].color);
        drawSphere(vec3(ring1[i].px,ring1[i].py,ring1[i].pz),20);

        //DRAW ACCENT RING 1
        setColor(aring1[i].color);
        drawSphere(vec3(aring1[i].px,aring1[i].py,aring1[i].pz),10);

        //DRAW ACCENT RING 2
        setColor(aring2[i].color);
        drawSphere(vec3(aring2[i].px,aring2[i].py,aring2[i].pz),10);

        //DRAW STORM
        setColor(storm[0].color);
        drawSphere(vec3(storm[0].px,storm[0].py,storm[0].pz),80);

        setColor(storm[1].color);
        drawSphere(vec3(storm[1].px,storm[1].py,storm[1].pz),60);

        setColor(storm[2].color);
        drawSphere(vec3(storm[2].px,storm[2].py,storm[2].pz),40);
      }
      //DRAW PLANET
      vec3 pColor = vec3(92,22,30)/255.0f;
      setColor(pColor);
      drawSphere(vec3(width()*0.5,height()*0.5,0),200);
    }

    float theta;
    float thetaRate;

    struct Particle {
      float px;
      float py;
      float pz;
      vec3 color;
    };

    Particle ring1 [360];
    Particle aring1 [360];
    Particle aring2 [360];
    Particle storm [3];
};

  int main(int argc, char** argv) {
    Unique viewer;
    viewer.run();
    return 0;
  }

