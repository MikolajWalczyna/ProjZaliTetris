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
//czyœci dwuwymiarowy wektor
}
void Board::clear() {
    // Inicjalizacja planszy zerami
    grid = std::vector<std::vector<int>>(boardHeight, std::vector<int>(boardWidth, 0));//tworzy wektor dwuwymiarowy  ptóry przechowuje stan poszczególnych pól
}

bool Board::isCollision(const Tetrimino& tetrimino, int offsetX, int offsetY) const {
    const std::vector<sf::Vector2i>& shape = tetrimino.getShape();//zaciaga ksztalt klocka
    sf::Vector2i position = tetrimino.getPosition();//zaciaga pozycje klocka

    if (tetrimino.hasReversedControls()) {
        for (const auto& block : shape) {//iteruje po kazdym bloku tworzacym klocek
            int x = position.x + block.x - offsetX;//"przesuwa" kazdy blok o offset
            int y = position.y + block.y + offsetY;

            // SprawdŸ, czy blok koliduje z umieszczonymi - inna wartosc niz 0 albo wychodzi za width/height
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

            // SprawdŸ, czy blok koliduje z umieszczonymi - inna wartosc niz 0 albo wychodzi za width/height
            if (x < 0 || x >= boardWidth || y >= boardHeight || (y >= 0 && grid[y][x] != 0)) {
                return true; // Kolizja znaleziona
            }
        }
    }
    return false; // Brak kolizji
}

void Board::placeTetrimino(const Tetrimino& tetrimino) {
    // Pobierz kszta³t i pozycjê klocka
    const std::vector<sf::Vector2i>& shape = tetrimino.getShape();
    sf::Vector2i position = tetrimino.getPosition();

    // Umieœæ klocek na planszy
    for (const auto& block : shape) {
        int x = position.x + block.x;//zaczytuje "globalna" pozycje kazdego bloku tworzacego klocek3
        int y = position.y + block.y;

        // SprawdŸ, czy kafelek znajduje siê w granicach planszy
        if (x >= 0 && x < boardWidth && y >= 0 && y < boardHeight) {
            grid[y][x] = 1; // Ustaw komórkê planszy na zajêt¹
        }
    }
    removeFullLines();//usuwa pelne linie
}



const std::vector<std::vector<int>>& Board::getGrid() const {
    return grid;
}

bool Board::isLineFull(int row) const {
    // SprawdŸ, czy wiersz mieœci siê w granicach planszy
    if (row < 0 || row >= boardHeight) {
        return false; // Wiersz poza zakresem
    }

    // SprawdŸ, czy ka¿da komórka w wierszu jest zajêta
    for (int j = 0; j < boardWidth; ++j) {
        if (grid[row][j] == 0) {
            return false; // Znaleziono pust¹ komórkê
        }
    }

    return true; // Wszystkie komórki w wierszu s¹ zajête
}

bool Board::moveTetriminoDown(Tetrimino& tetrimino) {
    // SprawdŸ, czy ruch w dó³ jest mo¿liwy
    if (!isCollision(tetrimino, 0, 1)) {
        // Przesuñ klocek w dó³
        tetrimino.moveDown();
        return true;
    }
    else {
        // Umieœæ klocek na planszy
        placeTetrimino(tetrimino);
        return false;
    }
}
bool Board::moveTetriminoLeft(Tetrimino& tetrimino) {
    // SprawdŸ, czy ruch w lewo jest mo¿liwy
    if (!isCollision(tetrimino, -1, 0)) {
        // Przesuñ klocek w lewo
        tetrimino.moveLeft();
        return true;
    }
    else {
        // Umieœæ klocek na planszy
        //placeTetrimino(tetrimino);
        return false;
    }
}
bool Board::moveTetriminoRight(Tetrimino& tetrimino) {
    // SprawdŸ, czy ruch w dó³ jest mo¿liwy
    if (!isCollision(tetrimino, 1, 0)) {
        // Przesuñ klocek w dó³
        tetrimino.moveRight();
        return true;
    }
    else {
        // Umieœæ klocek na planszy

        //placeTetrimino(tetrimino);
        return false;
    }
}
bool Board::isCollisionAfterRotation(const Tetrimino& tetrimino) const {
    // Tworzymy kopiê obiektu Tetrimino do przeprowadzenia obrotu
    Tetrimino tempTetrimino = tetrimino;

    // Wykonujemy obrot tymczasowego obiektu
    tempTetrimino.rotateShape();

    // Sprawdzamy, czy obrot spowoduje kolizjê z plansz¹
    return isCollision(tempTetrimino, 0, 0);
}

void Board::rotateTetrimino(Tetrimino& tetrimino) {
    // Sprawdzamy, czy obrot nie spowoduje kolizji
    if (!isCollisionAfterRotation(tetrimino)) {
        // Jeœli nie ma kolizji, wykonujemy rzeczywisty obrot
        tetrimino.rotateShape();
    }
}
bool Board::checkLossCondition() const {
    // SprawdŸ, czy którykolwiek blok z trzech górnych rzêdów jest zajêty
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            if (grid[i][j] != 0) {
                return true; // Gra zakoñczona pora¿k¹
            }
        }
    }

    return false; // Kontynuuj grê
}
void Board::removeFullLines() {
    // PrzechodŸ od do³u do góry planszy
    for (int i = boardHeight - 1; i >= 0; --i) {
        // SprawdŸ, czy linia jest pe³na
        if (isLineFull(i)) {
            // Usuñ pe³n¹ liniê
            removeLine(i);
            // Przesuñ wszystkie linie powy¿ej tej usuniêtej w dó³
            // Ponownie sprawdŸ tê sam¹ liniê, bo siê przesunê³a w dó³
            --i;
        }
    }
}

void Board::removeLine(int row) {
    // Usuñ pe³n¹ liniê i przesuñ pozosta³e linie w dó³
    for (int i = row; i > 0; --i) {
        grid[i] = grid[i - 1];
    }
    // Ustaw pierwszy wiersz jako pusty
    grid[0] = std::vector<int>(boardWidth, 0);
}
