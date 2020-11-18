#pragma once

#include <iostream>
#include "../sources/ConfigReader.hpp"

void configReaderTest() {
    
    ConfigReader::readConfig();

    std::cout << "uncrypted folder = " << ConfigReader::getConfig()->UNCRYPTED_FOLDER << std::endl
        << "encrypted folder = " << ConfigReader::getConfig()->ENCRYPTED_FOLDER << std::endl
        << "password = " << ConfigReader::getConfig()->PASSWORD << std::endl;

}
