#pragma once
#include <string>
#include <unordered_map>
#include "entry.h"

class Register {
public:
  static bool reg(std::string name, BaseEntry& entry);
  static const BaseEntry* lookup(std::string name);
  static void print();
private:
  static std::unordered_map<std::string, BaseEntry*>& get_entries(); 
};
