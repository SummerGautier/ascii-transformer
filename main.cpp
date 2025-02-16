#include <iostream>
#include <stdexcept>
#include <limits>
#include <cstdint>
#include <format>

#include "transformConfig.h"
#include "file.h"

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


	// input and output files created on the stack.
	File _sourceFile {};
	File _outputFile {};

	// captures output writing TransformConfig.
	TransformConfig::WriteFormat _writeFormat {TransformConfig::WriteFormat::asciiDraw};

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

		// set source file if it is a source file.
		if (_arg == "--src") {
			// search next argument.
			++_index;
			// read in raw file name.
			std::string _rawFileName = _argVector[_index];
			// parse raw file name to update source file.
			bool _supportedExtension = _sourceFile.ParseRawFileName(_rawFileName);
			if (!_supportedExtension) {
				// formatt error message with expected file extensions.
				std::string _message {
					std::format("Unable to process {} not supported. These are allowed extensions: {}. Use --help for more options.", 
						_sourceFile.Extension(), File::AllowedExtensions())
				};

				throw std::runtime_error(_message);
			}
		}

		// set mode to drawing ascii charachters.
		if (_arg == "--ascii-draw") {
			_writeFormat = TransformConfig::WriteFormat::asciiDraw;
		}

		// set mode to writing hexadecimal.
		if (_arg == "--hex") {
			_writeFormat = TransformConfig::WriteFormat::hexadecimal;
		}

		// set mode to writing binary.
		if (_arg == "--binary") {
			_writeFormat = TransformConfig::WriteFormat::binary;
		}

		// set mode to writing utf-8.
		if (_arg == "--utf8") {
			_writeFormat = TransformConfig::WriteFormat::utf8;
		}
	}

	// if source file was not found, except without exception.
	if (_sourceFile.FileName() == " ") {
		std::cout << "Please provide a source file using --src <filename> \nUse --help for more options." << std::endl;
		return EXIT_FAILURE;
	}

	// if out file is missing, use post-fix on srcfile
	if (_outputFile.FileName() == " ") {
		std::string _defaultFileName {_sourceFile.BaseName() + "-transformed" + _sourceFile.Extension()};
		bool _valid = _outputFile.ParseRawFileName(_defaultFileName);
		if (!_valid) {
			throw std::logic_error(std::format("Something went wrong, unable to generate default output filename. {} is not supported.", _defaultFileName));
		}

		std::cout << std::format("Using output file name: {}", _outputFile.FileName());
	}

	return EXIT_SUCCESS;
}