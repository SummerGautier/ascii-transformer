#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <map>

#include "ITransform.hpp"

class AsciiDraw : public ITransform {
public:
  // read-in literals to dictionary.
  AsciiDraw ();
  // translate and add value to buffer.
  // throws error if last value is a new_line (not flushed).
  void Store (const char _value) override;
  // writes to outstream layer by layer.
  void Flush (std::ofstream& _outStream) override;

private:
  // holds in-process references to literal orders.
  std::vector<int> buffer {};
  // holds references to literal set.
  std::map<int,std::vector<std::string>> dictionary {};
  // filename of where the literals are stored.
  const std::string referenceFile {"src/Transform/Data/Literals.txt"};
};
