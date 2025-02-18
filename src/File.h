#include <string>

class File {

	public:
		// update basename and extension form raw file name.
		bool ParseRawFileName (const std::string _rawFileName);
		// returns full file name.
		std::string FileName();
		// returns file base name only.
		std::string BaseName ();
		// returns file extension only.s
		std::string Extension();
		// return string_view (immutable) of allowed extensions.
		static std::string_view AllowedExtensions ();
		// verify if a given extension is supported.
		static bool VerifySupportedExtension (const std::string _extension);

	private: 
		// create an immutable string for lookup of extensions allowed. '|' charachter is non-fuctional, just for flair.
		static constexpr std::string_view allowedExtensions {".txt | .bin | .hex"};
		// structure for holding extension and name.
		struct Name {
			std::string baseName {""};
			std::string extension {""};
			std::string Full ();
		};
		// File object's name structure.
		Name name {};
};