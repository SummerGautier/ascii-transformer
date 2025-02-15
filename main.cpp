#include <iostream>
#include <stdexcept>
#include <limits>
#include <cstdint>

#include "transformConfig.h"

// displays options to user
void Help () {
	// generate help message.
	std::string _helpMessage {
		" -- TextTransform HELP --\n"
		"\n"
		" # OPTIONS: \n"
		" --src <filename> (required)\n"
		" [--out <filename>]\n" 
		" [--transform asciiDraw (default) | hex | binary | utf8]\n"
		" [--help]\n"
	};
	// write to console.
	std::cout << _helpMessage << '\n';
	return;
}

int main (int _argCount, char* _argVector[]) {

	// maximum allowed args is CHAR_MAX = 127,
	// a fixed limit prevents runaway loops.
	int maxAllowedArgs {std::numeric_limits<char>::max()};

	// continue reading args until index reaches arg.
	for (int _index {0}; _index < _argCount; _index++) {

		// ensure we are not running past argument max.
		if (_index > maxAllowedArgs) {
			throw std::runtime_error("maximum argument count exceeded.");
		}

		// get current argument.
		std::string _arg = _argVector[_index];

		// display help options if help arg sent.
		if (_arg == "--help") {
			Help();
			// help usually means we can exit.
			return EXIT_SUCCESS;
		}
	}

	return EXIT_SUCCESS;
}