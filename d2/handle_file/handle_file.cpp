#include <algorithm>
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
bool isSorted(const std::vector<int>& v) {
    if (v.size() <= 1) return true;  // Trivially sorted

    bool ascending = true;
    bool descending = true;

    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] < v[i - 1]) ascending = false;
        // if ((v[i]-v[i - 1])>3) ascending = false;
        if (v[i] > v[i - 1]) descending = false;
        // if ((v[i]-v[i - 1])<3) descending = false;
    }

    return ascending || descending;
}
void HandleFile::is_safe(){
  // vector<int> vec = {5,4,3,2,1};
  // vector<int> vec = {1,2,3,4,5};
  // vector<int> vec = {1,2,7,4,5};
  // if (is_sorted(vec.begin(),vec.end()))  
  //   cout << is_sorted(vec.begin(),vec.end()) << endl;
  // else if (is_sorted(vec.begin(),vec.end(), greater<int>{}))
  //   cout << is_sorted(vec.begin(),vec.end(), greater<int>{}) << endl;
  
  // cout << is_sorted(vec.begin(), vec.end()) || is_sorted(vec.begin(),vec.end(), greater<int>{});

  for (auto vec : vec_of_reports) { 
    vector<int> result {};
    adjacent_difference(vec.begin(), vec.end(), back_inserter(result));
    // for (auto i : result) {
    //   cout << i << " ";
    // }
    // cout << endl;
    auto in_bounds = true;
    for (int i = 1; i < vec.size(); i++) {
      if (vec[i]-vec[i-1] > 3 || vec[i]-vec[i-1] < -3) in_bounds = false;
      if (vec[i]-vec[i-1] == 0) in_bounds = false;
    } 

    if (isSorted(vec) == true && in_bounds == true) {
      sorted_count += 1;
    }
  }
  cout << "Safe: " << sorted_count << endl;

}
