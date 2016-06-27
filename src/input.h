#ifndef INPUT_H
#define INPUT_H
#include <GLFW/glfw3.h>
#include <queue>
#include <vector>
namespace pixeledit {
 
  class InputEvent {
  public:
    InputEvent(GLFWwindow* w);
    virtual ~InputEvent(); // Make this class polymorphic
    GLFWwindow* window;
  };

  class KeyEvent : public InputEvent {
  public:
    KeyEvent(GLFWwindow* w, int key, int scancode, int action, int mods);
    virtual ~KeyEvent();
    int key;
    int scancode;
    int action;
    int mods;
  };

  class MouseEvent : public InputEvent {
  public:
    MouseEvent(GLFWwindow* w, int _button, int _action, int _mods);
    virtual ~MouseEvent();
		int button;
    int action;
    int mods;
  };

  class CursorPosEvent : public InputEvent {
  public:
    CursorPosEvent(GLFWwindow* w, double _x, double _y);
    virtual ~CursorPosEvent();
    double x, y;
  };

  class InputListener;
  class InputHandler {
  public:
    InputHandler();
    /** Updates the handler, triggers input listener methods */
    void update();
    void addListener(InputListener*);
    void removeListener(InputListener*);
    void queueEvent(InputEvent*);
  private:
    std::vector<InputListener*> listeners;
    std::queue<InputEvent*> eventQueue;
  };

  class InputListener {
  public:
    InputListener();
    InputListener(InputListener const&);
    InputListener& operator=(InputListener);
    friend void swap(InputListener& a, InputListener& b);
    ~InputListener();
    virtual void keyEvent(KeyEvent& e);
    virtual void mouseEvent(MouseEvent& e);
    virtual void cursorPosEvent(CursorPosEvent& e);
    // The handlers this listener is attached to
    std::vector<InputHandler*> handlers;
  };


  // Set up singleton instance and functions
  extern InputHandler* inputHandler;
 	InputHandler& getInputHandler();

  // Setup GLFW callbacks
  void keyCallback(GLFWwindow* w, int key,
                   int scancode, int action, int mods);
  void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
  void mouseButtonCallback(GLFWwindow* window,
                           int button, int action, int mods);
}

#endif
