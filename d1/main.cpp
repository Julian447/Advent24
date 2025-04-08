// https://adventofcode.com/2024/day/1
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include "include/handle_file.hpp"

using namespace std;

class Diff {
  public:
    Diff(int l, int r) {
      l = l;
      r = r;
      if (l < r) {
        diff = r-l;
      }
      else {
        diff = l-r;
      }
      // diff = abs(l-r);
    }
    int diff;
    int l;
    int r;
};

int main (int argc, char *argv[]) {
  vector<int> l;
  vector<int> r;
  vector<Diff> diff_vec;
  get_file(l, r);
  cout << l.size() << endl;
  cout << r.size() << endl;
  auto loop_length = l.size();
  for (int i = 0; i < loop_length; i++) { 
    auto min_l = min_element(l.begin(),l.end());
    auto min_r = min_element(r.begin(),r.end());
    diff_vec.push_back(Diff(*min_l, *min_r));
    l.erase(min_l);
    r.erase(min_r);
    // cout << "Diff: " << diff_vec[i].diff << endl;
  }
  int total = 0;
  cout << diff_vec.size() << endl;
  for ( auto vec : diff_vec) {
    total += vec.diff;
  }
  cout << "Total: " << total << endl;

  return 0;
}


