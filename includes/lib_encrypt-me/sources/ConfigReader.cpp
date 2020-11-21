//
// Created by marsevil on 11/11/2020.
//

#include "ConfigReader.hpp"

const sf::path ConfigReader::CONFIG_FILE(std::getenv("HOME") + std::string("/encrypt-me_config.env"));
std::shared_ptr<Config> ConfigReader::config(new Config);

void ConfigReader::readConfig() {
    if (!sf::exists(ConfigReader::CONFIG_FILE)) throw std::runtime_error(ConfigReader::CONFIG_FILE.string() + " doesn't exist");
    
    std::ifstream configFile(CONFIG_FILE);
    std::map<std::string, std::string> parsedLine;

    for (std::string line; configFile; std::getline(configFile, line)) {
        std::istringstream iline(line);
        std::string key, value;

        if (std::getline(iline, key, '=') && std::getline(iline, value)) {
            formatString(key);
            lowerString(key);
            formatString(value);

            if (value.empty()) throw std::runtime_error(key + " value should not be empty.");
            parsedLine.insert_or_assign(key, value);
        }
    }

    try {
        config->UNCRYPTED_FOLDER = parsedLine.at("uncrypted_folder");
    } catch(std::out_of_range& e) {
        throw std::runtime_error("UNCRYPTED_FOLDER property is not defined.");
    }

    try {
        config->ENCRYPTED_FOLDER = parsedLine.at("encrypted_folder");
    } catch(std::out_of_range& e) {
        throw std::runtime_error("ENCRYPTED_FOLDER property is not defined.");
    }

    try {
        config->PASSWORD = parsedLine.at("password");
    } catch (std::out_of_range& e) {
        throw std::runtime_error("PASSWORD property is not defined.");
    }
}

void ConfigReader::formatString(std::string &str) {

    // Delete space before words.
    for (std::string::const_iterator it = str.begin(); *it == ' '; ) str.erase(it);

    // Delete space after words.
    while (*str.rbegin() == ' ') str.pop_back();
}

void ConfigReader::lowerString(std::string &str) {
    for (char& c : str) {
        c = (char)std::tolower(c);
    }
}
