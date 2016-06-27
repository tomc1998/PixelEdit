#include <GLFW/glfw3.h>
#include "input.h"
using namespace pixeledit;

/**************
 * InputEvent *
 **************/
InputEvent::InputEvent() {
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

/*****************
 * InputListener *
 *****************/
InputListener::InputListener() {
}

InputListener::~InputListener() {
  for (unsigned int i = 0; i < handlers.size(); ++i) {
    handlers[i]->removeListener(this);
  }
}

InputListener& InputListener::operator=(InputListener const& copy) {
	for (unsigned int i = 0; i < copy.handlers.size(); ++i) {
		handlers.push_back(copy.handlers[i]);
  }
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

InputHandler* pixeledit::inputHandler = new InputHandler();
InputHandler& pixeledit::getInputHandler() {
  return *inputHandler;
}

void pixeledit::keyCallback(GLFWwindow* w, int key,
                 int scancode, int action, int mods) {
  KeyEvent
}
