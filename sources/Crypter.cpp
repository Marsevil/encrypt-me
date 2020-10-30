/*
 * Crypter.cpp
 *
 *  Created on: 26 oct. 2020
 *      Author: Marsevil
 */

#include "Crypter.hpp"

Crypter::Crypter() {
	// Nothing to do here.
}

void Crypter::encrypt() {
	checkConfig(Process::ENCRYPT);

	// Prepare command.
	std::string command = std::string("openssl aes-256-cbc -salt -pbkdf2")
			+ std::string(" -in ") + clearFile // Add input file
			+ std::string(" -out ") + encryptedFile // Add output file
			+ std::string(" -pass pass:") + password; // Add password

	// Execute command
	system(command.c_str());
}

void Crypter::decrypt() {
	checkConfig(Process::DECRYPT);

	// Prepare command.
	std::string command = "openssl aes-256-cbc -d -salt -pbkdf2"
			+ std::string(" -in ") + encryptedFile // Add input file
			+ std::string(" -out ") + clearFile // Add output file
			+ std::string(" -pass pass:") + password; // Add password

	// Execute command.
	system(command.c_str());
}

void Crypter::checkConfig(Process process) {
	// Paths & password have to be defined.
	if (clearFile.empty()) throw std::runtime_error("Path to clear file have to be set !!");
	if (encryptedFile.empty()) throw std::runtime_error("Path to encrypted file have to be set !!");
	if (password.empty()) throw std::runtime_error("Password have to be set !!");

	// Check file existence.
	std::ifstream file;
	std::string err;
	switch (process) {
	case Process::DECRYPT :
		err = encryptedFile;
		break;
	case Process::ENCRYPT :
		err = clearFile;
	}
	file.open(err);
	if (!file.good()) {
		err += " can't be opened";
		throw std::runtime_error(err);
	}

	file.close();
}
