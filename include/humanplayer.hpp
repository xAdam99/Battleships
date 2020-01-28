#pragma once

#include <string>
#include <vector>

#include "player.hpp"
#include "field.hpp"
#include "initstate.hpp"


class HumanPlayer : public Player {
    InitState initState;

public:
    HumanPlayer(std::string n, Field &yourfield, std::vector<unsigned> shipz)
            : Player(n, yourfield), initState(yourfield, shipz) {}

    int make_move(float x, float y, Field &) override;

    bool init(float x, float y) override;

    ~HumanPlayer() override = default;
};
