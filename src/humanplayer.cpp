#include "humanplayer.hpp"
#include "field.hpp"


int HumanPlayer::make_move(float x, float y, Field &which_to_shoot) {
    for (int i = 0; i < 100; ++i) {
        auto bounds = opponents.at(i).rectangle.getGlobalBounds();
        bool is_inside = bounds.contains(x, y);
        if (!is_inside || ((opponents.at(i).st != State::empty))) {
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
    for (int i = 0; i < 100; ++i) {
        auto bounds = my.at(i).rectangle.getGlobalBounds();
        bool is_inside = bounds.contains(x, y);
        if (is_inside && (my.at(i).st == State::empty)) {
            int xi = i % 10;
            int yi = i / 10;
            init_state.setShip(xi, yi);
            return init_state.isReady();
        }
    }
    return false;
}
