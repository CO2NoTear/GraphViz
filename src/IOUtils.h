#pragma once
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void printResourceFiles(const vector<string> &files);
vector<string> getResourceFiles(const string &directory);
string getUserInputFile(const vector<string> &files);
float getUserInputTime(const float &defaultTime);
