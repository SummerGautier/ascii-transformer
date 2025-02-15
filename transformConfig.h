#pragma once

#include <vector>

// configuration for the text transformation.
namespace TransformConfig {
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
