#ifndef INPUT_H
#define INPUT_H
#include <GLFW/glfw3.h>
#include <queue>
#include <vector>
namespace pixeledit {
 
  class InputEvent {
  public:
    InputEvent();
  };

  class KeyEvent : public InputEvent {
  public:
    KeyEvent(int key, int scancode, int action, int mods);
    int key;
    int scancode;
    int action;
    int mods;
  };

  class InputListener {
  public:
    InputListener();
    InputListener(InputListener const&);
    InputListener& operator=(InputListener const&);
    ~InputListener();
    virtual void keyEvent(KeyEvent& e);
    // The handlers this listener is attached to
    std::vector<InputHandler*> handlers;
  };

  class InputHandler {
  public:
    InputHandler();
    /** Updates the handler, triggers input listener methods */
    void update();
    void addListener(InputListener*);
    void removeListener(InputListener*);
  private:
    std::vector<InputListener*> listeners;
    std::queue<InputEvent*> eventQueue;
  };

  // Set up singleton instance and functions
  extern InputHandler* inputHandler;
 	InputHandler& getInputHandler();

  // Setup GLFW callbacks
  void keyCallback(GLFWwindow* w, int key,
                   int scancode, int action, int mods);
}
#endif
