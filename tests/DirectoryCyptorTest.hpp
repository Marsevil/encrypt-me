#include "../sources/DirectoryCryptor.hpp"
#include "../sources/ConfigReader.hpp"

void directoryCryptorTest() {
    ConfigReader::readConfig();
    DirectoryCryptor* rootCyptor = new DirectoryCryptor;

    std::shared_ptr<Config> config = ConfigReader::getConfig();

    rootCyptor->setClear(config->UNCRYPTED_FOLDER);
    rootCyptor->setEncrypted(config->ENCRYPTED_FOLDER);

    rootCyptor->encrypt();

    rootCyptor->setClear("testTreeDecrypt");
    rootCyptor->decrypt();
}