#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <sys/types.h>
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
  auto sort_disk = [&](){
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
  };

  load();
  print();
  sort_disk();
  checksum();
  cout << endl;

  print();
  cout << "Sum: " << sum << endl;
}

void HandleFile::part2(){
  auto sort_disk = [&](){
    size_t i;
    size_t j;
    struct Block {
      string id;
      int start;
      int length;
    };
    vector<Block> files;
    vector<Block> dots;
    
    //find file groups
    for (int i = 0; i < disk.size(); ){
      if (disk[i] != ".") {
        string id = disk[i];
        int start = i;
        while(i < disk.size() && disk[i] == id) i++;
        files.push_back({id,start,i-start});
      } else {
        i++;
      }
    }
    //find dot groups
    auto find_dots = [&](int len)->Block{
      for (int i = 0; i < disk.size(); ){
        if (disk[i] == ".") {
          string id = disk[i];
          int start = i;
          while(i < disk.size() && disk[i] == id) i++;
          if (len <= i-start)
            return {id,start,i-start};
        } else {
          i++;
        }
      }
      return {"-1",0,0};
    };
    
    while (files.size() > 0){
      auto file = files.back();
      files.pop_back();
      auto dot = find_dots(file.length);
      if (file.length <= dot.length && file.start >= dot.start+file.length){
        swap_ranges(disk.begin()+file.start, disk.begin()+file.start+file.length, disk.begin()+dot.start);
        dot.length-=file.length;
        dot.start+=file.length;
      }

    }


  };
  load();
  // print();
  sort_disk();
  checksum();
  cout << endl;

  // print();
  cout << "Sum: " << sum << endl;
}

void HandleFile::get_file(){
  ifstream file("../input.txt");
  while (getline(file, str)) {
    // Process str
    input = str;
  }
  // part1();
  part2();
}

