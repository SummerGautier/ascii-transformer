#pragma once

#include <string>
#include "Config.h"

// used to verify and parse cli arguments in config object.
using namespace ConfigBuilder {
	// status of each step in config build operation.
	enum class Status {
		None = 0,
		Failed,
		Completed
	}
	// limit attempts to pass massive arg vector to the program.
	constexpr int MaxAllowedArgs {5};
	// used to pass ref to config for building.
	bool Build (Config& _configRef);
	// extract argument passed from input stream via main(). Throws runtime_error on max arg count.
	std::string ExtractArg (const int _index, const char* _argVector);
	// if --help was passed, display help screen
	Status Help (const std::string& _arg);
	// if --src was passed, read in filename to config & validate its supported.
	Status Source (const std::string _arg, Config& _configRef);
	// if --out was passed, read in filename to config & validate its supported, otherwise use default.
	Status Out (const std::string _arg, Config& _configRef);
	// if format flags were passed, read in and update WriteFormat of config.
	Status Formats (const std::string _arg, Config& _configRef);
	// confirm config data is expected types and ranges.
	Status ValidateConfig (Config& _configRef);
}