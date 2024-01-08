#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"

class GameWindow {
public:
    void drawBoard(sf::RenderWindow& window, const Board& board, const Tetrimino& currentTetrimino, const Tetrimino& tempTetrimino);
    void drawTetrimino(sf::RenderWindow& window, const Tetrimino& tetrimino, float tileSize, float borderThickness, const sf::Color& borderColor, const sf::Color& fillColor);

private:
};
