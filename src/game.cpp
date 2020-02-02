#include <SFML/Graphics.hpp>

#include "game.hpp"


std::string stateToStr(GameState gs);

void Game::start_game() {
    window.setFramerateLimit(30);
    bool p2init = true;
    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    switch (state) {
                        case GameState::start:
                            state = GameState::pick_mode;
                            break;
                        case GameState::pick_mode:
                            text.setString(p1->getName() + "'s TURN");
                            if (is_pvp.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                state = GameState::p1init;
                                pvp = true;
                                p2 = new HumanPlayer("Player2", f2, ships);
                            }
                            if (is_pvc.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                state = GameState::p1init;
                                pvp = false;
                                p2 = new ComputerPlayer(f2, ships);
                            }
                            break;
                        case GameState::p1init:
                            if (p1->init(event.mouseButton.x, event.mouseButton.y)) {
                                state = GameState::change_to_p2;
                                if (pvp) {
                                    text.setString(
                                            p2->getName() +
                                            ", YOUR TURN \n CLICK IF READY");
                                } else {
                                    text.setString(p2->getName() + "'s TURN");
                                }
                            }
                            break;
                        case GameState::change_to_p2:
                            if (p2init) {
                                p2init = false;
                                if (pvp) {
                                    text.setString(p2->getName() + "'s TURN");
                                    state = GameState::p2init;
                                } else {
                                    p2->init(1.0, 2.0);
                                    state = GameState::change_to_p1;
                                    text.setString(p2->getName() +
                                                   " HAS MADE ITS MOVE \n CLICK IF READY");
                                }
                            } else {
                                if (!pvp) {
                                    p2->make_move(event.mouseButton.x, event.mouseButton.y, f1);
                                    state = GameState::change_to_p1;
                                    text.setString(p1->getName() + ", YOUR TURN \n CLICK IF READY");
                                    if (f1.is_game_end()) {
                                        state = GameState::p2win;
                                        text.setString(p2->getName() + " WON! \n CONGRATULATIONS");
                                    }
                                } else {
                                    f2.set_com("Your fields");
                                    p2->opponents.set_com("Pick the attack target!");
                                    state = GameState::p2turn;
                                }
                            }
                            break;
                        case GameState::p2init:
                            if (p2->init(event.mouseButton.x, event.mouseButton.y)) {
                                state = GameState::change_to_p1;
                                if (pvp) {
                                    text.setString(p1->getName() + ", YOUR TURN \n CLICK IF READY");
                                }
                            }
                            break;
                        case GameState::change_to_p1:
                            state = GameState::p1turn;
                            text.setString(p1->getName() + "'s TURN");
                            f1.set_com("Your fields");
                            p1->opponents.set_com("Pick the attack target!");
                            break;
                        case GameState::p1turn: {
                            int hit = p1->make_move(event.mouseButton.x, event.mouseButton.y, f2);
                            if (hit > -1) {
                                state = GameState::p1result;
                                if (f2.is_ship_destroyed(hit % 10, hit / 10)) {
                                    p1->opponents.set_com("SHIP DESTROYED!");
                                }
                                if (f2.is_game_end() && !p2init) {
                                    state = GameState::p1win;
                                    text.setString(p1->getName() + " WON! \n CONGRATULATIONS");
                                }
                            }
                        }
                            break;
                        case GameState::p1result:
                            state = GameState::change_to_p2;
                            if (pvp) {
                                text.setString(p2->getName() + ", YOUR TURN \n CLICK IF READY");
                            } else {
                                text.setString(p2->getName() +
                                               " HAS MADE ITS MOVE \n CLICK IF READY");
                            }
                            break;
                        case GameState::p2turn: {
                            int hit = p2->make_move(event.mouseButton.x, event.mouseButton.y, f1);
                            if (hit > -1) {
                                state = GameState::p2result;
                                if (f1.is_ship_destroyed(hit % 10, hit / 10)) {
                                    p2->opponents.set_com("SHIP DESTROYED!");
                                }
                                if (f1.is_game_end()) {
                                    state = GameState::p2win;
                                    text.setString(p2->getName() + " WON! \n CONGRATULATIONS");
                                }
                            }
                            break;
                        }
                        case GameState::p2result:
                            state = GameState::change_to_p1;
                            if (pvp) {
                                text.setString(p1->getName() + ", YOUR TURN \n CLICK IF READY");
                            } else {
                                text.setString(p2->getName() +
                                               " HAS MADE ITS MOVE \n CLICK IF READY");
                            }
                            break;
                        case GameState::p1win:
                            //window.close();
                            break;
                        case GameState::p2win:
                            //window.close();
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        window.clear();
        switch (state) {
            case GameState::start:
                window.draw(text);
                break;
            case GameState::pick_mode:
                window.draw(mode_question);
                window.draw(is_pvp);
                window.draw(is_pvc);
                window.draw(is_pvp_text);
                window.draw(is_pvc_text);
                break;
            case GameState::p1init:
                window.draw(f1);
                window.draw(text);
                break;
            case GameState::change_to_p2:
                window.draw(text);
                break;
            case GameState::p2init:
                if (pvp) {
                    window.draw(f2);
                }
                window.draw(text);
                break;
            case GameState::change_to_p1:
                window.draw(text);
                break;
            case GameState::p1turn:
                window.draw(f1);
                window.draw(p1->opponents);
                break;
            case GameState::p1result:
                window.draw(f1);
                window.draw(p1->opponents);
                break;
            case GameState::p2turn:
                if (pvp) {
                    window.draw(f2);
                    window.draw(p2->opponents);
                } else {
                    window.draw(text);
                }
                break;
            case GameState::p2result:
                if (pvp) {
                    window.draw(f2);
                    window.draw(p2->opponents);
                } else {
                    window.draw(text);
                }
                break;
            case GameState::p1win:
                window.draw(text);
                window.draw(win_sprite);
                break;
            case GameState::p2win:
                window.draw(text);
                window.draw(win_sprite);
                break;
        }

        window.display();
    }
}

std::string stateToStr(GameState gs) {
    switch (gs) {
        case GameState::start:
            return "start";
        case GameState::p1init:
            return "p1init";
        case GameState::change_to_p2:
            return "change_to_p2";
        case GameState::p2init:
            return "p2init";
        case GameState::change_to_p1:
            return "change_to_p1";
        case GameState::p1turn:
            return "p1turn";
        case GameState::p1result:
            return "p1result";
        case GameState::p2turn:
            return "p2turn";
        case GameState::p2result:
            return "p2result";
        case GameState::p1win:
            return "p1win";
        case GameState::p2win:
            return "p2win";
        case GameState::pick_mode:
            return "pick_mode";
        default:
            return "unknown state";
    }
}
