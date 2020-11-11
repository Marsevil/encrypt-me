//
// Created by marsevil on 11/11/2020.
//

#include "ConfigReader.hpp"

const sf::path ConfigReader::CONFIG_FILE(std::getenv("HOME") + std::string("/encrypt-me_config.env"));
std::unique_ptr<Config> ConfigReader::config(new Config);

void ConfigReader::readConfig() {
    std::ifstream configFile(CONFIG_FILE);
    std::map<std::string, std::string> parsedLine;

    for (std::string line; configFile; std::getline(configFile, line)) {
        std::istringstream iline(line);
        std::string key, value;

        if (std::getline(iline, key, '=') && std::getline(iline, value)) {
            cleanString(key);
            cleanString(value);
            parsedLine.insert_or_assign(key, value);
        }
    }

    config->UNCRYPTED_FOLDER = parsedLine.at("UNCRYPTED_FOLDER");
    config->ENCRYPTED_FOLDER = parsedLine.at("ENCRYPTED_FOLDER");
    config->PASSWORD = parsedLine.at("PASSWORD");
}

void ConfigReader::cleanString(std::string &str) {
    std::string::const_iterator it = str.begin();
    while (it != str.end()) {
        if (*it == ' ') str.erase(it);
        else ++it;
    }
}
