//
// Created by marsevil on 11/11/2020.
//

#ifndef ENCRYPT_ME_CONFIGREADER_HPP
#define ENCRYPT_ME_CONFIGREADER_HPP

#include <filesystem>
#include <string>
#include <memory>
#include <fstream>
#include <map>
#include <istream>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <iostream>

namespace sf = std::filesystem;

/**
 * Represent memory projection of configuration.
 */
struct Config {
    sf::path UNCRYPTED_FOLDER;
    sf::path ENCRYPTED_FOLDER;
    std::string PASSWORD;
};

/**
 * This class read a config file to fill the Config structure.
 */
class ConfigReader {
    /**
     * Constant path to the $HOME/encrypt-me_config.env.
     */
    static const sf::path CONFIG_FILE;
    /**
     * Current configuration.
     */
    static std::unique_ptr<Config> config;

    /**
     * Suppress all space char in the string.
     * @param str can be empty.
     */
    static void formatString(std::string& str);
    /**
     * Change all char to lower case.
     * @param str
     */
    static void lowerString(std::string& str);

public:
    /**
     * Read the config file to fill config.
     */
    static void readConfig();

    /**
     * @return can be not relevant if call before readConfig function.
     */
    inline static std::unique_ptr<Config> const& getConfig() { return config; }
};


#endif //ENCRYPT_ME_CONFIGREADER_HPP
