#include "TetriminoFactory.h"
#include <cstdlib> 

Tetrimino* TetriminoFactory::createTetrimino() {
    int randomValue = rand() % 5;

    if (randomValue == 0) {
        return new RevControlTetrimino();
    }
    else {       
        return new Tetrimino();
    }
}
