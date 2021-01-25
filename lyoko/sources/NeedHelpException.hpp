//
// Created by marsevil on 25/01/2021.
//

#ifndef LYOKO_NEEDHELPEXCEPTION_HPP
#define LYOKO_NEEDHELPEXCEPTION_HPP

#include <stdexcept>

class NeedHelpException : public std::runtime_error {
public:
    explicit NeedHelpException(std::string _what = "") : std::runtime_error(_what) {
        // Nothing to do.
    }
};


#endif //LYOKO_NEEDHELPEXCEPTION_HPP
