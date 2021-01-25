//
// Created by marsevil on 10/01/2021.
//

#include "Controller.hpp"

Controller::Controller(sf::path const& _source, sf::path const& _destination, std::string const& _password)
: source(_source), destination(_destination), password(_password) {
    // Nothing to do here.
}

std::vector<Tuple> Controller::diff(bool encExtension) const {
    std::vector<Tuple> diffList(checkConfig());

    diff(encExtension, source, destination, diffList);

    return diffList;
}

void Controller::diff(bool encExtension, sf::path const& sourceDirectory, sf::path const& destinationDirectory, std::vector<Tuple>& diffList) {

    for (sf::path const& sourcePath : sf::directory_iterator(sourceDirectory)) {

        sf::path destinationPath(destinationDirectory / sourcePath.filename());
        bool destinationExist(sf::exists(destinationPath));

        if (!destinationExist) diffList.push_back({
            sourcePath,
            destinationPath,
            Tuple::Action::CREATE
        });

        if (sf::is_directory(sourcePath)) {
            // If sourcePath is a directory
            if (destinationExist && (sf::last_write_time(sourcePath) > sf::last_write_time(destinationPath))) {
                for (sf::path const& path : sf::directory_iterator(destinationPath)) {
                    if (!exists(sourcePath / path.filename())) diffList.push_back({
                            "",
                            path,
                            Tuple::Action::DELETE
                        });
                }
            }

            diff(encExtension, sourcePath, destinationPath, diffList);
        } else {
            // If sourcePath is not a directory.
            if (encExtension) {
                if (sourcePath.extension() == ".enc") destinationPath.replace_extension("");
                else destinationPath += ".enc";
            }

            if (destinationExist && (sf::last_write_time(sourcePath) > sf::last_write_time(destinationPath))) diffList.push_back({
                    sourcePath,
                    destinationPath,
                    Tuple::Action::UPDATE
                });
        }
    }

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