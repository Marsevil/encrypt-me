//
// Created by marsevil on 25/01/2021.
//

#include "CryptMan.hpp"

#ifdef __APPLE__
const std::string ADDITIONAL_PARAMS("");
#else
const std::string ADDITIONAL_PARAMS("-pbkdf2");
#endif

CryptMan::CryptMan(std::string _password)
: password(_password) {
    // Nothing to do.
}

void CryptMan::encrypt() const {
    sf::path sourceFile(getSource());
    sf::path destinationFile(getDestination());
    // Prepare command.
    std::string command = std::string("openssl aes-256-cbc -salt ") + ADDITIONAL_PARAMS
                          + std::string(" -in ") + '"' + sourceFile.string() + '"' // Add input file
                          + std::string(" -out ") + '"' + destinationFile.string() + '"' // Add output file
                          + std::string(" -pass pass:") + password; // Add password

    // Execute command
    system(command.c_str());
    sf::last_write_time(destinationFile, sf::last_write_time(sourceFile));
}

void CryptMan::decrypt() const {
    sf::path sourceFile(getSource());
    sf::path destinationFile(getDestination());

    // Prepare command.
    std::string command = std::string("openssl aes-256-cbc -d -salt ") + ADDITIONAL_PARAMS
                          + std::string(" -in ") + '"' + sourceFile.string() + '"' // Add input file
                          + std::string(" -out ") + '"' + destinationFile.string() + '"' // Add output file
                          + std::string(" -pass pass:") + password; // Add password

    // Execute command.
    system(command.c_str());
    sf::last_write_time(destinationFile, sf::last_write_time(sourceFile));
}

void CryptMan::apply(Process process) const {
    if (process == Process::DECRYPT) decrypt();
    else if (process == Process::ENCRYPT) encrypt();
    else throw std::invalid_argument("Process may be ENCRYPT or DECRYPT");
}
