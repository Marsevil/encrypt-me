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

namespace sf = std::filesystem;

/**
 * This have to encrypt and decrypt chosen files.
 */
class FileCryptor {
	/**
	 * Path to the clear file must be exist if encrypt function will be use.
	 */
	sf::path uncryptedFile;
	/**
	 * Path to the encrypted file must be exist if decrypt function will be use.
	 */
	sf::path encryptedFile;
	/**
	 * Represent password use for encryption or decryption.
	 */
	std::string password;

	/**
	 * Describe which process is currently in use.
	 */
	enum Process {
		ENCRYPT,
		DECRYPT
	};

	/**
	 *
	 * @param process is used to determine which file is the source and which one is the destination.
	 * @return path pointer to uncryptedFile if encrypt process and cryptedFile else.
	 */
	sf::path const* getSourcePath(Process process) const;
	/**
	 *
	 * @param process is used to determine which file is the source and which one is the destination.
	 * @return path pointer to cryptedFile if encrypt process and uncryptedFile else.
	 */
	sf::path const* getDestinationPath(Process process) const;

	/**
	 * Check if path to clear and encrypted file are set, if password is set and if the clear file or the encrypted file can be red.
	 *
	 * @throws runtime_error if one of the precedent conditions is unsatisfied.
	 *
	 * @param process allow to choose if clear or encrypted file have to be checked.
	 */
	void checkConfig(Process process) const;

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

	/**
	 * @param _clearFile Not null, should point to an existing file.
	 */
	inline void setClear(sf::path const& _uncryptedFile) { uncryptedFile = _uncryptedFile; }
	/**
	 * @param _encryptedFile Not null.
	 */
	inline void setEncrypted(sf::path const& _encryptedFile) { encryptedFile = _encryptedFile; }
	/**
	 * @param _password Not null.
	 */
	inline void setPassword(std::string const& _password) { password = _password; }

	/**
	 * @return Path to the file that will be encrypted.
	 */
	inline std::string getClear() const { return uncryptedFile; }
	/**
	 * @return Path to the file that represent encrypted version of the input file.
	 */
	inline std::string getEncrypted() const { return encryptedFile; }

	/**
	 * Encrypt clearFile and write result in encryptedFile
	 */
	void encrypt() const;
	/**
	 * Decrypt encryptedFile and write result in clearFile
	 */
	void decrypt() const;
};


#endif /* CRYPTOR_HPP_ */
