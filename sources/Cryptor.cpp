//
// Created by marsevil on 18/11/2020.
//

#include "Cryptor.hpp"

void Cryptor::checkConfig(Cryptor::Process process) const {
    // Paths & password have to be defined.
    if (uncryptedFile.empty()) throw std::runtime_error("Path to clear file have to be set !!");
    if (encryptedFile.empty()) throw std::runtime_error("Path to encrypted file have to be set !!");

    // Check file existence.
    sf::path const* path = getSourcePath(process);

    if (!sf::exists(*path)) {
        throw std::runtime_error(path->string() + " doesn't exists");
    }
}

sf::path const* Cryptor::getSourcePath(Process process) const {
    switch (process) {
        case Process::DECRYPT :
            return &encryptedFile;
            break;
        default :
            return &uncryptedFile;
    }
}

sf::path const* Cryptor::getDestinationPath(Process process) const {
    switch (process) {
        case Process::DECRYPT :
            return &uncryptedFile;
            break;
        default :
            return &encryptedFile;
    }
}

/*Cryptor::Cryptor() {
    // Do nothing
}

Cryptor::~Cryptor() {
    // Do nothing
}*/
