#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class MotionViewer : public atkui::Framework
{
public:
   MotionViewer() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
   }

   void file(char* f){
      BVHReader reader;
      if(f == NULL || f == ""){
         reader.load("../motions/Beta/jump.bvh", skeleton, motion);
      }else{
         std::string file;
         file += f;
          reader.load(file, skeleton, motion);
      }
      motion.update(skeleton, 0);
   }

   void scene() {
      
      if(paused == false){
         time += dt()*timeScale;
         motion.update(skeleton, time);
      }

      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;
         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }

      drawText(paused? "Paused" : "Playing", 10, 15);
      drawText("Current frame: "+std::to_string(currentFrame), 10, 35);
      drawText("Time scale: "+std::to_string(timeScale), 10, 55);
   }

   virtual void keyUp(int key, int mods) {
      if(key == 'P'){
         paused = !paused;
      }else if(key == '0'){
         time = 0;
      }else if(key == '.' && paused == true){
         time += dt();
         if(time > motion.getNumKeys()){
            time = 0;
         }
         motion.update(skeleton, time);
      }else if(key == ',' && paused == true){
         if(time < 0){
            time = motion.getNumKeys();
         }
         time -= dt();
         motion.update(skeleton, time);
      }else if(key == ']'){
         timeScale += 0.5;
         if(timeScale == 0){
            timeScale += 0.01;
         }
      }else if(key == '['){
         timeScale = timeScale/2;
      }
   }

private:
   Skeleton skeleton;
   Motion motion;

   float timeScale = 1.0f;
   int currentFrame = 0; 
   bool paused = false;
   float time = 0;
};


int main(int argc, char** argv) {
   char* f = argv[1];
   MotionViewer viewer;
   viewer.file(f);
   viewer.run();
}
