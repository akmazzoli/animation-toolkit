#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
#include "atk/toolkit.h"
#include "atkui/skeleton_drawer.h"
#include "atkui/framework.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

using namespace atk;
using namespace glm;

class AIKSimple : public atkui::Framework
{
 public:
  AIKSimple() : atkui::Framework(atkui::Perspective),
                mDrawer(),
                mGoalPosition()
  {
    mDrawer.showAxes = true;
    mDrawer.color = vec3(0.6, 1.0, 0.4);
  }

  virtual ~AIKSimple()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  void setup()
  {
    Joint *shoulder = new Joint("Shoulder");
    mActor.addJoint(shoulder);
    shoulder->setLocalTranslation(vec3(0, 0, 0));

    Joint *elbow = new Joint("Elbow");
    mActor.addJoint(elbow, shoulder);
    elbow->setLocalTranslation(vec3(100, 0, 0));

    Joint *wrist = new Joint("Wrist");
    mActor.addJoint(wrist, elbow);
    wrist->setLocalTranslation(vec3(80, 0, 0));

    mActor.fk();
    mGoalPosition = wrist->getGlobalTranslation();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

#if defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
#endif
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
  }

  void drawGui()
  {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Demo Controls");
    ImGui::SetWindowSize(ImVec2(150, 150));
    ImGui::SetWindowPos(ImVec2(5, 5));
    ImGui::SliderFloat("X", &mGoalPosition[0], -500.0f, 500.0f);
    ImGui::SliderFloat("Y", &mGoalPosition[1], -500.0f, 500.0f);
    ImGui::SliderFloat("Z", &mGoalPosition[2], -500.0f, 500.0f);
    if (ImGui::Button("Reset")) reset();
    ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

  void reset()
  {
    for (int i = 0; i < mActor.getNumJoints(); i++)
    {
      mActor.getByID(i)->setLocalRotation(atk::IdentityQ);
    }
    mActor.fk();
    mGoalPosition = mActor.getByID(2)->getGlobalTranslation();
  }

  void draw()
  {
    mDrawer.draw(mActor, *this);
    drawFloor(2000, 20, 50);

    vec2 screenPos = worldToScreen(mGoalPosition);

    setColor(vec3(1.0, 0.0, 1.0));
    ortho(0, width(), 0, height(), -1000, 1000);
    renderer.lookAt(vec3(0, 0, 1), vec3(0), vec3(0, 1, 0));

    vec3 c = vec3(screenPos, 0);
    vec3 v1 = c + vec3(10, 0, 0);
    vec3 v2 = c - vec3(10, 0, 0);
    vec3 h1 = c + vec3(0, 10, 0);
    vec3 h2 = c - vec3(0, 10, 0);

    beginShader("unlit");
    drawCircle(c, 5.0f);
    drawLine(v1, v2);
    drawLine(h1, h2);
    endShader();

    // reset projection
    perspective(glm::radians(60.0f), width() / (float)height(), 10.0f, 2000.0f);
    renderer.lookAt(camera.position(), camera.look(), camera.up());

    drawGui();
    solveIKTwoLink(mActor, mGoalPosition);
  }

  void solveIKTwoLink(Skeleton &skeleton, const vec3 &goalPosition)
  {
    //place skeleton's end effector at goalPos 
    //joint 0 is root
    //joint 1 is middle 
    //joint 2 is end effector 
    vec3 gp = vec3(100,0,0);
    Joint* root = skeleton.getByID(0);
    Joint* middle = skeleton.getByID(1);
    Joint* effector = skeleton.getByID(2);
    //we know distance btwn goal pd and p1 
    //adjust rotation of p2 so length matches 
    //we want ||p03 - p01|| = ||p0d - p01||   

    //r = ||pd - p01||
    vec3 rv = goalPosition - root->getGlobalTranslation();
    float r = sqrt((rv.x)*(rv.x) + (rv.y)*(rv.y) + (rv.z)*(rv.z));

    vec3 l1v = middle->getGlobalTranslation()-root->getGlobalTranslation();
    float l1 = sqrt((l1v.x)*(l1v.x) + (l1v.y)*(l1v.y) + (l1v.z)*(l1v.z));

    vec3 l2v = effector->getGlobalTranslation()-middle->getGlobalTranslation();
    float l2 = sqrt((l2v.x)*(l2v.x) + (l2v.y)*(l2v.y) + (l2v.z)*(l2v.z));

    float ctheta = ((r*r) - (l1*l1) - (l2*l2))/(-2.0*l1*l2);

    float theta = acos(ctheta);
    //std::cout<<theta;
   
    float theta2z = theta - 180;

    float stheta1z = -(l2*sin(theta))/r;
    float theta1z = asin(stheta1z);    
  }

 private:
  atk::Skeleton mActor;
  atkui::SkeletonDrawer mDrawer;
  glm::vec3 mGoalPosition;
};

int main(int argc, char **argv)
{
  AIKSimple viewer;
  viewer.run();
  return 0;
}
