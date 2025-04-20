#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "../include/handle_file.hpp"

using namespace std;

void HandleFile::print() {
  for (auto row : input) {
    cout << row << endl;
  }
}
void HandleFile::load(){
  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t j = 0; j < input[i].size(); ++j) {
      auto frequency = input[i][j];
      if (frequency != '.'){
        // cout << "Type: " << frequency << endl;
        antennas[frequency].push_back(pair(i,j));
      }
    }
  }
}

void HandleFile::part1(){
  print();
  load();

  auto insert_antenna = [&](int x, int y){
    if (in_bounds(x,y) && std::find(antinodes.begin(), antinodes.end(),pair(x,y))==antinodes.end()) {
      if (input[x][y] == '.')
        input[x][y] = '#';
      antinodes.push_back(pair(x,y));
    }
  };
  
  cout << endl;
  for (auto frequency : antennas) {
    // cout << "Type: " << frequency.first << ", Count: " << frequency.second.size() << endl;
    for (size_t i = 0; i < frequency.second.size(); ++i) {
      for (size_t j = i; j < frequency.second.size(); ++j) {
        if (frequency.second[i] == frequency.second[j])
          continue;
        
        int x_diff = frequency.second[j].first - frequency.second[i].first;
        int y_diff = frequency.second[j].second - frequency.second[i].second;
        // cout << "X: " << x_diff << ", Y: " << y_diff << endl;
        int x1 = frequency.second[j].first - x_diff*2;
        int y1 = frequency.second[j].second - y_diff*2;
        int x2 = frequency.second[j].first + x_diff;
        int y2 = frequency.second[j].second + y_diff;
        // cout << "X1: " << x1 << ", Y1: " << y1 << endl;
        // cout << "X2: " << x2 << ", Y2: " << y2 << endl;
        insert_antenna(x1, y1);
        insert_antenna(x2, y2);
      }

    }
  }
  print();
  cout << "Antinodes: " << antinodes.size() << endl;
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

