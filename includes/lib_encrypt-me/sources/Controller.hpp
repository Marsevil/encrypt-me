//
// Created by marsevil on 10/01/2021.
//

#ifndef LYOKO_CONTROLLER_HPP
#define LYOKO_CONTROLLER_HPP

#include <vector>
#include <stdexcept>

#include "Tuple.hpp"

class Controller {
    sf::path source;
    sf::path destination;
    std::string password;

public:
    Controller(sf::path const& _source, sf::path const& _destination, std::string const& _password);

    inline sf::path const& getSource() const { return source; }
    inline void setSource(sf::path const& _source) { source = _source; }

    inline sf::path const& getDestination() const { return destination; }
    inline void setDestination(sf::path const& _destination) { destination = _destination; }

    /**
     * @return List of tuples that represent all differences and all required action.
     */
    std::vector<Tuple> diff(bool encExtension = false) const;
    static void diff(bool encExtension, sf::path const& sourceDirectory, sf::path const& destinationDirectory, std::vector<Tuple>& diffList);

    std::vector<Tuple> checkConfig() const;
};


#endif //LYOKO_CONTROLLER_HPP
