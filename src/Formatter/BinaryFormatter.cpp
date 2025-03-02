#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include <stdexcept>
#include <iostream>

#include "IFormatter.hpp"
#include "BinaryFormatter.hpp"

void BinaryFormatter::Store (const char _value) {
  if (this->buffer.size() > 0 && this->buffer.back() == '\n') {
    std::cerr << "Store was called but newline was detected." << std::endl;
    throw std::runtime_error("Flush must be called on last line before storing.");
  }
  // update buffer with character.
  this->buffer.push_back(_value);
}

void BinaryFormatter::Flush (std::ofstream& _outStreamRef) {
  // validate that outstream is open.
  if (!_outStreamRef.is_open()) {
    throw std::ios_base::failure("Fatal: Flush called but output stream if closed.");
  }
  // translate and write each as hexadecimal.
  for (auto& _character : this->buffer) {
    // translate the charachter.
    std::string _binaryString = this->CharToBinary(_character);
    // write to file.
    _outStreamRef << _binaryString;
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

std::string BinaryFormatter::CharToBinary (const char _value) {
  // convert to binary.
  std::bitset<8> _binary(_value);
  // return string value.
  return _binary.to_string();
}
