#include "IOUtils.h"
#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <sstream>
namespace fs = std::filesystem;

vector<string> getResourceFiles(const string &directory) {
  vector<string> files;
  for (const auto &file : fs::directory_iterator(directory)) {
    files.push_back(file.path().filename());
  }
  return files;
}

void printResourceFiles(const vector<string> &files) {
  for (const auto &file : files) {
    cout << std::setw(2) << &file - &files[0] << ": " << file << endl;
  }
  cout << endl;
}

string getUserInputFile(const vector<string> &files) {
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
