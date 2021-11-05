#include <random>
#include <functional>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "devil.h"

using namespace atk;
using namespace glm;

class Thriller : public atkui::Framework
{
public:
   Thriller() : atkui::Framework(atkui::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup() {
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);

      int xPos = 0;
      int zPos = 0;
      int index = 0;
      for(int i = 0; i < 4; i++){
         xPos += 150;
         zPos = 0;
         for(int j = 0; j < 3; j++){
            zPos += 150;
            vec3 position = vec3(xPos,0,zPos);
            vec3 color = vec3(1,0,0);
            float size = 1.0f;
            _devil = Devil(position, color, size);
            devils[index] = _devil;
            index++;
         }
      }
   }

   virtual void scene() {
      for(int i = 0; i < 12; i++){
         if (!_paused) _motion.update(_skeleton, elapsedTime());
         devils[i].draw(_skeleton, *this);
      }
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   Devil _devil;
   Devil devils [12];
   
};

int main(int argc, char** argv) {
   Thriller viewer;
   viewer.run();
}

