#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "../include/handle_file.hpp"

using namespace std;


void HandleFile::part1(){
  for (const auto update  : updates) {
    vector<int> in_update{};
    bool correct_order = true;
    for (const int n : update) {
      std::vector<std::pair<int, int>> rules{};
      std::copy_if(order_rules.begin(), order_rules.end(), back_inserter(rules),
                                                          [n](const auto& p) {return p.first == n; });
      for (const auto rule : rules) {
        auto second_before_in_update = std::find_if(in_update.begin(), in_update.end(), 
                                                                    [rule](const auto& p) {return rule.second == p;});
        if (second_before_in_update != in_update.end()) {
          // cout << "not correct order" << endl;
          correct_order = false;
          break;
        }
      }
      in_update.push_back(n);
    }
    if (correct_order) {
      mid_num += in_update[(in_update.size()/2)];
    }
    for (auto i : in_update)
      cout << i << " ";
    cout << endl;
  }
  cout << mid_num << endl;
}

void HandleFile::part2(){
  for (const auto update  : updates) {
    vector<int> in_update{};
    bool correct_order = true;
    for (const int n : update) {
      std::vector<std::pair<int, int>> rules{};
      std::copy_if(order_rules.begin(), order_rules.end(), back_inserter(rules),
                                                          [n](const auto& p) {return p.first == n; });
      bool local_correct = true;
      int snd_index = -1;
      for (const auto rule : rules) {
        auto second_before_in_update = std::find_if(in_update.begin(), in_update.end(), 
                                                                    [rule](const auto& p) {return rule.second == p;});
        if (second_before_in_update != in_update.end()) {
          // cout << "not correct order" << endl;
          correct_order = false;
          local_correct = false;
          auto temp = static_cast<int>(distance(in_update.begin(),std::find(in_update.begin(), in_update.end(), rule.second)));
          if (snd_index == -1 || temp < snd_index)
            snd_index = temp;
        }
      }
      if (local_correct)
        in_update.push_back(n);
      else  
        in_update.insert(in_update.begin()+snd_index, n);

    }
    if (!correct_order) {
      mid_num += in_update[(in_update.size()/2)];
      for (auto i : in_update)
        cout << i << " ";
      cout << endl;
    }
  }
  cout << mid_num << endl;
}

void HandleFile::get_file(){
  ifstream file("../input.txt");
  while (getline(file, str)) {
    // Process str
    input.push_back(str);
  }
  regex r_rule("([0-9]+)\\|([0-9]+)");
  smatch m_rule;
  for (string str : input) {
    while(regex_search(str, m_rule, r_rule))
    {
      auto full = m_rule[0];

      pair<int,int> p{stoi(m_rule[1]),stoi(m_rule[2])};
      order_rules.push_back(p);

      str = m_rule.suffix();
    }
  }
  regex r_update("(([0-9]*)\\,)+([0-9]+)");
  smatch m_update;
  for (string str : input) {
    while(regex_search(str, m_update, r_update))
    {
      stringstream ss(m_update[0]);
      string token;
      vector<int> numbers;
      while (getline(ss, token, ',')) {
          numbers.push_back(std::stoi(token)); // convert string to int and add to vector
      }
      updates.push_back(numbers);
      
      str = m_update.suffix();
    }
  }
  // part1();
  part2();
}

