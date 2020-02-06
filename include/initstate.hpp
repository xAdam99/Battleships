#pragma once

#include <vector>

#include "field.hpp"


enum class InitPhase {
    FIRST_PART, LAST_PART, READY
};

class InitState {
    const std::vector<unsigned int> &ship_lengths;
    unsigned current_ship{0};
    InitPhase phase = InitPhase::FIRST_PART;
    Field &field;
    int lastX{-1};
    int lastY{-1};

    void updateText() {
        std::string com = "Pick ";
        com += phase == InitPhase::FIRST_PART ? "the beginning" : "the end";
        com += " of the ship of length " + std::to_string(ship_lengths[current_ship]);
        field.set_com(com);
    }

    void updateReadyState() {
        current_ship++;
        if (current_ship >= ship_lengths.size()) {
            phase = InitPhase::READY;
        }
    }

    bool checkBetween(int x1, int y1, int x2, int y2);

public:
    explicit InitState(Field &f, const std::vector<unsigned int> &ships)
            : field(f), ship_lengths(ships) {
        updateText();
    }

    bool isReady() { return phase == InitPhase::READY; }

    void setShip(int x, int y);
};
