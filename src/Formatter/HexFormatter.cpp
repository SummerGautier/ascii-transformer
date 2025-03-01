#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "IFormatter.hpp"
#include "HexFormatter.hpp"

void HexFormatter::Store (const char _value) {
  if (this->buffer.size() > 0 && this->buffer.back() == '\n') {
    std::cerr << "Store was called but newline was detected." << std::endl;
    throw std::runtime_error("Flush must be called on last line before storing.");
  }
  // update buffer with character.
  this->buffer.push_back(_value);
}

void HexFormatter::Flush (std::ofstream& _outStreamRef) {
  // validate that outstream is open.
  if (!_outStreamRef.is_open()) {
    throw std::ios_base::failure("Fatal: Flush called but output stream if closed.");
  }
  // translate and write each as hexadecimal.
  for (auto& _character : this->buffer) {
    // translate the charachter.
    std::string _hexString = this->CharToHex(_character);
    // write to file.
    _outStreamRef << _hexString;
    // validate that stream was not corrupted.
    if (_outStreamRef.fail()) {
        throw std::ios_base::failure("Fatal: can't continue writing to output file.");
    }
  }
  // flush with newline.
  _outStreamRef << '\n';

  // clear buffer.
  this->buffer.clear();
}

std::string HexFormatter::CharToHex (const char _value) {
  // check if this char was translated before.
  if (this->cache.contains(_value)) {
    return this->cache.at(_value);
  }

  // convert to hexadecimal.
  std::stringstream _stream;
  _stream << std::hex << int(_value);

  // update cache with pair.
  std::pair<char, std::string> _pair {_value, _stream.str()};
  this->cache.insert(_pair);

  // return string value.
  return _stream.str();
}
