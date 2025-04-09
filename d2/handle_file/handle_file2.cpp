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
bool isSorted(std::vector<int>& v, bool& tolerate) {
  if (v.size() <= 1) return true;  // Trivially sorted

  bool ascending = true;
  bool descending = true;

  for (size_t i = 1; i < v.size(); ++i) {
    if (v[i] < v[i - 1]) ascending = false;
    if (v[i] > v[i - 1]) descending = false;
    if (abs(v[i]-v[i-1]) == 0 && abs(v[i+1]-v[i]) == 0) return false;
  }

  return ascending || descending;
}
bool is_increasing(std::vector<int>& v, bool& tolerate) {
  if (v.size() <= 1) return true;  // Trivially sorted

  vector<int> not_inc_index;
  for (size_t i = 1; i < v.size(); ++i) {
    if (v[i] < v[i - 1]) not_inc_index.push_back(i);
    // if (v[i] > v[i - 1]) descending = false;
  }

  for (auto i : not_inc_index) {
    if (abs(v[i]-v[i-1]) == 0 && abs(v[i+1]-v[i]) == 0) return false;
    else if ((v[i-1] < v[i+1]) == false) return false;
    else return false;
  }
  return true;
}
bool can_be_sorted(vector<int> v, bool& tolerate){
  if (v.size() <= 2) return true;  // Trivially sorted

  return true;
}
void HandleFile::is_safe(){

  for (auto vec : vec_of_reports) { 
    // vector<int> result {};
    // adjacent_difference(vec.begin(), vec.end(), back_inserter(result));
    bool in_bounds = true;
    bool tolerate = true;
    for (int i = 1; i < vec.size(); i++) {
      int diff = vec[i]-vec[i-1];
      if (abs(diff) > 3) {
        if (tolerate == true) {
          tolerate = false;
          vec.erase(vec.begin()+i);
          --i;
        }
        else 
          in_bounds = false;
      }
      if (abs(diff) == 0) {
        if (tolerate == true) {
          tolerate = false;
          // tolerated_index = i;
          vec.erase(vec.begin()+i);
          --i;
        }
        else 
          in_bounds = false;
      }
    } 

    bool b = isSorted(vec,tolerate);
    if (b == true && in_bounds == true) {
      ++sorted_count;
    }

    for (auto i : vec) {
      cout << i << " ";
    }
    cout << endl;
    cout << "sorted: " << b << endl;
    cout << "tolerate: " << tolerate << endl;
    cout << "in_bounds: " << in_bounds << endl;
  }
  cout << "Safe: " << sorted_count << endl;

}
