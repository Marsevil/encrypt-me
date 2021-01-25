//
// Created by marsevil on 25/01/2021.
//

#ifndef LYOKO_APPLYER_HPP
#define LYOKO_APPLYER_HPP

#include <filesystem>

namespace sf = std::filesystem;

class Applyer {

    /**
     * Source file.
     */
    sf::path source;
    /**
     * Destination file.
     */
    sf::path destination;

public:

    virtual ~Applyer() = default;

    /**
     * Define process which will be applied.
     */
    enum Process {
        ENCRYPT,
        DECRYPT,
        COPY
    };

    inline void setSource(sf::path const& _source) { source = _source; }
    inline sf::path getSource() const { return source; }

    inline void setDestination(sf::path const& _destination) { destination = _destination; }
    inline sf::path getDestination() const { return destination; }

    /**
     * Function that apply chosen process.
     * @param process chosen by user.
     * @throws invalid_argument exception if passed process isn't supported.
     */
    virtual void apply(Process process) const = 0;
};


#endif //LYOKO_APPLYER_HPP
