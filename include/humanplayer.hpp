#pragma once

#include "initstate.hpp"
#include "player.hpp"


class HumanPlayer : public Player {
    InitState initState;

public:
    HumanPlayer(std::string n, Field &yourfield, std::vector<unsigned> shipz)
            : Player(n, yourfield), initState(yourfield, shipz) {}

    int make_move(float x, float y, Field &) override;

    bool init(float x, float y) override;

    ~HumanPlayer() override = default;
};