/*
 * Crypter.cpp
 *
 *  Created on: 26 oct. 2020
 *      Author: Marsevil
 */

#include "FileCryptor.hpp"

FileCryptor::FileCryptor() : Cryptor() {
	// Nothing to do here.
}

void FileCryptor::encrypt() const {
	checkConfig(Process::ENCRYPT);

	// Prepare command.
	std::string command = std::string("openssl aes-256-cbc -salt -pbkdf2")
			+ std::string(" -in ") + '"' + getClear().string() + '"' // Add input file
			+ std::string(" -out ") + '"' + getEncrypted().string() + '"' // Add output file
			+ std::string(" -pass pass:") + password; // Add password

	// Execute command
	if (checkTimeStamp(Process::ENCRYPT)) system(command.c_str());
}

void FileCryptor::decrypt() const {
	checkConfig(Process::DECRYPT);

	// Prepare command.
	std::string command = "openssl aes-256-cbc -d -salt -pbkdf2"
			+ std::string(" -in ") + '"' + getEncrypted().string() + '"' // Add input file
			+ std::string(" -out ") + '"' + getClear().string() + '"' // Add output file
			+ std::string(" -pass pass:") + password; // Add password

	// Execute command.
	if (checkTimeStamp(Process::DECRYPT)) system(command.c_str());
}

void FileCryptor::checkConfig(Process process) const {
    Cryptor::checkConfig(process);

    // Password shouldn't be empty.
    if (password.empty()) throw std::runtime_error("Password have to be set !!");
}

bool FileCryptor::checkTimeStamp(Process process) const {
	// Get source & destination depending of process.
	sf::path sourceFile(*getSourcePath(process));
	sf::path destinationFile(*getDestinationPath(process));

	// Check existence of destinationFile.
	if (!sf::exists(destinationFile)) return true;

	return (sf::last_write_time(sourceFile) > sf::last_write_time(destinationFile));
}

FileCryptor::~FileCryptor() {
    // Do nothing here.
}
