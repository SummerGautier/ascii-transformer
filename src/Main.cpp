#include <cstdint>

#include "Config.hpp"
#include "ConfigBuilder.hpp"
#include "ArgumentParser.hpp"

int main (int _argCount, char* _argVector[]) {
	Config _config {};
	ConfigBuilder _configBuilder {};
	ArgumentParser _parser {_argCount, _argVector};
	// fail early if config builder is unable to complete.
	if (!_configBuilder.Build (_config, _parser)) {
		return EXIT_FAILURE;
	}
}
