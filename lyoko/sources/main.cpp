#include <iostream>
#include <string>
#include <memory>

#include "ConfigReader.hpp"
#include "../../includes/lib_encrypt-me/sources/DirectoryCryptor.hpp"

DirectoryCryptor* configRootDR() {
    // Read Config file.
    ConfigReader::readConfig();
    std::shared_ptr config(ConfigReader::getConfig());

    // Create new DirectoryCryptor witch point to the root directory.
    auto* dr(new DirectoryCryptor);
    dr->setClear(config->UNCRYPTED_FOLDER);
    dr->setEncrypted(config->ENCRYPTED_FOLDER);

    return dr;
}

void testDecryption(DirectoryCryptor* dr) {
    dr->setClear("testTreeDecrypt");
    dr->decrypt();
}

void printHelp() {
    std::cout << "usage : lyoko <command>" << std::endl
        << std::endl << "push\t Copy unencrypted directory to encrypted directory by encrypting all files." << std::endl
        << "pull\t Copy encrypted directory to unencrypted directory by decrypting all files." << std::endl
        << "help\t Print help (this page)." << std::endl
        << std::endl << "v1.0.1" << std::endl;
}

int main(int argc, char const *argv[]) {
    if (argc > 2) {
        std::cout << "Only one argument is expected." << std::endl << std::endl;
        printHelp();
    }
    else if (argc < 2) {
        std::cout << "One argument is expected." << std::endl << std::endl;
        printHelp();
    }
    else {
        std::string param(argv[1]);

        if (param == "pull") {
            DirectoryCryptor* rootDR(configRootDR());

            rootDR->decrypt();

            delete rootDR;
        } else if (param == "push") {
            DirectoryCryptor* rootDR(configRootDR());

            rootDR->encrypt();

            delete rootDR;
        } else if (param == "help") {
            printHelp();
        } else {
            std::cout << "Unknown parameter : " << param << '.' << std::endl << std::endl;
            printHelp();
        }
    }

    return EXIT_SUCCESS;
}
