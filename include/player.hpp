#pragma once

#include <string>

#include "field.hpp"


class Player {
protected:
    std::string name;
    Field &my;

public:
    Field opponents;

    Player(std::string n, Field &your_field)
            : name(std::move(n)), my(your_field), opponents(700) {}

    std::string getName() { return name; }

    virtual int make_move(float x, float y, Field &) = 0;

    virtual bool init(float x, float y) = 0;

    virtual ~Player() = default;
};
