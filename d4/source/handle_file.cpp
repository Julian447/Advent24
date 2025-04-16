#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "../include/handle_file.hpp"

using namespace std;

bool HandleFile::check_direction(int i, int j, int di, int dj) {
  const std::string word = "XMAS";
  for (char letter : word) {
    if (!is_valid(i, j) || grid[i][j] != letter)
      return false;
    i += di;
    j += dj;
  }
  return true;
}

void HandleFile::part1(){
  const vector<pair<int, int>> directions{
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
    {1, 0}, {1, -1}, {0, -1}, {-1, -1}
  };
  for (size_t i = 0; i < grid.size(); ++i) { 
    for (size_t j = 0; j < grid[i].size(); ++j) {
      if (grid[i][j] == 'X') {
        for (const auto& dir : directions) {
          if (check_direction(i, j, dir.first, dir.second))
            ++xmas_count;
        }
      }
    }
  }
  cout << xmas_count << endl;
}


bool HandleFile::check_x(int i, int j) {
  // const std::string letters = "MS";
  if (!is_valid(i-1, j-1) || !is_valid(i-1, j+1) ||
      !is_valid(i+1, j-1) || !is_valid(i+1, j+1))
    return false;

  char ul = grid[i-1][j-1]; // up-left
  char ur = grid[i-1][j+1]; // up-right
  char dl = grid[i+1][j-1]; // down-left
  char dr = grid[i+1][j+1]; // down-right

  // Valid if opposite diagonals are M and S
  return ((ul == 'M' && dr == 'S') || (ul == 'S' && dr == 'M')) &&
         ((ur == 'M' && dl == 'S') || (ur == 'S' && dl == 'M'));
}
void HandleFile::part2(){
  // const vector<pair<int, int>> directions{
  //   {-1, 1}, {1, 1}, {-1, -1}, {1, -1}
  // };
  for (size_t i = 0; i < grid.size(); ++i) { 
    for (size_t j = 0; j < grid[i].size(); ++j) {
      if (grid[i][j] == 'A') {
        if (check_x(i, j))
          ++xmas_count;
      }
    }
  }
  cout << xmas_count << endl;
}

void HandleFile::get_file(){
  ifstream file("../input.txt");
  while (getline(file, str)) {
    // Process str
    grid.push_back(str);
  }
  // for (auto v : vec) {
  //   cout << v << endl;
  // }
  // part1();
  part2();
}

