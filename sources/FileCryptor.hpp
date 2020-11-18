/*
 * Crypter.hpp
 *
 *  Created on: 26 oct. 2020
 *      Author: Marsevil
 */

#ifndef CRYPTOR_HPP_
#define CRYPTOR_HPP_

#include <string>
#include <stdexcept>
#include <fstream>
#include <filesystem>

#include "Cryptor.hpp"

namespace sf = std::filesystem;

/**
 * This have to encrypt and decrypt chosen files.
 */
class FileCryptor : public Cryptor {
	/**
	 * Represent password use for encryption or decryption.
	 */
	std::string password;

	/**
	 * @inherit
	 * Add some test on password.
	 */
	void checkConfig(Process process) const override;

	/**
	 * Check if the destination file have to be updated or not.
	 * @param process is used to determine which file is source and which is destination.
	 * @return if the destination file should be updated (true if it doesn't exists and according to last modification date else).
	 */
	bool checkTimeStamp(Process process) const;

public:
	/**
	 * Default constructor
	 */
	FileCryptor();
	~FileCryptor();

	/**
	 * @param _password Not null.
	 */
	inline void setPassword(std::string const& _password) { password = _password; }

	void encrypt() const override;
	void decrypt() const override;
};


#endif /* CRYPTOR_HPP_ */
