#pragma once

#include <iostream>
#include "../sources/FileCryptor.hpp"

void cryptorTest() {

    FileCryptor* crp = new FileCryptor;

    crp->setPassword("azerty");

    crp->setClear("test.txt");
    crp->setEncrypted("test.txt.enc");
    crp->encrypt();

    crp->setClear("testDecode.txt");
    crp->decrypt();

    delete crp;
}