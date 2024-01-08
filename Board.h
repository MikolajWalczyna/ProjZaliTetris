#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "Tetrimino.h"
#include "RevControlTetrimino.h"

class Board {
public:
    Board(); // Konstruktor, inicjalizuje planszê.

    ~Board();

    // Funkcje do zarz¹dzania plansz¹
    void clear(); // Wyczyszczenie planszy
    bool isCollision(const Tetrimino& tetrimino, int offsetX, int offsetY) const; // Sprawdzenie kolizji z klockiem
    bool isCollisionAfterRotation(const Tetrimino& tetrimino) const;
    void rotateTetrimino(Tetrimino& tetrimino);
    void placeTetrimino(const Tetrimino& tetrimino); // Umieszczenie klocka na planszy

    // Funkcje do dostêpu do planszy
    const std::vector<std::vector<int>>& getGrid() const;
    bool moveTetriminoDown(Tetrimino& tetrimino);
    bool moveTetriminoLeft(Tetrimino& tetrimino);
    bool moveTetriminoRight(Tetrimino& tetrimino);
    bool checkLossCondition() const;


private:
    // Rozmiary planszy
    static const int boardWidth = 10;
    static const int boardHeight = 20;

    // Plansza gry
    std::vector<std::vector<int>> grid;

    // Prywatna funkcja do sprawdzania czy linia jest pe³na
    bool isLineFull(int row) const;
    // W pliku Board.cpp


    void removeFullLines();
    void removeLine(int row);
    void moveLinesDown(int startRow);
 
};

#endif 

