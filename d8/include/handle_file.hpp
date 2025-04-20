#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class HandleFile {
  string str; 
  vector<string> input;
  vector<pair<int,int>> antinodes;
  unordered_map<char, vector<pair<int,int>>> antennas;

  public:
    void get_file();
    void part1();
    void part2();
    void load();
    void print();
    bool in_bounds(int i, int j) const {
    return i >= 0 && i < static_cast<int>(input.size()) &&
           j >= 0 && j < static_cast<int>(input[0].size());
  }
};

