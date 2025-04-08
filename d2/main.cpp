// https://adventofcode.com/2024/day/2
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "include/handle_file.hpp"

using namespace std;

int main (int argc, char *argv[]) {
  HandleFile h;
  h.get_file();
  h.is_safe();
  // cout << l.size() << endl;
  // cout << r.size() << endl;
  // // auto loop_length = l.size();
  // auto loop_length = 1;
  // for (int i = 0; i < loop_length; i++) { 
  //   auto min_l = min_element(l.begin(),l.end());
  //   auto min_r = min_element(r.begin(),r.end());
  //   diff_vec.push_back(Diff(*min_l, *min_r));
  //   cout << "Diff: " << diff_vec[i].diff << endl;
  // }
  // int total = 0;
  // cout << diff_vec.size() << endl;
  // for ( auto vec : diff_vec) {
  //   total += vec.diff;
  // }
  // cout << "Total: " << total << endl;

  return 0;
}


