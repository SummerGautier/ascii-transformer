#include <iostream>
#include <stdexcept>
#include <limits>
#include <cstdint>
#include <format>

#include "TransformConfig.h"
#include "File.h"

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

struct TransformConfiguration {
	// input and output files created on the stack.
	File sourceFile {};
	File outputFile {};

	// captures output writing TransformConfig.
	TransformConfig::WriteFormat writeFormat {TransformConfig::WriteFormat::asciiDraw};
};

int main (int _argCount, char* _argVector[]) {

	TransformConfiguration _config {};

	// maximum allowed args is CHAR_MAX = 127,
	// a fixed limit prevents runaway loops.
	int _maxAllowedArgs {std::numeric_limits<char>::max()};

	// continue reading args until index reaches arg.
	for (int _index {0}; _index <= _argCount; _index++) {

		// ensure we are not running past argument max.
		if (_index > _maxAllowedArgs) {
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
			
			// check that next arg is available.
			if (_index+1 >= _argCount) {
				std::cerr << "Unable to continue. Source file was not provided. Use --help for more options.";
				return EXIT_FAILURE;
			}
			// since next arg is availble, move 'pointer' forward.
			++_index;
			// read in raw file name.
			std::string _rawFileName = _argVector[_index];
			// parse raw file name to update source file.
			bool _supportedExtension = _config.sourceFile.ParseRawFileName(_rawFileName);
			if (!_supportedExtension) {
				// formatt error message with expected file extensions.
				std::string _message {
					std::format("Unable to process {} not supported. These are allowed extensions: {}. Use --help for more options.", 
						_config.sourceFile.Extension(), File::AllowedExtensions())
				};

				std::cerr << _message;
				return EXIT_FAILURE;
			}
		}

		// set mode to drawing ascii charachters.
		if (_arg == "--ascii-draw") {
			_config.writeFormat = TransformConfig::WriteFormat::asciiDraw;
		}

		// set mode to writing hexadecimal.
		if (_arg == "--hex") {
			_config.writeFormat = TransformConfig::WriteFormat::hexadecimal;
		}

		// set mode to writing binary.
		if (_arg == "--binary") {
			_config.writeFormat = TransformConfig::WriteFormat::binary;
		}

		// set mode to writing utf-8.
		if (_arg == "--utf8") {
			_config.writeFormat = TransformConfig::WriteFormat::utf8;
		}
	}

	// if source file was not found, except without exception.
	if (_config.sourceFile.FileName() == " ") {
		std::cout << "Please provide a source file using --src <filename> \nUse --help for more options." << std::endl;
		return EXIT_FAILURE;
	}

	// if out file is missing, use post-fix on srcfile
	if (_config.outputFile.FileName() == " ") {
		std::string _defaultFileName {_config.sourceFile.BaseName() + "-transformed" + _config.sourceFile.Extension()};
		bool _valid = _config.outputFile.ParseRawFileName(_defaultFileName);
		if (!_valid) {
			throw std::logic_error(std::format("Something went wrong, unable to generate default output filename. {} is not supported.", _defaultFileName));
		}
		std::cout << std::format("Using output file name: {}", _config.outputFile.FileName());
	}

	return EXIT_SUCCESS;
}