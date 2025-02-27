#pragma once
#include <string>
#include <utility>

// parses command-line arguments
class ArgumentParser {
	public:
		// create argument parser. reset index and current arg.
		ArgumentParser (int _argCount, char** _argVector);
		// increment index, current. returns next. exception if HasNext is false?
		std::string Next ();
		// returns true if index is less than arg count, does not increment.
		bool HasNext ();
		// returns current index and current arg.
		std::pair<int, std::string> Current ();
	private:
		// total passed arguments from cli.
		int argCount;
		// vector of all passed arguments from cli.
		char** argVector;
		// current argument value.
		std::string current {""};
		// current index.
		int index {0};
		// limit attempts to pass massive arg vector to the program.
		static constexpr int MaxAllowedArgs {5};
};
