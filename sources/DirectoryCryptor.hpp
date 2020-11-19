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
#include "ConfigReader.hpp"

namespace sf = std::filesystem;

class DirectoryCryptor : public Cryptor {

    /**
     * @inherit
     * Check if files are directories.
     */
    void checkConfig(Process const& process) const override;

    void doIt(Process const& process) const;
    
    static void deleteByFileName(sf::path const &source, sf::path const &destination);

public:
    /**
     * Default constructor
     */
    DirectoryCryptor() = default;
    ~DirectoryCryptor() override = default;

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
