#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "../include/handle_file.hpp"

using namespace std;

void HandleFile::get_file(){
  ifstream file("../input.txt");
  string str; 
  while (getline(file, str)) {
    // Process str
    // getline(file,str);
    std::stringstream s(str);
    vector<int> numbers((istream_iterator<int>(s)), istream_iterator<int>());
    vec_of_reports.push_back(numbers);
  }
}
bool isSorted(std::vector<int>& v) {
  if (v.size() <= 1) return true;  // Trivially sorted

  bool ascending = true;
  bool descending = true;

  for (size_t i = 1; i < v.size(); ++i) {
    if (v[i] < v[i - 1]) ascending = false;
    if (v[i] > v[i - 1]) descending = false;
  }

  return ascending || descending;
}
bool can_be_true(std::vector<int>& v) {
  if (isSorted(v)) return true;

  for (size_t i = 1; i < v.size(); i++) {
    vector<int> mod_v = v;
    mod_v.erase(mod_v.begin()+i);
    if(isSorted(mod_v)) return true;
  }
  return false;
}
void HandleFile::is_safe(){

  for (auto vec : vec_of_reports) { 
    vector<int> result {};
    adjacent_difference(vec.begin(), vec.end(), back_inserter(result));
    auto in_bounds = true;
    for (int i = 1; i < vec.size(); i++) {
      int diff = vec[i]-vec[i-1];
      if (abs(diff) > 3) in_bounds = false;
      if (abs(diff) == 0) in_bounds = false;
      
    } 
    // for (auto i : vec) {
    //   cout << i << " ";
    // }
    // cout << endl;
    // cout << "tolerate: " << tolerate << endl;
    if (can_be_true(vec) == true && in_bounds == true) {
      ++sorted_count;
    }
  }
  cout << "Safe: " << sorted_count << endl;

}
