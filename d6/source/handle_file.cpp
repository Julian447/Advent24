#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <set>
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
  print();
  load_guards();

  size_t i = position.first, j = position.second;
  bool blockade_placed = false;
  int loops = 0; 
  pair<int,int> block_pos;
  auto original_input = input;
  auto original_pos = position;
  auto original_dir = direction;
  set<tuple<int, int,string>> visited_positions;

  auto moveForward = [&]() -> pair<int,int>{
      if (direction == "up") return {-1, 0};
      if (direction == "right") return {0, 1};
      if (direction == "down") return {1, 0};
      if (direction == "left") return {0, -1};
      return {i, j}; // Should not reach here
  };

  auto place_blockade = [&](){
    auto moves = moveForward();
    auto di = moves.first, dj = moves.second;
    original_input = input;
    original_pos = position;
    original_dir = direction;

    if (input[i+di][j+dj] != '^') {
      input[i+di][j+dj] = 'O';
      block_pos = {i+di, j+dj};
      blockade_placed = true;
    }
  };
  auto remove_blockade = [&](){
    //restore state
    blockade_placed = false;
    input = original_input;
    position = original_pos;
    direction = original_dir;
    auto moves = moveForward();
    i = position.first + moves.first;
    j = block_pos.second + moves.second;
    visited_positions.clear();
  };


  auto step = [&]() -> bool {
    auto moves = moveForward();
    auto di = moves.first, dj = moves.second;

    if (input[i][j] != '^') {
      if ((direction == "up" || direction == "down") && input[i][j] == '.') input[i][j] = '|';
      else if ((direction == "up" || direction == "down") && input[i][j] == '-') input[i][j] = '+';
      else if ((direction == "left" || direction == "right") && input[i][j] == '.') input[i][j] = '-';
      else if ((direction == "left" || direction == "right") && input[i][j] == '|') input[i][j] = '+';
    }

    if (visited_positions.count({i,j,direction})) {
      loops++;
      cout << "Detected a loop at " << i << ", " << j << endl;
      // print();
      // cout << endl;
      // remove_blockade();
      return false; // or break, or whatever your logic is
    } else {
      // cout << i << " " << j << " " << direction << endl;
      visited_positions.insert({i,j,direction});
    }

    if (!in_bounds(i + di, j + dj) && blockade_placed == true) {
      remove_blockade();
      return false;
    }
    else if (!in_bounds(i + di, j + dj)) {
      return false;
    }
    
    if (input[i + di][j + dj] == 'O') {
      print();
      cout << endl;
      change_direction();
      return true;
    }
    if (input[i + di][j + dj] == '#') {
      print();
      // cout << endl;
      // change_direction();
      return true;
    }

    i += di;
    j += dj;
    position.first = i, position.second = j;

    return true;
  };


  while (true) {
    // cout << endl;
    if (blockade_placed == false) place_blockade();

    if (direction == "left" && !step()) break;
    else if (direction == "up" && !step()) break;
    else if (direction == "right" && !step()) break;
    else if (direction == "down" && !step()) break;
    // }
  }
  cout << endl;

  print();
  cout << loops << endl;
}

void HandleFile::get_file(){
  ifstream file("../input.txt");
  while (getline(file, str)) {
    // Process str
    input.push_back(str);
  }
  // part1();
  part2();
}

