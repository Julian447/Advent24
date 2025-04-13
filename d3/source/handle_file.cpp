#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "../include/handle_file.hpp"

using namespace std;

void HandleFile::part1(){
  regex r("(mul)\\(([0-9]+)\\,([0-9]+)\\)");
  smatch m;
  while(regex_search(str, m, r))
  {
    // std::cout << m[0] << std::endl;
    auto full = m[0];
    auto x = stoi(m[2]);
    auto y = stoi(m[3]);
    mult += x*y;

    // std::cout << full << std::endl;
    // std::cout << x*y << std::endl;
    
    str = m.suffix();
  }
}

void HandleFile::part2(){
  regex r("(mul)\\(([0-9]+)\\,([0-9]+)\\)|do\\(\\)|don't\\(\\)");
  smatch m;
  while(regex_search(str, m, r))
  {
    if (m[0] == "do()")
      enabled = true;
    else if (m[0] == "don't()")
      enabled = false;
    else if (enabled) {
      auto full = m[0];
      auto x = stoi(m[2]);
      auto y = stoi(m[3]);
      mult += x*y;
    }

    // std::cout << m[0] << std::endl;
    // std::cout << full << std::endl;
    // std::cout << x*y << std::endl;
    
    str = m.suffix();
  }
}

void HandleFile::get_file(){
  ifstream file("../input.txt");
  while (getline(file, str)) {
    // Process str
    // part1();
    part2();
  }
  cout << mult << endl;
}

