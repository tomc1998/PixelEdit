#include <GLFW/glfw3.h>
#include "input.h"
#include <queue>
using namespace pixeledit;

/**************
 * InputEvent *
 **************/
InputEvent::InputEvent() {
}
InputEvent::~InputEvent() {
}

/************
 * KeyEvent *
 ************/
KeyEvent::KeyEvent(int _key, int _scancode, int _action, int _mods) {
  key = _key;
  scancode = _scancode;
  action = _action;
  mods = _mods;
}
KeyEvent::~KeyEvent() {};

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

void InputHandler::queueEvent(KeyEvent* e) {
  eventQueue.push(e);
}

InputHandler* pixeledit::inputHandler = new InputHandler();
InputHandler& pixeledit::getInputHandler() {
  return *inputHandler;
}

void pixeledit::keyCallback(GLFWwindow* w, int key,
                 int scancode, int action, int mods) {
  KeyEvent* event = new KeyEvent(key, scancode, action, mods);
  getInputHandler().queueEvent(event);
}
