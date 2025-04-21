#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../include/handle_file.hpp"

using namespace std;

void HandleFile::print() {
  for (auto s : disk) {
    cout << s;
  }
  cout << endl;
}

void HandleFile::load(){
  int id = 0;
  auto add_to_disk = [&](int num, string s){
    for (size_t j = 0; j < num; ++j) {
      disk.push_back(s);
    }
  };

  for (size_t i = 0; i < input.length(); ++i) {
    if (i % 2 == 0){
      // cout << input[i] << endl;
      add_to_disk(stoi(string(1,input[i])), to_string(id));
      id++;
    }
    else {
      add_to_disk(stoi(string(1,input[i])), ".");
    }
  }
}

void HandleFile::sort() {
  size_t i;
  size_t j;
  for (i = disk.size()-1; i > 0; --i) {
    if (disk[i] != "."){
      for (j = 0; j < i; ++j) {
        if (disk[j] == ".") {
          swap(disk[j],disk[i]);
          break;
        }
      }
    } 
  }
}

void HandleFile::checksum() {
  cout << "Length: " << disk.size() << endl;
  for (size_t i = 0; i < disk.size()-1; ++i) {
    if (disk[i] != ".") {
      int id = stoi(disk[i]);
      sum+=i*id;
    }
  }

}

void HandleFile::part1(){
  load();
  print();

  sort();
  print();
  checksum();
  print();
  cout << "Sum: " << sum << endl;
}

void HandleFile::part2(){
  print();
}

void HandleFile::get_file(){
  ifstream file("../input.txt");
  while (getline(file, str)) {
    // Process str
    input = str;
  }
  part1();
  // part2();
}

