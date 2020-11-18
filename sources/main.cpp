#include <iostream>
#include "../tests/CryptorTest.hpp"
#include "../tests/ConfigReaderTest.hpp"
#include "../tests/DirectoryCyptorTest.hpp"

int main(int argc, char const *argv[]) {

    //std::cout << "Test class FileCryptor." << std::endl;
    //cryptorTest();
    //std::cout << "Test class ConfigReader." << std::endl;
    //configReaderTest();
    std::cout << "Test class DirectoryCryptor" << std::endl;
    directoryCryptorTest();

    return EXIT_SUCCESS;
}
