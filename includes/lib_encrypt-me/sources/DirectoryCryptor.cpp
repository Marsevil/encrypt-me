//
// Created by marsevil on 18/11/2020.
//

#include "DirectoryCryptor.hpp"

void DirectoryCryptor::doIt(Process const& process) const {
    DirectoryCryptor* dc = new DirectoryCryptor;
    FileCryptor* fc = new FileCryptor;
    sf::path const* source = getSourcePath(process);
    sf::path const* dest = getDestinationPath(process);
    fc->setPassword(ConfigReader::getConfig()->PASSWORD);
    Cryptor* cryptor;

    // For each file contained in this directory
    for (sf::path const& path : sf::directory_iterator(*source)) {

        sf::path clearPath(getClear() / path.filename());
        sf::path encryptedPath(getEncrypted() / path.filename());

        // Using DirectoryCryptor or FileCryptor depending file type.
        if (sf::is_directory(path)) cryptor = dc;
        else {
            cryptor = fc;
            if (clearPath.extension() == ".enc") clearPath.replace_extension("");
            if (encryptedPath.extension() != ".enc") encryptedPath += ".enc";
        }

        cryptor->setClear(clearPath);
        cryptor->setEncrypted(encryptedPath);

        switch (process) {
            case Process::ENCRYPT:
                cryptor->encrypt();
                break;
            default:
                cryptor->decrypt();
        }
    }

    sf::last_write_time(*dest, sf::last_write_time(*source));

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

void DirectoryCryptor::checkConfig(Process const& process) const {
    Cryptor::checkConfig(process);

    //Check if files are directories.
    sf::path const* source = getSourcePath(process);
    sf::path const* destination = getDestinationPath(process);

    if (!sf::is_directory(*source)) throw std::runtime_error(source->string() + " is not a directory.");
    if (sf::exists(*destination)) {
        if (!sf::is_directory(*destination)) throw std::runtime_error(source->string() + " is not a directory.");
        if (checkTimeStamp(process)) deleteByFileName(*source, *destination);
    } else {
        sf::create_directory(*destination);
    }

}

void DirectoryCryptor::deleteByFileName(sf::path const &source, sf::path const &destination)
{
    // Process all destination files
    for (sf::path const& path : sf::directory_iterator(destination))
    {
        // Build the path which have to be checked in the source directory.
        sf::path checkedPath(source / path.filename());

        // If the path is not a directory extension have to remove or add.
        if (!sf::is_directory(path)) {
            if (checkedPath.extension() == ".enc") checkedPath.replace_extension("");
            else checkedPath += ".enc";
        }

        if (!sf::exists(checkedPath))
        {
            sf::remove_all(path);
        }
    }
}

