#include "Config.h"
#include "BuildConfig.h"

int main (int _argCount, char* _argVector[]) {
	Config _config {};
	// fail early if config builder is unable to complete.
	if (!BuildConfig::Build (_config, _argCount, _argVector)) {
		return std::EXIT_FAILURE;
	}
}