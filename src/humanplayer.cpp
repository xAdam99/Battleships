#include "humanplayer.hpp"


int HumanPlayer::make_move(float x, float y, Field &which_to_shoot) {
    for (int i = 0; i < 100; i++) {
        auto bounds = opponents.at(i).rekt.getGlobalBounds();
        bool isInside = bounds.contains(x, y);
        if (!isInside || (isInside && (opponents.at(i).st != State::empty))) {
            continue;
        }
        auto &whats_there = which_to_shoot.at(i);
        if (whats_there.st == State::ship) {
            whats_there.setSt(State::destroyed);
            opponents.at(i).setSt(State::destroyed);
            opponents.set_com("You hit!");
            return i;
        }
        if (whats_there.st == State::empty) {
            whats_there.setSt(State::missed);
            opponents.at(i).setSt(State::missed);
            opponents.set_com("You miss!");
            return i;
        }
    }
    return -1;
}

bool HumanPlayer::init(float x, float y) {
    for (int i = 0; i < 100; i++) {
        auto bounds = my.at(i).rekt.getGlobalBounds();
        bool isInside = bounds.contains(x, y);
        if (isInside && (my.at(i).st == State::empty)) {
            // my.at(i).setSt(State::ship);
            int x = i % 10;
            int y = i / 10;
            initState.setShip(x, y);
            return initState.isReady();
        }
    }
}
