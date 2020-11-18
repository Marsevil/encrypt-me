//
// Created by marsevil on 18/11/2020.
//

#include "DirectoryCryptor.hpp"

DirectoryCryptor::DirectoryCryptor() : Cryptor() {
    // Nothing to do here.
}

void DirectoryCryptor::encrypt() const {

}

void DirectoryCryptor::checkConfig(Process process) const {
    Cryptor::checkConfig(process);

    //Check if file are directory.

}
