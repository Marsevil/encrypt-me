//
// Created by marsevil on 25/01/2021.
//

#include "CommandView.hpp"
#include "NeedHelpException.hpp"

CommandView::CommandView(size_t argc, const char** argv)
: verbose(false), askConfirm(false), action(Action::APPLY) {
    bool isActionSet(false);

    for (size_t i = 1; i < argc; ++i) {
        std::string param(argv[i]);
        if (param == "-v" || param == "--verbose") verbose = true;
        else if (param == "push") {
            process = Applyer::Process::ENCRYPT;
            isActionSet = true;
        } else if (param == "pull") {
            process = Applyer::Process::DECRYPT;
            isActionSet = true;
        } else if (param == "--ask-confirm") askConfirm = true;
        else if (param == "--help") throw NeedHelpException();
        else if (param == "diff") action = Action::SHOW;
    }

    ConfigReader::readConfig();

    if (!isActionSet) throw NeedHelpException("No action set.");
}

void CommandView::printDiff(const std::vector<Tuple> &tuples) {
    std::cout << getSource() << "-->" << getDestination() << std::endl;
    if (tuples.empty()) {
        std::cout << "Nothing to do." << std::endl;
    } else {
        for (Tuple const& tuple : tuples) {
            std::cout << "--------------------" << std::endl
                      << "source path : " << tuple.source << std::endl
                      << "destination path : " << tuple.destination << std::endl
                      << "action : ";
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
                case Tuple::Action::CREATE_DIR:
                    std::cout << "CREATE DIRECTORY";
                    break;
                default:
                    std::cout << "Undifined";
            }
            std::cout << std::endl;
        }

        std::cout << "--------------------" << std::endl;
    }
}

std::string CommandView::getPassword() {
    return ConfigReader::getConfig()->PASSWORD;
}

Applyer::Process CommandView::getProcess() {
    return process;
}

sf::path CommandView::getSource() {
    if (process == Applyer::DECRYPT) return ConfigReader::getConfig()->ENCRYPTED_FOLDER;
    else return ConfigReader::getConfig()->UNCRYPTED_FOLDER;
}

sf::path CommandView::getDestination() {
    if (process == Applyer::DECRYPT) return ConfigReader::getConfig()->UNCRYPTED_FOLDER;
    else return ConfigReader::getConfig()->ENCRYPTED_FOLDER;
}

void CommandView::printTask(const Tuple &task) {
    if (verbose) {
        std::cout << task.destination << "is being";

        if (task.toDo == Tuple::DELETE) std::cout << " deleted";
        else if (task.toDo == Tuple::CREATE || task.toDo == Tuple::CREATE_DIR) std::cout << " created";
        else if (task.toDo == Tuple::UPDATE) std::cout << " updated";

        std::cout << '.' << std::endl;
    }
}

bool CommandView::confirmDiff(const std::vector<Tuple> &tuples) {
    if (askConfirm) {
        std::cout << "The following tasks will be applied :" << std::endl;

        printDiff(tuples);

        std::string userResponse;
        do {
            std::cout << "Do you accept (Y/n)";
            std::cin >> userResponse;
        } while (userResponse.empty() &&
        userResponse != "y" &&
        userResponse != "Y" &&
        userResponse != "n" &&
        userResponse != "N");

        return (userResponse == "y" || userResponse == "Y" || userResponse.empty());
    } else {
        return true;
    }
}

void CommandView::printDone() {
    std::cout << "OK." << std::endl;
}

Action CommandView::getAction() {
    return action;
}