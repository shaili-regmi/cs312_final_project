// Shaili Regmi
// CS312 - Final Project
// Particle Planetarium
// Base Code: Bryn Mawr College, alinen, 2020 and OpenGL (learnopengl.com), David Wolff - OpenGL 4.0 Shading Language Cookbook

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include "planetarium.h"
#include "renderer.h"

using namespace std;
using namespace glm;
using namespace agl;

Planetarium theSystem;

double xpos, ypos;
float change_x, change_y;

float Dist = 3.0f;
float Azimuth = 0.0f;
float Elevation = 0.0f;
float fov = 40.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (action != GLFW_PRESS) return;

   if (key == GLFW_KEY_ESCAPE)
   {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
   }
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   // Prevent a divide by zero
   if (height == 0) height = 1;

   // Set Viewport to window dimensions
   glViewport(0, 0, width, height);
   ParticleSystem::GetRenderer().perspective(radians(60.0f), 1.0f, 0.1f, 100.0f);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    float temp_Dist = 0.0f;
    if (state == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
    }
    else if (state == GLFW_RELEASE)
    {

    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state != GLFW_PRESS) return;

    float x, y, z;
    double old_xpos = xpos;
    double old_ypos = ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    
    if (xpos > radians(180.0)) xpos = radians(180.0);
    if (xpos < radians(-180.0)) xpos = radians(-180.0);
    if (ypos > radians(90.0)) ypos = radians(90.0);
    if (ypos < radians(-90.0)) ypos = radians(-90.0);
    
    change_x = xpos - old_xpos;
    change_y = ypos - old_ypos;

    Azimuth = 0.01 * change_x;
    Elevation = 0.01 * change_y;

    x = Dist * sin(Azimuth) * cos(Elevation);
    y = Dist * sin(Elevation);
    z = Dist * cos(Azimuth) * cos(Elevation);

    ParticleSystem::GetRenderer().perspective(fov, 1.0f, 0.01f, 100.0f);
    ParticleSystem::GetRenderer().lookAt(vec3(x, y, z), vec3(0));
}

int main(int argc, char** argv)
{
   GLFWwindow* window;

   if (!glfwInit())
   {
      return -1;
   }

   // Explicitly ask for a 4.0 context 
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   /* Create a windowed mode window and its OpenGL context */
   float width = 500;
   float height = 500;
   window = glfwCreateWindow(width, height, "Particle Planetarium", NULL, NULL);
   if (!window)
   {
      glfwTerminate();
      return -1;
   }

   glfwMakeContextCurrent(window);
   glfwSetKeyCallback(window, key_callback);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   glfwSetMouseButtonCallback(window, mouse_button_callback);
   glfwSetScrollCallback(window, scroll_callback);
   glfwSetCursorPosCallback(window, cursor_position_callback);

#ifndef APPLE
   if (glewInit() != GLEW_OK)
   {
      cout << "Cannot initialize GLEW\n";
      return -1;
   }
#endif

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glClearColor(0, 0, 0, 1);

   float x, y, z;
   x = Dist * sin(Azimuth) * cos(Elevation);
   y = Dist * sin(Elevation);
   z = Dist * cos(Azimuth) * cos(Elevation);
   
   ParticleSystem::GetRenderer().perspective(fov, 1.0f, 0.01f, 100.0f);
   ParticleSystem::GetRenderer().lookAt(vec3(x, y, z), vec3(0));
   theSystem.init(2); // TODO: Set number of particles here
   

   float lastTime = glfwGetTime();
   while (!glfwWindowShouldClose(window))
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

      float dt = glfwGetTime() - lastTime;
      lastTime = glfwGetTime();

      theSystem.update(dt);
      theSystem.draw();

      // Swap front and back buffers
      glfwSwapBuffers(window);

      // Poll for and process events
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}

