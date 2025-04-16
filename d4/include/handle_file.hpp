#include <string>
#include <tuple>
#include <vector>

using namespace std;

class XMAS {
  public:
    vector<tuple<int,int>> x_pos;
    vector<tuple<int,int>> m_pos;
    vector<tuple<int,int>> a_pos;
    vector<tuple<int,int>> s_pos;
};

class HandleFile {
  string str; 
  int xmas_count = 0;
  vector<string> grid;
  // XMAS pos;

  bool is_valid(int i, int j) const {
    return i >= 0 && i < static_cast<int>(grid.size()) &&
           j >= 0 && j < static_cast<int>(grid[0].size());
  }
  
  public:
    void get_file();
    void part1();
    void part2();
    bool check_direction(int i, int j, int di, int dj);
    bool check_x(int i, int j);
};

