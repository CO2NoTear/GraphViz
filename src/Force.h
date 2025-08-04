#pragma once
#include "SimpleGraph.h"

struct AbstractForce {
  double force_;
  double x_, y_;
  double K = 1e-3;
  AbstractForce() {};
  AbstractForce(const double &k) : K(k) {}
  virtual void computeForce(const Node &nodeFirst, const Node &nodeSecond) = 0;
  virtual void interact(Node &nodeFirst, Node &nodeSecond) = 0;
};

struct RepulsionForce : public AbstractForce {
  void computeForce(const Node &nodeFirst, const Node &nodeSecond) override;
  void interact(Node &nodeFirst, Node &nodeSecond) override;
};
struct AttractionForce : public AbstractForce {
  void computeForce(const Node &nodeFirst, const Node &nodeSecond) override;
  void interact(Node &nodeFirst, Node &nodeSecond) override;
};
