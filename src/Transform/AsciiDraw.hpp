#include <fstream>

#include "ITransform.hpp"

class AsciiDraw : ITransform {
public:
  // read-in literals to dictionary.
  AsciiDraw ();
  // translate and add value to buffer.
  // throws error if last value is a new_line (not flushed).
  void Store (const char _value);
  // writes to outstream layer by layer.
  void Flush (std::ofstream& _outStream);

private:
  // holds in-process references to literal orders.
  std::vector<int> buffer {};
  // holds references to literal set.
  std::map<int,std::string> dictionary {};
}
