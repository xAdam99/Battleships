#pragma once

#include "player.hpp"


class ComputerPlayer : public Player {
    std::vector<unsigned> ships;
    int last_hit;

public:
    explicit ComputerPlayer(Field &yourfield, std::vector<unsigned> shipz)
            : Player("Computer", yourfield), ships(shipz) {}

    int make_move(float x, float y, Field &) override;

    bool init(float x, float y) override;

    ~ComputerPlayer() override = default;
};