#pragma once

#include <string>
#include <vector>

#include "player.hpp"
#include "field.hpp"
#include "initstate.hpp"


class HumanPlayer : public Player {
    InitState init_state;

public:
    HumanPlayer(std::string n, Field &your_field, const std::vector<unsigned int> &ships)
            : Player(std::move(n), your_field), init_state(your_field, ships) {}

    int make_move(float x, float y, Field &) override;

    bool init(float x, float y) override;

    ~HumanPlayer() override = default;
};
