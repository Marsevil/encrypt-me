#include <iostream>
#include "../sources/Cryptor.hpp"

int main(int argc, char const *argv[]) {

    Cryptor* crp = new Cryptor;

    crp->setPassword("azerty");

    crp->setClear("test.txt");
    crp->setEncrypted("test.txt.enc");
    crp->encrypt();

    crp->setClear("testDecode.txt");
    crp->decrypt();

    delete crp;

    return EXIT_SUCCESS;
}