#include <vector>

class HandleFile {
  // std::vector<int> vec;
  std::vector<std::vector<int>> vec_of_reports;
  int sorted_count = 0;
  public:
    void get_file();
    void is_safe();

};

