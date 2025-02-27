#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>
#include <string>

#include "AsciiDraw.hpp"

AsciiDraw::AsciiDraw () {

  std::ifstream _literals {
    this->referenceFile,
    std::ios::in
  };

  if (!_literals.is_open() || _literals.fail() || _literals.bad()) {
    throw std::ios_base::failure("\n Fatal: Unable to read ascii reference.");
  }

  std::string _line {};

  std::getline(_literals, _line);
  const int _height = std::stoi(_line);

  std::getline(_literals, _line);
  const int _width = std::stoi(_line);

  std::cout << _height << std::endl;
  std::cout << _width << std::endl;

  int _newline = false;
  int _key = 0;
  while (std::getline(_literals, _line)) {
    if (_line.size() == 0) {
      _newline= true;
    } else if (_newline) {
        _newline = false;
        _key = std::stoi(_line);
        std::vector<std::string> _value {};
        std::pair<int, std::vector<std::string>>  _pair { _key, _value };
        this->dictionary.insert(_pair);
    } else {
        this->dictionary.at(_key).push_back(_line);
    }
  }

  _literals.close();

  if (this->dictionary.size() == 0) {
    throw std::runtime_error ("\n Fatal: Ascii Dictionary did not initialize");
  }

  for (auto& pair : this->dictionary) {
    std::vector<std::string> _letter = pair.second;
    for (auto& row : _letter) {
      std::cout << row << '\n';
    }
  }

  return;
}

void AsciiDraw::Store (const char _value) {
  std::cout << "store" << std::endl;
  // if buffer.top() == newline
    // throw exception
  // get ascii value
  // if key in dict()
    // buffer.append(key)
  // else
    // buffer.append(default)
  return;

}

void AsciiDraw::Flush (std::ofstream& _outStream) {
  std::cout << "flush" << std::endl;
  // for int row = 0; row < 7
      // for int letterRef in buffer
          // std::string line = dictionary.get(letterRef).get(row);
          // out << line
      // out << newline
  // out << newline
  return;
}
