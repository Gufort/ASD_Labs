#ifndef GAMES_H
#define GAMES_H

#include <string>
#include <vector>
#include <sstream>

class Game {
public:
    std::vector<std::string> games;
    Game(const std::string& line) {
        char separator = ',';
        std::string item;
        std::stringstream ss(line);

        while (std::getline(ss, item, separator)) {
            games.push_back(item);
        }
    }

    std::string operator[](size_t i) const {
        return games[i];
    }
};


#endif // !GAMES_H

