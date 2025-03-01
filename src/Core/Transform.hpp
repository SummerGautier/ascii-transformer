#pragma once

#include <fstream>
#include "../Configuration/Config.hpp"
#include "../Formatter/IFormatter.hpp"

namespace Transform {
	void InitTransform (IFormatter*& _formatterPtrRef, Config& _configRef);
	void ExecuteTransform (std::ifstream& _ifstreamRef, std::ofstream& _ofstreamRef, IFormatter& _formatterRef);
};
