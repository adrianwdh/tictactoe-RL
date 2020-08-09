#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <random>

using namespace std;
//typedef array<int, 9> Grid;	// 3X3 Grid
//typedef array<bool, 52> Grid;	
typedef long Grid;	// 3X3 Grid
const int total_state = 19683;
typedef array<float, total_state> QValue;	// Only 3^9 ways of grid