//
// Created by marsevil on 18/11/2020.
//

#ifndef ENCRYPT_ME_DIRECTORYCRYPTOR_HPP
#define ENCRYPT_ME_DIRECTORYCRYPTOR_HPP

#include <filesystem>
#include <stdexcept>

#include "Cryptor.hpp"

namespace sf = std::filesystem;

class DirectoryCryptor : Cryptor {

    void checkConfig(Process process) const override;

public:
    /**
     * Default constructor
     */
    DirectoryCryptor();

    void encrypt() const override;
};


#endif //ENCRYPT_ME_DIRECTORYCRYPTOR_HPP
