/*
 * Crypter.cpp
 *
 *  Created on: 26 oct. 2020
 *      Author: Marsevil
 */

#include "FileCryptor.hpp"

FileCryptor::FileCryptor() {
	// Nothing to do here.
}

void FileCryptor::encrypt() const {
	checkConfig(Process::ENCRYPT);

	// Prepare command.
	std::string command = std::string("openssl aes-256-cbc -salt -pbkdf2")
			+ std::string(" -in ") + uncryptedFile.string() // Add input file
			+ std::string(" -out ") + encryptedFile.string() // Add output file
			+ std::string(" -pass pass:") + password; // Add password

	// Execute command
	if (checkTimeStamp(Process::ENCRYPT)) system(command.c_str());
}

void FileCryptor::decrypt() const {
	checkConfig(Process::DECRYPT);

	// Prepare command.
	std::string command = "openssl aes-256-cbc -d -salt -pbkdf2"
			+ std::string(" -in ") + encryptedFile.string() // Add input file
			+ std::string(" -out ") + uncryptedFile.string() // Add output file
			+ std::string(" -pass pass:") + password; // Add password

	// Execute command.
	if (checkTimeStamp(Process::DECRYPT)) system(command.c_str());
}

sf::path const* FileCryptor::getSourcePath(Process process) const {
	switch (process) {
	case Process::DECRYPT :
		return &encryptedFile;
		break;
	default :
		return &uncryptedFile;
	}
}

sf::path const* FileCryptor::getDestinationPath(Process process) const {
	switch (process) {
	case Process::DECRYPT :
		return &uncryptedFile;
		break;
	default :
		return &encryptedFile;
	}
}

void FileCryptor::checkConfig(Process process) const {
	// Paths & password have to be defined.
	if (uncryptedFile.empty()) throw std::runtime_error("Path to clear file have to be set !!");
	if (encryptedFile.empty()) throw std::runtime_error("Path to encrypted file have to be set !!");
	if (password.empty()) throw std::runtime_error("Password have to be set !!");

	// Check file existence.
	std::ifstream file;
	sf::path const* path = getSourcePath(process);

	if (!sf::exists(*path)) {
		throw std::runtime_error(path->string() + " doesn't exists");
	}
}

bool FileCryptor::checkTimeStamp(Process process) const {
	// Get source & destination depending of process.
	sf::path sourceFile(*getSourcePath(process));
	sf::path destinationFile(*getDestinationPath(process));

	// Check existence of destinationFile.
	if (!sf::exists(destinationFile)) return true;

	return (sf::last_write_time(sourceFile) > sf::last_write_time(destinationFile));
}
