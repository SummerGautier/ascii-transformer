#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>
#include <string>

#include "AsciiDraw.hpp"

AsciiDraw::AsciiDraw () {
  // file of ascii images.
  std::ifstream _literals {
    this->referenceFile,
    std::ios::in
  };
  // fatal error if unable to read ascii images.
  if (!_literals.is_open() || _literals.fail() || _literals.bad()) {
    throw std::ios_base::failure("\n Fatal: Unable to read ascii reference.");
  }
  // read in header information (height/width).
  this->ReadHeader(_literals);
  // read in ascii image vectors.
  this->ReadLiterals(_literals);
  // close file stream.
  _literals.close();
  // dictionary must have at least one value.
  if (this->dictionary.size() == 0) {
    throw std::runtime_error ("\n Fatal: Ascii Dictionary did not initialize");
  }
}

void AsciiDraw::ReadHeader (std::ifstream& _file) {
  // validate that we are not at the end of file.
  if (_file.eof()) {
    throw std::ios_base::failure("\n Fatal: Unable to read ascii header information, end of file encountered");
  }
  // height is first line of literals file.
  std::string _line {};
  std::getline(_file, _line);
  this->fontHeight = std::stoi(_line);
  // width is second line of literals file.
  std::getline(_file, _line);
  this->fontWidth = std::stoi(_line);
  // validate that stream is still alive.
  if (_file.fail()) {
    throw std::ios_base::failure("\n Fatal: File stream corrupted reading ascii reference header information.");
  }
}

void AsciiDraw::ReadLiterals (std::ifstream& _file) {
  // validate that we are not at the end of the file.
  if (_file.eof()) {
    throw std::ios_base::failure("\n Fatal: Unable to read ascii image reference, end of file encountered.");
  }
  // _newline is false if the last line was not a newline.
  int _newline = false;
  // key is the numeric of the ascii letter whose image we're reading.
  // key = 97 would have the value for ascii image associated with 'a'.
  int _key {0};
  std::string _line {};
  // now that header was parsed, read the content.
  while (std::getline(_file, _line)) {
    if (_newline) {
      // if last line was a newline:
      _newline = false;
      // int of string representing ascii decimal.
      _key = std::stoi(_line);
      // initialize image vector to empty array.
      std::vector<std::string> _value {};
      // store decimal:image-vector pair to dictionary.
      std::pair<int, std::vector<std::string>>  _pair { _key, _value };
      this->dictionary.insert(_pair);
    }
    if (_line.size() == 0) {
      // if current line is a newline:
      _newline = true;
    }
    if (_line.size() > 0) {
      // line is a row of an image for the current key.
      // add row to the image vector for the key.
      this->dictionary.at(_key).push_back(_line);
    }
  }
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
