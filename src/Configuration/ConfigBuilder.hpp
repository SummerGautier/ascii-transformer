#pragma once

#include <string>
#include "Config.hpp"
#include "ArgumentParser.hpp"

// used to verify and parse cli arguments in config object.
class ConfigBuilder {
	public:
		// status of each step in config build operation.
		enum class Status {
			None = 0,
			Failed,
			Completed
		};

		// used to pass ref to config for building.
		bool Build (Config& _configRef, ArgumentParser& _parserRef);
		// if --help was passed, display help screen
		Status Help (ArgumentParser& _parser);
		// if --src was passed, read in filename to config & validate its supported.
		Status Source (Config& _configRef, ArgumentParser& _parserRef);
		// if --out was passed, read in filename to config & validate its supported, otherwise use default.
		Status Out (Config& _configRef, ArgumentParser& _parserRef);
		// if format flags were passed, read in and update WriteFormat of config.
		Status Formats (Config& _configRef, ArgumentParser& _parserRef);
		// confirm config data is expected types and ranges.
		Status ValidateConfig (Config& _configRef);
};

