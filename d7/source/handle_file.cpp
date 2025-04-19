#include <cstddef>
#include <cstdlib>
#include <fstream>
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
void HandleFile::part1(){
  // print();
  
  auto loads = [&](string row) -> pair<int,vector<int>>{
    vector<string> extracted;
    stringstream ss(row);
    int result;

    while (getline(ss,str, ':')) {
      extracted.push_back(str);
    }
    result = stoi(extracted[0]);
    stringstream s(extracted[1]);
    vector<int> combinators((istream_iterator<int>(s)), istream_iterator<int>());
    return {result, combinators};
  };
  
  int sum_result = 0;
  auto load = loads(input[0]);
  cout << load.first << endl;
  for (auto i : load.second) {
    cout << i << " ";
  }
  cout << endl;

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

