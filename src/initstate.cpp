#include "initstate.hpp"


bool InitState::checkBetween(int x1, int y1, int x2, int y2) {
    if (x1 != x2 && y1 != y2) {
        return false;
    }

    if (int dist = std::abs(x1 - x2) + std::abs(y1 - y2) + 1;
            dist != shipLengths[currentShip]) {
        return false;
    }

    if (x1 == x2) { // horizontal
        int x = x1;
        int a = std::min(y1, y2);
        int b = std::max(y1, y2);
        for (int y = a + 1; y < b; y++) {
            if (x != 0 && field.at(x - 1, y).st == State::ship) {
                return false;
            }
            if (x != 9 && field.at(x + 1, y).st == State::ship) {
                return false;
            }
            if (field.at(x, y).st == State::ship) {
                return false;
            }
        }
    } else { // vertical
        int y = y1;
        int a = std::min(x1, x2);
        int b = std::max(x1, x2);
        for (int x = a + 1; x < b; x++) {
            if (y != 0 && field.at(x, y - 1).st == State::ship) {
                return false;
            }
            if (y != 9 && field.at(x, y + 1).st == State::ship) {
                return false;
            }
            if (field.at(x, y).st == State::ship) {
                return false;
            }
        }
    }
    return true;
}

void InitState::setShip(int x, int y) {
    if (isReady()) {
        throw std::logic_error("initialization has ended");
    }
    if (field.at(x, y).st == State::ship) {
        if (phase == InitPhase::LAST_PART && lastX == x && lastY == y) {
            field.at(x, y).setSt(State::empty);
            phase = InitPhase::FIRST_PART;
            lastX = -1;
            lastY = -1;
        }
        return;
    }
    if ((x != 0 && field.at(x - 1, y).st == State::ship) ||
        (x != 9 && field.at(x + 1, y).st == State::ship) ||
        (y != 0 && field.at(x, y - 1).st == State::ship) ||
        (y != 9 && field.at(x, y + 1).st == State::ship)) {
        return;
    }
    if (phase == InitPhase::FIRST_PART) {
        if (shipLengths[currentShip] == 1) {
            field.at(x, y).setSt(State::ship);
            updateReadyState();
            updateText();
            return;
        }
        lastX = x;
        lastY = y;
        phase = InitPhase::LAST_PART;
        field.at(x, y).rekt.setFillColor(sf::Color::Magenta);
        updateText();
    } else {
        if (!checkBetween(x, y, lastX, lastY)) {
            return;
        }

        int min_x = std::min(x, lastX);
        int max_x = std::max(x, lastX);
        int min_y = std::min(y, lastY);
        int max_y = std::max(y, lastY);
        for (int a = min_x; a <= max_x; a++) {
            for (int b = min_y; b <= max_y; b++) {
                field.at(a, b).setSt(State::ship);
            }
        }
        phase = InitPhase::FIRST_PART;
        updateReadyState();
        updateText();
    }
}
