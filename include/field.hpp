#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <vector>


enum class State {
    empty = 0, ship = 1, destroyed = 2, missed = 3
};

class Rec {
    State _st;

public:
    sf::RectangleShape rekt;
    const State &st = _st;

    Rec() : _st(State::empty), rekt(sf::Vector2f(50, 50)) {}

    void setSt(State newSt) {
        _st = newSt;
        switch (_st) {
            case State::empty:
                rekt.setFillColor(sf::Color::White);
                break;
            case State::ship:
                rekt.setFillColor(sf::Color(100, 100, 100));
                break;
            case State::destroyed:
                rekt.setFillColor(sf::Color::Green);
                break;
            case State::missed:
                rekt.setFillColor(sf::Color::Red);
        }
    }
};

class Field : public sf::Drawable {
    std::vector<Rec> fields{100};
    std::string com;
    sf::Font font;
    mutable sf::Text text;

protected:
    void draw(sf::RenderTarget &, sf::RenderStates) const override;

public:
    explicit Field(float p = 0);

    Field(const Field &f);

    Rec &at(unsigned int a) { return fields[a]; }

    Rec &at(unsigned x, unsigned y) {
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            throw std::invalid_argument("x or y out of range");
        }
        return fields[y * 10 + x];
    }

    void set_com(std::string communicate);

    bool is_game_end() const;

    bool operator==(const Field &f);

    enum CheckDirection {
        ALL,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    bool is_ship_destroyed(unsigned x, unsigned y, CheckDirection dir = ALL);
};