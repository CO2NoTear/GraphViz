#include "Force.h"
#include "IOUtils.h"
#include "SimpleGraph.h"
#include <chrono>
#include <iostream>

using std::cout;
using std::endl;

const float defaultTime = 3.0f; // Default time limit for graph rendering

void Welcome();
fs::path userFileSelection(const fs::path &directory);
float userTimeLimitInput(const float &);
void initGraphObject(const fs::path &graphDataFile, SimpleGraph &userGraph);
void iteration(SimpleGraph &userGraph, const auto &timeLimitInSeconds);

// Main method
int main() {
  Welcome();
  const string graphFile =
      userFileSelection("/home/co2notear/Code/01_GraphViz/res/");
  const float timeLimit = userTimeLimitInput(defaultTime);
  // const float timeLimit = 3.0f;
  SimpleGraph graph{};
  initGraphObject(graphFile, graph);

  cout << "Now start iteration:" << endl;
  iteration(graph, timeLimit);

  return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
  cout << "Welcome to CS106L GraphViz!" << endl;
  cout << "This program uses a force-directed graph layout algorithm" << endl;
  cout << "to render sleek, snazzy pictures of various graphs." << endl;
  cout << endl;
}

fs::path userFileSelection(const fs::path &directory) {
  cout << "There are some preset graphs you can visualize:" << endl;
  auto files = getResourceFiles(directory);
  printResourceFiles(files);

  cout << "Which one do you wanna choose to visualize? " << endl;
  cout << "Type a filename or sequence number:" << endl;

  auto userInput = getUserInputFile(files);
  cout << "Your choice for graph is: " << userInput << endl;
  return userInput;
}

float userTimeLimitInput(const float &defaultTime) {
  cout << "How many seconds would you wait for a graph to stop iteration?"
       << endl;
  float userTime = getUserInputTime(defaultTime);
  cout << "Your input for time is: " << userTime << "s" << endl;
  return userTime;
}

void initGraphObject(const fs::path &graphDataFile, SimpleGraph &userGraph) {
  auto [nodes, edges] = readGraphDataFromFile(graphDataFile);
  userGraph.nodes = nodes;
  userGraph.edges = edges;
  InitGraphNodePositions(userGraph);

  InitGraphVisualizer(userGraph);
  DrawGraph(userGraph);

  return;
}

void iteration(SimpleGraph &userGraph, const auto &timeLimitInSeconds) {
  auto startTime = std::chrono::system_clock().now();
  size_t iterationCount = 0;

  do {
    ++iterationCount;
    for (auto &nodeFirst : userGraph.nodes) {
      for (auto &nodeSecond : userGraph.nodes) {
        RepulsionForce repulsionForce;
        repulsionForce.computeForce(nodeFirst, nodeSecond);
        repulsionForce.interact(nodeFirst, nodeSecond);
      }
    }
    for (const auto &edge : userGraph.edges) {
      auto &nodeFisrt = userGraph.nodes[edge.start];
      auto &nodeSecond = userGraph.nodes[edge.end];

      AttractionForce attractionForce;
      attractionForce.computeForce(nodeFisrt, nodeSecond);
      attractionForce.interact(nodeFisrt, nodeSecond);
    }

    DrawGraph(userGraph);
  } while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock().now() - startTime)
                       .count() /
                   1e3 <
               timeLimitInSeconds &&
           iterationCount < 300000);

  cout << "Iteration Ended after " << iterationCount
       << " iterations or time limit of " << timeLimitInSeconds << " seconds."
       << endl;
  return;
}
