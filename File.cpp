#include "File.h"


bool File::ParseRawFileName (const std::string _rawFileName) {
	int _delimiterPos = _rawFileName.find('.');
	// extract filename and type.
	std::string _baseName = _rawFileName.substr(0, _delimiterPos);

	// calculate how far to read extension
	int _extensionCharCount = _rawFileName.size() - _baseName.size() - 1;
	std::string _extension = _rawFileName.substr(_delimiterPos+1, _extensionCharCount);
	// verify the filetype is supported.
	if (VerifySupportedExtension(_extension)) {
		this->name.baseName = _baseName;
		this->name.extension = _extension;
		return true;
	}
	// file type is not accepted.
	return false;
}

bool File::VerifySupportedExtension (const std::string _extension) {
	// check if extension of current file is found in supported extensions string.
	return (AllowedExtensions().find(_extension) ==  std::string::npos);
}

std::string File::FileName() {
	return this->name.Full();
}

std::string File::BaseName () {
	return this->name.baseName;
}

std::string File::Extension() {
	return this->name.extension;
}

std::string_view File::AllowedExtensions () {
	return allowedExtensions;
}

std::string File::Name::Full () {
	return this->baseName + this->extension;
}