#include <fstream>

  AsciiDraw::AsciiDraw () {
    // create dictionary
    // int (ascii number) : std::vector<std::string>> (rows for that letter)
  }

  void AsciiDraw::Store (const char _value) {
    // if buffer.top() == newline
      // throw exception
    // get ascii value
    // if key in dict()
      // buffer.append(key)
    // else
      // buffer.append(default)

  }

  void AsciiDraw::Flush (std::ofstream& _outStream) {
    // for int row = 0; row < 7
        // for int letterRef in buffer
            // std::string line = dictionary.get(letterRef).get(row);
            // out << line
        // out << newline
    // out << newline
  }
