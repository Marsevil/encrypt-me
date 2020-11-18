#include <iostream>
#include "../tests/CryptorTest.hpp"
#include "../tests/ConfigReaderTest.hpp"

int main(int argc, char const *argv[]) {

    std::cout << "Test class FileCryptor." << std::endl;
    cryptorTest();
    std::cout << "Test class ConfigReader." << std::endl;
    configReaderTest();

    return EXIT_SUCCESS;
}
