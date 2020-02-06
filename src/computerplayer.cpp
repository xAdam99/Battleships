#include <utility>
#include <set>

#include "computerplayer.hpp"
#include "field.hpp"
#include "utils.hpp"


int ComputerPlayer::make_move(float x, float y, Field &which_to_shoot) {
    if (mode == HUNT) {
        hit_strike.clear();
        while (true) {
            int shoot = random(0, 99);
            if (which_to_shoot.at(shoot).st == State::empty) {
                which_to_shoot.at(shoot).setSt(State::missed);
                opponents.at(shoot).setSt(State::missed);
                opponents.set_com("Computer missed!");
                return shoot;
            } else if (which_to_shoot.at(shoot).st == State::ship) {
                which_to_shoot.at(shoot).setSt(State::destroyed);
                opponents.at(shoot).setSt(State::destroyed);
                opponents.set_com("Computer hits!");

                unsigned int shoot_x = shoot % 10;
                unsigned int shoot_y = shoot / 10;
                hit_strike.insert(std::pair(shoot_x, shoot_y));

                if (shoot_x > 0) {
                    const Rec &target = which_to_shoot.at(shoot_x - 1, shoot_y);
                    if (target.st != State::missed && target.st != State::destroyed) {
                        targets.push(std::pair(shoot_x - 1, shoot_y));
                    }
                }
                if (shoot_x < 9) {
                    const Rec &target = which_to_shoot.at(shoot_x + 1, shoot_y);
                    if (target.st != State::missed && target.st != State::destroyed) {
                        targets.push(std::pair(shoot_x + 1, shoot_y));
                    }
                }
                if (shoot_y > 0) {
                    const Rec &target = which_to_shoot.at(shoot_x, shoot_y - 1);
                    if (target.st != State::missed && target.st != State::destroyed) {
                        targets.push(std::pair(shoot_x, shoot_y - 1));
                    }
                }
                if (shoot_y < 9) {
                    const Rec &target = which_to_shoot.at(shoot_x, shoot_y + 1);
                    if (target.st != State::missed && target.st != State::destroyed) {
                        targets.push(std::pair(shoot_x, shoot_y + 1));
                    }
                }

                mode = TARGET;
                return shoot;
            }
        }
    } else if (mode == TARGET) {
        if (targets.empty()) {
            mode = HUNT;
            return make_move(x, y, which_to_shoot);
        }
        const std::pair<unsigned int, unsigned int> &target = targets.top();
        targets.pop();
        if (which_to_shoot.at(target.first, target.second).st == State::empty) {
            which_to_shoot.at(target.first, target.second).setSt(State::missed);
            opponents.at(target.first, target.second).setSt(State::missed);
            opponents.set_com("Computer missed!");
            return target.second * 10 + target.first;
        } else if (which_to_shoot.at(target.first, target.second).st == State::ship) {
            which_to_shoot.at(target.first, target.second).setSt(State::destroyed);
            opponents.at(target.first, target.second).setSt(State::destroyed);
            opponents.set_com("Computer hits!");
            hit_strike.insert(target);

            // new targets
            while (!targets.empty()) {
                targets.pop();
            }

            auto one = *hit_strike.cbegin();
            auto two = *(++hit_strike.cbegin());
            if (one.first == two.first) {  // x the same
                std::set<std::pair<unsigned int, unsigned int>, y_comp> sorted_hits(
                        hit_strike.cbegin(), hit_strike.cend());
                const auto &min_y = *sorted_hits.cbegin();
                const auto &max_y = *(--sorted_hits.cend());
                if (min_y.second > 0) {
                    State target_state = which_to_shoot.at(min_y.first, min_y.second - 1).st;
                    if (target_state != State::missed && target_state != State::destroyed) {
                        targets.push(std::pair(min_y.first, min_y.second - 1));
                    }
                }
                if (max_y.second < 9) {
                    State target_state = which_to_shoot.at(max_y.first, max_y.second + 1).st;
                    if (target_state != State::missed && target_state != State::destroyed) {
                        targets.push(std::pair(max_y.first, max_y.second + 1));
                    }
                }

            } else if (one.second == two.second) {  // y the same
                std::set<std::pair<unsigned int, unsigned int>, x_comp> sorted_hits(
                        hit_strike.cbegin(), hit_strike.cend());
                const auto &min_x = *sorted_hits.cbegin();
                const auto &max_x = *(--sorted_hits.cend());

                if (min_x.first > 0) {
                    State target_state = which_to_shoot.at(min_x.first - 1, min_x.second).st;
                    if (target_state != State::missed && target_state != State::destroyed) {
                        targets.push(std::pair(min_x.first - 1, min_x.second));
                    }
                }
                if (max_x.first < 9) {
                    State target_state = which_to_shoot.at(max_x.first + 1, max_x.second).st;
                    if (target_state != State::missed && target_state != State::destroyed) {
                        targets.push(std::pair(max_x.first + 1, max_x.second));
                    }
                }
            }
            return target.second * 10 + target.first;
        }
    }
    return -1;
}

bool ComputerPlayer::init(float x, float y) {
    // TODO
    if (ships.size() <= 5) {
        int ships_structure = random(0, 7);
        switch (ships_structure) {
            case 0:
                for (int i = 0; i < ships.size(); ++i) {
                    for (int j = 0; j < ships[i]; ++j) {
                        my.at(j, i * 2).setSt(State::ship);
                    }
                }
                break;
            case 1:
                for (int i = ships.size() - 1; i >= 0; --i) {
                    for (int j = 0; j < ships[i]; ++j) {
                        my.at(j, i * 2).setSt(State::ship);
                    }
                }
                break;
            case 2:
                for (int i = 0; i < ships.size(); ++i) {
                    for (int j = 0; j < ships[i]; ++j) {
                        my.at(j, 9 - i * 2).setSt(State::ship);
                    }
                }
                break;
            case 3:
                for (int i = ships.size() - 1; i >= 0; --i) {
                    for (int j = 0; j < ships[i]; ++j) {
                        my.at(j, 9 - i * 2).setSt(State::ship);
                    }
                }
                break;
            case 4:
                for (int i = 0; i < ships.size(); ++i) {
                    for (int j = 0; j < ships[i]; ++j) {
                        my.at(i * 2, j).setSt(State::ship);
                    }
                }
                break;
            case 5:
                for (int i = ships.size() - 1; i >= 0; --i) {
                    for (int j = 0; j < ships[i]; ++j) {
                        my.at(i * 2, j).setSt(State::ship);
                    }
                }
                break;
            case 6:
                for (int i = 0; i < ships.size(); ++i) {
                    for (int j = 0; j < ships[i]; ++j) {
                        my.at(9 - i * 2, j).setSt(State::ship);
                    }
                }
                break;
            case 7:
                for (int i = ships.size() - 1; i >= 0; --i) {
                    for (int j = 0; j < ships[i]; ++j) {
                        my.at(9 - i * 2, j).setSt(State::ship);
                    }
                }
                break;
        }
    } else {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < ships[i]; ++j) {
                my.at(j, i * 2).setSt(State::ship);
            }
        }
        for (int i = 0; i < ships.size() - 5; ++i) {
            for (int j = 9; j > 9 - ships[i]; --j) {
                my.at(j, i * 2).setSt(State::ship);
            }
        }
    }
    return true;
}
