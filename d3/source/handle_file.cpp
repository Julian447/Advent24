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

void HandleFile::get_file(){
  ifstream file("../input.txt");
  string str; 
  int mult = 0;
  while (getline(file, str)) {
    // Process str
    regex r("(mul)\\(([0-9]+)\\,([0-9]+)\\)");
    smatch ma;
    while(regex_search(str, ma, r))
    {
      // std::cout << ma[0] << std::endl;
      auto full = ma[0];
      auto x = stoi(ma[2]);
      auto y = stoi(ma[3]);
      mult += x*y;

      // std::cout << full << std::endl;
      // std::cout << x*y << std::endl;
      
      str = ma.suffix();
    }
  }
  cout << mult << endl;
}
