#include "IOUtils.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

vector<fs::path> getResourceFiles(const string &directory) {
  vector<fs::path> files;
  for (const auto &file : fs::directory_iterator(directory)) {
    files.push_back(std::filesystem::canonical(file.path()));
  }
  return files;
}

void printResourceFiles(const vector<fs::path> &files) {
  for (const auto &file : files) {
    cout << std::setw(2) << &file - &files[0] << ": " << file << endl;
  }
  cout << endl;
}

// fs::path getUserInputFile(const vector<fs::path> &files) { return files[12];
// }
fs::path getUserInputFile(const vector<fs::path> &files) {
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
    } else if (std::find_if(files.begin(), files.end(),
                            [&rawInput](const auto &path) {
                              return path.stem() == rawInput;
                            }) != files.end()) {
      return std::move(rawInput);
    } else {
      cout << "Invalid input, please try again." << endl;
      continue;
    }
  } while (!rawInput.empty());
  cout << "Nothing was gotten from user. Program exits." << endl;
  return "";
}

float getUserInputTime(const float &defaultTime = 3.0f) {
  string rawInput;
  do {
    cout << "Please enter a time limit in seconds (default: " << std::fixed
         << std::setprecision(1) << defaultTime << "s): ";
    std::getline(cin, rawInput);
    std::istringstream iss(rawInput);
    float val;
    char remain;

    if (!cin.eof() && iss >> std::fixed >> std::setprecision(1) >> val &&
        !(iss >> remain) && val > 0.0f) {
      return val;
    }
    cout << "Invalid input, a positive value is needed. Please try again."
         << endl;
    continue;
  } while (!rawInput.empty());
  cout << "Nothing was gotten from user. Program exits." << endl;
  return defaultTime;
}

pair<vector<Node>, vector<Edge>> readGraphDataFromFile(const fs::path &file) {
  std::fstream inputFile;
  cout << "Reading graph data from file: " << fs::canonical(file).string()
       << endl;
  inputFile.open(file, std::ios::in);
  if (!inputFile.is_open())
    throw std::domain_error("Could not open file: " +
                            fs::canonical(file).string());

  unsigned nodeSize;
  unsigned fromNodeIndex, toNodeIndex;
  vector<Node> nodes;
  vector<Edge> edges;

  string rawInput;

  // first line for node size
  std::getline(inputFile, rawInput);
  nodeSize = rawInput.empty() ? 0 : std::stoul(rawInput);

  std::fill_n(std::back_inserter(nodes), nodeSize, Node{0.0, 0.0});

  while (std::getline(inputFile, rawInput)) {
    std::istringstream iss(rawInput);

    iss >> fromNodeIndex >> toNodeIndex;
    Edge newEdge{fromNodeIndex, toNodeIndex};

    edges.push_back(newEdge);
  }

  return {nodes, edges};
}
