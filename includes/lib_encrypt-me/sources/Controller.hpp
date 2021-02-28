//
// Created by marsevil on 10/01/2021.
//

#ifndef LYOKO_CONTROLLER_HPP
#define LYOKO_CONTROLLER_HPP

#include <vector>
#include <stdexcept>

#include "Tuple.hpp"
#include "Applyer.hpp"
#include "CryptMan.hpp"
#include "View.hpp"

class Controller {
    View* view;
    /**
     * Root directory which will be use as reference.
     */
    sf::path source;
    /**
     * Root directory which have to be sync with source.
     */
    sf::path destination;
    /**
     * Password use for encryption.
     */
    std::string password;

    /**
     * fill diffList with all differences.
     * @param encExtension Should be true if .enc extension have to be added or removed in destination.
     * @param sourceDirectory
     * @param destinationDirectory
     * @param diffList list which have to be fill.
     */
    static void diff(bool encExtension, sf::path const& sourceDirectory, sf::path const& destinationDirectory, std::vector<Tuple>& diffList);

    static void checkDirectoryContent(bool encExtension, sf::path sourcePath, sf::path destinationPath, std::vector<Tuple>& diffList);

    /**
     * Use process to instantiate the right applyer.
     * @param process action that the user want to be done.
     * @return New applyer instance.
     */
    Applyer* getApplyer(Applyer::Process const& process) const;

public:
    Controller(View* _view, sf::path const& _source = "", sf::path const& _destination = "", std::string const& _password = "");
    ~Controller();

    /**
     * @return not null.
     */
    inline sf::path const& getSource() const { return source; }
    /**
     * @param _source shouldn't be null.
     */
    inline void setSource(sf::path const& _source) { source = _source; }

    /**
     * @return not null.
     */
    inline sf::path const& getDestination() const { return destination; }
    /**
     * @param _destination should not be null.
     */
    inline void setDestination(sf::path const& _destination) { destination = _destination; }

    /**
     * @param _password should not be empty.
     */
    inline void setPassword(std::string _password) { password = _password; }

    /**
     * @param encExtension Should be true if .enc extension have to be added or removed in destination.
     * @return List of tuples that represent all differences and all required action.
     */
    std::vector<Tuple> diff(bool encExtension = false) const;

    /**
     * @throws runtime_error if the source does not exist.
     * @throws runtime_error if the source is not a directory.
     * @return an empty vector if the destination directory exist, if not a create tuple will be created.
     */
    std::vector<Tuple> checkConfig(bool isCryptography) const;

    /**
     * Apply modifications according to diffList.
     * @param diffList list of differences.
     * @param process define what we want to do.
     */
    void apply(std::vector<Tuple> const& diffList, Applyer::Process process) const;

    /**
     * Run sequence of instructions to execute chosen process.
     */
    void run();
};


#endif //LYOKO_CONTROLLER_HPP
