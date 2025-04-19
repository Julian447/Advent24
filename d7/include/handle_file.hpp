#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;


class HandleFile {
  string str; 
  vector<string> input;
  string direction = "up";
  pair<int,int> position;
  vector<pair<int, int>> guards;
  int walked = 0;
  
  public:
    void get_file();
    void part1();
    void part2();
    void print();
    bool in_bounds(int i, int j) const {
    return i >= 0 && i < static_cast<int>(input.size()) &&
           j >= 0 && j < static_cast<int>(input[0].size());
  }
};

