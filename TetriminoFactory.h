#ifndef TETRIMINO_FACTORY_H
#define TETRIMINO_FACTORY_H

#include "Tetrimino.h"
#include "RevControlTetrimino.h"

class TetriminoFactory {
public:
    Tetrimino* createTetrimino();
};

#endif 
