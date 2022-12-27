#include "Tree.hpp"
#include "Node.hpp"


using namespace std;

// Node for tree structures.

Node::Node() {
  depth = 1;
  data = 0;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}
Node::Node(const int &word_) {
  depth = 1;
  data = word_;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}
Node::Node(const int &word_, const int &depth_) {
  depth = depth_;
  data = word_;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

void Node::setParent(Node *n) {
  parent = n;
  depth = parent->depth + 1;
}
void Node::setLeft(Node *n) { left = n; }
void Node::setRight(Node *n) { right = n; }

void Node::setData(const int &word_) { data = word_; }
void Node::setDepth(const int &depth_) { depth = depth_; }
int Node::getDepth() {

  Node *n = this;
  int depth_ = 1;
  while (n->parent != nullptr) {

    n = n->parent;
    depth_ += 1;
  }
  return depth_;
}
const Node Node::getParent() { return *parent; }
const int Node::getData() { return data; }