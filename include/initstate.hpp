#pragma once

#include <cmath>
#include <vector>
#include "field.hpp"


enum class InitPhase {
    FIRST_PART, LAST_PART, READY
};

class InitState {
    std::vector<unsigned> shipLengths;
    unsigned currentShip{0};
    InitPhase phase = InitPhase::FIRST_PART;
    Field &field;
    int lastX{-1};
    int lastY{-1};

    void updateText() {
        std::string com = "Pick ";
        com += phase == InitPhase::FIRST_PART ? "the beginning" : "the end";
        com += " of the ship of length " + std::to_string(shipLengths[currentShip]);
        field.set_com(com);
    }

    void updateReadyState() {
        currentShip++;
        if (currentShip >= shipLengths.size()) {
            phase = InitPhase::READY;
        }
    }

    bool checkBetween(int x1, int y1, int x2, int y2);

public:
    explicit InitState(Field &f, std::vector<unsigned> ships = {4, 1})
            : field(f), shipLengths(std::move(ships)) {
        updateText();
    }

    bool isReady() { return phase == InitPhase::READY; }

    void setShip(int x, int y);
};