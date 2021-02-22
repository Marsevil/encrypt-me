#include <iostream>
#include <string>
#include <memory>

#include "NeedHelpException.hpp"
#include "../../includes/lib_encrypt-me/sources/Controller.hpp"
#include "CommandView.hpp"

void printHelp() {
    std::cout << "usage : lyoko [<option>] [diff] <command>" << std::endl
        << std::endl << "push\t Copy unencrypted directory to encrypted directory by encrypting all files." << std::endl
        << "pull\t Copy encrypted directory to unencrypted directory by decrypting all files." << std::endl
        << "help\t Print help (this page)." << std::endl
        << "diff\t show changes without apply them." << std::endl
        << "-v or --verbose\t show which change is applying." << std::endl
        << "--ask-confirm\t show changes before apply them." << std::endl
        << std::endl << "v1.1.0" << std::endl;
}

int main(int argc, char const **argv) {
    if (argc > 4) {
        std::cout << "Only one argument is expected." << std::endl << std::endl;
        printHelp();
    }
    else if (argc < 2) {
        std::cout << "One argument is expected." << std::endl << std::endl;
        printHelp();
    }
    else {
        std::string param(argv[1]);

        if (param == "help" || param == "--help" || param == "-h") printHelp();
        else {
            try {
                auto* ctrl = new Controller(new CommandView(argc, argv));

                ctrl->run();

                delete ctrl;
            } catch (NeedHelpException const& e) {
                std::cout << e.what() << std::endl;
                printHelp();
            }
        }
    }

    return EXIT_SUCCESS;
}
