#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "field.hpp"


Field::Field(float p) {
    for (int i = 0; i < fields.size(); ++i) {
        fields[i].rectangle.setPosition(i % 10 * 51 + p, i / 10 * 51);
        fields[i].rectangle.setFillColor(sf::Color(sf::Color::White));
    }
    if (!font.loadFromFile("./fonts/lunchds.ttf")) {
        throw std::runtime_error("cannot load font");
    }

    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(0 + p, 600);
}

void Field::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &field : fields) {
        target.draw(field.rectangle);
    }
    target.draw(text);
}

void Field::set_com(const std::string &communicate) {
    if (!communicate.empty()) {
        text.setString(communicate);
    }
}

bool Field::operator==(const Field &f) {
    for (int i = 0; i < fields.size(); ++i) {
        if (fields[i].st != f.fields[i].st) {
            return false;
        }
    }
    return true;
}

bool Field::is_game_end() const {
    for (const auto &field : fields) {
        if (field.st == State::ship) {
            return false;
        }
    }
    return true;
}

bool Field::is_ship_destroyed(unsigned x, unsigned y, CheckDirection dir) {
    if (dir == ALL && at(x, y).st == State::missed) {
        return false;
    }
    if (at(x, y).st == State::ship) {
        return false;
    }
    if (dir == ALL) {
        bool isDestroyed = true;
        if (x != 0) {
            isDestroyed &= is_ship_destroyed(x - 1, y, LEFT);
        }
        if (x != 9) {
            isDestroyed &= is_ship_destroyed(x + 1, y, RIGHT);
        }
        if (y != 0) {
            isDestroyed &= is_ship_destroyed(x, y - 1, UP);
        }
        if (y != 9) {
            isDestroyed &= is_ship_destroyed(x, y + 1, DOWN);
        }
        return isDestroyed;
    }
    if (at(x, y).st == State::destroyed) {
        if (dir == LEFT && x != 0) {
            return is_ship_destroyed(x - 1, y, LEFT);
        }
        if (dir == RIGHT && x != 9) {
            return is_ship_destroyed(x + 1, y, RIGHT);
        }
        if (dir == UP && y != 0) {
            return is_ship_destroyed(x, y - 1, UP);
        }
        if (dir == DOWN && y != 9) {
            return is_ship_destroyed(x, y + 1, DOWN);
        }
    }
    return true;
}
