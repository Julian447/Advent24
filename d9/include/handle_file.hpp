#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class HandleFile {
  string str; 
  // vector<string> input;
  string input;
  vector<string> disk;
  // unordered_map<char, vector<pair<int,int>>> antennas;
  uint64_t sum = 0;

  public:
    void get_file();
    void part1();
    void part2();
    void print();
    void load();
    void checksum(); 
};

