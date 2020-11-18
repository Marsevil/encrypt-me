//
// Created by marsevil on 18/11/2020.
//

#ifndef ENCRYPT_ME_DIRECTORYCRYPTOR_HPP
#define ENCRYPT_ME_DIRECTORYCRYPTOR_HPP

#include <filesystem>
#include <stdexcept>

namespace sf = std::filesystem;

class DirectoryCryptor {
    /**
     * Describe which process is currently in use.
     */
    enum Process {
        ENCRYPT,
        DECRYPT
    };

    /**
     * Path to the encrypted version of the directory.
     */
    sf::path encryptedDirectory;
    /**
     * Path to the uncrypted version of the directory.
     */
    sf::path uncryptedDirectory;

    void checkConfig(Process process);

public:
    /**
     * Default constructor
     */
    DirectoryCryptor();

    /**
     * @return can be empty.
     */
    inline sf::path getEncryptedDirectory() { return encryptedDirectory; }
    /**
     * @return can be empty.
     */
    inline sf::path getUncryptedDirectory() { return uncryptedDirectory; }
    /**
     * @param path can be empty.
     */
    inline void setEncryptedDirectory(sf::path path) { encryptedDirectory = path; }
    /**
     * @param path can be empty.
     */
    inline void setUncryptedDirectory(sf::path path) { uncryptedDirectory = path; }

    void encrypt();
};


#endif //ENCRYPT_ME_DIRECTORYCRYPTOR_HPP
