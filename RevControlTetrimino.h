#ifndef REV_CONTROL_TETRIMINO_H
#define REV_CONTROL_TETRIMINO_H

#include "Tetrimino.h"

class RevControlTetrimino : public Tetrimino {
public:
    RevControlTetrimino();
    sf::Color getColor() const;
    void moveLeft() override;
    void moveRight() override;
};

#endif 
