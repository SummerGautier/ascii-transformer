#include "BuildConfig.h"

struct Config {
	// input and output files created on the stack.
	File sourceFile {};
	File outputFile {};

	// captures output writing TransformConfig.
	Options::WriteFormat writeFormat {Options::WriteFormat::asciiDraw};
};

int main (int _argCount, char* _argVector[]) {
	Config _config {};
}