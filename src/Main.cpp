#include <cstdint>

#include "Configuration/Config.hpp"

#include <fstream>
#include <iostream>

int main (int _argCount, char* _argVector[]) {
	/**
	 * Read in Configuration
	 **/

	Config _config {};
	if (!_config.Complete(_argCount, _argVector)) {
		std::cerr << "Unable to process configuration." << std::endl;
		return EXIT_FAILURE;
	}


	/**
	 * Write Transform to Output File
	 **/


	//open input and output streams.
	std::ifstream _ifstream {
		_config.sourceFile.FileName(),
		std::ios::in
	};

	if (!_ifstream.is_open()) {
		throw std::runtime_error("Unable to open file.");
	}

	char _current {' '};

	while (!_ifstream.eof()) {

		if (_ifstream.bad()) {
			throw std::runtime_error("I/O error while rading.");
		}
		if (_ifstream.fail()) {
			throw std::runtime_error("Corrupted data encountered.");
		}

		_current = _ifstream.get();

		if (!_ifstream.eof()) {
			std::cout << _current << std::endl;
		}
	}


	// read in input file one charachter at a time.
	// for each charachter
		// calculate transform
		// write the transform to the output
	// close input and output streams.
}
