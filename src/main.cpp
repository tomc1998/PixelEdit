#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer.h"
#include "state.h"
#include "input.h"
using namespace pixeledit;

GLFWwindow* window;

int W = 800, H = 600;
int CW = 4000, CH = 4000;

void initGL() {
  glfwInit();
  window = glfwCreateWindow(W, H, "PixelEdit", NULL, NULL);
  glfwMakeContextCurrent(window);
  glViewport(0, 0, W, H);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, W, H, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(1, 0, 0, 1);

  // Callback implemented in input.cpp
  glfwSetKeyCallback(window, keyCallback);
}

/** Handles ESC keypress to close window faster for debug */
class DebugListener : public InputListener {
  virtual void keyEvent(KeyEvent& e) override {
    if (e.key == GLFW_KEY_ESCAPE && e.action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
  }
};

int main(int argc, char** argv) {
  initGL();
  State state;
  Renderer renderer;
  InputHandler& inputHandler = getInputHandler();
  DebugListener debugListener;
  inputHandler.addListener(&debugListener);

  while (true) {
    if (glfwWindowShouldClose(window)) {
      break;
    }
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  return 0;
}

