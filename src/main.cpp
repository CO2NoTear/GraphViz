#include "SimpleGraph.h"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void Welcome();

// Main method
int main() {
  Welcome();
  return 0;
}

vector<string> getResourceFiles(const string &directory) {
  vector<string> files;
  for (const auto &file : fs::directory_iterator(directory)) {
    files.push_back(file.path().filename());
  }
  return files;
}

void printResourceFiles(const vector<string> &files) {
  cout << "There are some preset graphs you can visualize:" << endl;
  for (const auto &file : files) {
    cout << std::setw(2) << &file - &files[0] << ": " << file << endl;
  }
  cout << endl;
}

string getUserInputFile(const vector<string> &files) {
  cout << "Which one do you wanna choose to visualize? " << endl;
  cout << "Type a filename or sequence number:" << endl;

  string rawInput;
  do {
    std::getline(cin, rawInput);
    std::istringstream iss(rawInput);
    int val;
    char remain;

    if (!cin.eof() && iss >> val && !(iss >> remain)) {
      if (val < 0 || val >= files.size()) {
        cout << "Invalid input, please try again." << endl;
        continue;
      }
      return files[val];
    } else if (std::find(files.begin(), files.end(), rawInput) != files.end()) {
      return std::move(rawInput);
    } else {
      cout << "Invalid input, please try again." << endl;
      continue;
    }
  } while (!rawInput.empty());
  cout << "Nothing was gotten from user. Program exits." << endl;
  return "";
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
  cout << "Welcome to CS106L GraphViz!" << endl;
  cout << "This program uses a force-directed graph layout algorithm" << endl;
  cout << "to render sleek, snazzy pictures of various graphs." << endl;
  cout << endl;

  auto files = getResourceFiles("res/");
  printResourceFiles(files);

  auto userInput = getUserInputFile(files);
  cout << userInput << endl;
}
