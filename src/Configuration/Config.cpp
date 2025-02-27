#include <stdexcept>

#include "Config.hpp"
#include "ConfigBuilder.hpp"
#include "ArgumentParser.hpp"

Options::WriteFormat Options::ParseInt (const int _value) {
	// check if value is above supported range.
	if (_value > Options::MaxWriteFormat()) {
		throw std::invalid_argument("Unable to parse integer into Options::WriteFormat. Value is beyond range.");
	}
	// check if value below supported range.
	if (_value < Options::MinWriteFormat()) {
		throw std::invalid_argument("Unable to parse integer into Options::WriteFormat. Value is below range.");
	}
	// create Options to return.
	Options::WriteFormat _format = Options::WriteFormatMap.at(_value);
	return _format;
}

int Options::MaxWriteFormat () {
	// largest enum value in WriteFormat.
	return int(Options::WriteFormat::hexadecimal);
}

int Options::MinWriteFormat () {
	// largest enum value in WriteFormat.
	return int(Options::WriteFormat::asciiDraw);
}

bool Config::Complete (int _argCount, char* _argVector[]) {
	// init config builder which is the controller.
	ConfigBuilder _configBuilder {};
	// init parser which handles just reading input.
	ArgumentParser _parser {_argCount, _argVector};
	// return the success/fail of the build.
	return _configBuilder.Build (*this, _parser);
}
