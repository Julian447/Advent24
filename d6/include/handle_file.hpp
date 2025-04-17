#include <string>
#include <tuple>
#include <vector>

using namespace std;


class HandleFile {
  string str; 
  vector<string> input;
  
  public:
    void get_file();
    void part1();
    void part2();
};

