#include "Board.h"
#include <iostream>

Board::Board() {
    clear();//tworzy pusta plansze
}
Board::~Board() {
    for (size_t i = 0; i < grid.size(); ++i) {
        grid[i].clear();
    }
    grid.clear();
//czy�ci dwuwymiarowy wektor
}
void Board::clear() {
    // Inicjalizacja planszy zerami
    grid = std::vector<std::vector<int>>(boardHeight, std::vector<int>(boardWidth, 0));//tworzy wektor dwuwymiarowy  pt�ry przechowuje stan poszczeg�lnych p�l
}

bool Board::isCollision(const Tetrimino& tetrimino, int offsetX, int offsetY) const {
    const std::vector<sf::Vector2i>& shape = tetrimino.getShape();//zaciaga ksztalt klocka
    sf::Vector2i position = tetrimino.getPosition();//zaciaga pozycje klocka

    if (tetrimino.hasReversedControls()) {
        for (const auto& block : shape) {//iteruje po kazdym bloku tworzacym klocek
            int x = position.x + block.x - offsetX;//"przesuwa" kazdy blok o offset
            int y = position.y + block.y + offsetY;

            // Sprawd�, czy blok koliduje z umieszczonymi - inna wartosc niz 0 albo wychodzi za width/height
            if (x < 0 || x >= boardWidth || y >= boardHeight || (y >= 0 && grid[y][x] != 0)) {
                return true; // Kolizja znaleziona
            }
        }
    }
    else
    {
        for (const auto& block : shape) {//iteruje po kazdym bloku tworzacym klocek
            int x = position.x + block.x + offsetX;//"przesuwa" kazdy blok o offset
            int y = position.y + block.y + offsetY;

            // Sprawd�, czy blok koliduje z umieszczonymi - inna wartosc niz 0 albo wychodzi za width/height
            if (x < 0 || x >= boardWidth || y >= boardHeight || (y >= 0 && grid[y][x] != 0)) {
                return true; // Kolizja znaleziona
            }
        }
    }
    return false; // Brak kolizji
}

void Board::placeTetrimino(const Tetrimino& tetrimino) {
    // Pobierz kszta�t i pozycj� klocka
    const std::vector<sf::Vector2i>& shape = tetrimino.getShape();
    sf::Vector2i position = tetrimino.getPosition();

    // Umie�� klocek na planszy
    for (const auto& block : shape) {
        int x = position.x + block.x;//zaczytuje "globalna" pozycje kazdego bloku tworzacego klocek3
        int y = position.y + block.y;

        // Sprawd�, czy kafelek znajduje si� w granicach planszy
        if (x >= 0 && x < boardWidth && y >= 0 && y < boardHeight) {
            grid[y][x] = 1; // Ustaw kom�rk� planszy na zaj�t�
        }
    }
    removeFullLines();//usuwa pelne linie
}



const std::vector<std::vector<int>>& Board::getGrid() const {
    return grid;
}

bool Board::isLineFull(int row) const {
    // Sprawd�, czy wiersz mie�ci si� w granicach planszy
    if (row < 0 || row >= boardHeight) {
        return false; // Wiersz poza zakresem
    }

    // Sprawd�, czy ka�da kom�rka w wierszu jest zaj�ta
    for (int j = 0; j < boardWidth; ++j) {
        if (grid[row][j] == 0) {
            return false; // Znaleziono pust� kom�rk�
        }
    }

    return true; // Wszystkie kom�rki w wierszu s� zaj�te
}

bool Board::moveTetriminoDown(Tetrimino& tetrimino) {
    // Sprawd�, czy ruch w d� jest mo�liwy
    if (!isCollision(tetrimino, 0, 1)) {
        // Przesu� klocek w d�
        tetrimino.moveDown();
        return true;
    }
    else {
        // Umie�� klocek na planszy
        placeTetrimino(tetrimino);
        return false;
    }
}
bool Board::moveTetriminoLeft(Tetrimino& tetrimino) {
    // Sprawd�, czy ruch w lewo jest mo�liwy
    if (!isCollision(tetrimino, -1, 0)) {
        // Przesu� klocek w lewo
        tetrimino.moveLeft();
        return true;
    }
    else {
        // Umie�� klocek na planszy
        //placeTetrimino(tetrimino);
        return false;
    }
}
bool Board::moveTetriminoRight(Tetrimino& tetrimino) {
    // Sprawd�, czy ruch w d� jest mo�liwy
    if (!isCollision(tetrimino, 1, 0)) {
        // Przesu� klocek w d�
        tetrimino.moveRight();
        return true;
    }
    else {
        // Umie�� klocek na planszy

        //placeTetrimino(tetrimino);
        return false;
    }
}
bool Board::isCollisionAfterRotation(const Tetrimino& tetrimino) const {
    // Tworzymy kopi� obiektu Tetrimino do przeprowadzenia obrotu
    Tetrimino tempTetrimino = tetrimino;

    // Wykonujemy obrot tymczasowego obiektu
    tempTetrimino.rotateShape();

    // Sprawdzamy, czy obrot spowoduje kolizj� z plansz�
    return isCollision(tempTetrimino, 0, 0);
}

void Board::rotateTetrimino(Tetrimino& tetrimino) {
    // Sprawdzamy, czy obrot nie spowoduje kolizji
    if (!isCollisionAfterRotation(tetrimino)) {
        // Je�li nie ma kolizji, wykonujemy rzeczywisty obrot
        tetrimino.rotateShape();
    }
}
bool Board::checkLossCondition() const {
    // Sprawd�, czy kt�rykolwiek blok z trzech g�rnych rz�d�w jest zaj�ty
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            if (grid[i][j] != 0) {
                return true; // Gra zako�czona pora�k�
            }
        }
    }

    return false; // Kontynuuj gr�
}
void Board::removeFullLines() {
    // Przechod� od do�u do g�ry planszy
    for (int i = boardHeight - 1; i >= 0; --i) {
        // Sprawd�, czy linia jest pe�na
        if (isLineFull(i)) {
            // Usu� pe�n� lini�
            removeLine(i);
            // Przesu� wszystkie linie powy�ej tej usuni�tej w d�
            // Ponownie sprawd� t� sam� lini�, bo si� przesun�a w d�
            --i;
        }
    }
}

void Board::removeLine(int row) {
    // Usu� pe�n� lini� i przesu� pozosta�e linie w d�
    for (int i = row; i > 0; --i) {
        grid[i] = grid[i - 1];
    }
    // Ustaw pierwszy wiersz jako pusty
    grid[0] = std::vector<int>(boardWidth, 0);
}
