#include <GLFW/glfw3.h>
#include "input.h"
#include <queue>
using namespace pixeledit;

/**************
 * InputEvent *
 **************/
InputEvent::InputEvent(GLFWwindow* _window) {
  window = _window;
}
InputEvent::~InputEvent() {
}

/************
 * KeyEvent *
 ************/
KeyEvent::KeyEvent(GLFWwindow* _window, int _key, int _scancode,
                   int _action, int _mods)
  : InputEvent(_window) {
  key = _key;
  scancode = _scancode;
  action = _action;
  mods = _mods;
}
KeyEvent::~KeyEvent() {};

/**************
 * MouseEvent *
 **************/
MouseEvent::MouseEvent(GLFWwindow* _window, int _button, int _action, int _mods)
	: InputEvent(_window) {
  button = _button;
  action = _action;
  mods = _mods;
}
MouseEvent::~MouseEvent() {};

/******************
 * CursorPosEvent *
 ******************/
CursorPosEvent::CursorPosEvent(GLFWwindow* _window, double _x, double _y)
  : InputEvent(_window) {
  x = _x;
  y = _y;
}
CursorPosEvent::~CursorPosEvent() {};

/*****************
 * InputListener *
 *****************/
InputListener::InputListener() {
}

InputListener::InputListener(InputListener const& copy) {
	for (unsigned int i = 0; i < copy.handlers.size(); ++i) {
		handlers.push_back(copy.handlers[i]);
  }
}

InputListener::~InputListener() {
  for (unsigned int i = 0; i < handlers.size(); ++i) {
    handlers[i]->removeListener(this);
  }
}

namespace pixeledit {
  void swap(InputListener& a, InputListener& b) {
    std::swap(a.handlers, b.handlers);
  }
}

// Copy in the copy
InputListener& InputListener::operator=(InputListener copy) {
  swap(*this, copy);
  return *this;
}

void InputListener::keyEvent(KeyEvent& e) {
}
void InputListener::cursorPosEvent(CursorPosEvent& e) {
}
void InputListener::mouseEvent(MouseEvent& e) {
}

/****************
 * InputHandler *
 ****************/
InputHandler::InputHandler() {
}

void InputHandler::update() {
  unsigned int len = eventQueue.size();
  for (int i = 0; i < len; ++i) {
    InputEvent* e = eventQueue.front();
    for (int j = 0; j < listeners.size(); ++j) {
      if (KeyEvent* ke = dynamic_cast<KeyEvent*>(e)) {
        listeners[j]->keyEvent(*ke);
      }
      else if (MouseEvent* ke = dynamic_cast<MouseEvent*>(e)) {
        listeners[j]->mouseEvent(*ke);
      }
      else if (CursorPosEvent* ke = dynamic_cast<CursorPosEvent*>(e)) {
        listeners[j]->cursorPosEvent(*ke);
      }
    }
    eventQueue.pop();
    delete e;
  }
}

void InputHandler::addListener(InputListener* listener) {
  listeners.push_back(listener);
}

void InputHandler::removeListener(InputListener* listener) {
  // Just search linearly
  for (unsigned int i = 0; i < listeners.size(); ++i) {
    if (listeners[i] == listener) {
      listeners.erase(listeners.begin()+i);
      return;
    }
  }
}

void InputHandler::queueEvent(InputEvent* e) {
  eventQueue.push(e);
}

InputHandler* pixeledit::inputHandler = new InputHandler();
InputHandler& pixeledit::getInputHandler() {
  return *inputHandler;
}

void pixeledit::keyCallback(GLFWwindow* w, int key,
                 int scancode, int action, int mods) {
  KeyEvent* event = new KeyEvent(w, key, scancode, action, mods);
  getInputHandler().queueEvent(event);
}

void pixeledit::cursorPosCallback(GLFWwindow* window, double x, double y) {
  CursorPosEvent* event = new CursorPosEvent(window, x, y);
  getInputHandler().queueEvent(event);
}

void pixeledit::mouseButtonCallback(GLFWwindow* window, int button,
                                    int action, int mods) {
  MouseEvent* event = new MouseEvent(window, button, action, mods);
  getInputHandler().queueEvent(event);
}
