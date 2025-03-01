#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "IFormatter.hpp"

class HexFormatter : public IFormatter {
public:
  // write character to buffer.
  void Store (const char _value) override;
  // translate & writes buffer to oustream file.
  void Flush (std::ofstream& _outStreamRef) override;

private:
  // holds the characters that haven't been flushed.
  std::vector<char> buffer {};
  // caches translated charachters for lookup.
  std::map<char, std::string> cache {};
  // translate value to hex and returns string representation.
  std::string CharToHex(const char _value);
};
