//
// Created by marsevil on 25/01/2021.
//

#ifndef LYOKO_VIEW_HPP
#define LYOKO_VIEW_HPP

#include <vector>

#include "Tuple.hpp"
#include "Applyer.hpp"
#include "Action.hpp"

class View {
public:
    // Required.
    virtual sf::path getSource() = 0;
    virtual sf::path getDestination() = 0;
    virtual std::string getPassword() = 0;
    virtual Applyer::Process getProcess() = 0;
    virtual Action getAction() = 0;

    // User feedback.
    virtual void printDiff(std::vector<Tuple> const& tuples) = 0;
    virtual void printTask(Tuple const& task) = 0;
    virtual bool confirmDiff(std::vector<Tuple> const & tuples) = 0;
    virtual void printDone() = 0;
};


#endif //LYOKO_VIEW_HPP
