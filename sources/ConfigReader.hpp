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

namespace sf = std::filesystem;

struct Config {
    sf::path UNCRYPTED_FOLDER;
    sf::path ENCRYPTED_FOLDER;
    std::string PASSWORD;
};

class ConfigReader {
    static const sf::path CONFIG_FILE;
    static std::unique_ptr<Config> config;
    
    static void formatString(std::string& str);
    static void lowerString(std::string& str);

public:
    static void readConfig();

    inline static std::unique_ptr<Config> const& getConfig() { return config; }
};


#endif //ENCRYPT_ME_CONFIGREADER_HPP
