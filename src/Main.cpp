#include <cstdint>

#include "Config.hpp"
#include "ConfigBuilder.hpp"

int main (int _argCount, char* _argVector[]) {
	Config _config {};
	// fail early if config builder is unable to complete.
	if (!ConfigBuilder::Build (_config, _argCount, _argVector)) {
		return EXIT_FAILURE;
	}
}
