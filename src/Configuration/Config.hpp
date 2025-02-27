#pragma once
#include <vector>

#include "File.hpp"

// options for text transformation.
namespace Options {
	// what format to use for output file when transforming text.
	enum class WriteFormat {
		asciiDraw,
		utf8,
		binary,
		hexadecimal
	};
	// used to map an integer to an applicable format.
	const std::vector<WriteFormat> WriteFormatMap {
		WriteFormat::hexadecimal,
		WriteFormat::asciiDraw,
		WriteFormat::binary,
		WriteFormat::utf8,
	};
	// process parsing itneger to a WriteFormat.
	WriteFormat ParseInt (const int _value);
	// find largest enum value for WriteFormat.
	int MaxWriteFormat ();
	// find smallest enum value for WriteFormat.
	int MinWriteFormat ();
};

// contains the configuration for the program.
struct Config {

	// read input from the command line and fill config data.
	bool Complete (int _argCount, char* _argVector[]);

	// input and output files created on the stack.
	File sourceFile {};
	File outputFile {};

	// captures output writing TransformConfig.
	Options::WriteFormat writeFormat {
		Options::WriteFormat::asciiDraw
	};
};
