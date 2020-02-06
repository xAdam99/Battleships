#pragma once

#include <vector>
#include <stack>
#include <utility>
#include <unordered_set>

#include "player.hpp"


class ComputerPlayer : public Player {
    enum Mode {
        HUNT, TARGET
    };
    Mode mode = HUNT;
    const std::vector<unsigned int> &ships;

    std::stack<std::pair<unsigned int, unsigned int>> targets;

    struct pair_hash {
        inline std::size_t operator()(const std::pair<int, int> &v) const {
            return v.first * 31 + v.second;
        }
    };

    struct x_comp {
        bool operator()(const std::pair<unsigned int, unsigned int> &lhs,
                        const std::pair<unsigned int, unsigned int> &rhs) const {
            return lhs.first < rhs.first;
        }
    };

    struct y_comp {
        bool operator()(const std::pair<unsigned int, unsigned int> &lhs,
                        const std::pair<unsigned int, unsigned int> &rhs) const {
            return lhs.second < rhs.second;
        }
    };

    std::unordered_set<std::pair<unsigned int, unsigned int>, pair_hash> hit_strike;

public:
    explicit ComputerPlayer(Field &your_field, const std::vector<unsigned int> &ships)
            : Player("Computer", your_field), ships(ships) {}

    int make_move(float x, float y, Field &) override;

    bool init(float x, float y) override;

    ~ComputerPlayer() override = default;
};
