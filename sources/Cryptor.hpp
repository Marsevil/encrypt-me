//
// Created by marsevil on 18/11/2020.
//

#ifndef ENCRYPT_ME_CRYPTOR_HPP
#define ENCRYPT_ME_CRYPTOR_HPP

#include <filesystem>

namespace sf = std::filesystem;

/**
 * Interface class for basic encryption processes.
 */
class Cryptor {
    /**
	 * Path to the clear file must be exist if encrypt function will be use.
	 */
    sf::path uncryptedFile;
    /**
     * Path to the encrypted file must be exist if decrypt function will be use.
     */
    sf::path encryptedFile;

protected:
    /**
     * Describe which process is currently in use.
     */
    enum Process {
        ENCRYPT,
        DECRYPT
    };

    /**
	 * Check if path to clear and encrypted file are set, and if the clear file or the encrypted file can be red.
	 *
	 * @throws runtime_error if one of the precedent conditions is unsatisfied.
	 *
	 * @param process allow to choose if clear or encrypted file have to be checked.
	 */
    virtual void checkConfig(Process process) const;

    /**
	 * Check if the destination file have to be updated or not.
	 * @param process is used to determine which file is source and which is destination.
	 * @return if the destination file should be updated (true if it doesn't exists and according to last modification date else).
	 */
    bool checkTimeStamp(Process process) const;

public:
    Cryptor() = default;
    virtual ~Cryptor() = default;

    /**
	 * @param _clearFile Not null, should point to an existing file.
	 */
    inline void setClear(sf::path const& _uncryptedFile) { uncryptedFile = _uncryptedFile; }
    /**
     * @param _encryptedFile Not null.
     */
    inline void setEncrypted(sf::path const& _encryptedFile) { encryptedFile = _encryptedFile; }

    /**
	 * @return Path to the file that will be encrypted.
	 */
    inline sf::path getClear() const { return uncryptedFile; }
    /**
     * @return Path to the file that represent encrypted version of the input file.
     */
    inline sf::path getEncrypted() const { return encryptedFile; }

    /**
	 * @param process is used to determine which file is the source and which one is the destination.
	 * @return path pointer to uncryptedFile if encrypt process and cryptedFile else.
	 */
    sf::path const* getSourcePath(Process process) const;
    /**
     * @param process is used to determine which file is the source and which one is the destination.
     * @return path pointer to cryptedFile if encrypt process and uncryptedFile else.
     */
    sf::path const* getDestinationPath(Process process) const;

    /**
	 * Encrypt clearFile and write result in encryptedFile
	 */
    virtual void encrypt() const = 0;
    /**
	 * Decrypt encryptedFile and write result in clearFile
	 */
    virtual void decrypt() const = 0;
};


#endif //ENCRYPT_ME_CRYPTOR_HPP
