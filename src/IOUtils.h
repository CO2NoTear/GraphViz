#pragma once
#include "SimpleGraph.h"
#include <filesystem>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

namespace fs = std::filesystem;
void printResourceFiles(const vector<fs::path> &files);
vector<fs::path> getResourceFiles(const string &directory);
fs::path getUserInputFile(const vector<fs::path> &files);
float getUserInputTime(const float &defaultTime);
pair<vector<Node>, vector<Edge>> readGraphDataFromFile(const fs::path &file);
