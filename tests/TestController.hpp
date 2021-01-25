//
// Created by marsevil on 10/01/2021.
//

#ifndef LYOKO_TESTCONTROLLER_HPP
#define LYOKO_TESTCONTROLLER_HPP

#include <iostream>

#include "../includes/lib_encrypt-me/sources/Controller.hpp"

void testDiffFunction() {
    Controller* ctrl = new Controller("testTree", "testTreeDiff", "azerty");

    std::vector<Tuple> vect(ctrl->diff());

    for (Tuple const& tuple : vect) {
        std::cout << '{' << std::endl;
        std::cout << "source path : " << tuple.source << std::endl;
        std::cout << "destination path : " << tuple.destination << std::endl;
        std::cout << "action : ";
        switch(tuple.toDo) {
            case Tuple::Action::CREATE:
                std::cout << "CREATE";
                break;
            case Tuple::Action::DELETE:
                std::cout << "DELETE";
                break;
            case Tuple::Action::UPDATE:
                std::cout << "UPDATE";
                break;
            default:
                std::cout << "Undifined";
        }
        std::cout << std::endl;
        std::cout << '}' << std::endl;
    }

    delete ctrl;
}

void testApplyFunctionEncrypt() {
    Controller* ctrl = new Controller("testTree", "testTreeEncrypt", "azerty");

    std::vector<Tuple> diffList(ctrl->diff(true));
    ctrl->apply(diffList, Applyer::Process::ENCRYPT);

    delete ctrl;
}

#endif //LYOKO_TESTCONTROLLER_HPP
