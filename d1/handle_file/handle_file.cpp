#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/handle_file.hpp"

using namespace std;

void get_file(std::vector<int>& l, std::vector<int>& r){
  ifstream file("../input.txt");
  string str; 
  while (getline(file, str)) {
    // Process str
    // getline(file,str);
    std::stringstream s(str);
    int str1, str2;
    s>>str1>>str2;
    l.push_back(str1);
    r.push_back(str2);

    // cout << str1 << endl;
    // cout << str2 << endl;
  }
}
