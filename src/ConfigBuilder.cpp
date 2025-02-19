#include <iostream>
#include <stdexcept>
#include <limits>
#include <cstdint>
#include <format>

#include "Config.hpp"
#include "ConfigBuilder.hpp"

bool ConfigBuilder::Build (Config& _configRef, int _argCount, char* _argVector[]) {
	// continue reading args until index reaches arg.
	for (int _index {0}; _index < _argCount; _index++) {

		std::string _arg = ExtractArg(_index, _argVector);

		if (Help(_arg) == ConfigBuilder::Status::Completed) {
			// exit program if help screen was displayed.
			std::exit(EXIT_SUCCESS);
		}
		if (Source(_arg, _configRef, _index, _argVector, _argCount) == ConfigBuilder::Status::Failed) {
			// exit program if error processing source file arg.
			return false;
		}
		if (Out(_arg, _configRef, _index, _argVector, _argCount) == ConfigBuilder::Status::Failed) {
			//exit program if error processing output file arg.
			return false;
		}
		if (Formats(_arg, _configRef) == ConfigBuilder::Status::Failed) {
			// exit program if format could not be set.
			return false;
		}
	}
	// return true of config is valid.
	return (ValidateConfig(_configRef) == ConfigBuilder::Status::Completed);
}

std::string ConfigBuilder::ExtractArg (int _index, char* _argVector[]) {
	// ensure we are not running past argument max.
	if (_index > ConfigBuilder::MaxAllowedArgs) {
		throw std::runtime_error("maximum argument count exceeded.");
	}
	// get current argument.
	return _argVector[_index];
}

ConfigBuilder::Status ConfigBuilder::Help (const std::string _arg) {
	// display help options if help arg sent.
	if (_arg == "--help") {
		// generate help message.
		std::string _helpMessage {
			" -- TextTransform HELP --\n"
			"\n"
			" # OPTIONS: \n"
			" --src <filename> (required)\n"
			" [--out <filename>]\n" 
			" [--asciiDraw (default) | hex | binary | utf8]\n"
			" [--help]\n"
		};
		// write to console.
		std::cout << _helpMessage << '\n';
		// compelted status.
		return ConfigBuilder::Status::Completed;
	}
	// no activity performed.
	return ConfigBuilder::Status::None;
}

ConfigBuilder::Status ConfigBuilder::Source (const std::string _arg, Config& _configRef, int& _index, char* _argVector[], int _argCount) {
	// set source file if it is a source file.
	if (_arg == "--src") {
		// check that next arg is available.
		if (_index+1 >= _argCount) {
			std::cerr << "ERROR: Unable to continue. Source file was not provided. Use --help for more options." << std::endl;
			return ConfigBuilder::Status::Failed;
		}
		// since next arg is availble, move 'pointer' forward.
		++_index;
		// read in raw file name.
		std::string _rawFileName = _argVector[_index];
		// parse raw file name to update source file.
		bool _supportedExtension = _configRef.sourceFile.ParseRawFileName(_rawFileName);
		if (!_supportedExtension) {
			// formatt error message with expected file extensions.
			std::string _message {
				std::format("ERROR: Unable to process, supplied source file type not supported.\n These are allowed extensions: {}.\n Use --help for more options.", File::AllowedExtensions())
			};

			std::cerr << _message << std::endl;
			return Status::Failed;
		}
		return ConfigBuilder::Status::Completed;
	}
	return ConfigBuilder::Status::None;
}

ConfigBuilder::Status ConfigBuilder::Out (const std::string _arg, Config& _configRef, int& _index, char*_argVector[], int _argCount) {
	// set source file if it is a source file.
	if (_arg == "--out") {
		// check that next arg is available.
		if (_index+1 >= _argCount) {
			std::cout << "--out flag was recieved without filename. Use default filename? [Y/n] ";
			std::string _useDefault {};
			std::cin >> _useDefault;
			if (_useDefault == "n") {
				std::cerr << "Exiting without exception." << std::endl;
				return ConfigBuilder::Status::Failed;
			} 
			std::cout << "Resuming." << std::endl;
		} else {
			// since next arg is availble, move 'pointer' forward.
			++_index;
			// read in raw file name.
			std::string _rawFileName = _argVector[_index];
			// parse raw file name to update source file.
			bool _supportedExtension = _configRef.outputFile.ParseRawFileName(_rawFileName);
			if (!_supportedExtension) {
				// formatt error message with expected file extensions.
				std::string _message {
					std::format(" ERROR: Unable to process, supplied outpfile type not supported.\n These are allowed extensions: {}.\n Use --help for more options.", File::AllowedExtensions())
				};

				std::cerr << _message << std::endl;
				return ConfigBuilder::Status::Failed;
			}
		}
		return ConfigBuilder::Status::Completed;
	}
	return ConfigBuilder::Status::None;
}

ConfigBuilder::Status ConfigBuilder::Formats (const std::string _arg, Config& _configRef) {
	// set mode to drawing ascii charachters by
	_configRef.writeFormat = Options::WriteFormat::asciiDraw;
	// this if doesn't change function of last line, it's just for symmetry :) 
	if (_arg == "--ascii-draw") {
		_configRef.writeFormat = Options::WriteFormat::asciiDraw;
	}
	// set mode to writing hexadecimal.
	if (_arg == "--hex") {
		_configRef.writeFormat = Options::WriteFormat::hexadecimal;
	}
	// set mode to writing binary.
	if (_arg == "--binary") {
		_configRef.writeFormat = Options::WriteFormat::binary;
	}
	// set mode to writing utf-8.
	if (_arg == "--utf8") {
		_configRef.writeFormat = Options::WriteFormat::utf8;
	}
	// mode will always be set by default.
	return ConfigBuilder::Status::Completed;
}

ConfigBuilder::Status ConfigBuilder::ValidateConfig (Config& _configRef) {
	// if source file was not found, except without exception.
	if (_configRef.sourceFile.FileName() == "") {
		std::cerr << " ERROR: Please provide a source file using --src <filename>\n Use --help for more options." << std::endl;
		return ConfigBuilder::Status::Failed;
	}
	// if out file is missing, use post-fix on srcfile
	if (_configRef.outputFile.FileName() == "") {
		std::string _defaultFileName {_configRef.sourceFile.BaseName() + "-transformed" + _configRef.sourceFile.Extension()};
		bool _valid = _configRef.outputFile.ParseRawFileName(_defaultFileName);
		if (!_valid) {
			std::cerr << std::format(" Something went wrong, unable to generate default output filename.\n {} is not a valid file type.", _defaultFileName) << std::endl;
			return ConfigBuilder::Status::Failed;
		}
		std::cout << std::format(" Using output file name: {}", _configRef.outputFile.FileName()) << std::endl;
	}

	if (!_configRef.sourceFile.VerifySupportedExtension(_configRef.sourceFile.Extension())) {
		return ConfigBuilder::Status::Failed;
	}

	if (!_configRef.outputFile.VerifySupportedExtension(_configRef.outputFile.Extension())) {
		return ConfigBuilder::Status::Failed;
	}
	return ConfigBuilder::Status::Completed;
}
