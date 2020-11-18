//
// Created by marsevil on 18/11/2020.
//

#ifndef ENCRYPT_ME_DUPLICATOR_HPP
#define ENCRYPT_ME_DUPLICATOR_HPP

#include <filesystem>

namespace sf = std::filesystem;

class Duplicator {
    /**
     * Path to the encrypted version of the directory.
     */
    sf::path encryptedDirectory;
    /**
     * Path to the uncrypted version of the directory.
     */
    sf::path uncryptedDirectory;

public:
    /**
     * Default constructor
     */
    Duplicator();

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
};


#endif //ENCRYPT_ME_DUPLICATOR_HPP
