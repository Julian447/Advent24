#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../include/handle_file.hpp"

using namespace std;

void HandleFile::print(){
  for (auto row : input) {
    for (auto s : row) {
      cout << s << " ";
    }
    cout << endl;
  }
}
void HandleFile::change_direction(){
  if (direction == "up") direction = "right";
  else if (direction == "right") direction = "down";
  else if (direction == "down") direction = "left";
  else if (direction == "left") direction = "up";
}
void HandleFile::load_guards(){
  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t j = 0; j < input[i].size(); ++j) {
      if (input[i][j] == '#') guards.push_back(pair<int, int>(i,j));
      if (input[i][j] == '^') position = pair<int,int>(i,j);
    }
  }
}
void HandleFile::cleaned_patrol() {
  size_t i = position.first, j = position.second;

  auto step = [&](int di, int dj, char marker) -> bool {
    if (input[i][j] != 'X') walked++;
    input[i][j] = 'X';

    if (!in_bounds(i + di, j + dj)) {
      walked++;
      return false;
    }

    if (input[i + di][j + dj] == '#') {
      input[i][j] = marker;
      change_direction();
      // print();
      return true;
    }

    i += di;
    j += dj;
    position.first = i, position.second = j;
    return true;
  };

  while (true) {
    if (direction == "left") {
      if (!step(0, -1, '^')) break;
    } else if (direction == "up") {
      if (!step(-1, 0, '>')) break;
    } else if (direction == "right") {
      if (!step(0, 1, 'v')) break;
    } else if (direction == "down") {
      if (!step(1, 0, '<')) break;
    }
  }
}
void HandleFile::patrol(){
  size_t i = position.first;
  size_t j = position.second;

  while(true){ 
    if (input[i][j] != 'X')
      walked++;
    input[i][j] = 'X';

    if (direction == "left") {
      --j;
      if (!in_bounds(i, j-1)){
        input[i][j] = 'X';
        walked++;
        break;
      }
      if (input[i][j-1] == '#') {
        input[i][j] = '^';
        change_direction();
        cout << "Walked: " << walked << endl;
      }
    }
    else if (direction == "up") {
      --i;
      if (!in_bounds(i-1, j)){
        input[i][j] = 'X';
        walked++;
        break;
      }
      if (input[i-1][j] == '#') {
        input[i][j] = '>';
        change_direction();
        cout << "Walked: " << walked << endl;
      }
    }
    else if (direction == "right") {
      ++j;
      if (!in_bounds(i, j+1)){
        input[i][j] = 'X';
        walked++;
        break;
      }
      if (input[i][j+1] == '#') {
        input[i][j] = 'v';
        change_direction();
        cout << "Walked: " << walked << endl;
      }
    }
    else if (direction == "down") {
      ++i;
      if (!in_bounds(i+1, j)){
        input[i][j] = 'X';
        walked++;
        break;
      }
      if (input[i+1][j] == '#') {
        input[i][j] = '<';
        change_direction();
        cout << "Walked: " << walked << endl;
      }
    }
  }
}

void HandleFile::part1(){
  print();
  load_guards();
  // patrol();
  cleaned_patrol();
  cout << endl;

  print();
  cout << "Walked: " << walked << endl;
}

void HandleFile::part2(){
}

void HandleFile::get_file(){
  ifstream file("../input.txt");
  while (getline(file, str)) {
    // Process str
    input.push_back(str);
  }
  part1();
  // part2();
}

