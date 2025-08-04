#include "Force.h"

const double epsilon = 1e-6; // Small value to avoid division by zero

void RepulsionForce::interact(Node &nodeFirst, Node &nodeSecond) {
  nodeFirst.x -= this->x_;
  nodeFirst.y -= this->y_;
  nodeSecond.x += this->x_;
  nodeSecond.y += this->y_;
}
void AttractionForce::interact(Node &nodeFirst, Node &nodeSecond) {
  nodeFirst.x += this->x_;
  nodeFirst.y += this->y_;
  nodeSecond.x -= this->x_;
  nodeSecond.y -= this->y_;
}
void RepulsionForce::computeForce(const Node &nodeFirst,
                                  const Node &nodeSecond) {
  double dx = nodeSecond.x - nodeFirst.x;
  double dy = nodeSecond.y - nodeFirst.y;
  double distance = std::sqrt(dx * dx + dy * dy);
  if (distance > epsilon) {
    force_ = K / distance;
  } else {
    force_ = 0;
  }

  double theta = std::atan2(dy, dx);
  x_ = std::cos(theta) * force_;
  y_ = std::sin(theta) * force_;
};

void AttractionForce::computeForce(const Node &nodeFirst,
                                   const Node &nodeSecond) {
  double dx = nodeSecond.x - nodeFirst.x;
  double dy = nodeSecond.y - nodeFirst.y;
  double distance = std::sqrt(dx * dx + dy * dy);
  if (distance > epsilon) {
    force_ = K * distance * distance;
  } else {
    force_ = 0;
  }

  double theta = std::atan2(dy, dx);
  x_ = std::cos(theta) * force_;
  y_ = std::sin(theta) * force_;
};
