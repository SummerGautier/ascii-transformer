#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

#include "IFormatter.hpp"

class BinaryFormatter : public IFormatter {
public:
  // store char into row buffer.
  void Store (const char _value) override;
  // translate and write buffer to outstream;
  void Flush (std::ofstream& _outStreamRef) override;
private:
  // holds char buffer waiting to be written.
  std::vector<char> buffer;
  // translate char to binary string representation.
  std::string CharToBinary (const char _value);
};
