#include <fstream>
#include <iostream>

#include "../Configuration/Config.hpp"
#include "../Formatter/IFormatter.hpp"
#include "../Formatter/AsciiDraw.hpp"

#include "Transform.hpp"

void Transform::InitTransform (IFormatter*& _formatterPtrRef, Config& _configRef) {
	if (_configRef.writeFormat == Options::WriteFormat::asciiDraw) {
		_formatterPtrRef = new AsciiDraw();
	}
}

void Transform::ExecuteTransform (std::ifstream& _ifstreamRef, std::ofstream& _ofstreamRef, IFormatter& _formatterRef) {
	char _current {' '};

	while (!_ifstreamRef.eof()) {

		if (_ifstreamRef.bad()) {
			throw std::runtime_error("I/O error while reading.");
		}
		if (_ifstreamRef.fail()) {
			throw std::runtime_error("Corrupted data encountered.");
		}

		_current = _ifstreamRef.get();

		if (!_ifstreamRef.eof()) {
			std::cout << _current << std::endl;
			_formatterRef.Store(_current);
			if (_current == '\n') {
				_formatterRef.Flush(_ofstreamRef);
			}
		}
	}

	_formatterRef.Flush(_ofstreamRef);
}

