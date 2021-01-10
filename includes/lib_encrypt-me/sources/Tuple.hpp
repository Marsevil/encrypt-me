//
// Created by marsevil on 10/01/2021.
//

#ifndef LYOKO_TUPLE_HPP
#define LYOKO_TUPLE_HPP

#include <filesystem>

namespace sf = std::filesystem;

struct Tuple {

    enum Action {
        UPDATE,
        DELETE,
        CREATE
    };

    sf::path source;
    sf::path destination;
    Action toDo;
};


#endif //LYOKO_TUPLE_HPP
