#include <string>
#include <tuple>
#include <vector>

using namespace std;


class HandleFile {
  string str; 
  vector<string> input;
  vector<pair<int,int>> order_rules;
  vector<vector<int>> updates;
  int mid_num = 0;
  
  public:
    void get_file();
    void part1();
    void part2();
};

