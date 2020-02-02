#pragma once

#include <vector>

#include "player.hpp"


class ComputerPlayer : public Player {
    const std::vector<unsigned> &ships;

public:
    explicit ComputerPlayer(Field &your_field, const std::vector<unsigned> &ships)
            : Player("Computer", your_field), ships(ships) {}

    int make_move(float x, float y, Field &) override;

    bool init(float x, float y) override;

    ~ComputerPlayer() override = default;
};
