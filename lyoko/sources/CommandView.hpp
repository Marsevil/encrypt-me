//
// Created by marsevil on 25/01/2021.
//

#ifndef LYOKO_COMMANDVIEW_HPP
#define LYOKO_COMMANDVIEW_HPP

#include <filesystem>
#include <memory>
#include <iostream>

#include "../../includes/lib_encrypt-me/sources/View.hpp"
#include "ConfigReader.hpp"

namespace sf = std::filesystem;

class CommandView : public View {
    bool verbose;
    bool askConfirm;
    Applyer::Process process;
    Action action;

public:
    CommandView() = delete;
    CommandView(size_t argc, const char** argv);

    sf::path getDestination() override;
    sf::path getSource() override;
    std::string getPassword() override;
    Applyer::Process getProcess() override;
    Action getAction() override;

    void printDiff(std::vector<Tuple> const& tuples) override;
    void printTask(const Tuple &task) override;
    bool confirmDiff(const std::vector<Tuple> &tuples) override;
    void printDone() override;
};


#endif //LYOKO_COMMANDVIEW_HPP
