#include "IOUtils.h"
#include "SimpleGraph.h"
#include <format>
#include <iostream>

using std::cout;
using std::endl;

const float defaultTime = 3.0f; // Default time limit for graph rendering

void Welcome();
void userFileSelection();
void userTimeLimitInput(const float &);

// Main method
int main() {
  Welcome();
  userFileSelection();
  userTimeLimitInput(defaultTime);
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

void userFileSelection() {
  cout << "There are some preset graphs you can visualize:" << endl;
  auto files = getResourceFiles("res/");
  printResourceFiles(files);

  cout << "Which one do you wanna choose to visualize? " << endl;
  cout << "Type a filename or sequence number:" << endl;

  auto userInput = getUserInputFile(files);
  cout << "Your choice for graph is: " << userInput << endl;
}

void userTimeLimitInput(const float &defaultTime) {
  cout << "How many seconds would you wait for a graph to stop iteration?"
       << endl;
  float userTime = getUserInputTime(defaultTime);
  cout << "Your input for time is: " << userTime << "s" << endl;
}
