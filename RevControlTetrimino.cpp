#include "RevControlTetrimino.h"

RevControlTetrimino::RevControlTetrimino() : Tetrimino() {
    RevControl = true;
}

void RevControlTetrimino::moveLeft() {
    position.x += 1;
}

void RevControlTetrimino::moveRight() {
    position.x -= 1;
}
sf::Color RevControlTetrimino::getColor() const {
    return sf::Color::Cyan;
}


