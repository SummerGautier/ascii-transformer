#include "ArgumentParser.hpp"
#include <utility>
#include <stdexcept>

ArgumentParser::ArgumentParser (int _argCount, char* _argVector[])
  : argCount(_argCount), argVector(_argVector) {
  // automatically collect first argument at index 0.
  this->index = 0;
  this->current = this->argVector[this->index];
}

std::string ArgumentParser::Next () {
  // only move to next argument if we're within bounds.
  if (HasNext()) {
    this->index++;
    this->current = this->argVector[this->index];
    return this->current;
  }
  // this should never happen, so if it does, program is wrong.
  throw std::runtime_error("Out of bounds exception. HasNext() is false but Next() was called.");
}

bool ArgumentParser::HasNext () {
  // avoid inputing huge argument count.
  if (this->index >= ArgumentParser::MaxAllowedArgs) {
    return false;
  }
  // index should not exceed total arguments given.
  if (this->index >= this->argCount - 1) {
    return false;
  }
  return true;
}

std::pair<int, std::string> ArgumentParser::Current () {
  // simple pair object of index and value.
  return std::pair {this->index, this->current};
}
