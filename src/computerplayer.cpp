#include "computerplayer.hpp"
#include "field.hpp"
#include "utils.hpp"


int ComputerPlayer::make_move(float x, float y, Field &which_to_shoot) {
    while (true) {
        int shoot = random(0, 99);
        if (which_to_shoot.at(shoot).st == State::empty) {
            which_to_shoot.at(shoot).setSt(State::missed);
            opponents.at(shoot).setSt(State::missed);
            opponents.set_com("Computer missed!");
            return shoot;
        }
        if (which_to_shoot.at(shoot).st == State::ship) {
            which_to_shoot.at(shoot).setSt(State::destroyed);
            opponents.at(shoot).setSt(State::destroyed);
            opponents.set_com("Computer hits!");
            return shoot;
        }
    }
}

bool ComputerPlayer::init(float x, float y) {
    // TODO
    if (ships.size() <= 5) {
        int ships_structure = random(0, 7);
        switch (ships_structure) {
            case 0:
                for (int i = 0; i < ships.size(); i += 1) {
                    for (int j = 0; j < ships[i]; j++) {
                        my.at(j, i * 2).setSt(State::ship);
                    }
                }
                break;
            case 1:
                for (int i = ships.size() - 1; i >= 0; i -= 1) {
                    for (int j = 0; j < ships[i]; j++) {
                        my.at(j, i * 2).setSt(State::ship);
                    }
                }
                break;
            case 2:
                for (int i = 0; i < ships.size(); i += 1) {
                    for (int j = 0; j < ships[i]; j++) {
                        my.at(j, 9 - i * 2).setSt(State::ship);
                    }
                }
                break;
            case 3:
                for (int i = ships.size() - 1; i >= 0; i -= 1) {
                    for (int j = 0; j < ships[i]; j++) {
                        my.at(j, 9 - i * 2).setSt(State::ship);
                    }
                }
                break;
            case 4:
                for (int i = 0; i < ships.size(); i += 1) {
                    for (int j = 0; j < ships[i]; j++) {
                        my.at(i * 2, j).setSt(State::ship);
                    }
                }
                break;
            case 5:
                for (int i = ships.size() - 1; i >= 0; i -= 1) {
                    for (int j = 0; j < ships[i]; j++) {
                        my.at(i * 2, j).setSt(State::ship);
                    }
                }
                break;
            case 6:
                for (int i = 0; i < ships.size(); i += 1) {
                    for (int j = 0; j < ships[i]; j++) {
                        my.at(9 - i * 2, j).setSt(State::ship);
                    }
                }
                break;
            case 7:
                for (int i = ships.size() - 1; i >= 0; i -= 1) {
                    for (int j = 0; j < ships[i]; j++) {
                        my.at(9 - i * 2, j).setSt(State::ship);
                    }
                }
                break;
        }
    } else {
        for (int i = 0; i < 5; i += 1) {
            for (int j = 0; j < ships[i]; j++) {
                my.at(j, i * 2).setSt(State::ship);
            }
        }
        for (int i = 0; i < ships.size() - 5; i += 1) {
            for (int j = 9; j > 9 - ships[i]; j--) {
                my.at(j, i * 2).setSt(State::ship);
            }
        }
    }
    return true;
}
