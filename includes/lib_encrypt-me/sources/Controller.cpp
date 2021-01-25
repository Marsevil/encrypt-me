//
// Created by marsevil on 10/01/2021.
//

#include "Controller.hpp"

Controller::Controller(View* _view, sf::path const& _source, sf::path const& _destination, std::string const& _password)
: view(_view), source(_source), destination(_destination), password(_password) {
    // Nothing to do here.
}

std::vector<Tuple> Controller::diff(bool encExtension) const {
    std::vector<Tuple> diffList(checkConfig(encExtension));

    diff(encExtension, source, destination, diffList);

    return diffList;
}

void Controller::diff(bool encExtension, sf::path const& sourceDirectory, sf::path const& destinationDirectory, std::vector<Tuple>& diffList) {

    for (sf::path const& sourcePath : sf::directory_iterator(sourceDirectory)) {

        sf::path destinationPath(destinationDirectory / sourcePath.filename());
        bool isDirectory(sf::is_directory(sourcePath));

        if (isDirectory) {
            // If sourcePath is a directory
            if (!sf::exists(destinationPath)) diffList.push_back({
                sourcePath,
                destinationPath,
                Tuple::Action::CREATE_DIR
            });
            else if (sf::last_write_time(sourcePath) > sf::last_write_time(destinationPath)) {
                for (sf::path const& path : sf::directory_iterator(destinationPath)) {
                    sf::path hypotheticalSourcePath(sourcePath / path.filename());
                    if (encExtension) {
                        if (hypotheticalSourcePath.extension() == ".enc") hypotheticalSourcePath.replace_extension("");
                        else hypotheticalSourcePath += ".enc";
                    }
                    if (!exists(hypotheticalSourcePath)) diffList.push_back({
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

            if (!sf::exists(destinationPath)) diffList.push_back({
                sourcePath,
                destinationPath,
                Tuple::Action::CREATE
            });
            else if (sf::last_write_time(sourcePath) > sf::last_write_time(destinationPath)) diffList.push_back({
                sourcePath,
                destinationPath,
                Tuple::Action::UPDATE
            });
        }
    }

}

std::vector<Tuple> Controller::checkConfig(bool isCryptography) const {
    std::vector<Tuple> ret;

    if (!sf::exists(source)) throw std::runtime_error("Source doesn't exists.");
    else if (!sf::is_directory(source)) throw std::runtime_error("Source should be a directory.");
    if (!sf::exists(destination)) ret.push_back({
        source,
        destination,
        Tuple::Action::CREATE_DIR
    });

    if (isCryptography && password.empty()) throw std::runtime_error("Password should not be empty.");

    return ret;
}

Applyer* Controller::getApplyer(const Applyer::Process &process) const {
    if (process == Applyer::Process::ENCRYPT || process == Applyer::Process::DECRYPT) {
        return new CryptMan(password);
    } else if (process == Applyer::Process::COPY) {
        throw std::runtime_error("Copy function not implemented yet.");
    } else {
        throw std::domain_error("Process not supported.");
    }
}

void Controller::apply(std::vector<Tuple> const& diffList, Applyer::Process process) const {
    Applyer* applyer = getApplyer(process);

    // Apply modifications.
    for (Tuple const& tuple : diffList) {
        view->printTask(tuple);

        if (tuple.toDo == Tuple::Action::CREATE_DIR) sf::create_directories(tuple.destination);
        else if (tuple.toDo == Tuple::Action::CREATE || tuple.toDo == Tuple::Action::UPDATE) {
            applyer->setSource(tuple.source);
            applyer->setDestination(tuple.destination);
            applyer->apply(process);
        } else if (tuple.toDo == Tuple::DELETE) sf::remove_all(tuple.destination);

        view->printDone();
    }

    // Copy last modified time.
    for (Tuple const& tuple : diffList) {
        if (tuple.toDo != Tuple::DELETE && tuple.source.lexically_relative(source).has_parent_path())
            sf::last_write_time(tuple.destination.parent_path(), sf::last_write_time(tuple.source.parent_path()));
    }

    delete applyer;
}

void Controller::run() {
    setSource(view->getSource());
    setDestination(view->getDestination());

    Applyer::Process process(view->getProcess());
    Action action(view->getAction());

    bool isCryptography = (process == Applyer::DECRYPT || process == Applyer::ENCRYPT);
    if (isCryptography) setPassword(view->getPassword());
    std::vector<Tuple> diffs(diff(isCryptography));

    if (action == Action::APPLY && view->confirmDiff(diffs)) apply(diffs, process);
    else if (action == Action::SHOW) view->printDiff(diffs);
}