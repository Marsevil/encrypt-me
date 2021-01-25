//
// Created by marsevil on 25/01/2021.
//

#ifndef LYOKO_CRYPTMAN_HPP
#define LYOKO_CRYPTMAN_HPP

#include "Applyer.hpp"

class CryptMan : public Applyer {
    /**
     * Password which will be used to encrypt file.
     */
    std::string password;

    void encrypt() const;
    void decrypt() const;

public:
    CryptMan(std::string _password = "");
    ~CryptMan() = default;

    inline void setPassword(std::string const& _password) { password = _password; }
    inline std::string getPassword() { return password; }

    /**
     * @inherit
     */
    virtual void apply(Process process) const;
};


#endif //LYOKO_CRYPTMAN_HPP
