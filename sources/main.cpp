#include <iostream>
#include "Crypter.hpp"

int main(int argc, char const *argv[]) {
    
    Crypter* crp = new Crypter;

    crp->setPassword("azerty");

    crp->setClear("test.txt");
    crp->setEncrypted("test.txt.enc");
    crp->encrypt();

    crp->setClear("testDecode.txt");
    crp->decrypt();

    delete crp;

    return EXIT_SUCCESS;
}
