#include <stdexcept>

#include "TransformConfig.h"

TransformConfig::WriteFormat TransformConfig::ParseInt (const int _value) {
	// check if value is above supported range.
	if (_value > TransformConfig::MaxWriteFormat()) {
		throw std::invalid_argument("Unable to parse integer into TransformConfig::WriteFormat. Value is beyond range.");
	}
	// check if value below supported range.
	if (_value < TransformConfig::MinWriteFormat()) {
		throw std::invalid_argument("Unable to parse integer into TransformConfig::WriteFormat. Value is below range.");
	}
	// create TransformConfig to return.
	TransformConfig::WriteFormat _format = TransformConfig::WriteFormatMap.at(_value);
	return _format;
}

int TransformConfig::MaxWriteFormat () {
	// largest enum value in WriteFormat.
	return int(TransformConfig::WriteFormat::hexadecimal);
}

int TransformConfig::MinWriteFormat () {
	// largest enum value in WriteFormat.
	return int(TransformConfig::WriteFormat::asciiDraw);
}