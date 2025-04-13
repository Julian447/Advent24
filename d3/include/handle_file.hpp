#include <map>
#include <string>
#include <vector>

using namespace std;

class HandleFile {
  string str; 
  int mult = 0;
  bool enabled = true;
  
  public:
    void get_file();
    void part1();
    void part2();
};

