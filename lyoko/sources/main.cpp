#include <iostream>
#include <string>
#include <memory>

#include "../../includes/lib_encrypt-me/sources/ConfigReader.hpp"
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

int main(int argc, char const *argv[]) {
    if (argc > 2) std::cout << "Only one argument is expected." << std::endl;
    else if (argc < 2) std::cout << "One argument is expected." << std::endl;
    else {
        std::string param(argv[1]);

        if (param == "pull") {
            DirectoryCryptor* rootDR(configRootDR());

            rootDR->decrypt();

            delete rootDR;
        } else if (param == "push") {
            DirectoryCryptor* rootDR(configRootDR());

            rootDR->encrypt();
            testDecryption(rootDR);

            delete rootDR;
        } else if (param == "help") {
            std::cout << "No help are available." << std::endl;
        } else {
            std::cout << "Unknown parameter : " << param << '.' << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
