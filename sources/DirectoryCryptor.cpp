//
// Created by marsevil on 18/11/2020.
//

#include "DirectoryCryptor.hpp"

DirectoryCryptor::DirectoryCryptor() : Cryptor() {
    // Nothing to do here.
}

void DirectoryCryptor::doIt(Process process) const {
    DirectoryCryptor* dc = new DirectoryCryptor;
    FileCryptor* fc = new FileCryptor;
    fc->setPassword(ConfigReader::getConfig()->PASSWORD);
    Cryptor* cryptor;

    // For each file contained in this directory
    for (sf::path path : sf::directory_iterator(*getSourcePath(process))) {

        // Using DirectoryCryptor or FileCryptor depending file type.
        if (sf::is_directory(path)) cryptor = dc;
        else cryptor = fc;

        cryptor->setClear(getClear() / path.filename());
        cryptor->setEncrypted(getEncrypted() / path.filename());

        switch (process) {
            case Process::ENCRYPT:
                cryptor->encrypt();
                break;
            default:
                cryptor->decrypt();
        }
    }

    delete dc;
    delete fc;
}

void DirectoryCryptor::encrypt() const {
    checkConfig(Process::ENCRYPT);
    doIt(Process::ENCRYPT);
}

void DirectoryCryptor::decrypt() const {
    checkConfig(Process::DECRYPT);
    doIt(Process::DECRYPT);
}

void DirectoryCryptor::checkConfig(Process process) const {
    Cryptor::checkConfig(process);

    //Check if files are directories.
    sf::path const* source = getSourcePath(process);
    sf::path const* destination = getDestinationPath(process);

    if (!sf::is_directory(*source)) throw std::runtime_error(source->string() + " is not a directory.");
    if (sf::exists(*destination)) {
        if (!sf::is_directory(*destination)) throw std::runtime_error(source->string() + " is not a directory.");
    } else {
        sf::create_directory(*destination);
    }
}
