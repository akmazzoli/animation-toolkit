#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "atk/toolkit.h"
#include <iostream>
#include <cmath>

using namespace glm;
using namespace std;
using namespace atk;

class WASDSimple : public atkui::Framework
{
public:
  WASDSimple() : atkui::Framework(atkui::Perspective) {}

  virtual void setup()
  {
    BVHReader reader;
    reader.load("../motions/Beta/walking.bvh", _skeleton, _walk);
    _drawer.showAxes = true;
  }

  virtual void scene()
  {
    update();
    _drawer.draw(_skeleton, *this);

    // draw heading
    vec3 p = _skeleton.getRoot()->getGlobalTranslation();
    p[1] = 10; // set height close above the floor

    setColor(vec3(0, 1, 1));
    push();
    translate(p);
    rotate(_heading, vec3(0, 1, 0));
    translate(vec3(0,0,25));
    scale(vec3(10, 10, 50));
    drawCylinder(vec3(0), 1.0f);
    pop();
  }

  virtual void update()
  {
    vec3 start = _walk.getValue(0).rootPos;
    vec3 globalPos;
    vec3 globalLookPos;
    for(int i = 0; i < _walk.getNumKeys(); i++){
      Pose pinned = _walk.getValue(i);
      Joint* root = _skeleton.getByName("Beta:Hips");
      pinned.jointRots[root->getID()] = eulerAngleRO(XYZ,vec3(0,_heading,0));
      //pinned.rootPos = start;
      pinned.rootPos = _skeleton.getRoot()->getGlobalTranslation() + float(100)*vec3(0,0,_heading) * dt();
      _walk.editKey(i,pinned);

      Joint* head = _skeleton.getByName("Beta:Head");
      vec3 headPosGlobal = head->getGlobalTranslation();
      vec3 offset = _skeleton.getByName("Beta:Head")->getLocal2Global().transformVector(glm::vec3(0,0,-300));
      globalPos = headPosGlobal + offset;
      globalLookPos = root->getGlobalTranslation();
      lookAt(globalPos,globalLookPos,vec3(0,1,0) /*up*/);
    }

    _walk.update(_skeleton, elapsedTime());

    if (keyIsDown('D')) _heading -= 0.05;
    if (keyIsDown('A')) _heading += 0.05;
  }

protected:
  float _heading;

  Motion _walk;
  Skeleton _skeleton;
  atkui::SkeletonDrawer _drawer;
};

int main(int argc, char **argv)
{
  WASDSimple viewer;
  viewer.run();
}
