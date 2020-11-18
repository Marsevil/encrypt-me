#include <iostream>
#include "../sources/FileCryptor.hpp"

int main(int argc, char const *argv[]) {

    FileCryptor* crp = new FileCryptor;

    crp->setPassword("azerty");

    crp->setClear("test.txt");
    crp->setEncrypted("test.txt.enc");
    crp->encrypt();

    crp->setClear("testDecode.txt");
    crp->decrypt();

    delete crp;

    return EXIT_SUCCESS;
}