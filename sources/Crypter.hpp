/*
 * Crypter.hpp
 *
 *  Created on: 26 oct. 2020
 *      Author: Marsevil
 */

#ifndef CRYPTER_HPP_
#define CRYPTER_HPP_

#include <string>
#include <stdexcept>
#include <fstream>

/**
 * This have to encrypt and decrypt chosen files.
 */
class Crypter {
	/**
	 * Path to the clear file must be exist if encrypt function will be use.
	 */
	std::string clearFile;
	/**
	 * Path to the encrypted file must be exist if decrypt function will be use.
	 */
	std::string encryptedFile;
	/**
	 * Represent password use for encryption or decryption.
	 */
	std::string password;

	enum Process {
		ENCRYPT,
		DECRYPT
	};

public:
	/**
	 * Default constructor
	 */
	Crypter();

	/**
	 * @param _clearFile Not null, should point to an existing file.
	 */
	inline void setClear(std::string _clearFile) { clearFile = _clearFile; }
	/**
	 * @param _encryptedFile Not null.
	 */
	inline void setEncrypted(std::string _encryptedFile) { encryptedFile = _encryptedFile; }
	/**
	 * @param _password Not null.
	 */
	inline void setPassword(std::string _password) { password = _password; }

	/**
	 * @return Path to the file that will be encrypted.
	 */
	inline std::string getClear() const { return clearFile; }
	/**
	 * @return Path to the file that represent encrypted version of the input file.
	 */
	inline std::string getEncrypted() const { return encryptedFile; }

	/**
	 * Encrypt clearFile and write result in encryptedFile
	 */
	void encrypt();
	/**
	 * Decrypt encryptedFile and write result in clearFile
	 */
	void decrypt();

	/**
	 * Check if path to clear and encrypted file are set, if password is set and if the clear file or the encrypted file can be red.
	 * @throws runtime_error if one of the precedent conditions is unsatisfied.
	 * @param process allow to choose if clear or encrypted file have to be checked.
	 */
	void checkConfig(Process process);
};


#endif /* CRYPTER_HPP_ */
