#include <iostream>
#include "Cryptor.hpp"
#include "ConfigReader.hpp"

int main(int argc, char const *argv[]) {
    
    ConfigReader::readConfig();

    std::cout << "uncrypted folder = " << ConfigReader::getConfig()->UNCRYPTED_FOLDER << std::endl
        << "encrypted folder = " << ConfigReader::getConfig()->ENCRYPTED_FOLDER << std::endl
        << "password = " << ConfigReader::getConfig()->PASSWORD << std::endl;

    return EXIT_SUCCESS;
}
