#pragma once

#include <string>
#include "Config.hpp"

// parses command-line arguments
class ArgumentParser {
	public:
		// create argument parser. reset index and current arg.
		ArgumentParser (int _argCount, char* _argVector);
		// increments index and returns next arg.
		std::string Next ();
		// returns true if index is less than arg count.
		bool hasNext ();
		// returns current index and current arg.
		std::pair<int, std::string> Current ();
	private:
		// total passed arguments from cli.
		int argCount;
		// vector of all passed arguments from cli.
		char* argVector[] {};
		// current argument value.
		std::string current {""};
		// current index.
		int index {0};
		// limit attempts to pass massive arg vector to the program.
		constexpr int MaxAllowedArgs {5};
};

// used to verify and parse cli arguments in config object.
namespace ConfigBuilder {
	// status of each step in config build operation.
	enum class Status {
		None = 0,
		Failed,
		Completed
	};


	// used to pass ref to config for building.
	bool Build (Config& _configRef, int _argCount, char* _argVector[]);
	// extract argument passed from input stream via main(). Throws runtime_error on max arg count.
	std::string ExtractArg (int _index, char* _argVector[]);
	// if --help was passed, display help screen
	Status Help (const std::string _arg);
	// if --src was passed, read in filename to config & validate its supported.
	Status Source (const std::string _arg, Config& _configRef, int& _index, char* _argVector[], int _argCount);
	// if --out was passed, read in filename to config & validate its supported, otherwise use default.
	Status Out( const std::string _arg, Config& _configRef, int& _index, char* _argVector[], int _argCount) ;
	// if format flags were passed, read in and update WriteFormat of config.
	Status Formats (const std::string _arg, Config& _configRef);
	// confirm config data is expected types and ranges.
	Status ValidateConfig (Config& _configRef);
};

