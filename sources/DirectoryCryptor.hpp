//
// Created by marsevil on 18/11/2020.
//

#ifndef ENCRYPT_ME_DIRECTORYCRYPTOR_HPP
#define ENCRYPT_ME_DIRECTORYCRYPTOR_HPP

#include <filesystem>
#include <stdexcept>
#include <memory>

#include "Cryptor.hpp"
#include "FileCryptor.hpp"

namespace sf = std::filesystem;

class DirectoryCryptor : Cryptor {

    /**
     * @inherit
     * Check if files are directories.
     */
    void checkConfig(Process process) const override;

    void doIt(Process process) const;

public:
    /**
     * Default constructor
     */
    DirectoryCryptor();

    /**
     * @inherit
     */
    void encrypt() const override;
    /**
     * @inherit
     */
     void decrypt() const override;
};


#endif //ENCRYPT_ME_DIRECTORYCRYPTOR_HPP
