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

void AsciiDraw::ReadHeader (std::ifstream& _fileRef) {
  // validate that we are not at the end of file.
  if (_fileRef.eof()) {
    throw std::ios_base::failure("\n Fatal: Unable to read ascii header information, end of file encountered");
  }
  // height is first line of literals file.
  std::string _line {};
  std::getline(_fileRef, _line);
  this->fontHeight = std::stoi(_line);
  // width is second line of literals file.
  std::getline(_fileRef, _line);
  this->fontWidth = std::stoi(_line);
  // validate that stream is still alive.
  if (_fileRef.fail()) {
    throw std::ios_base::failure("\n Fatal: File stream corrupted reading ascii reference header information.");
  }
}

void AsciiDraw::ReadLiterals (std::ifstream& _fileRef) {
  // validate that we are not at the end of the file.
  if (_fileRef.eof()) {
    throw std::ios_base::failure("\n Fatal: Unable to read ascii image reference, end of file encountered.");
  }
  // _newline is false if the last line was not a newline.
  int _newline = false;
  // key is the numeric of the ascii letter whose image we're reading.
  // key = 97 would have the value for ascii image associated with 'a'.
  int _key {0};
  std::string _line {};
  // now that header was parsed, read the content.
  while (std::getline(_fileRef, _line)) {
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
    } else if (_line.size() == 0) {
      // if current line is a newline:
      _newline = true;
    } else if (_line.size() > 0) {
      // line is a row of an image for the current key.
      // add row to the image vector for the key.
      this->dictionary.at(_key).push_back(_line);
    }
  }
}

void AsciiDraw::Store (const char _value) {
  // store should not be called if a line is not flushed.
  if (this->buffer.size() > 0 && this->buffer.back() == int('\n')) {
    std::cerr << "Store was called but newline was detected." << std::endl;
    throw std::runtime_error("Flush must be called on last line before storing.");
  }

  // key should be integer of charachter.
  int _key = int(std::tolower(_value));

  // if key does not have a literal, use default.
  if (!this->dictionary.contains(_key) && _value != '\n') {
    _key = this->defaultKey;
  }

  // enter key into the buffer.
  this->buffer.push_back(_key);
}

void AsciiDraw::Flush (std::ofstream& _outStreamRef) {

  if (!_outStreamRef.is_open()) {
    throw std::ios_base::failure("Fatal: Flush called but output stream if closed.");
  }

  /**
   * Since each letter has multiple layers, we have to write the same layer simultaneously for the rows.
   * Example: ACE ->
   *   a   cccc eeee # has to be printed 1st.
   *  aaa  c    ee   # has to be printed 2nd.
   * a   a cccc eeee # has to be printed 3rd.
   *
   *
   * The buffer index contains the ascii number of each letter. ACE = [97, 99, 101]
   * The letter images have the same number of rows (fontHeight) and cols (fontWidth);
   *
   * To print them in the right order per layer, we do the following:
   * For each row:
   *    For each letter
   *      Get the image vector for that letter.
   *      Get the row of the letter's image equal to the current overall row we're printing.
   *      Print that row without a newline.
   *    At the end of the row, print the newline.
   * This will print the letters layer by layer next to eachother.
   * **/

  for (int _row = 0; _row < this->fontHeight; ++_row) {
    for (int _col = 0; _col < this->buffer.size(); ++_col) {
        int _key = this->buffer.at(_col);
        if (_key != int('\n')) {
          std::vector<std::string> _image = this->dictionary.at(_key);
          _outStreamRef << _image.at(_row) << "   ";
        }
        if (_outStreamRef.fail()) {
          throw std::ios_base::failure("Fatal: can't continue writing to output file.");
        }
    }
    _outStreamRef << '\n';
  }
  _outStreamRef << std::endl;
  this->buffer.clear();
}
