//
// Created by marsevil on 10/01/2021.
//

#include "Controller.hpp"

Controller::Controller(sf::path const& _source, sf::path const& _destination, std::string const& _password)
: source(_source), destination(_destination), password(_password) {
    // Nothing to do here.
}

std::vector<Tuple> Controller::diff(bool encExtension, sf::path const& newSource) const {

    std::vector<Tuple> retValue;
    sf::path source(newSource);

    if (newSource.empty()) {
        retValue = checkConfig();
        source = getSource();
    }

    for (sf::path const& sourcePath : sf::directory_iterator(source)) {

        sf::path destinationPath(getDestination() / sourcePath.lexically_relative(getSource()));
        bool destinationExist(sf::exists(destinationPath));

        if (!destinationExist) retValue.push_back({
            sourcePath,
            destinationPath,
            Tuple::Action::CREATE
        });
        if (sf::is_directory(sourcePath)) {
            // If sourcePath is a directory
            if (destinationExist && (sf::last_write_time(sourcePath) > sf::last_write_time(destinationPath))) {
                for (sf::path const& path : sf::directory_iterator(destinationPath)) {
                    if (!exists(sourcePath / path.filename())) retValue.push_back({
                            "",
                            path,
                            Tuple::Action::DELETE
                        });
                }
            }

            std::vector<Tuple> directoryDiff(diff(encExtension, sourcePath));
            retValue.insert(retValue.end(), directoryDiff.begin(), directoryDiff.end());
        } else {
            // If sourcePath is not a directory.
            if (encExtension) {
                if (destinationPath.extension() != ".enc") destinationPath += ".enc";
            }

            if (destinationExist && (sf::last_write_time(sourcePath) > sf::last_write_time(destinationPath))) retValue.push_back({
                    sourcePath,
                    destinationPath,
                    Tuple::Action::UPDATE
                });
        }
    }

    return retValue;
}

std::vector<Tuple> Controller::checkConfig() const {
    std::vector<Tuple> ret;

    if (!sf::exists(source)) throw std::runtime_error("Source doesn't exists.");
    else if (!sf::is_directory(source)) throw std::runtime_error("Source should be a directory.");
    if (!sf::exists(destination)) ret.push_back({
        source,
        destination,
        Tuple::Action::CREATE
    });

    return ret;
}