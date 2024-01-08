// TetriminoTypes.cpp
#include "TetriminoTypes.h"

IBlock::IBlock() {
    // Ustaw kszta速 klocka I
    setShape({ {0, 0}, {1, 0}, {2, 0}, {3, 0} });
}

JBlock::JBlock() {
    // Ustaw kszta速 klocka J
    setShape({ {0, 0}, {0, 1}, {0, 2}, {1, 2} });
}

LBlock::LBlock() {
    // Ustaw kszta速 klocka L
    setShape({ {0, 2}, {1, 2}, {2, 2}, {2, 1} });
}

OBlock::OBlock() {
    // Ustaw kszta速 klocka O
    setShape({ {0, 0}, {0, 1}, {1, 0}, {1, 1} });
}

SBlock::SBlock() {
    // Ustaw kszta速 klocka S
    setShape({ {1, 0}, {2, 0}, {0, 1}, {1, 1} });
}

TBlock::TBlock() {
    // Ustaw kszta速 klocka T
    setShape({ {1, 0}, {0, 1}, {1, 1}, {2, 1} });
}

ZBlock::ZBlock() {
    // Ustaw kszta速 klocka Z
    setShape({ {0, 0}, {1, 0}, {1, 1}, {2, 1} });
}