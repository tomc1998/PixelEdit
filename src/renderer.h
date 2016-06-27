#ifndef RENDERER_H
#define RENDERER_H
namespace pixeledit {

  class State;
  class Renderer {
  public:
    Renderer();
    void render(State* state);
  };

}

#endif
