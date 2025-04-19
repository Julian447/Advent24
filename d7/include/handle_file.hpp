#include <cstdint>
#include <string>
#include <vector>

using namespace std;


class HandleFile {
  string str; 
  vector<string> input;

  public:
    void get_file();
    void part1();
    void part2();
    void print();
    // bool combine(int result, const vector<int>& combinators, int iterator, size_t index);
    bool combine(uint64_t result, const vector<uint64_t>& combinators);
    bool in_bounds(int i, int j) const {
    return i >= 0 && i < static_cast<int>(input.size()) &&
           j >= 0 && j < static_cast<int>(input[0].size());
  }
};

