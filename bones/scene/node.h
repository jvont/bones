#pragma once

#include <vector>

namespace bones
{
  class Node
  {
    public: //private:
      Node* parent;
      std::vector<Node*> children;

      // transform

    public:
      // Node(InputHandler input);

      virtual void update(float dt) {}

      // void handle_input(const InputEvent& event);
  };
}