#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../include/handle_file.hpp"

using namespace std;

void HandleFile::print(){
  for (auto row : input) {
    cout << row << endl;
  }
}

bool HandleFile::combine(uint64_t result, const vector<uint64_t>& combinators) {
  function<bool(uint64_t, size_t)> dfs = [&](uint64_t current, size_t index) {
    if (index == combinators.size()) {
      return current == result;
    }

    uint64_t next = combinators[index];
    uint64_t comb = stoull(to_string(current) + to_string(next));
    return dfs(current + next, index + 1) || dfs(current * next, index + 1) || dfs(comb, index + 1);
  };

  // Start from the first number, begin chaining from index 1
  return dfs(combinators[0], 1);
}
void HandleFile::part1(){
  // print();
  
  auto loads = [&](const string& row) -> pair<uint64_t, vector<uint64_t>> {
    size_t colon_pos = row.find(':');
    if (colon_pos == string::npos) {
      throw runtime_error("Invalid input format: missing ':'");
    }

    uint64_t result = stoull(row.substr(0, colon_pos));
    // cout << "Result: " << result << ", ";
  
    string combinator_part = row.substr(colon_pos + 1);
    stringstream s(combinator_part);
    vector<uint64_t> combinators((istream_iterator<uint64_t>(s)), istream_iterator<uint64_t>());
    
    string test = to_string(result) + ": ";
    for (size_t i = 0; i < combinators.size(); ++i){
      if (i == combinators.size()-1)
        test += to_string(combinators[i]);
      else
        test += to_string(combinators[i]) + " ";
    }
    if (test != row) {
      cout << "Result: " << result << ", " << endl;
      cout << "Combinators: ";
      for (long long num : combinators) {
          cout << num << " ";
      }
      cout << endl;
    }

    return {result, combinators};
  };

  uint64_t sum_result = 0;  
  for (size_t i = 0; i < input.size(); ++i) { 
    auto load = loads(input[i]);
  
    if (combine(load.first,load.second) != 0){
      auto prev_sum_result = sum_result;
      sum_result += load.first;
      if ((sum_result - prev_sum_result) != load.first){
        cout << "Result: " << load.first << " can be combined, Loads: ";
        for (auto s : load.second) {
          cout << s << " ";
        }
        cout << endl;
        cout << sum_result << endl;
      }
    }
    else {
      // cout << "can not be combined" << endl;
    }
  }
  cout << sum_result << endl;

}

void HandleFile::part2(){
}

void HandleFile::get_file(){
  ifstream file("../input.txt");
  while (getline(file, str)) {
    // Process str
    input.push_back(str);
  }
  part1();
  // part2();
}

