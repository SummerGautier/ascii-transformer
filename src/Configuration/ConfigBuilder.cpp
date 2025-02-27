#include <iostream>
#include <stdexcept>
#include <limits>
#include <cstdint>
#include <format>

#include "Config.hpp"
#include "ConfigBuilder.hpp"
#include "ArgumentParser.hpp"

bool ConfigBuilder::Build (Config& _configRef, ArgumentParser& _parserRef) {
	bool _reading = _parserRef.HasNext();
	// continue reading args until index reaches arg.
	while (_reading) {

		if (Help(_parserRef) == ConfigBuilder::Status::Completed) {
			// exit program if help screen was displayed.
			std::exit(EXIT_SUCCESS);
		}
		if (Source(_configRef, _parserRef) == ConfigBuilder::Status::Failed) {
			// exit program if error processing source file arg.
			return false;
		}
		if (Out(_configRef, _parserRef) == ConfigBuilder::Status::Failed) {
			//exit program if error processing output file arg.
			return false;
		}
		if (Formats(_configRef, _parserRef) == ConfigBuilder::Status::Failed) {
			// exit program if format could not be set.
			return false;
		}

		if (_parserRef.HasNext()) {
			_parserRef.Next();
		} else {
			_reading = false;
		}
	}
	// return true of config is valid.
	return (ValidateConfig(_configRef) == ConfigBuilder::Status::Completed);
}

ConfigBuilder::Status ConfigBuilder::Help (ArgumentParser& _parserRef) {
	// display help options if help arg sent.
	if (_parserRef.Current().second == "--help") {
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

ConfigBuilder::Status ConfigBuilder::Source (Config& _configRef, ArgumentParser& _parserRef) {
	// set source file if it is a source file.
	if (_parserRef.Current().second == "--src") {
		// check that next arg is available.
		if (!_parserRef.HasNext()) {
			std::cerr << "ERROR: Unable to continue. Source file was not provided. Use --help for more options." << std::endl;
			return ConfigBuilder::Status::Failed;
		}
		// read in raw file name.
		std::string _rawFileName = _parserRef.Next();
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

ConfigBuilder::Status ConfigBuilder::Out (Config& _configRef, ArgumentParser& _parserRef) {
	// set source file if it is a source file.
	if (_parserRef.Current().second == "--out") {
		if (!_parserRef.HasNext()) {
		// check that next arg is available.
			std::cout << "--out flag was recieved without filename. Use default filename? [Y/n] ";
			std::string _useDefault {};
			std::cin >> _useDefault;
			if (_useDefault == "n") {
				std::cerr << "Exiting without exception." << std::endl;
				return ConfigBuilder::Status::Failed;
			} 
			std::cout << "Resuming." << std::endl;
		} else {
			// read in raw file name.
			std::string _rawFileName = _parserRef.Next();
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

ConfigBuilder::Status ConfigBuilder::Formats (Config& _configRef, ArgumentParser& _parserRef) {

	if (_parserRef.Current().second == "--ascii-draw") {
		_configRef.writeFormat = Options::WriteFormat::asciiDraw;
	}
	// set mode to writing hexadecimal.
	if (_parserRef.Current().second  == "--hex") {
		_configRef.writeFormat = Options::WriteFormat::hexadecimal;
	}
	// set mode to writing binary.
	if (_parserRef.Current().second  == "--binary") {
		_configRef.writeFormat = Options::WriteFormat::binary;
	}
	// set mode to writing utf-8.
	if (_parserRef.Current().second  == "--utf8") {
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
