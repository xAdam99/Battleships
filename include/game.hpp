#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "computerplayer.hpp"
#include "humanplayer.hpp"
#include "player.hpp"


enum class GameState {
    start,
    pick_mode,
    initp1,
    change_to_p2,
    initp2,
    change_to_p1,
    p1turn,
    p1result,
    p2turn,
    p2result,
    p1win,
    p2win
};

class Game {
    Player *p1 = nullptr;
    Player *p2 = nullptr;
    Field f1;
    Field f2;
    sf::RenderWindow window{sf::VideoMode(1210, 700), "BATTLESHIPS"};
    GameState state;
    sf::Font font;
    sf::Texture win_image;
    sf::Sprite win_sprite;
    mutable sf::Text text;
    bool pvp;
    sf::RectangleShape ispvp;
    sf::RectangleShape ispvc;
    sf::Text mode_question;
    sf::Text ispvp_text;
    sf::Text ispvc_text;
    std::vector<unsigned> ships = {4, 3, 2, 2, 1};

public:
    Game() : state(GameState::start) {
        p1 = new HumanPlayer("Player1", f1, ships);

        if (!font.loadFromFile("./fonts/lunchds.ttf")) {
            throw std::runtime_error("cannot load font lunchds.ttf");
        }

        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition(700, 250);
        text.setString("CLICK TO START!");

        mode_question.setFont(font);
        mode_question.setCharacterSize(80);
        mode_question.setFillColor(sf::Color::White);
        mode_question.setPosition(185, 175);
        mode_question.setString("Pick the game mode!");

        ispvp_text.setFont(font);
        ispvp_text.setCharacterSize(50);
        ispvp_text.setFillColor(sf::Color::White);
        ispvp_text.setPosition(300, 350);
        ispvp_text.setString("PvP");

        ispvp.setSize(sf::Vector2<float>(80, 50));
        ispvp.setPosition(300, 350);
        ispvp.setFillColor(sf::Color::Red);

        ispvc_text.setFont(font);
        ispvc_text.setCharacterSize(50);
        ispvc_text.setFillColor(sf::Color::White);
        ispvc_text.setPosition(905, 350);
        ispvc_text.setString("PvC");

        ispvc.setSize(sf::Vector2<float>(80, 50));
        ispvc.setPosition(905, 350);
        ispvc.setFillColor(sf::Color::Red);

        if (!win_image.loadFromFile("./images/win.png")) {
            throw std::runtime_error("cannot load win.png");
        }
        win_sprite.setTexture(win_image);
    }

    void start_game();
};
