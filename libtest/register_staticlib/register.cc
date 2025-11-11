#include "register.h"
#include "entry.h"
#include <iostream>

bool Register::reg(std::string name, BaseEntry& entry) {
  auto& entries = get_entries();
  if (entries.find(name) != entries.end()) {
    return false;
  }
  entries.emplace(name, &entry);
  return true;
}

const BaseEntry* Register::lookup(std::string name) {
  auto& entries = get_entries();
  if (entries.find(name) == entries.end()) {
    return nullptr;
  }
  return entries[name];
}

std::unordered_map<std::string, BaseEntry*>& Register::get_entries() {
  static std::unordered_map<std::string, BaseEntry*> entries;
  return entries;
}

void Register::print() {
  auto& entries = get_entries();
  for (auto&& [key, value] : entries) {
    std::cout << "key: " << key << " printing " << std::endl;
    value->print();
  }
}
