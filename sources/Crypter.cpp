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
	// Command construction.
	std::string command = std::string("openssl aes-256-cbc -salt -pbkdf2")
			+ std::string(" -in ") + clearFile
			+ std::string(" -out ") + encryptedFile
			+ std::string(" -pass pass:") + password;

	system(command.c_str());
}

void Crypter::decrypt() {
	std::string command = "openssl aes-256-cbc -d -salt -pbkdf2"
			+ std::string(" -in ") + encryptedFile
			+ std::string(" -out ") + clearFile
			+ std::string(" -pass pass:") + password;

	system(command.c_str());
}
