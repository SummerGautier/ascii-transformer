#include <cstdint>
#include <fstream>
#include <iostream>
#include <format>

#include "Core/Transform.hpp"

int main (int _argCount, char* _argVector[]) {
	// handle for configuration information.
	Config _config {};

	// validate user configuration from cli.
	if (!_config.Complete(_argCount, _argVector)) {
		std::cerr << "Unable to process configuration." << std::endl;
		return EXIT_FAILURE;
	}

	// prepare handles for file streams.
	std::ifstream _ifstream {_config.sourceFile.FileName(), std::ios::in};
	std::ofstream _ofstream {_config.outputFile.FileName(), std::ios::out};

	// build transform class based on config.
	IFormatter* _formatterPtr;
	Transform::InitTransform(_formatterPtr, _config);
	// execute transform process.
	Transform::ExecuteTransform(_ifstream, _ofstream, *_formatterPtr);

	// file management.
	_ifstream.close();
	_ofstream.close();

	// memory management.
	delete _formatterPtr;
	_formatterPtr = nullptr;
}
