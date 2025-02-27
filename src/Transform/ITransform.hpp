#pragma once

#include <fstream>

class ITransform {
	public:
		// translate the input char and store in the buffer.
		virtual void Store (const char _value) = 0;
		// write the buffer value to the out stream.
		virtual void Flush (std::ofstream& _outStream) = 0;
		// destructor.
		virtual ~ITransform() = default;
};
