//
// Created by marsevil on 18/11/2020.
//

#include "DirectoryCryptor.hpp"

DirectoryCryptor::DirectoryCryptor() {
    // Nothing to do here.
}

void DirectoryCryptor::checkConfig(Process process) {
    // Paths & password have to be defined.
    if (uncryptedDirectory.empty()) throw std::runtime_error("Path to clear file have to be set !!");
    if (encryptedDirectory.empty()) throw std::runtime_error("Path to encrypted file have to be set !!");
}
