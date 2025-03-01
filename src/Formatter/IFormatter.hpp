#pragma once

#include <fstream>
#include <stdexcept>

class IFormatter {
	public:
		// translate the input char and store in the buffer.
		virtual void Store (const char _value) {
			throw std::logic_error("Method not implemented.");
		}
		// write the buffer value to the out stream.
		virtual void Flush (std::ofstream& _outStream) {
			throw std::logic_error("Method not implemented.");
		}
		// destructor.
		virtual ~IFormatter() = default;
};
