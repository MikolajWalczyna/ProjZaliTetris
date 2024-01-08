// TetriminoTypes.cpp
#include "TetriminoTypes.h"

IBlock::IBlock() {
    // Ustaw kszta�t klocka I
    setShape({ {0, 0}, {1, 0}, {2, 0}, {3, 0} });
}

JBlock::JBlock() {
    // Ustaw kszta�t klocka J
    setShape({ {0, 0}, {0, 1}, {0, 2}, {1, 2} });
}

LBlock::LBlock() {
    // Ustaw kszta�t klocka L
    setShape({ {0, 2}, {1, 2}, {2, 2}, {2, 1} });
}

OBlock::OBlock() {
    // Ustaw kszta�t klocka O
    setShape({ {0, 0}, {0, 1}, {1, 0}, {1, 1} });
}

SBlock::SBlock() {
    // Ustaw kszta�t klocka S
    setShape({ {1, 0}, {2, 0}, {0, 1}, {1, 1} });
}

TBlock::TBlock() {
    // Ustaw kszta�t klocka T
    setShape({ {1, 0}, {0, 1}, {1, 1}, {2, 1} });
}

ZBlock::ZBlock() {
    // Ustaw kszta�t klocka Z
    setShape({ {0, 0}, {1, 0}, {1, 1}, {2, 1} });
}